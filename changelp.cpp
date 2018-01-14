#include "changelp.h"
#include "ui_changelp.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

changeLP::changeLP(QWidget *parent) :
    QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint),
    ui(new Ui::changeLP)
{
    ui->setupUi(this);

    // звездочки при вводе
    ui->newPass->setEchoMode(QLineEdit::Password);
    ui->oldPass->setEchoMode(QLineEdit::Password);

    connect(ui->acceptButton, SIGNAL(clicked()), this, SLOT(accept()));
}

changeLP::~changeLP()
{
    delete ui;
}

// замена
void changeLP::on_acceptButton_clicked()
{
    ui->newLog->clear();
    ui->newPass->clear();
    ui->oldPass->clear();

    QString pass = "", login = "";
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

    if (ui->oldPass->text() == pass)
    {
        if(!ui->newLog->text().isEmpty() || !ui->newPass->text().isEmpty())
        {
            QFile updt("admin.txt");
            if(updt.open(QIODevice::WriteOnly))
            {
                QTextStream stream1(&updt);

                if(!ui->newLog->text().isEmpty())
                    stream1 << ui->newLog->text() << endl;
                else
                    stream1 << login << endl;

                if(!ui->newPass->text().isEmpty())
                    stream1 << ui->newPass->text() << endl;
                else
                    stream1 << pass << endl;

                updt.close();
            }
        }
    }
    else // при ошибке ввода старого пароля
    {
        QMessageBox::information(this, "Error", "Старый пароль введен неправильно!", QMessageBox::Yes);
    }
}
