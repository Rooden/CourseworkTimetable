#include "admin.h"
#include "ui_admin.h"
#include "enter.h"
#include "read.h"
#include "about.h"
#include "changelp.h"
#include <QMessageBox>
#include <QAxObject>
#include <qaxobject.h>
#include <QFile>
#include <QTextStream>
#include <QTableWidget>
#include <QTimer>
#include <QTextCodec>
#include <QFileDialog>
#include "BasicExcel.hpp"

using namespace YExcel;

QTimer* tmr = new QTimer();
QTimer* tbl = new QTimer();

admin::admin(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);

    // Событие вызова формы факультета по нажатию кнопки
    facult *facultForm = new facult();
    connect(ui->facultButton, SIGNAL(clicked()), facultForm, SLOT(show()));

    // Событие вызова формы группы по нажатию кнопки
    connect(ui->groupButton, SIGNAL(clicked()), this, SLOT(grp()));

    // Событие вызова формы смены лог/пас
    changeLP *chng = new changeLP();
    connect(ui->changeButton, SIGNAL(clicked()), chng, SLOT(show()));

    // изначальный размер таблицы
    int col = 7, row = 18;
    ui->tableWidget->setRowCount(row);
    ui->tableWidget->setColumnCount(col);

    // заполнение таблицы пробелами для сохранения
    for (int i = 0; i < row; i++)
        for (int j = 0 ; j < col+1; j++)
        {
            QTableWidgetItem *str = new QTableWidgetItem(QString::fromLocal8Bit(" "));
            ui->tableWidget->setItem(i,j,str);
        }
    // установка ширины солонок
    for (int i = 0; i < col+1; i++)
        ui->tableWidget->setColumnWidth(i,172);

    // запрет редактирования 1ой колонки
    for (int i = 0; i < row; i+=3)
    {
        ui->tableWidget->setSpan(i,0,3,1);
        ui->tableWidget->setItemDelegateForColumn(0,new NonEditTableColumnDelegate());
    }

    // Добавление факультетов в комбоБокс
    QFile editFile("facult.txt");
    if(editFile.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&editFile);
        QString str;
        while(!stream.atEnd())
        {
            str = stream.readLine();
            ui->facultBox->addItem(str);
        }
    }
    editFile.close();

    // скрытие номера строк
    ui->tableWidget->verticalHeader()->hide();

    // определить неделю
    QString week;
    if(!ui->week1Radio->isDown())
        week = "1";
    else
        week = "2";

    // заполнение таблицы выбранной группой
    QString name = ui->facultBox->currentText() + ui->groupBox->currentText() + week + ".txt";
    QFile file(name);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        for(int i = 0; i < ui->tableWidget->rowCount(); i++)
            for(int j = 0; j < ui->tableWidget->columnCount(); j++)
            {
                QString itm = stream.readLine();
                QTableWidgetItem *line = new QTableWidgetItem();
                line->setText(itm);
                ui->tableWidget->setItem(i,j,line);
            }
    }

    // заполнение расписания
    QString name1 = "label" + name;
    QFile file1(name1);
    if(file1.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file1);

        QString str = stream.readLine();
        ui->lineEdit_1->setText(str);
        str = stream.readLine();
        ui->lineEdit_2->setText(str);
        str = stream.readLine();
        ui->lineEdit_3->setText(str);
        str = stream.readLine();
        ui->lineEdit_4->setText(str);
        str = stream.readLine();
        ui->lineEdit_5->setText(str);
        str = stream.readLine();
        ui->lineEdit_6->setText(str);
        str = stream.readLine();
        ui->lineEdit_7->setText(str);
        str = stream.readLine();
        ui->lineEdit_8->setText(str);
        str = stream.readLine();
        ui->lineEdit_9->setText(str);
        str = stream.readLine();
        ui->lineEdit_10->setText(str);
        str = stream.readLine();
        ui->lineEdit_13->setText(str);
        str = stream.readLine();
        ui->lineEdit_14->setText(str);

        file1.close();
    }
    else
    {
        ui->lineEdit_1->setText("I пара");
        ui->lineEdit_2->setText("8:30-10:05");
        ui->lineEdit_3->setText("II пара");
        ui->lineEdit_4->setText("10:25-12:00");
        ui->lineEdit_5->setText("III пара");
        ui->lineEdit_6->setText("12:20-13:55");
        ui->lineEdit_7->setText("IV пара");
        ui->lineEdit_8->setText("14:15-15:50");
        ui->lineEdit_9->setText("V пара");
        ui->lineEdit_10->setText("16:10-17:45");
        ui->lineEdit_13->setText("VI пара");
        ui->lineEdit_14->setText("18:05-19:40");
    }

    setMouseTracking(true);

    // таймеры на раззные события
    QTimer* timer = new QTimer();
    QTimer* ref = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    connect(timer, SIGNAL(timeout()), this, SLOT(changeTable()));
    timer->start(100);

    connect(tmr, SIGNAL(timeout()), this, SLOT(color()));
    tmr->start(1);

    connect(tbl, SIGNAL(timeout()), this, SLOT(table()));
    tbl->start(1);

    connect(ref, SIGNAL(timeout()), this, SLOT(on_saveButton_clicked()));
    ref->start(60000);
}

