#include "read.h"
#include "ui_read.h"
#include "about.h"
#include <QStandardItemModel>
#include <QFile>
#include <QTimer>
#include <QTextStream>
#include <QMessageBox>

QTimer* tim = new QTimer();
QTimer* tbl2 = new QTimer();

read::read(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::read)
{
    ui->setupUi(this);

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

    int col = 7, row = 18;
    ui->tableWidget->setRowCount(row);
    ui->tableWidget->setColumnCount(col);

    for (int i = 0; i < row; i++)
        for (int j = 0 ; j < col+1; j++)
        {
            QTableWidgetItem *str = new QTableWidgetItem(QString::fromLocal8Bit(" "));
            ui->tableWidget->setItem(i,j,str);
        }
    for (int i = 0; i < col+1; i++)
        ui->tableWidget->setColumnWidth(i,172);

    for (int i = 0; i < row; i+=3)
    {
        ui->tableWidget->setSpan(i,0,3,1);
    }

    for (int i = 0; i < ui->tableWidget->columnCount(); i++)
    {
        ui->tableWidget->setItemDelegateForColumn(i,new NonEditTableColumnDelegate());
    }

    QString week;
    if(!ui->week1Radio->isDown())
        week = "1";
    else
        week = "2";

    QString name = ui->facultBox->currentText() + ui->groupBox->currentText() + week + ".txt";
    QFile file(name);
    QTextStream stream(&file);
    if (file.open(QIODevice::ReadOnly))
    {
        for (int i = 0; i != ui->tableWidget->rowCount(); i++)
            for (int j = 0; j != ui->tableWidget->columnCount(); j++)
            {
                QString itm = stream.readLine();
                QTableWidgetItem *line = new QTableWidgetItem();
                line->setText(itm);
                ui->tableWidget->setItem(i,j,line);
            }
        file.close();
    }

    ui->tableWidget->verticalHeader()->hide();

    QString name1 = "label" + name;
    QFile file1(name1);
    if(file1.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file1);

        QString str = stream.readLine();
        ui->para1->setText(str);
        str = stream.readLine();
        ui->time1->setText(str);
        str = stream.readLine();
        ui->para2->setText(str);
        str = stream.readLine();
        ui->time2->setText(str);
        str = stream.readLine();
        ui->para3->setText(str);
        str = stream.readLine();
        ui->time3->setText(str);
        str = stream.readLine();
        ui->para4->setText(str);
        str = stream.readLine();
        ui->time4->setText(str);
        str = stream.readLine();
        ui->para5->setText(str);
        str = stream.readLine();
        ui->time5->setText(str);
        str = stream.readLine();
        ui->para6->setText(str);
        str = stream.readLine();
        ui->time6->setText(str);

        file1.close();
    }
    else
    {
        ui->para1->setText("I пара");
        ui->time1->setText("8:30-10:05");
        ui->para2->setText("II пара");
        ui->time2->setText("10:25-12:00");
        ui->para3->setText("III пара");
        ui->time3->setText("12:20-13:55");
        ui->para4->setText("IV пара");
        ui->time4->setText("14:15-15:50");
        ui->para5->setText("V пара");
        ui->time5->setText("16:10-17:45");
        ui->para6->setText("VI пара");
        ui->time6->setText("18:05-19:40");
    }


    QTimer* timer = new QTimer();
    connect(timer,
            SIGNAL(timeout()),
            this,
            SLOT(changeTable()));
    timer->start(100);

    connect(tim,
            SIGNAL(timeout()),
            this,
            SLOT(color()));
    tim->start(1);

    connect(tbl2,
            SIGNAL(timeout()),
            this,
            SLOT(table()));
    tbl2->start(1);
}

read::~read()
{
    delete ui;
}

void read::on_facultBox_currentIndexChanged(int index)
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

void read::on_week2Radio_clicked()
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

void read::on_week1Radio_clicked()
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

void read::changeTable()
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

void read::on_quitButton_clicked()
{
    int res = QMessageBox::information(this,"Выход", "Вы уверены?",QMessageBox::Yes | QMessageBox::No );
    switch(res)
    {
    case QMessageBox::Yes:
        read::close();
        break;
    case QMessageBox::No:
        break;
    }
}

void read::color()
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
}

void read::on_abtButton_clicked()
{
    about* abt = new about();
    abt->show();
}

void read::table()
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

    tbl2->stop();
}
