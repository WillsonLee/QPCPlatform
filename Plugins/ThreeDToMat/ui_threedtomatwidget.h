/********************************************************************************
** Form generated from reading UI file 'threedtomatwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THREEDTOMATWIDGET_H
#define UI_THREEDTOMATWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ThreeDToMatWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *comboBox;

    void setupUi(QWidget *ThreeDToMatWidget)
    {
        if (ThreeDToMatWidget->objectName().isEmpty())
            ThreeDToMatWidget->setObjectName(QStringLiteral("ThreeDToMatWidget"));
        ThreeDToMatWidget->resize(102, 76);
        verticalLayout = new QVBoxLayout(ThreeDToMatWidget);
        verticalLayout->setSpacing(4);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        groupBox = new QGroupBox(ThreeDToMatWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(ThreeDToMatWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        comboBox = new QComboBox(groupBox_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_2->addWidget(comboBox);


        verticalLayout->addWidget(groupBox_2);


        retranslateUi(ThreeDToMatWidget);

        QMetaObject::connectSlotsByName(ThreeDToMatWidget);
    } // setupUi

    void retranslateUi(QWidget *ThreeDToMatWidget)
    {
        ThreeDToMatWidget->setWindowTitle(QApplication::translate("ThreeDToMatWidget", "Form", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("ThreeDToMatWidget", "GSD", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("ThreeDToMatWidget", "Mode", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ThreeDToMatWidget: public Ui_ThreeDToMatWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THREEDTOMATWIDGET_H
