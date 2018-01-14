#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>

namespace Ui
{
class editDialog;
}

class editDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editDialog(QWidget *parent = 0);
    ~editDialog();

private slots:
    void on_acceptButton_pressed();

    void onTimeout();

private:
    Ui::editDialog *ui;
};

#endif // EDITDIALOG_H