admin::~admin()
{
    delete ui;
}

// кнопка выхода
void admin::on_quitButton_clicked()
{
    int res = QMessageBox::information(this,"Выход", "Вы уверены?",QMessageBox::Yes | QMessageBox::No );
    switch(res)
    {
    case QMessageBox::Yes:
        admin::close();
        break;
    case QMessageBox::No:
        break;
    }
}

// смена факультета - смена списка групп
void admin::on_facultBox_currentIndexChanged(int index)
{
    QString name = "group" + ui->facultBox->currentText() + ".txt";
    QFile edit(name);
    if(edit.open(QIODevice::ReadOnly) && edit.exists())
    {
        QTextStream stream1(&edit);
        QString str;
        ui->groupBox->clear();
        while(!stream1.atEnd())
        {
            str = stream1.readLine();
            ui->groupBox->addItem(str);
        }
        edit.close();
    }
    else
    {
        ui->groupBox->clear();
    }
}

// проверка на изменения в группах/факультетах
void admin::onTimeout()
{
    QString str = "", temp1 = "", temp2 = "";
    QString name;

    QFile file("facult.txt");
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        while(!stream.atEnd())
        {
            str = stream.readLine();
            temp1 += str;
        }
    }
    file.close();

    str = "";
    for (int i = 0; i < ui->facultBox->count(); i++)
        str += ui->facultBox->itemText(i);

    if (str != temp1)
    {
        ui->facultBox->clear();
        QFile edit("facult.txt");
        if(edit.open(QIODevice::ReadOnly))
        {
            QTextStream stream1(&edit);
            while(!stream1.atEnd())
            {
                temp2 = stream1.readLine();
                ui->facultBox->addItem(temp2);
            }
        }
        edit.close();
    }

    temp1 = ""; temp2 = "";
    name = "group" + ui->facultBox->currentText() + ".txt";
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

    for (int i = 0; i < ui->groupBox->count(); i++)
    {
        str = ui->groupBox->itemText(i);
        temp2 += str;
    }

    // если не совпадение - заменить
    if (temp1 != temp2)
    {
        ui->groupBox->clear();
        QFile addGr(name);
        if (addGr.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&addGr);
            while (!stream.atEnd())
            {
                str = stream.readLine();
                ui->groupBox->addItem(str);
            }
        }
        addGr.close();
    }
}

