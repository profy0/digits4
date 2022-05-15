#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QRandomGenerator>
#include <QDialog>
#include "inputdialog.h"
#include <ctype.h>
#include <iostream>
#include <QMessageBox>
#include <set>

Form *frm;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("Игра не начата");
    ui->label_2->setText("Введите число:");
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Число"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Результат"));
    ui->tableWidget->setColumnWidth(0,229);
    ui->tableWidget->setColumnWidth(1,230);
    firstTime = true;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::addToTable(int x, int y)
{
    if(!firstTime) ui->tableWidget->setRowCount(++rowCnt); else firstTime = false;
    ui->tableWidget->setItem(last,0,new QTableWidgetItem(currentStr));
    ui->tableWidget->setItem(last++,1,new QTableWidgetItem("Быков: " + QString::number(x) + "; Коров: " + QString::number(y)));
    ui->lineEdit->clear();
}


void MainWindow::on_pushButton_clicked()   // new form
{
    if(frm!=nullptr) frm->close();
    frm = new Form();
    frm->setWindowTitle("Рекорды");
    frm->setMinimumHeight(400);
    frm->setMaximumHeight(400);
    frm->setMinimumWidth(400);
    frm->setMaximumWidth(400);
    frm->show();

}

void MainWindow::on_pushButton_2_clicked()   // add string
{
    currentStr = ui->lineEdit->text();
    bool ok = 0;
    for(auto now : currentStr) ok |= !(now>='0'&&now<='9');
    if(currentStr.size()!=4 || ok) {
        QMessageBox::warning(this, "Ошибка", "Введите число от 1000 до 10000!");
        ui->lineEdit->clear();
        return;
    }
    std::set <QChar> s;
    for(auto now : currentStr) s.insert(now);
    if(s.size()!=4) {
        QMessageBox::warning(this, "Ошибка", "Все цифры в числе должны быть различны!");
        ui->lineEdit->clear();
        return;
    }
    int k=0,b=0;

    for(int i=0;i<currentStr.size();i++) {
        b+=(cur[i]==currentStr[i]);
    }

    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            if(currentStr[i]==cur[j]&&i!=j) {
                k++;
                break;
            }
        }
    }

    addToTable(b,k);

    if(b==4) {
        inputDialog *dialog = new inputDialog;
        dialog->record = QString::number(rowCnt);
        dialog->exec();
    }
}

void MainWindow::on_pushButton_3_clicked()    // new game
{
    ui->lineEdit->setEnabled(1);
    ui->pushButton_2->setEnabled(1);
    ui->label->setText("Игра начата");
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(1);
    firstTime = 1;
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Число"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Результат"));
    ui->lineEdit->clear();
    rnd = QRandomGenerator::global();
    cur.clear();
    std::set <int> s;
    for(int i=0;i<10;i++) s.insert(i);
    int mx = 9;
    for(int i=0;i<4;i++) {
        int x = rnd->bounded(0,mx--);
        auto now = s.begin();
        while(x--) {
            now++;
        }
        cur+=QString::number(*now);
        s.erase(now);
    }

    last=0, rowCnt=1;
  //  qDebug() << cur;
}
