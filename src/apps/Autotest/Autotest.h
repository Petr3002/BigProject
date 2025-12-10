#ifndef AUTOTEST_H
#define AUTOTEST_H

#include <QObject>

class Autotest : public QObject {
    Q_OBJECT
public:
    explicit Autotest(QObject *parent = nullptr);

private slots:
    void testFirstExample();
    void testSecondExample();
    void testThirdExample();
    void testThirdExample_data();
};


#endif // AUTOTEST_H

