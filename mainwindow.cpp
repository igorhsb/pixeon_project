
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{  
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_addImgBTN_clicked()
{
    this->fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));
    //QPixmap pix(":/img1.png");
    this->ui->imgLabel->setText(fileName);

    //this->ui->imgLabel->setStyleSheet("border-image:url(:/2.png);");
    //this->ui->imgLabel->setPixmap(pix);

    //printf(asd);

}

