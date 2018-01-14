#ifndef READ_H
#define READ_H

#include <QDialog>
#include "admin.h"

namespace Ui
{
class read;
}

class read : public QDialog
{
    Q_OBJECT

public:
    explicit read(QWidget *parent = 0);
    ~read();

private slots:
    void on_facultBox_currentIndexChanged(int index);

    void changeTable();

    void on_week2Radio_clicked();

    void on_week1Radio_clicked();

    void on_quitButton_clicked();

    void color();

    void on_abtButton_clicked();

    void table();

private:
    Ui::read *ui;
};

class NonEditTableColumnDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    NonEditTableColumnDelegate(QObject * parent = 0) : QItemDelegate(parent) {}
    virtual QWidget * createEditor ( QWidget *, const QStyleOptionViewItem &,
                                     const QModelIndex &) const
    {
        return 0;
    }
};

#endif // READ_H
