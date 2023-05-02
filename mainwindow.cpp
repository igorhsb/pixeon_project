
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
    // Essa função tem o objetivo de realizar a inicialização de todos os elementos e parâmetros da aplicação

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
    // Essa função tem o objetivo de resetar todos os parâmetros ao seu estado inicial
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

void MainWindow::UpdateScreen()
{
    // Essa função tem como objetivo atualizar a visualização da imagem no QLabel
    if(this->pix.load(fileNames[this->imgIndex]))
    {
        this->pix = this->pix.scaled(this->scale*this->ui->imgLabel->size());    // Aplica o zoom de acordo com o parâmetro

        QPixmap rotatedPixmap(this->pix.size());                                 // Linhas 75-83: Aplica a rotação ao pixmap de acordo com o parâmetro
        rotatedPixmap.fill(QColor::fromRgb(0, 0, 0, 0));
        QPainter* p = new QPainter(&rotatedPixmap);
        p->translate(this->pix.height()/2,this->pix.height()/2);
        p->rotate(this->rotateAngle);
        p->translate(-this->pix.height()/2,-this->pix.height()/2);
        p->drawPixmap(0, 0, this->pix);
        p->end();
        this->pix = rotatedPixmap;

        QPixmap panPixmap(this->pix.size());                                     // Linhas 85-90: Aplica os deslocamentos ao pixmap de acordo com os parâmetros de pan(x,y)
        panPixmap.fill(QColor::fromRgb(0, 0, 0, 0));
        p = new QPainter(&panPixmap);
        p->drawPixmap(this->xDesloc, this->yDesloc, this->pix.width(), this->pix.height(), this->pix);
        p->end();
        this->pix = panPixmap;

        QPixmap brightPixmap(this->pix.size());                                 // Linhas 92-98: Altera o brilho do pixmap de acordo com o parâmetro
        brightPixmap.fill(QColor::fromRgb(0, 0, 0, 0));
        p = new QPainter(&brightPixmap);
        p->setOpacity(this->brightness);
        p->drawPixmap(0, 0, this->pix);
        p->end();
        this->pix = brightPixmap;

        delete p;
        this->ui->imgLabel->setPixmap(this->pix);                              // Após as modificações no QPixmap, atualiza o mesmo no QLabel
    }
}

void MainWindow::on_addImgBTN_clicked()
{
    // Evento de clicked do botão de adicionar imagem, tem o objetivo de abrir um dialog para inclusão de imagens
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
    // Evento de troca de índice do combo box com as imagens inseridas, tem o objetivo de setar o índice atual no atributo da MainWindow
    this->imgIndex = index;
    this->ResetParameters();
    this->UpdateScreen();
}

void MainWindow::on_zoomSL_valueChanged(int value)
{
    // Evento de troca de índice do slider de zoom. Tem o objetivo de setar o valor de zoom no atributo da MainWindow
    if (!fileNames.isEmpty())
    {
        this->scale = 1.0 + double(value/100.0);
        this->UpdateScreen();
    }
}


void MainWindow::on_xPanSL_valueChanged(int value)
{
    // Evento de troca de índice do slider de pan(x). Tem o objetivo de setar o valor de pan na direção x no atributo da MainWindow
    if (!fileNames.isEmpty())
    {
        this->xDesloc = value;
        this->UpdateScreen();
    }
}


void MainWindow::on_yPanSL_valueChanged(int value)
{
    // Evento de troca de índice do slider de pan(y). Tem o objetivo de setar o valor de pan na direção y no atributo da MainWindow
    if (!fileNames.isEmpty())
    {
        this->yDesloc = -value;
        this->UpdateScreen();
    }
}


void MainWindow::on_pushButton_clicked()
{
    // Evento de clicked do botão de resete. Tem o objetivo de invocar a função ResetParameters
    this->ResetParameters();
}


void MainWindow::on_rotateSL_valueChanged(int value)
{
    // Evento de troca de índice do slider de rotação. Tem o objetivo de setar o valor de rotação no atributo da MainWindow
    if (!fileNames.isEmpty())
    {
        this->rotateAngle = value;
        this->UpdateScreen();
    }
}


void MainWindow::on_brightSL_valueChanged(int value)
{
    // Evento de troca de índice do slider de brilho. Tem o objetivo de setar o valor de brilho no atributo da MainWindow
    if (!fileNames.isEmpty())
    {
        this->brightness = (double)(value/100.0);
        this->UpdateScreen();
    }
}

