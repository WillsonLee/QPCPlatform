/********************************************************************************
** Form generated from reading UI file 'convexhullwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONVEXHULLWIDGET_H
#define UI_CONVEXHULLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConvexHullWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QRadioButton *multiRadio;
    QRadioButton *binaryRadio;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *comboBox;

    void setupUi(QWidget *ConvexHullWidget)
    {
        if (ConvexHullWidget->objectName().isEmpty())
            ConvexHullWidget->setObjectName(QStringLiteral("ConvexHullWidget"));
        ConvexHullWidget->resize(162, 78);
        verticalLayout_2 = new QVBoxLayout(ConvexHullWidget);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, 2, 2, 2);
        groupBox = new QGroupBox(ConvexHullWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(4);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        multiRadio = new QRadioButton(groupBox);
        multiRadio->setObjectName(QStringLiteral("multiRadio"));

        horizontalLayout->addWidget(multiRadio);

        binaryRadio = new QRadioButton(groupBox);
        binaryRadio->setObjectName(QStringLiteral("binaryRadio"));

        horizontalLayout->addWidget(binaryRadio);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(ConvexHullWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(2, 2, 2, 2);
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        comboBox = new QComboBox(groupBox_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_2->addWidget(comboBox);


        verticalLayout_2->addWidget(groupBox_2);


        retranslateUi(ConvexHullWidget);

        QMetaObject::connectSlotsByName(ConvexHullWidget);
    } // setupUi

    void retranslateUi(QWidget *ConvexHullWidget)
    {
        ConvexHullWidget->setWindowTitle(QApplication::translate("ConvexHullWidget", "Form", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("ConvexHullWidget", "Mask Type", Q_NULLPTR));
        multiRadio->setText(QApplication::translate("ConvexHullWidget", "multi-label", Q_NULLPTR));
        binaryRadio->setText(QApplication::translate("ConvexHullWidget", "binary", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("ConvexHullWidget", "Convexhull", Q_NULLPTR));
        label->setText(QApplication::translate("ConvexHullWidget", "algorithm:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ConvexHullWidget: public Ui_ConvexHullWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONVEXHULLWIDGET_H
