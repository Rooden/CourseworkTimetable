#include "group.h"
#include "ui_group.h"
#include <QFile>
#include <QTextStream>
#include <QTimer>

group::group(QWidget *parent) :
    QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint),
    ui(new Ui::group)
{
    ui->setupUi(this);

    connect(ui->editButton,SIGNAL(clicked()),this,SLOT(edit()));

    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer->start(100);
}

group::~group()
{
    delete ui;
}

//  удаление
void group::on_delButton_clicked()
{    
    QString name = "";
    bool status = false;
    QListWidgetItem *itm;

    for (int i = 0; i < ui->facultWidget->count(); i++)
    {
        itm = ui->facultWidget->item(i);
        if (ui->facultWidget->isItemSelected(itm))
        {
            status = true;
            break;
        }
    }

    if (status == false)
    {
        name = "group" + ui->facultWidget->item(0)->text() + ".txt";
    }
    else
    {
        name = "group" + ui->facultWidget->currentItem()->text() + ".txt";
    }

    delete ui->groupWidget->takeItem(ui->groupWidget->currentRow());

    QFile file(name);
    if(file.open(QIODevice::WriteOnly))
    {
        for(int i = 0; i < ui->groupWidget->count(); i++)
        {
            QTextStream stream(&file);
            stream << ui->groupWidget->item(i)->text() << endl;
        }
    }
    file.close();
}

// заполнение при добавлении/удалении
void group::onTimeout()
{
    QString str = "", temp1 = "", temp2 = "", name = "";
    bool status = false;

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
        QFile addFac("facult.txt");
        if (addFac.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&addFac);
            while (!stream.atEnd())
            {
                str = stream.readLine();
                ui->facultWidget->addItem(str);
            }
        }
        addFac.close();

        ui->groupWidget->clear();
        QString name = "group" + ui->facultWidget->item(0)->text() + ".txt";
        QFile addGr(name);
        if (addGr.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&addGr);
            while (!stream.atEnd())
            {
                str = stream.readLine();
                ui->groupWidget->addItem(str);
            }
        }
        addGr.close();
    }




    /*Определение изменения групп*/
    temp1 = ""; temp2 = "";
    QListWidgetItem *itm;
    for (int i = 0; i < ui->facultWidget->count(); i++)
    {
        itm = ui->facultWidget->item(i);
        if (ui->facultWidget->isItemSelected(itm))
        {
            status = true;
            break;
        }
    }

    if (status == false)
    {
        name = "group" + ui->facultWidget->item(0)->text() + ".txt";
    }
    else
    {
        name = "group" + ui->facultWidget->currentItem()->text() + ".txt";
    }

    QFile gr(name);
    if (gr.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&gr);
        while (!stream.atEnd())
        {
            str = stream.readLine();
            temp1 += str;
        }
    }
    gr.close();

    for (int i = 0; i < ui->groupWidget->count(); i++)
    {
        str = ui->groupWidget->item(i)->text();
        temp2 += str;
    }

    if (temp1 != temp2)
    {
        ui->groupWidget->clear();
        QFile addgr(name);
        if (addgr.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&addgr);
            while (!stream.atEnd())
            {
                str = stream.readLine();
                ui->groupWidget->addItem(str);
            }
        }
        addgr.close();
    }

    /*status = false;
    for (int i = 0; i < ui->groupWidget->count(); i++)
    {
        itm = ui->groupWidget->item(i);
        if (ui->groupWidget->isItemSelected(itm))
        {
            status = true;
            break;
        }
    }

    if (status == false)
    {
        itm = ui->groupWidget->item(0);
        ui->groupWidget->setItemSelected(itm, true);
    }
*/

















    /*QString name = ui->facultWidget->item(ui->facultWidget->currentRow())->text() + ".txt";
    ui->editButton->setText(name);*/

    /*QString temp1 = "", temp2 = "", str = "";

    QFile file3("facult.txt");
    if(file3.open(QIODevice::ReadOnly))
    {
        QTextStream stream1(&file3);
        while(!stream1.atEnd())
        {
            str = stream1.readLine();
            temp1 += str;
        }
    }
    file3.close();

    for (int i = 0; i < ui->facultWidget->count(); i++)
    {
        str = ui->facultWidget->item(i)->text();
        temp2 += str;
    }

    if (temp1 != temp2)
    {
        QFile file4("facult.txt");
        if(file4.open(QIODevice::ReadOnly))
        {
            QTextStream stream1(&file4);
            while(!stream1.atEnd())
            {
                str = stream1.readLine();
                ui->facultWidget->addItem(str);
            }
        }
        file4.close();
    }

    temp1 = ""; temp2 = "";
    QString name = "group" + ui->facultWidget->currentItem()->text() + ".txt";
    //QString name = "group.txt";
    QFile file1(name);
    if(file1.open(QIODevice::ReadOnly))
    {
        QTextStream stream1(&file1);
        while(!stream1.atEnd())
        {
            str = stream1.readLine();
            temp1 += str;
        }
    }
    file1.close();

    for (int i = 0; ui->groupWidget->count(); i++)
    {
        str = ui->groupWidget->item(i)->text();
        temp2 += str;
    }

    if (temp1 != temp2)
    {

        QFile add(name);
        if(add.open(QIODevice::ReadOnly))
        {
            ui->groupWidget->clear();
            QTextStream stream(&add);
            while(!stream.atEnd())
            {
                str = stream.readLine();
                ui->groupWidget->addItem(str);
            }
        }
        add.close();
    }*/

    /*ui->facultWidget->clear();
    QFile fac("facult.txt");
    if (fac.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&fac);
        while (!stream.atEnd())
        {
            QString str = stream.readLine();
            ui->facultWidget->addItem(str);
        }
    }
    fac.close();*/
}

