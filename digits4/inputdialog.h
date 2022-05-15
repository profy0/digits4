#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>


class QLabel;
class QLineEdit;
class QPushButton;

class inputDialog : public QDialog
{

    Q_OBJECT

public:

    inputDialog(QWidget *parent = 0);
    void setRecord(int);
    QString record;

private slots:

    void findClicked();
    void enableFindButton(const QString &text);

private:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *addButton;
    QPushButton *closeButton;


};

#endif // INPUTDIALOG_H
