/********************************************************************************
** Form generated from reading UI file 'gammatransformwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMMATRANSFORMWIDGET_H
#define UI_GAMMATRANSFORMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GammaTransformWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox;

    void setupUi(QWidget *GammaTransformWidget)
    {
        if (GammaTransformWidget->objectName().isEmpty())
            GammaTransformWidget->setObjectName(QStringLiteral("GammaTransformWidget"));
        GammaTransformWidget->resize(100, 24);
        horizontalLayout = new QHBoxLayout(GammaTransformWidget);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        label = new QLabel(GammaTransformWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        doubleSpinBox = new QDoubleSpinBox(GammaTransformWidget);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setDecimals(2);
        doubleSpinBox->setMinimum(0.01);
        doubleSpinBox->setMaximum(100);

        horizontalLayout->addWidget(doubleSpinBox);


        retranslateUi(GammaTransformWidget);

        QMetaObject::connectSlotsByName(GammaTransformWidget);
    } // setupUi

    void retranslateUi(QWidget *GammaTransformWidget)
    {
        GammaTransformWidget->setWindowTitle(QApplication::translate("GammaTransformWidget", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("GammaTransformWidget", "Gamma:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GammaTransformWidget: public Ui_GammaTransformWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMMATRANSFORMWIDGET_H
