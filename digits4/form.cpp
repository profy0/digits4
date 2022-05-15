#include "form.h"
#include "ui_form.h"
#include <QFile>
#include <QDebug>
#include <vector>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(1);

    ui->tableWidget->setColumnWidth(0,185);
    ui->tableWidget->setColumnWidth(1,186);
    QFile file("data.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream fl(&file);
    std::vector <std::pair<int, QString> > pr;
    while (!fl.atEnd()) {
        QString attempts, name;
        fl >> attempts >> name;
        int x = attempts.toInt();
        pr.push_back({x, name});
    }
    ui->tableWidget->setRowCount(0);
    pr.pop_back();
    std::sort(pr.begin(), pr.end());
    int sz = pr.size();
    if(sz>10) sz = 10;
    ui->tableWidget->setRowCount(sz);
    int pos=0;
    for(int i=0;i<sz;i++) {
        auto now = pr[i];
        ui->tableWidget->setItem(pos,0,new QTableWidgetItem(QString::number(now.first)));
        ui->tableWidget->setItem(pos++,1,new QTableWidgetItem(now.second));
    }
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Попыток"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Имя"));

}

Form::~Form()
{
    delete ui;
}

bool Form::getOpened() const
{
    return opened;
}