void group::on_facultWidget_currentRowChanged(int currentRow)
{
    QString name = "group" + ui->facultWidget->item(currentRow)->text() + ".txt";
    QString str = "";

    ui->groupWidget->clear();

    QFile addGr(name);
    if (addGr.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&addGr);
        while (!stream.atEnd())
        {
            str = stream.readLine();
            ui->groupWidget->addItem(str);
        }
    }
    addGr.close();















    //QString name = "group" + ui->facultWidget->item(currentRow)->text() + ".txt";
    //QString edit = "editGroup" + ui->facultWidget->item(currentRow)->text() + ".txt";

    /*QString temp1 = "", temp2 = "";
    QFile file1(name);
    if(file1.open(QIODevice::ReadOnly))
    {
        QTextStream stream1(&file1);
        QString str;
        while(!stream1.atEnd())
        {
            str = stream1.readLine();
            temp1 += str;
        }
    }
    file1.close();*/

    /*QFile file2(edit);
    if(file2.open(QIODevice::ReadOnly))
    {
        QTextStream stream2(&file2);
        QString str;
        while(!stream2.atEnd())
        {
            str = stream2.readLine();
            temp2 += str;
        }
    }
    file2.close();*/

    /*for (int i = 0; i < ui->groupWidget->count(); i ++)
    {
        QString str = ui->groupWidget->item(i)->text();
        temp2 += str;
    }

    if (temp1 != temp2)
    {*/
    /*if (temp1 > temp2)
        {
            QFile edit1(edit);
            QFile group(name);
            if(edit1.open(QIODevice::WriteOnly) && group.open(QIODevice::ReadOnly))
            {
                QTextStream streamEdit(&edit1);
                QTextStream streamFacult(&group);
                while(!streamEdit.atEnd())
                    streamEdit << streamFacult.readLine() << endl;
            }
            edit1.close();
            group.close();
        }
        else
        {
            QFile edit1(edit);
            QFile group(name);
            if(edit1.open(QIODevice::ReadOnly) && group.open(QIODevice::WriteOnly))
            {
                QTextStream streamEdit(&edit1);
                QTextStream streamFacult(&group);
                while(!streamEdit.atEnd())
                    streamFacult << streamEdit.readLine() << endl;
            }
            edit1.close();
            group.close();

            QFile add(name);
            if(add.open(QIODevice::ReadOnly))
            {
                ui->groupWidget->clear();
                QTextStream stream(&add);
                QString str;
                while(!stream.atEnd())
                {
                    str = stream.readLine();
                    ui->groupWidget->addItem(str);
                }
            }
            add.close();
        }
    }*/

    /*QFile file1edit(name);
    ui->groupWidget->clear();
    if(file1edit.open(QIODevice::ReadOnly))
    {
        QTextStream stream1(&file1edit);
        QString str;
        while(!stream1.atEnd())
        {
            str = stream1.readLine();
            ui->groupWidget->addItem(str);
        }
    }
    file1edit.close();*/
}

void group::edit()
{
    QString name = "";
    bool status = false;
    QListWidgetItem *itm;

    for (int i = 0; i < ui->facultWidget->count(); i++)
    {
        itm = ui->facultWidget->item(i);
        if (ui->facultWidget->isItemSelected(itm))
        {
            status = true;
            break;
        }
    }

    if (status == false)
    {
        name = "group" + ui->facultWidget->item(0)->text() + ".txt";
    }
    else
    {
        name = "group" + ui->facultWidget->currentItem()->text() + ".txt";
    }

    QFile file("editGroup.txt");
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << name;

    }
    file.close();

    editDialogG *editForm = new editDialogG();
    editForm->show();
}