// сохранение
void admin::on_saveButton_clicked()
{
    QString name;
    if(ui->week1Radio->isChecked())
        name = ui->facultBox->currentText() + ui->groupBox->currentText() + "1.txt";
    else
        name = ui->facultBox->currentText() + ui->groupBox->currentText() + "2.txt";

    QFile file(name);
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        for(int i = 0; i < ui->tableWidget->rowCount(); i++)
            for(int j = 0; j < ui->tableWidget->columnCount(); j++)
            {
                if (ui->tableWidget->item(i,j)->text().isEmpty())
                    stream << " " << endl;
                else
                    stream << ui->tableWidget->item(i,j)->text() << endl;
            }

        file.close();
    }

    if(ui->week1Radio->isChecked() == false)
        name = ui->facultBox->currentText() + ui->groupBox->currentText() + "1.txt";
    else
        name = ui->facultBox->currentText() + ui->groupBox->currentText() + "2.txt";

    QFile file2(name);
    if(!file2.exists())
        if(file2.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&file2);
            for(int i = 0; i < ui->tableWidget->rowCount(); i++)
                for(int j = 0; j < ui->tableWidget->columnCount(); j++)
                {
                    if (ui->tableWidget->item(i,j)->text().isEmpty())
                        stream << " " << endl;
                    else
                        stream << ui->tableWidget->item(i,j)->text() << endl;
                }

            file2.close();
        }

    QString name1 = "label" + name;
    QFile file1(name1);
    if(file1.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file1);
        stream << ui->lineEdit_1->text() << endl;
        stream << ui->lineEdit_2->text() << endl;
        stream << ui->lineEdit_3->text() << endl;
        stream << ui->lineEdit_4->text() << endl;
        stream << ui->lineEdit_5->text() << endl;
        stream << ui->lineEdit_6->text() << endl;
        stream << ui->lineEdit_7->text() << endl;
        stream << ui->lineEdit_8->text() << endl;
        stream << ui->lineEdit_9->text() << endl;
        stream << ui->lineEdit_10->text() << endl;
        stream << ui->lineEdit_13->text() << endl;
        stream << ui->lineEdit_14->text() << endl;

        file1.close();
    }
}

// смена расписания
void admin::changeTable()
{
    static QString path;
    QString path2;
    QString week;
    if(!ui->week1Radio->isDown())
        week = "1";
    else
        week = "2";

    path2 = ui->facultBox->currentText() + ui->groupBox->currentText() + week + ".txt";

    if (path != path2)
    {
        for(int i = 0; i < ui->tableWidget->rowCount(); i++)
            for(int j = 0; j < ui->tableWidget->columnCount(); j++)
            {
                QTableWidgetItem *str = new QTableWidgetItem(QString::fromLocal8Bit(" "));
                ui->tableWidget->setItem(i,j,str);
            }

        path = path2;
        QFile edit(path);
        if(edit.open(QIODevice::ReadOnly))
        {
            QTextStream stream1(&edit);
            for(int i = 0; i < ui->tableWidget->rowCount(); i++)
                for(int j = 0; j < ui->tableWidget->columnCount(); j++)
                {
                    QString itm = stream1.readLine();
                    QTableWidgetItem *line = new QTableWidgetItem();
                    line->setText(itm);
                    ui->tableWidget->setItem(i,j,line);
                }
        }
        edit.close();
    }
}

// смена расписания по выбору недели
void admin::on_week2Radio_clicked()
{
    ui->week2Radio->setChecked(true);
    ui->week1Radio->setChecked(false);

    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
        for(int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            QTableWidgetItem *str = new QTableWidgetItem(QString::fromLocal8Bit(" "));
            ui->tableWidget->setItem(i,j,str);
        }

    QString name = ui->facultBox->currentText() + ui->groupBox->currentText() + "2.txt";

    QFile edit(name);
    if(edit.open(QIODevice::ReadOnly))
    {
        QTextStream stream1(&edit);
        for(int i = 0; i < ui->tableWidget->rowCount(); i++)
            for(int j = 0; j < ui->tableWidget->columnCount(); j++)
            {
                QString itm = stream1.readLine();
                QTableWidgetItem *line = new QTableWidgetItem();
                line->setText(itm);
                ui->tableWidget->setItem(i,j,line);
            }
    }
    edit.close();
}

// смена расписания по выбору недели
void admin::on_week1Radio_clicked()
{
    ui->week1Radio->setChecked(true);
    ui->week2Radio->setChecked(false);

    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
        for(int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            QTableWidgetItem *str = new QTableWidgetItem(QString::fromLocal8Bit(" "));
            ui->tableWidget->setItem(i,j,str);
        }

    QString name = ui->facultBox->currentText() + ui->groupBox->currentText() + "1.txt";

    QFile edit(name);
    if(edit.open(QIODevice::ReadOnly))
    {
        QTextStream stream1(&edit);
        for(int i = 0; i < ui->tableWidget->rowCount(); i++)
            for(int j = 0; j < ui->tableWidget->columnCount(); j++)
            {
                QString itm = stream1.readLine();
                QTableWidgetItem *line = new QTableWidgetItem();
                line->setText(itm);
                ui->tableWidget->setItem(i,j,line);
            }
    }
    edit.close();
}

