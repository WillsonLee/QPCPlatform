/********************************************************************************
** Form generated from reading UI file 'spacialclusterwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPACIALCLUSTERWIDGET_H
#define UI_SPACIALCLUSTERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpacialClusterWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QCheckBox *tolCheckBox;
    QLineEdit *tolLineEdit;

    void setupUi(QWidget *SpacialClusterWidget)
    {
        if (SpacialClusterWidget->objectName().isEmpty())
            SpacialClusterWidget->setObjectName(QStringLiteral("SpacialClusterWidget"));
        SpacialClusterWidget->resize(204, 36);
        horizontalLayout = new QHBoxLayout(SpacialClusterWidget);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        tolCheckBox = new QCheckBox(SpacialClusterWidget);
        tolCheckBox->setObjectName(QStringLiteral("tolCheckBox"));

        horizontalLayout->addWidget(tolCheckBox);

        tolLineEdit = new QLineEdit(SpacialClusterWidget);
        tolLineEdit->setObjectName(QStringLiteral("tolLineEdit"));

        horizontalLayout->addWidget(tolLineEdit);


        retranslateUi(SpacialClusterWidget);

        QMetaObject::connectSlotsByName(SpacialClusterWidget);
    } // setupUi

    void retranslateUi(QWidget *SpacialClusterWidget)
    {
        SpacialClusterWidget->setWindowTitle(QApplication::translate("SpacialClusterWidget", "Form", Q_NULLPTR));
        tolCheckBox->setText(QApplication::translate("SpacialClusterWidget", "Auto Tolerance:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SpacialClusterWidget: public Ui_SpacialClusterWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPACIALCLUSTERWIDGET_H
