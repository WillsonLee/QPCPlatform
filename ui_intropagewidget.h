/********************************************************************************
** Form generated from reading UI file 'intropagewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTROPAGEWIDGET_H
#define UI_INTROPAGEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IntroPageWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *pathLineEdit;
    QLineEdit *nameLineEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *IntroPageWidget)
    {
        if (IntroPageWidget->objectName().isEmpty())
            IntroPageWidget->setObjectName(QStringLiteral("IntroPageWidget"));
        IntroPageWidget->resize(309, 150);
        gridLayout = new QGridLayout(IntroPageWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(IntroPageWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label = new QLabel(IntroPageWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        pathLineEdit = new QLineEdit(IntroPageWidget);
        pathLineEdit->setObjectName(QStringLiteral("pathLineEdit"));

        gridLayout->addWidget(pathLineEdit, 1, 1, 1, 1);

        nameLineEdit = new QLineEdit(IntroPageWidget);
        nameLineEdit->setObjectName(QStringLiteral("nameLineEdit"));

        gridLayout->addWidget(nameLineEdit, 0, 1, 1, 2);

        pushButton = new QPushButton(IntroPageWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMaximumSize(QSize(25, 16777215));

        gridLayout->addWidget(pushButton, 1, 2, 1, 1);

        gridLayout->setColumnStretch(0, 4);
        gridLayout->setColumnStretch(1, 8);
        gridLayout->setColumnStretch(2, 1);

        retranslateUi(IntroPageWidget);

        QMetaObject::connectSlotsByName(IntroPageWidget);
    } // setupUi

    void retranslateUi(QWidget *IntroPageWidget)
    {
        IntroPageWidget->setWindowTitle(QApplication::translate("IntroPageWidget", "Form", Q_NULLPTR));
        label_2->setText(QApplication::translate("IntroPageWidget", "path:", Q_NULLPTR));
        label->setText(QApplication::translate("IntroPageWidget", "project name:", Q_NULLPTR));
        nameLineEdit->setText(QString());
        pushButton->setText(QApplication::translate("IntroPageWidget", "...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class IntroPageWidget: public Ui_IntroPageWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTROPAGEWIDGET_H
