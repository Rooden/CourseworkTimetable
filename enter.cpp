#include "enter.h"
#include "ui_enter.h"
#include "read.h"
#include "about.h"
#include "admin.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

enter::enter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::enter)
{
    ui->setupUi(this);

    // кнопка about
    about *abot = new about();
    connect(ui->aboutButton, SIGNAL(clicked()), abot, SLOT(show()));

    // кнопка  read only
    read *red = new read();
    connect(ui->readButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->readButton, SIGNAL(clicked()), red, SLOT(show()));

    // звездочками
    ui->passEdit->setEchoMode(QLineEdit::Password);
}

enter::~enter()
{
    delete ui;
}

// вход
void enter::on_enterButton_clicked()
{
    QString login = "";
    QString pass = "";
    QFile log("admin.txt");
    if(log.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&log);
        QString str;

        str = stream.readLine();
        login += str;

        str = stream.readLine();
        pass += str;

        log.close();
    }

    if (ui->loginEdit->text() == login && ui->passEdit->text() == pass)
    {
        admin *adm = new admin();
        adm->show();
        this->close();
    }
    else
    {
        QMessageBox::information(this, "Error", "Введен неправильно логин или пароль", QMessageBox::Yes);
    }
}
