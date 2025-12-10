#include "Autotest.h"
#include <QTest>
#include "PlaneGeometry/PlaneOperations.h"
#include <cmath>
#include <qstring.h>

Autotest::Autotest(QObject *parent) : QObject(parent){}
void Autotest::testFirstExample(){
    double a1 = 2, a2 = 3;
    double res = pointProduct(a1, a2);
    double waitRes = 6;

    QVERIFY(fabs(res - waitRes) < 1e-6);
}

void Autotest::testSecondExample(){
    double a1 = 2.0, a2 = 3.0;
    double res = pointProduct(a1, a2);
    double waitRes = 6.0;

    QVERIFY2(fabs(res - waitRes) < 1e-6, "Misha, vsyo ne tak, davai po novoi");
    QCOMPARE(res, waitRes);
}

void Autotest::testThirdExample(){
    QFETCH(double, a);
    QFETCH(double, b);
    QFETCH(double, res);
    double actual = pointProduct(a, b);

    QCOMPARE(actual, res);
}

void Autotest::testThirdExample_data(){
    QTest::addColumn<double>("a");
    QTest::addColumn<double>("b");
    QTest::addColumn<double>("res");

    for (int i = 0; i < 10; i++) {
        QTest::newRow("aaaaaaaaaaaaa") << i * 2.0 << i + 3.0 << 2.0 * i * (i + 3);

    }
}
