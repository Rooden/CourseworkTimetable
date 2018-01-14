#ifndef ENTER_H
#define ENTER_H

#include <QMainWindow>

namespace Ui {
class enter;
}

class enter : public QMainWindow
{
    Q_OBJECT

public:
    explicit enter(QWidget *parent = 0);
    ~enter();

private slots:
    void on_enterButton_clicked();

private:
    Ui::enter *ui;
};

#endif // ENTER_H
