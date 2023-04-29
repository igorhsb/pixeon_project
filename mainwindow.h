
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QPainter>
#include <QTransform>

//#define imgPlaceholdPath ".."

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addImgBTN_clicked();

    void on_imgListCB_currentIndexChanged(int index);

    void on_zoomSL_valueChanged(int value);

    void on_xPanSL_valueChanged(int value);

    void on_yPanSL_valueChanged(int value);

    void on_pushButton_clicked();

    void on_rotateSL_valueChanged(int value);

    void on_brightSL_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QStringList fileNames;
    QPixmap pix;
    int imgIndex, yDesloc, xDesloc;
    double scale;

    void InitComponents();
    void UpdateScreen();
    void ResetParameters();
};

#endif // MAINWINDOW_H
