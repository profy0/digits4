#include <QtGui>
#include "inputdialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

inputDialog::inputDialog(QWidget *parent)
      : QDialog(parent)
  {

    label = new QLabel(tr("Input &name:"));
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);

    addButton = new QPushButton(tr("&OK"));
    addButton->setDefault(true);
    addButton->setEnabled(false);

    closeButton = new QPushButton(tr("Cancel"));
    connect(lineEdit, SIGNAL(textChanged(const QString &)),
        this, SLOT(enableFindButton(const QString &)));
    connect(addButton, SIGNAL(clicked()),
        this, SLOT(findClicked()));
    connect(closeButton, SIGNAL(clicked()),
        this, SLOT(close()));
    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(lineEdit);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);

    QHBoxLayout *rightLayout = new QHBoxLayout;
    rightLayout->addWidget(closeButton);
    rightLayout->addWidget(addButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    setLayout(mainLayout);
    setWindowTitle(tr("Input"));
    setFixedHeight(sizeHint().height());
}


void inputDialog::findClicked() {
    QString text = lineEdit->text();
    QFile file2("data.txt");
    if(!file2.open(QIODevice::Append)) {
        qDebug() << "file error";
    }
    QTextStream fileStream(&file2);
    fileStream << record << " " << text << "\n";
    file2.close();
    close();
 }

void inputDialog::enableFindButton(const QString &text) {
    addButton->setEnabled(!text.isEmpty());
}
