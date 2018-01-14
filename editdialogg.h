#ifndef EDITDIALOGG_H
#define EDITDIALOGG_H

#include <QDialog>

namespace Ui
{
class editDialogG;
}

class editDialogG : public QDialog
{
    Q_OBJECT

public:
    explicit editDialogG(QWidget *parent = 0);
    ~editDialogG();

private slots:
    void on_acceptButton_pressed();

    void onTimeout();

private:
    Ui::editDialogG *ui;
};

#endif // EDITDIALOGG_H
