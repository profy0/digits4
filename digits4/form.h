#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
    bool getOpened() const;

private:
    Ui::Form *ui;
    bool opened;
};

#endif // FORM_H
