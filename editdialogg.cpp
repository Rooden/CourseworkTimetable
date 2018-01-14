#include "editdialogg.h"
#include "ui_editdialogg.h"
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QTimer>

using namespace std;

editDialogG::editDialogG(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editDialogG)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer->start(100);
}

editDialogG::~editDialogG()
{
    delete ui;
}

// добавление группы
void editDialogG::on_acceptButton_pressed()
{
    QString nameF;
    QFile name("editGroup.txt");
    if(name.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&name);
        stream >> nameF;
    }
    name.close();

    QFile editFile(nameF);
    if(editFile.open(QIODevice::Append))
    {
        QTextStream stream(&editFile);
        stream << ui->lineEdit->text() << endl;
    }
    editFile.close();
}

// проверка на пустоту поля
void editDialogG::onTimeout()
{
    if (ui->lineEdit->text().isEmpty())
        ui->acceptButton->setEnabled(false);
    else
        ui->acceptButton->setEnabled(true);
}
