/********************************************************************************
** Form generated from reading UI file 'matthresholdwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATTHRESHOLDWIDGET_H
#define UI_MATTHRESHOLDWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MatThresholdWidget
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *threshEdit;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *maxSpin;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *typesCombo;

    void setupUi(QWidget *MatThresholdWidget)
    {
        if (MatThresholdWidget->objectName().isEmpty())
            MatThresholdWidget->setObjectName(QStringLiteral("MatThresholdWidget"));
        MatThresholdWidget->resize(159, 80);
        verticalLayout = new QVBoxLayout(MatThresholdWidget);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        frame = new QFrame(MatThresholdWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        threshEdit = new QLineEdit(frame);
        threshEdit->setObjectName(QStringLiteral("threshEdit"));

        horizontalLayout->addWidget(threshEdit);


        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(MatThresholdWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(frame_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        maxSpin = new QSpinBox(frame_2);
        maxSpin->setObjectName(QStringLiteral("maxSpin"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(maxSpin->sizePolicy().hasHeightForWidth());
        maxSpin->setSizePolicy(sizePolicy);
        maxSpin->setMaximum(255);

        horizontalLayout_2->addWidget(maxSpin);


        verticalLayout->addWidget(frame_2);

        frame_3 = new QFrame(MatThresholdWidget);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_3);
        horizontalLayout_3->setSpacing(2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(frame_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        typesCombo = new QComboBox(frame_3);
        typesCombo->setObjectName(QStringLiteral("typesCombo"));
        sizePolicy.setHeightForWidth(typesCombo->sizePolicy().hasHeightForWidth());
        typesCombo->setSizePolicy(sizePolicy);
        typesCombo->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_3->addWidget(typesCombo);


        verticalLayout->addWidget(frame_3);


        retranslateUi(MatThresholdWidget);

        QMetaObject::connectSlotsByName(MatThresholdWidget);
    } // setupUi

    void retranslateUi(QWidget *MatThresholdWidget)
    {
        MatThresholdWidget->setWindowTitle(QApplication::translate("MatThresholdWidget", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("MatThresholdWidget", "Thresh:", Q_NULLPTR));
        label_2->setText(QApplication::translate("MatThresholdWidget", "Max:", Q_NULLPTR));
        label_3->setText(QApplication::translate("MatThresholdWidget", "Type:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MatThresholdWidget: public Ui_MatThresholdWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATTHRESHOLDWIDGET_H
