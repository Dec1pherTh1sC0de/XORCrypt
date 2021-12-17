#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    this->move(center.x()-this->width()*0.5, center.y()-this->height()*0.5);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Кодирование
void MainWindow::stringEncrypt(QString strInput, QString strPassword)
{
    int i,j;
        QString strOutput="";

        // Перевод строк в битовые массивы с использованием локальных таблиц
        QByteArray baInput    = strInput.toLocal8Bit();
        QByteArray baPassword = strPassword.toLocal8Bit();

        // Кодирование информации
        for (i=0; i < baInput.size(); i++)
        {
            for (j=0; j < baPassword.size(); j++)
            {
                // XOR - кодировка символа
                baInput[i] = baInput[i] ^ (baPassword[j] + (i*j));
            }

            //Преобразование числа в шестнадцатеричную систему
            strOutput += QString("%1").arg((int)((unsigned char)baInput[i]),2,16,QChar('0'));
        }

        //Возврат кодированной строки
        strTXT = strOutput;
}

//Декодирование
void MainWindow::stringDecrypt(QString strInput, QString strPassword)
{
    int i,j;

        // Декодировка строки из 16-ричной системы в битовый массив
        QByteArray baInput    = QByteArray::fromHex(strInput.toLocal8Bit());
        // Перевод строки пароля в битовый массив
        QByteArray baPassword = strPassword.toLocal8Bit();

        // Декодирование информации
        for (i=0; i < baInput.size(); i++)
        {
            for (j=0; j < baPassword.size(); j++)
            {
                // XOR - кодировка символа
                baInput[i] = baInput[i] ^ (baPassword[j] + (i*j));
            }
        }

        //Возврат декодированной строки
        strTXT = QString::fromLocal8Bit(baInput.data());
}

//Зашифровка текста
void MainWindow::on_pushButton_clicked()
{
    stringEncrypt(this->ui->lineEdit->text(),this->ui->label_2->text());
    this->ui->lineEdit_3->setText(strTXT);
}

//Расшифровка текста
void MainWindow::on_pushButton_2_clicked()
{
    stringDecrypt(this->ui->lineEdit->text(),this->ui->label_2->text());
    this->ui->lineEdit_3->setText(strTXT);
}

//Очистка полей
void MainWindow::on_pushButton_3_clicked()
{
    this->ui->lineEdit->clear();
    this->ui->lineEdit_2->clear();
    this->ui->lineEdit_3->clear();
}

