#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include <QItemDelegate>
#include "facult.h"
#include "group.h"
#include "BasicExcel.hpp"

namespace Ui {
class admin;
}

class admin : public QDialog
{
    Q_OBJECT

public:
    explicit admin(QDialog *parent = 0);
    ~admin();

private slots:
    void on_quitButton_clicked();

    void on_facultBox_currentIndexChanged(int index);

    void onTimeout();

    void on_saveButton_clicked();

    void changeTable();

    void on_week2Radio_clicked();

    void on_week1Radio_clicked();

    void grp();

    void on_exportButton_clicked();

    void color();

    void table();

    void on_pushButton_clicked();

private:
    facult *facultForm;
    group *groupForm;
    Ui::admin *ui;
};

#endif // ADMIN_H
