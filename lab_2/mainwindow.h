#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

class DrawingArea;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    DrawingArea *area;
    QMenu *menu;
    QMenu *format;
    QMenu *file;
    QMenu *userHelp;
    void doMenu();
    void doAction();
    bool modificated();
    bool saveInFormat(const QByteArray &format);
    QAction *userActions;
    QList<QAction *> formatActions;
    QAction *colorActions;
    QAction *widthActions;
    QAction *printActions;
    QAction *clearActions;
    QAction *helpActions;
    QAction *QtHelpActions;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void help();
    void color();
    void width();
    void fileOpen();
    void fileSave();
};
#endif // MAINWINDOW_H
