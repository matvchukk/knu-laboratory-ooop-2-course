#include <QtWidgets>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "area.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    area = new DrawingArea;
    setCentralWidget(area);
    doAction();
    doMenu();
    setWindowTitle(tr("This is your drawing area! :)"));
    resize(500, 500);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (modificated())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::help()
{
    QMessageBox::about(this, tr("About App"), tr("<p>Some text hihi</p>"));
}

void MainWindow::color()
{
    QColor newColor = QColorDialog::getColor(area->penColor());

    if (newColor.isValid())
        area->setColor(newColor);
}

void MainWindow::width()
{
    bool set;
    int newWidth = QInputDialog::getInt(this, tr("Scribble"),tr("Select pen width:"),area->penWidth(), 1, 50, 1, &set);
    if (set)
        area->setWidth(newWidth);
}

void MainWindow::fileOpen()
{
    if (modificated())
    {
        QString file = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
        if (!file.isEmpty())
            area->openFile(file);
    }
}

void MainWindow::fileSave()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveInFormat(fileFormat);
}

void MainWindow::doAction()
{
    userActions = new QAction(tr("&Open..."), this);
    userActions->setShortcuts(QKeySequence::Open);
    connect(userActions, SIGNAL(triggered()), this, SLOT(open()));

    foreach (QByteArray format, QImageWriter::supportedImageFormats())
    {
            QString text = tr("%1...").arg(QString(format).toUpper());
            QAction *action = new QAction(text, this);
            action->setData(format);
            connect(action, SIGNAL(triggered()), this, SLOT(save()));
            formatActions.append(action);
    }

    printActions = new QAction(tr("&Print..."), this);
    connect(printActions, SIGNAL(triggered()), area, SLOT(print()));

    colorActions = new QAction(tr("&Pen Color..."), this);
    connect(colorActions, SIGNAL(triggered()), this, SLOT(penColor()));

    widthActions = new QAction(tr("Pen &Width..."), this);
    connect(widthActions, SIGNAL(triggered()), this, SLOT(penWidth()));

    clearActions = new QAction(tr("&Clear Screen"), this);
    clearActions->setShortcut(tr("Ctrl+L"));
    connect(clearActions, SIGNAL(triggered()), area, SLOT(clearImage()));

    exitActions = new QAction(tr("E&xit"), this);
    exitActions->setShortcuts(QKeySequence::Quit);
    connect(exitActions, SIGNAL(triggered()), this, SLOT(close()));

    helpActions = new QAction(tr("&Help"), this);
    connect(helpActions, SIGNAL(triggered()), this, SLOT(about()));

    QtHelpActions = new QAction(tr("About &Qt"), this);
    connect(QtHelpActions, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::doMenu()
{
     menuSave = new QMenu(tr("&Save As"), this);
     foreach (QAction *action, formatActions)
     menuSave->addAction(action);

     menuFile = new QMenu(tr("&File"), this);
     menuFile->addMenu(menuSave);
     menuFile->addAction(userActions);
     menuFile->addAction(printActions);
     menuFile->addAction(exitActions);
     menuFile->addSeparator();

     menuOption = new QMenu(tr("&Options"), this);
     menuOption->addAction(colorActions);
     menuOption->addAction(widthActions);
     menuOption->addAction(clearActions);
     menuOption->addSeparator();

     menuUserHelp = new QMenu(tr("&Help"), this);
     menuUserHelp->addAction(helpActions);
     menuUserHelp->addAction(QtHelpActions);

     menuBar()->addMenu(menuFile);
     menuBar()->addMenu(menuOption);
     menuBar()->addMenu(menuUserHelp);
}

bool MainWindow::modificated()
{
    if (area->pictureModified())
    {
       QMessageBox::StandardButton askAbtSaving;
       askAbtSaving = QMessageBox::warning(this, tr("Scribble"), tr("Do you want to save your changes?"), QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

       if (askAbtSaving == QMessageBox::Save)
       {
            return saveInFormat("png");
       }
       else if (askAbtSaving == QMessageBox::Cancel)
       {
            return false;
       }
    }
    return true;
}

bool MainWindow::saveInFormat(const QByteArray &fileFormat)
{
    QString path = QDir::currentPath() + "/untitled." + fileFormat;
    QString file = QFileDialog::getSaveFileName(this, tr("Save As"), path, tr("%1 Files (*.%2);;All Files (*)").arg(QString::fromLatin1(fileFormat.toUpper())).arg(QString::fromLatin1(fileFormat)));

    if (file.isEmpty()) return false;
    else {
        return area->saveFile(file, fileFormat.constData());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

