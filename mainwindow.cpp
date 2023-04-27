
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{  
    ui->setupUi(this);
    this->ui->imgListCB->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_addImgBTN_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter(tr("Images (*.jpg *.jpeg)"));
    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    this->ui->imgLabel->setAlignment(Qt::AlignCenter);
    if (!fileNames.isEmpty()) {
        this->ui->imgListCB->setVisible(true);
        this->ui->imgListCB->addItems(fileNames);
    }
}


void MainWindow::on_imgListCB_currentIndexChanged(int index)
{
    if(this->pix.load(fileNames[index])) {
        this->pix = this->pix.scaled(this->ui->imgLabel->size(), Qt::KeepAspectRatio);
        this->ui->imgLabel->setPixmap(this->pix);
    }
}

