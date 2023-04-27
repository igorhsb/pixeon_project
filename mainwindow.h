
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>


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

private:
    Ui::MainWindow *ui;
    QStringList fileNames;
    QPixmap pix;
};

#endif // MAINWINDOW_H
