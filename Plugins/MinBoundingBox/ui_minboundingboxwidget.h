/********************************************************************************
** Form generated from reading UI file 'minboundingboxwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINBOUNDINGBOXWIDGET_H
#define UI_MINBOUNDINGBOXWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MinBoundingBoxWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *radioButtonBinary;
    QRadioButton *radioButtonMulti;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *checkBoxMerge;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QSpinBox *nodeSpinBox;

    void setupUi(QWidget *MinBoundingBoxWidget)
    {
        if (MinBoundingBoxWidget->objectName().isEmpty())
            MinBoundingBoxWidget->setObjectName(QStringLiteral("MinBoundingBoxWidget"));
        MinBoundingBoxWidget->resize(112, 119);
        verticalLayout = new QVBoxLayout(MinBoundingBoxWidget);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        groupBox = new QGroupBox(MinBoundingBoxWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, 1, 2, 1);
        radioButtonBinary = new QRadioButton(groupBox);
        radioButtonBinary->setObjectName(QStringLiteral("radioButtonBinary"));

        verticalLayout_2->addWidget(radioButtonBinary);

        radioButtonMulti = new QRadioButton(groupBox);
        radioButtonMulti->setObjectName(QStringLiteral("radioButtonMulti"));

        verticalLayout_2->addWidget(radioButtonMulti);


        verticalLayout->addWidget(groupBox);

        frame = new QFrame(MinBoundingBoxWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setSpacing(3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(2, 1, 2, 1);
        checkBoxMerge = new QCheckBox(frame);
        checkBoxMerge->setObjectName(QStringLiteral("checkBoxMerge"));

        verticalLayout_3->addWidget(checkBoxMerge);

        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_2);
        verticalLayout_4->setSpacing(3);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(2, 1, 2, 1);
        label = new QLabel(frame_2);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_4->addWidget(label);

        nodeSpinBox = new QSpinBox(frame_2);
        nodeSpinBox->setObjectName(QStringLiteral("nodeSpinBox"));
        nodeSpinBox->setMinimum(1);
        nodeSpinBox->setMaximum(4);

        verticalLayout_4->addWidget(nodeSpinBox);


        verticalLayout_3->addWidget(frame_2);


        verticalLayout->addWidget(frame);


        retranslateUi(MinBoundingBoxWidget);

        QMetaObject::connectSlotsByName(MinBoundingBoxWidget);
    } // setupUi

    void retranslateUi(QWidget *MinBoundingBoxWidget)
    {
        MinBoundingBoxWidget->setWindowTitle(QApplication::translate("MinBoundingBoxWidget", "Form", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MinBoundingBoxWidget", "Mode", Q_NULLPTR));
        radioButtonBinary->setText(QApplication::translate("MinBoundingBoxWidget", "binary", Q_NULLPTR));
        radioButtonMulti->setText(QApplication::translate("MinBoundingBoxWidget", "multi-label", Q_NULLPTR));
        checkBoxMerge->setText(QApplication::translate("MinBoundingBoxWidget", "merge overlap", Q_NULLPTR));
        label->setText(QApplication::translate("MinBoundingBoxWidget", "overlapped node:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MinBoundingBoxWidget: public Ui_MinBoundingBoxWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINBOUNDINGBOXWIDGET_H
