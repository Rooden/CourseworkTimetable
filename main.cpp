#include "enter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    enter w;
    w.show();

    return a.exec();
}
