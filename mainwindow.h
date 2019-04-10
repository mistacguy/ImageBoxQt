#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QPixmap>
#include <QLabel>
#include <hbmp24.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void showBmpInfor();
    void showImage();
    void refresh();

    void on_actionOpen_triggered();

    void on_actionInvert_triggered();

    void on_actionFlip_Horizontal_triggered();

    void on_actionFlip_Vertical_triggered();

    void on_actionGray_Scale_triggered();

signals:
    void loadSucc();
    void change();

private:
    Ui::MainWindow *ui;
    QString filename;
    hBmp24 *hbmp;
};

#endif // MAINWINDOW_H
