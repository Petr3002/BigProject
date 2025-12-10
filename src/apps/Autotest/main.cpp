#include <QCoreApplication>
#include <QTest>
#include "Autotest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Autotest test;
    return QTest::qExec(&test);
}
