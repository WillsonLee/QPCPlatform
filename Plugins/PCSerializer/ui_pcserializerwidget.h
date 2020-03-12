/********************************************************************************
** Form generated from reading UI file 'pcserializerwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PCSERIALIZERWIDGET_H
#define UI_PCSERIALIZERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PCSerializerWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *PCSerializerWidget)
    {
        if (PCSerializerWidget->objectName().isEmpty())
            PCSerializerWidget->setObjectName(QStringLiteral("PCSerializerWidget"));
        PCSerializerWidget->resize(216, 41);
        horizontalLayout = new QHBoxLayout(PCSerializerWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(PCSerializerWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(PCSerializerWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(PCSerializerWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(0, 0));
        pushButton->setMaximumSize(QSize(25, 16777215));

        horizontalLayout->addWidget(pushButton);


        retranslateUi(PCSerializerWidget);

        QMetaObject::connectSlotsByName(PCSerializerWidget);
    } // setupUi

    void retranslateUi(QWidget *PCSerializerWidget)
    {
        PCSerializerWidget->setWindowTitle(QApplication::translate("PCSerializerWidget", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("PCSerializerWidget", "folder:", Q_NULLPTR));
        pushButton->setText(QApplication::translate("PCSerializerWidget", "...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PCSerializerWidget: public Ui_PCSerializerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PCSERIALIZERWIDGET_H
