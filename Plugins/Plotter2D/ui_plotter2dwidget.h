/********************************************************************************
** Form generated from reading UI file 'plotter2dwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTTER2DWIDGET_H
#define UI_PLOTTER2DWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Plotter2DWidget
{
public:
    QVBoxLayout *verticalLayout;
    QCustomPlot *customPlot;
    QTextEdit *textEdit;

    void setupUi(QWidget *Plotter2DWidget)
    {
        if (Plotter2DWidget->objectName().isEmpty())
            Plotter2DWidget->setObjectName(QStringLiteral("Plotter2DWidget"));
        Plotter2DWidget->resize(291, 225);
        verticalLayout = new QVBoxLayout(Plotter2DWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(6, 6, 6, 6);
        customPlot = new QCustomPlot(Plotter2DWidget);
        customPlot->setObjectName(QStringLiteral("customPlot"));

        verticalLayout->addWidget(customPlot);

        textEdit = new QTextEdit(Plotter2DWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy);
        textEdit->setMaximumSize(QSize(16777215, 50));
        textEdit->setReadOnly(true);

        verticalLayout->addWidget(textEdit);

        verticalLayout->setStretch(0, 4);
        verticalLayout->setStretch(1, 1);

        retranslateUi(Plotter2DWidget);

        QMetaObject::connectSlotsByName(Plotter2DWidget);
    } // setupUi

    void retranslateUi(QWidget *Plotter2DWidget)
    {
        Plotter2DWidget->setWindowTitle(QApplication::translate("Plotter2DWidget", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Plotter2DWidget: public Ui_Plotter2DWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTTER2DWIDGET_H
