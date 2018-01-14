#include "facult.h"
#include "ui_facult.h"
#include <QFile>
#include <QTextStream>
#include <QTimer>

facult::facult(QWidget *parent) :
    QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint),
    ui(new Ui::facult)
{
    ui->setupUi(this);

    editDialog *editForm = new editDialog();
    connect(ui->editButton,SIGNAL(clicked()),editForm,SLOT(show()));

    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer->start(100);

    QFile editFile("facult.txt");
    if(editFile.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&editFile);
        QString str;
        while(!stream.atEnd())
        {
            str = stream.readLine();
            ui->facultWidget->addItem(str);
        }
    }
    editFile.close();
}

facult::~facult()
{
    delete ui;
}

// удаление
void facult::on_delButton_clicked()
{
    QString str = "";

    delete ui->facultWidget->takeItem(ui->facultWidget->currentRow());

    QFile fac("facult.txt");
    if (fac.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&fac);
        for (int i = 0; i < ui->facultWidget->count(); i++)
        {
            str = ui->facultWidget->item(i)->text();
            stream << str << endl;
        }
    }
    fac.close();
}

// замена при добавлении/удалении
void facult::onTimeout()
{
    QString str = "", temp1 = "", temp2 = "";

    QFile fac("facult.txt");
    if (fac.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&fac);
        while (!stream.atEnd())
        {
            str = stream.readLine();
            temp1 += str;
        }
    }
    fac.close();

    for (int i = 0; i < ui->facultWidget->count(); i++)
    {
        str = ui->facultWidget->item(i)->text();
        temp2 += str;
    }

    if (temp1 != temp2)
    {
        ui->facultWidget->clear();

        QFile add("facult.txt");
        if (add.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&add);
            while (!stream.atEnd())
            {
                str = stream.readLine();
                ui->facultWidget->addItem(str);
            }
        }
        add.close();
    }
}
