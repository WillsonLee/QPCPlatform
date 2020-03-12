/********************************************************************************
** Form generated from reading UI file 'flow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLOW_H
#define UI_FLOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Flow
{
public:

    void setupUi(QWidget *Flow)
    {
        if (Flow->objectName().isEmpty())
            Flow->setObjectName(QStringLiteral("Flow"));
        Flow->resize(400, 300);

        retranslateUi(Flow);

        QMetaObject::connectSlotsByName(Flow);
    } // setupUi

    void retranslateUi(QWidget *Flow)
    {
        Flow->setWindowTitle(QApplication::translate("Flow", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Flow: public Ui_Flow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLOW_H
