#include "loader.h"
#include "ui_loader.h"
#include <QTimer>

static int ld = 0;
static int counter = 0;

QTimer* asd = new QTimer();

loader::loader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loader)
{
    ui->setupUi(this);

    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);

    connect(asd,
            SIGNAL(timeout()),
            this,
            SLOT(load()));
    asd->start(1000);
}

loader::~loader()
{
    delete ui;
}

void loader::load()
{
    ld += 100/9;
    ui->progressBar->setValue(ld);
    counter++;

    if (counter == 9)
    {
        ld = 100;
        ui->progressBar->setValue(ld);
        loader::close();
    }
}
