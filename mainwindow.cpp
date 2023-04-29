
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
    this->brightness = 1.0;
    this->rotateAngle = 0;
    this->ui->brightSL->setMaximum(100);
    this->ui->brightSL->setMinimum(0);
    this->ui->rotateSL->setMaximum(360);
    this->ui->rotateSL->setMinimum(0);
    this->ui->zoomSL->setMaximum(200);
    this->ui->zoomSL->setMinimum(0);
    this->ui->xPanSL->setMaximum(400);
    this->ui->xPanSL->setMinimum(-400);
    this->ui->yPanSL->setMaximum(300);
    this->ui->yPanSL->setMinimum(-300);
    this->ui->brightSL->setValue((int)(this->brightness*100));
    this->ui->xPanSL->setValue(this->xDesloc);
    this->ui->yPanSL->setValue(this->yDesloc);
    this->ui->rotateSL->setValue(this->rotateAngle);
    this->ui->zoomSL->setValue(0);
    this->ui->imgLabel->setAlignment(Qt::AlignCenter);
    this->ui->imgLabel->setStyleSheet("QLabel { background-color : gray; font: 16px; border-style: outset; border-width: 2px; border-radius: 10px; border-color: blue;}");
    this->ui->titleLBL->setAlignment(Qt::AlignCenter);
    this->ui->titleLBL->setStyleSheet("QLabel { color : blue; }");
}

void MainWindow::ResetParameters()
{
    if(!this->fileNames.empty())
    {
        this->xDesloc = 0;
        this->yDesloc = 0;
        this->scale = 1.0;
        this->brightness = 1.0;
        this->rotateAngle = 0;
        this->ui->brightSL->setValue((int)(this->brightness*100));
        this->ui->xPanSL->setValue(this->xDesloc);
        this->ui->yPanSL->setValue(this->yDesloc);
        this->ui->rotateSL->setValue(this->rotateAngle);
        this->ui->zoomSL->setValue(0);
        this->UpdateScreen();
    }
}

void MainWindow::UpdateScreen() {
    if(this->pix.load(fileNames[this->imgIndex]))
    {
        this->pix = this->pix.scaled(this->scale*this->ui->imgLabel->size());    // Aplica o zoom de acordo com o parâmetro

        QPixmap rotatedPixmap(this->pix.size());                                                    // Linhas 54-62: Aplica a rotação ao pixmap de acordo com o parâmetro
        rotatedPixmap.fill(QColor::fromRgb(0, 0, 0, 0));
        QPainter* p = new QPainter(&rotatedPixmap);
        p->translate(this->pix.height()/2,this->pix.height()/2);
        p->rotate(this->rotateAngle);
        p->translate(-this->pix.height()/2,-this->pix.height()/2);
        p->drawPixmap(0, 0, this->pix);
        p->end();
        this->pix = rotatedPixmap;

        QPixmap panPixmap(this->pix.size());                                                   // Linhas 64-69: Aplica os deslocamentos ao pixmap de acordo com os parâmetros de pan(x,y)
        panPixmap.fill(QColor::fromRgb(0, 0, 0, 0));
        p = new QPainter(&panPixmap);
        p->drawPixmap(this->xDesloc, this->yDesloc, this->pix.width(), this->pix.height(), this->pix);
        p->end();
        this->pix = panPixmap;

        QPixmap brightPixmap(this->pix.size());                                                      // Linhas 54-59: Altera o brilho do pixmap de acordo com o parâmetro
        brightPixmap.fill(QColor::fromRgb(0, 0, 0, 0));
        p = new QPainter(&brightPixmap);
        p->setOpacity(this->brightness);
        p->drawPixmap(0, 0, this->pix);
        p->end();
        this->pix = brightPixmap;

        delete p;
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
    if (dialog.exec())
    {
        imgListAux = dialog.selectedFiles();
        foreach (value, imgListAux)
        {
            if (!this->fileNames.contains(value))
            {
                this->fileNames.append(value);
                this->ui->imgListCB->addItem(value);
            }
        }
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
    if (!fileNames.isEmpty())
    {
        this->scale = 1.0 + double(value/100.0);
        this->UpdateScreen();
    }
}


void MainWindow::on_xPanSL_valueChanged(int value)
{
    if (!fileNames.isEmpty())
    {
        this->xDesloc = value;
        this->UpdateScreen();
    }
}


void MainWindow::on_yPanSL_valueChanged(int value)
{
    if (!fileNames.isEmpty())
    {
        this->yDesloc = -value;
        this->UpdateScreen();
    }
}


void MainWindow::on_pushButton_clicked()
{
    this->ResetParameters();
}


void MainWindow::on_rotateSL_valueChanged(int value)
{
    if (!fileNames.isEmpty())
    {
        this->rotateAngle = value;
        this->UpdateScreen();
    }
}


void MainWindow::on_brightSL_valueChanged(int value)
{
    if (!fileNames.isEmpty())
    {
        this->brightness = (double)(value/100.0);
        this->UpdateScreen();
    }
}

