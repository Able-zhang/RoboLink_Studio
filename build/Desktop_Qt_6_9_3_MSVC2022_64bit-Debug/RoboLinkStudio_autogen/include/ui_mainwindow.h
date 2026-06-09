/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *labelBackendName;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnConnect;
    QPushButton *btnDisconnect;
    QPushButton *btnSendTestFrame;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *textEditLog;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnClearLog;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(900, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        labelBackendName = new QLabel(groupBox);
        labelBackendName->setObjectName("labelBackendName");
        labelBackendName->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        horizontalLayout->addWidget(labelBackendName);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnConnect = new QPushButton(groupBox);
        btnConnect->setObjectName("btnConnect");

        horizontalLayout->addWidget(btnConnect);

        btnDisconnect = new QPushButton(groupBox);
        btnDisconnect->setObjectName("btnDisconnect");
        btnDisconnect->setEnabled(false);

        horizontalLayout->addWidget(btnDisconnect);

        btnSendTestFrame = new QPushButton(groupBox);
        btnSendTestFrame->setObjectName("btnSendTestFrame");
        btnSendTestFrame->setEnabled(false);

        horizontalLayout->addWidget(btnSendTestFrame);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        textEditLog = new QTextEdit(groupBox_2);
        textEditLog->setObjectName("textEditLog");
        textEditLog->setReadOnly(true);
        QFont font;
        font.setFamilies({QString::fromUtf8("Consolas")});
        font.setPointSize(9);
        textEditLog->setFont(font);

        verticalLayout_2->addWidget(textEditLog);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btnClearLog = new QPushButton(groupBox_2);
        btnClearLog->setObjectName("btnClearLog");

        horizontalLayout_2->addWidget(btnClearLog);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(groupBox_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 900, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "RoboLinkStudio", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\345\220\216\347\253\257\346\216\247\345\210\266", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\345\220\216\347\253\257:", nullptr));
        labelBackendName->setText(QCoreApplication::translate("MainWindow", "MockBackend", nullptr));
        btnConnect->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245 (Connect)", nullptr));
        btnDisconnect->setText(QCoreApplication::translate("MainWindow", "\346\226\255\345\274\200 (Disconnect)", nullptr));
        btnSendTestFrame->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\346\265\213\350\257\225CAN\345\270\247", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\346\227\245\345\277\227\346\230\276\347\244\272", nullptr));
        btnClearLog->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\346\227\245\345\277\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
