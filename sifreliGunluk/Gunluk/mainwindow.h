#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qfile.h"
#include "qdir.h"
#include <QFile>
#include <QDir>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString stringGunluk;
    QList<int>sifreAsci;
    QString gunluk;
    int y;
    int sayac=0;
    int sayac2=0;
    QList<QString> path_liste;
    QString dosya_adi="";
    QList<int> asciler;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_dosya_Adi_returnPressed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
