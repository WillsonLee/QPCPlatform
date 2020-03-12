/********************************************************************************
** Form generated from reading UI file 'axtobthpluscwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AXTOBTHPLUSCWIDGET_H
#define UI_AXTOBTHPLUSCWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AXToBthPlusCWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *displayLabel;
    QFrame *frame;
    QFormLayout *formLayout;
    QLineEdit *aLineEdit;
    QLineEdit *bLineEdit;
    QLabel *label_5;
    QLabel *label_4;
    QLabel *label;
    QLineEdit *cLineEdit;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *okButton;
    QPushButton *resetButton;

    void setupUi(QWidget *AXToBthPlusCWidget)
    {
        if (AXToBthPlusCWidget->objectName().isEmpty())
            AXToBthPlusCWidget->setObjectName(QStringLiteral("AXToBthPlusCWidget"));
        AXToBthPlusCWidget->resize(269, 180);
        verticalLayout = new QVBoxLayout(AXToBthPlusCWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        displayLabel = new QLabel(AXToBthPlusCWidget);
        displayLabel->setObjectName(QStringLiteral("displayLabel"));

        verticalLayout->addWidget(displayLabel);

        frame = new QFrame(AXToBthPlusCWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        formLayout = new QFormLayout(frame);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setHorizontalSpacing(3);
        formLayout->setVerticalSpacing(3);
        formLayout->setContentsMargins(3, 3, 3, 3);
        aLineEdit = new QLineEdit(frame);
        aLineEdit->setObjectName(QStringLiteral("aLineEdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, aLineEdit);

        bLineEdit = new QLineEdit(frame);
        bLineEdit->setObjectName(QStringLiteral("bLineEdit"));

        formLayout->setWidget(5, QFormLayout::FieldRole, bLineEdit);

        label_5 = new QLabel(frame);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_5);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_4);

        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label);

        cLineEdit = new QLineEdit(frame);
        cLineEdit->setObjectName(QStringLiteral("cLineEdit"));

        formLayout->setWidget(7, QFormLayout::FieldRole, cLineEdit);


        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(AXToBthPlusCWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_2);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(3, 3, 3, 3);
        okButton = new QPushButton(frame_2);
        okButton->setObjectName(QStringLiteral("okButton"));

        horizontalLayout->addWidget(okButton);

        resetButton = new QPushButton(frame_2);
        resetButton->setObjectName(QStringLiteral("resetButton"));

        horizontalLayout->addWidget(resetButton);


        verticalLayout->addWidget(frame_2);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 6);
        verticalLayout->setStretch(2, 2);

        retranslateUi(AXToBthPlusCWidget);

        QMetaObject::connectSlotsByName(AXToBthPlusCWidget);
    } // setupUi

    void retranslateUi(QWidget *AXToBthPlusCWidget)
    {
        AXToBthPlusCWidget->setWindowTitle(QApplication::translate("AXToBthPlusCWidget", "Form", Q_NULLPTR));
        displayLabel->setText(QApplication::translate("AXToBthPlusCWidget", "calculate y=a*x^b+c", Q_NULLPTR));
        label_5->setText(QApplication::translate("AXToBthPlusCWidget", "c:", Q_NULLPTR));
        label_4->setText(QApplication::translate("AXToBthPlusCWidget", "b:", Q_NULLPTR));
        label->setText(QApplication::translate("AXToBthPlusCWidget", "a:", Q_NULLPTR));
        okButton->setText(QApplication::translate("AXToBthPlusCWidget", "OK", Q_NULLPTR));
        resetButton->setText(QApplication::translate("AXToBthPlusCWidget", "Reset", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AXToBthPlusCWidget: public Ui_AXToBthPlusCWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AXTOBTHPLUSCWIDGET_H
