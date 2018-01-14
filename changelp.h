#ifndef CHANGELP_H
#define CHANGELP_H

#include <QDialog>

namespace Ui {
class changeLP;
}

class changeLP : public QDialog
{
    Q_OBJECT

public:
    explicit changeLP(QWidget *parent = 0);
    ~changeLP();

private slots:
    void on_acceptButton_clicked();

private:
    Ui::changeLP *ui;
};

#endif // CHANGELP_H
