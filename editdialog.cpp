#include "editdialog.h"
#include "ui_editdialog.h"
#include <iostream>
#include <QFile>
#include <QTimer>
#include <QTextStream>

using namespace std;

editDialog::editDialog(QWidget *parent) :
    QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint),
    ui(new Ui::editDialog)
{
    ui->setupUi(this);

    ui->lineEdit->setText("");

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer->start(100);
}

editDialog::~editDialog()
{
    delete ui;
}

// добавление факультета
void editDialog::on_acceptButton_pressed()
{
    QFile editFile("facult.txt");
    if(editFile.open(QIODevice::Append))
    {
        QTextStream stream(&editFile);
        stream << ui->lineEdit->text() << endl;
        editFile.close();
    }
}

// проверка на пустоту поля
void editDialog::onTimeout()
{
    if (ui->lineEdit->text().isEmpty())
        ui->acceptButton->setEnabled(false);
    else
        ui->acceptButton->setEnabled(true);
}
