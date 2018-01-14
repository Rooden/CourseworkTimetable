#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);

    //Добавление картинки
    ui->img->setPixmap(QPixmap("img.png"));
}

about::~about()
{
    delete ui;
}
