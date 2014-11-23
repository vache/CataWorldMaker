#include "cataworldmaker.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CataWorldMaker w;
    w.show();

    return a.exec();
}
