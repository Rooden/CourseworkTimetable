#ifndef LOADER_H
#define LOADER_H

#include <QWidget>

namespace Ui {
class loader;
}

class loader : public QWidget
{
    Q_OBJECT

public:
    explicit loader(QWidget *parent = 0);
    ~loader();

private slots:
    void load();

private:
    Ui::loader *ui;
};

#endif // LOADER_H
