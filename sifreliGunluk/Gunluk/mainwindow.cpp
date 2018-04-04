#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QDirIterator>
#include <QMessageBox>
#include <QModelIndex>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDir klasor("/home/metin/Masaüstü/klasör/");
    if(!klasor.exists())
    {
        QDir().mkdir("/home/metin/Masaüstü/klasör/");
    }

    QDirIterator it("/home/metin/Masaüstü/klasör", QStringList() , QDir::NoFilter, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QFile f(it.next());
        f.open(QIODevice::ReadOnly);
        QString x = it.fileName();
        path_liste.push_back(x);
    }

    for (int i = 0; i < path_liste.length(); ++i) {
        if(path_liste.at(i)!="." && path_liste.at(i)!="..")
            ui->listWidget->addItem(path_liste.at(i));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString sifre=ui->lineEdit->text();    

    gunluk=ui->plainTextEdit->toPlainText();

    for (int i = 0; i < sifre.length(); ++i) {
        QChar x=sifre.at(i);
        y=x.toLatin1();
        sifreAsci.push_back(y);
    }
    while(sayac<gunluk.length()){
        for (int j = 0; j < sifreAsci.size(); j++) {
            QChar x = gunluk.at(sayac);
            int y=x.toLatin1();
            y+=sifreAsci.value(j);
            y%=127;
            //şŞüÜöÖİğĞıçÇ
            //&#351;&#350;&#252;&#220;&#246;&#214;&#304;&#287;&#286;&#305;&#231;&#199;
            if(gunluk.at(sayac)=="ş"){
                //351
                y=351+2;
            }
            if(gunluk.at(sayac)=="Ş"){
                //350
                y=350+20;
            }
            if(gunluk.at(sayac)=="ü"){
                //252
                y=252+4;
            }
            if(gunluk.at(sayac)=="Ü"){
                //220
                y=220+5;
            }
            if(gunluk.at(sayac)=="ö"){
                //246
                y=246+6;
            }
            if(gunluk.at(sayac)=="Ö"){
                //214
                y=214+7;
            }
            if(gunluk.at(sayac)=="İ"){
                //304
                y=304+8;
            }
            if(gunluk.at(sayac)=="ğ"){
                //287
                y=287+9;
            }
            if(gunluk.at(sayac)=="Ğ"){
                //286
                y=286+21;
            }
            if(gunluk.at(sayac)=="ı"){
                //305
                y=305+11;
            }
            if(gunluk.at(sayac)=="ç"){
                //231
                y=231+12;
            }
            if(gunluk.at(sayac)=="Ç"){
                //199
                y=199+13;
            }
            asciler.push_back(y);
            stringGunluk+=(QString)y;
            sayac++;
            if(sayac==gunluk.length())
                break;
       }
        if(sayac==gunluk.length())
            break;
    }

    if(dosya_adi.isEmpty()){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "UYARI", "Şifre belirlemediniz devam etmek istiyor musunuz? uygulama kapanacak",QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            QApplication::quit();
        }
        else{
            return;
        }
    }
    QFile bosalt("/home/metin/Masaüstü/klasör/"+dosya_adi+".txt");
    bosalt.open(QIODevice::Truncate|QFile::WriteOnly);
    char *deger=(char*)malloc(10);
    QByteArray ba=stringGunluk.toLatin1();
    strcpy(deger,ba.data());
    bosalt.write(deger);
    bosalt.close();
}

