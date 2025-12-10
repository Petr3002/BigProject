/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <drawwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    DrawWidget *widget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QRadioButton *RadioVectorPoint;
    QRadioButton *RadioVectorVector;
    QRadioButton *RadioPolygon;
    QPushButton *pushButton_2;
    QTextBrowser *textBrowser;
    QWidget *tab_2;
    QLineEdit *y_1;
    QLineEdit *lineEdit;
    QLineEdit *x_1;
    QLabel *label;
    QLineEdit *x_2;
    QLineEdit *y_2;
    QLineEdit *x_3;
    QLineEdit *y_3;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(855, 661);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 821, 581));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        widget = new DrawWidget(tab);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 20, 521, 501));
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(550, 20, 258, 316));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        RadioVectorPoint = new QRadioButton(layoutWidget);
        RadioVectorPoint->setObjectName(QString::fromUtf8("RadioVectorPoint"));

        verticalLayout->addWidget(RadioVectorPoint);

        RadioVectorVector = new QRadioButton(layoutWidget);
        RadioVectorVector->setObjectName(QString::fromUtf8("RadioVectorVector"));

        verticalLayout->addWidget(RadioVectorVector);

        RadioPolygon = new QRadioButton(layoutWidget);
        RadioPolygon->setObjectName(QString::fromUtf8("RadioPolygon"));

        verticalLayout->addWidget(RadioPolygon);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        textBrowser = new QTextBrowser(layoutWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        y_1 = new QLineEdit(tab_2);
        y_1->setObjectName(QString::fromUtf8("y_1"));
        y_1->setGeometry(QRect(20, 80, 211, 41));
        lineEdit = new QLineEdit(tab_2);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(280, 240, 113, 26));
        x_1 = new QLineEdit(tab_2);
        x_1->setObjectName(QString::fromUtf8("x_1"));
        x_1->setGeometry(QRect(20, 30, 211, 41));
        label = new QLabel(tab_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(310, 210, 66, 18));
        x_2 = new QLineEdit(tab_2);
        x_2->setObjectName(QString::fromUtf8("x_2"));
        x_2->setGeometry(QRect(250, 30, 211, 41));
        y_2 = new QLineEdit(tab_2);
        y_2->setObjectName(QString::fromUtf8("y_2"));
        y_2->setGeometry(QRect(250, 80, 211, 41));
        x_3 = new QLineEdit(tab_2);
        x_3->setObjectName(QString::fromUtf8("x_3"));
        x_3->setGeometry(QRect(480, 30, 211, 41));
        y_3 = new QLineEdit(tab_2);
        y_3->setObjectName(QString::fromUtf8("y_3"));
        y_3->setGeometry(QRect(480, 80, 211, 41));
        pushButton = new QPushButton(tab_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(290, 150, 88, 26));
        tabWidget->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 855, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        RadioVectorPoint->setText(QCoreApplication::translate("MainWindow", "\320\222\320\265\320\272\321\202\320\276\321\200 \320\270 \321\202\320\276\321\207\320\272\320\260", nullptr));
        RadioVectorVector->setText(QCoreApplication::translate("MainWindow", "2 \320\262\320\265\320\272\321\202\320\276\321\200\320\260", nullptr));
        RadioPolygon->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\273\320\270\320\263\320\276\320\275", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Answer", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\321\201\321\207\320\270\321\202\320\260\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
