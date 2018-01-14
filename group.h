#ifndef GROUP_H
#define GROUP_H

#include <QDialog>
#include "editdialogg.h"

namespace Ui
{
  class group;
}

class editDialogG;
class group : public QDialog
{
  Q_OBJECT

public:
  explicit group(QWidget *parent = 0);
  ~group();

private slots:
    void on_delButton_clicked();

    void onTimeout();

    void on_facultWidget_currentRowChanged(int currentRow);

    void edit();

private:
  Ui::group *ui;
};

#endif // GROUP_H
