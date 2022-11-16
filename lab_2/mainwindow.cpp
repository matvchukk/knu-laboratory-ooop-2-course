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

MainWindow::~MainWindow()
{
    delete ui;
}