// вывод формы групп по кнопке
void admin::grp()
{
    group *groupForm = new group();
    groupForm->show();
}

// экспорт в ексел
void admin::on_exportButton_clicked()
{
    // выбор места сохранения файла
    QString name = QFileDialog::getSaveFileName(
                this,
                "Сохранить",
                "C://",
                "Excel File(*.xls)"
                );

    BasicExcel e;

    // создание таблицы
    e.New(1);
    e.RenameWorksheet("Sheet1", "Group");
    BasicExcelWorksheet* sheet = e.GetWorksheet("Group");

    // заполнение
    if (sheet)
    {
        for (size_t i = 0; i < ui->tableWidget->rowCount(); i++)
        {
            for (size_t j = 0; j < ui->tableWidget->columnCount(); j++)
            {
                QTableWidgetItem* itm = ui->tableWidget->item(i, j);
                QString itim = itm->text();
                //QTextCodec *cdc = QTextCodec::codecForName("CP1251");
                //QTextCodec::setCodecForLocale(cdc);
                char* same = itim.toUtf8().data();
                sheet->Cell(i, j)->SetString(same);
            }
        }
    }
    e.SaveAs(name.toUtf8().data());
}

// установка цвета
void admin::color()
{
    int counter = 0;

    for (int i = 1; i < ui->tableWidget->columnCount(); i+=2)
        for (int j = 0; j < ui->tableWidget->rowCount(); j++)
        {
            if (counter == 3)
            {
                j+=2;
                counter=0;
            }
            else
            {
                ui->tableWidget->item(j,i)->setBackgroundColor(Qt::gray);
                counter++;
            }
        }


    for (int i = 2; i < ui->tableWidget->columnCount(); i+=2)
    {
        counter = 0;
        for (int j = 3; j < ui->tableWidget->rowCount(); j++)
        {
            if (counter == 3)
            {
                j+=2;
                counter = 0;
            }
            else
            {
                ui->tableWidget->item(j,i)->setBackgroundColor(Qt::gray);
                counter++;
            }
        }
    }

    // установка тултипов
    for(int j = 1; j < ui->tableWidget->columnCount(); j++)
        for(int i = 0; i < ui->tableWidget->rowCount(); i++)
        {
            ui->tableWidget->item(i,j)->setToolTip("Предмет");
            i++;
            ui->tableWidget->item(i,j)->setToolTip("Преподователь");
            i++;
            ui->tableWidget->item(i,j)->setToolTip("Аудитория");
        }
}

// названия колонок
void admin::table()
{
    QTableWidgetItem *itm = new QTableWidgetItem();
    itm = new QTableWidgetItem(QString::fromUtf8(""));
    ui->tableWidget->setHorizontalHeaderItem(0,itm);
    itm = new QTableWidgetItem(QString::fromUtf8("Понедельник"));
    ui->tableWidget->setHorizontalHeaderItem(1,itm);
    itm = new QTableWidgetItem(QString::fromUtf8("Вторник"));
    ui->tableWidget->setHorizontalHeaderItem(2,itm);
    itm = new QTableWidgetItem(QString::fromUtf8("Среда"));
    ui->tableWidget->setHorizontalHeaderItem(3,itm);
    itm = new QTableWidgetItem(QString::fromUtf8("Четверг"));
    ui->tableWidget->setHorizontalHeaderItem(4,itm);
    itm = new QTableWidgetItem(QString::fromUtf8("Пятница"));
    ui->tableWidget->setHorizontalHeaderItem(5,itm);
    itm = new QTableWidgetItem(QString::fromUtf8("Суббота"));
    ui->tableWidget->setHorizontalHeaderItem(6,itm);

    tbl->stop();
}

// кнопка о программе
void admin::on_pushButton_clicked()
{
    about* abt = new about();
    abt->show();
}
