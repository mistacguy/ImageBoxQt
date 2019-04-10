#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    hbmp(nullptr)
{
    ui->setupUi(this);
    this->setFixedSize( this->width (),this->height ());
    connect(this,SIGNAL(loadSucc()),
            this,SLOT(showBmpInfor()));
    connect(this,SIGNAL(loadSucc()),
            this,SLOT(showImage()));
    connect(this,SIGNAL(change()),
            this,SLOT(refresh()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showBmpInfor()
{
    hbmp = new hBmp24;
    hbmp->load(filename.toStdString());
    //ui->inforlabel->setText(QString::fromStdString(hbmp->showInformation()));
    ui->inforLabel->setText(QString::fromStdString(hbmp->showInformation()));

}

void MainWindow::showImage()
{
    QImage img;
    img.load(filename);
    if((int)hbmp->infor->bmiHeader.biWidth > ui->imageLabel->width()||
       (int)hbmp->infor->bmiHeader.biHeight > ui->imageLabel->height())
    {
        ui->imageLabel->setPixmap(QPixmap::fromImage(img).scaled(ui->imageLabel->size()));
    }
    else
    {
        ui->imageLabel->setPixmap(QPixmap::fromImage(img));
    }
}

void MainWindow::refresh()
{
    QImage img;
    img.load("catch.bmp");
    if((int)hbmp->infor->bmiHeader.biWidth > ui->imageLabel->width()||
       (int)hbmp->infor->bmiHeader.biHeight > ui->imageLabel->height())
    {
        ui->imageLabel->setPixmap(QPixmap::fromImage(img).scaled(ui->imageLabel->size()));
    }
    else
    {
        ui->imageLabel->setPixmap(QPixmap::fromImage(img));
    }
}

void MainWindow::on_actionOpen_triggered()
{
    filename = QFileDialog::getOpenFileName(
                this,
                tr("选择文件"),
                "/home",
                tr("图片文件(*bmp)"));
    if(filename.isEmpty())
    {
        return;
    }
    emit loadSucc();
}

void MainWindow::on_actionInvert_triggered()
{
    if(!hbmp)
        return;
    hbmp->invert();
    hbmp->save();
    emit change();
}

void MainWindow::on_actionFlip_Horizontal_triggered()
{
    if(!hbmp)
        return;
    hbmp->flipHorizontal();
    hbmp->save();
    emit change();
}

void MainWindow::on_actionFlip_Vertical_triggered()
{
    if(!hbmp)
        return;
    hbmp->flipVertical();
    hbmp->save();
    emit change();
}

void MainWindow::on_actionGray_Scale_triggered()
{
    if(!hbmp)
        return;
    hbmp->toGrayScale();
    hbmp->save();
    emit change();
}
