
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitComponents();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitComponents()
{
    this->imgIndex = 0;
    this->xDesloc = 0;
    this->yDesloc = 0;
    this->scale = 1.0;
    this->ui->imgListCB->setHidden(true);
    this->ui->zoomSL->setHidden(true);
    this->ui->xPanSL->setHidden(true);
    this->ui->yPanSL->setHidden(true);
    this->ui->zoomSL->setMaximum(200);
    this->ui->zoomSL->setMinimum(0);
    this->ui->xPanSL->setMaximum(400);
    this->ui->xPanSL->setMinimum(-400);
    this->ui->yPanSL->setMaximum(300);
    this->ui->yPanSL->setMinimum(-300);
    this->ui->imgLabel->setAlignment(Qt::AlignCenter);
}

void MainWindow::ResetParameters()
{
    this->xDesloc = 0;
    this->yDesloc = 0;
    this->scale = 1.0;
    this->ui->xPanSL->setValue(this->xDesloc);
    this->ui->yPanSL->setValue(this->yDesloc);
    this->ui->zoomSL->setValue(0);
    this->UpdateScreen();
}

void MainWindow::UpdateScreen() {
    if(this->pix.load(fileNames[this->imgIndex]))
    {
        this->pix = this->pix.scaled(this->scale*this->ui->imgLabel->size(),Qt::KeepAspectRatio);
        QPixmap displacedImage(this->pix.width(), this->pix.height());

        QPainter painter(&displacedImage);

        painter.drawPixmap(this->xDesloc, this->yDesloc, this->pix.width(), this->pix.height(), this->pix);
        painter.end();
        this->pix = displacedImage;
        this->ui->imgLabel->setPixmap(this->pix);
    }
}

void MainWindow::on_addImgBTN_clicked()
{
    QFileDialog dialog(this);
    QStringList imgListAux;
    QString value;

    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter(tr("Images (*.jpg *.jpeg)"));
    if (dialog.exec()) {
        imgListAux = dialog.selectedFiles();
        foreach (value, imgListAux) {
            if (!this->fileNames.contains(value))
            {
                this->fileNames.append(value);
                this->ui->imgListCB->addItem(value);
            }
        }
    }
    if (!fileNames.isEmpty()) {
        this->ui->imgListCB->setHidden(false);
        this->ui->zoomSL->setHidden(false);
        this->ui->xPanSL->setHidden(false);
        this->ui->yPanSL->setHidden(false);
    }
}


void MainWindow::on_imgListCB_currentIndexChanged(int index)
{
    this->imgIndex = index;
    this->ResetParameters();
    this->UpdateScreen();
}

void MainWindow::on_zoomSL_valueChanged(int value)
{
    this->scale = 1.0 + double(value/100.0);
    this->UpdateScreen();
}


void MainWindow::on_xPanSL_valueChanged(int value)
{
    this->xDesloc = value;
    this->UpdateScreen();
}


void MainWindow::on_yPanSL_valueChanged(int value)
{
    this->yDesloc = value;
    this->UpdateScreen();
}


void MainWindow::on_pushButton_clicked()
{
    this->ResetParameters();
}


void MainWindow::on_rotateSL_valueChanged(int value)
{
    if(this->pix.load(fileNames[this->imgIndex]))
    {
        this->pix = this->pix.scaled(this->ui->imgLabel->size(),Qt::KeepAspectRatio);
        QTransform transform;
        QTransform trans = transform.rotate(45);
        this->pix = this->pix.scaled(sqrt(this->pix.size().width()), sqrt(this->pix.size().height()));
        QPixmap *transPixmap = new QPixmap(this->pix.transformed(trans));
        this->ui->imgLabel->setPixmap(this->pix);
    }
}


void MainWindow::on_brightSL_valueChanged(int value)
{

}