void MainWindow::on_pushButton_2_clicked()
{
   // ui->listWidget->addItem(secilen_dosya);
    QString sifresiz_gunluk;
    while(sayac2<stringGunluk.length()){
        for (int j = 0; j < sifreAsci.size(); ++j) {
            QChar c = stringGunluk.at(sayac2);
            int sifreli_ascii=c.toLatin1();
            int asil_ascii=sifreli_ascii-sifreAsci.at(j);
            if(asil_ascii<0)
                asil_ascii=sifreli_ascii+127-sifreAsci.at(j);
            if(asciler.at(sayac2)==353){
                //351+2
                asil_ascii=351;
            }
            if(asciler.at(sayac2)==370){
                //350+20
                asil_ascii=350;
            }
            if(asciler.at(sayac2)==256){
                //252+4
                asil_ascii=252;
            }
            if(asciler.at(sayac2)==225){
                //220+5
                asil_ascii=220;
            }
            if(asciler.at(sayac2)==252){
                //246+6
                asil_ascii=246;
            }
            if(asciler.at(sayac2)==221){
                //214+7
                asil_ascii=214;
            }
            if(asciler.at(sayac2)==312){
                //304+8
                asil_ascii=304;
            }
            if(asciler.at(sayac2)==296){
                //287+9
                asil_ascii=287;
            }
            if(asciler.at(sayac2)==307){
                //286+21
                asil_ascii=286;
            }
            if(asciler.at(sayac2)==316){
                //305+11
                asil_ascii=305;
            }
            if(asciler.at(sayac2)==243){
                //231+12
                asil_ascii=231;
            }
            if(asciler.at(sayac2)==212){
                //199+13
                asil_ascii=199;
            }

            sifresiz_gunluk+=(QString)asil_ascii;
            sayac2++;
            if(sayac2==stringGunluk.length())
                break;
        }
        if(sayac2==stringGunluk.length())
            break;
    }
    ui->listWidget->addItem(sifresiz_gunluk);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString secilen_dosya=ui->listWidget->currentItem()->text();
    ui->label->setText(secilen_dosya);
    /*if(dosya_adi.isEmpty()){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "UYARI", "Şifre belirlemediniz devam etmek istiyor musunuz? uygulama kapanacak",QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            QApplication::quit();
        }
        else{
            return;
        }
    }*/
    QString path = "/home/metin/Masaüstü/klasör/"+secilen_dosya+"";
    QFile file(path);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }
    QTextStream in(&file);
    QString myText = in.readAll();
    ui->listWidget->addItem("satirim:"+myText);
    file.close();

    int sayac2=0;

    QString sifresiz_gunluk;
    stringGunluk=myText;
    QString sifre=ui->lineEdit_3->text();
    sifreAsci.clear();
    asciler.clear();
    for (int i = 0; i < myText.length(); ++i) {
        QChar x=myText.at(i);
        y=x.toLatin1();
        asciler.push_back(y);
    }
    for (int i = 0; i < sifre.length(); ++i) {
        QChar x=sifre.at(i);
        y=x.toLatin1();
        sifreAsci.push_back(y);
    }
    ui->listWidget->addItem("dddddddd "+QString::number(sayac2));
    while(sayac2<stringGunluk.length()){
        ui->listWidget->addItem("sasd");
        for (int j = 0; j < sifreAsci.size(); ++j) {

            QChar c = stringGunluk.at(sayac2);
            int sifreli_ascii=c.toLatin1();
            int asil_ascii=sifreli_ascii-sifreAsci.at(j);
            if(asil_ascii<0)
                asil_ascii=sifreli_ascii+127-sifreAsci.at(j);
            if(asciler.at(sayac2)==353){
                //351+2
                asil_ascii=351;
            }
            if(asciler.at(sayac2)==370){
                //350+20
                asil_ascii=350;
            }
            if(asciler.at(sayac2)==256){
                //252+4
                asil_ascii=252;
            }
            if(asciler.at(sayac2)==225){
                //220+5
                asil_ascii=220;
            }
            if(asciler.at(sayac2)==252){
                //246+6
                asil_ascii=246;
            }
            if(asciler.at(sayac2)==221){
                //214+7
                asil_ascii=214;
            }
            if(asciler.at(sayac2)==312){
                //304+8
                asil_ascii=304;
            }
            if(asciler.at(sayac2)==296){
                //287+9
                asil_ascii=287;
            }
            if(asciler.at(sayac2)==307){
                //286+21
                asil_ascii=286;
            }
            if(asciler.at(sayac2)==316){
                //305+11
                asil_ascii=305;
            }
            if(asciler.at(sayac2)==243){
                //231+12
                asil_ascii=231;
            }
            if(asciler.at(sayac2)==212){
                //199+13
                asil_ascii=199;
            }

            sifresiz_gunluk+=(QString)asil_ascii;
            sayac2++;
            if(sayac2==stringGunluk.length())
                break;
        }
        if(sayac2==stringGunluk.length())
            break;
    }
    ui->plainTextEdit->document()->setPlainText(sifresiz_gunluk);

}

void MainWindow::on_dosya_Adi_returnPressed()
{
    dosya_adi=ui->dosya_Adi->text();
}
