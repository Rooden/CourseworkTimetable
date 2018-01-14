#ifndef FACULT_H
#define FACULT_H

#include <QDialog>
#include "editdialog.h"

namespace Ui
{
  class facult;
}

class editDialog;
class facult : public QDialog
{
  Q_OBJECT


public:
  explicit facult(QWidget *parent = 0);
  ~facult();


private slots:
    void on_delButton_clicked();

    void onTimeout();


private:
  Ui::facult *ui;
};

#endif // FACULT_H
