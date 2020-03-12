/********************************************************************************
** Form generated from reading UI file 'loopcontrolwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOOPCONTROLWIDGET_H
#define UI_LOOPCONTROLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoopControlWidget
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLCDNumber *lcdNumber;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *startButton;
    QPushButton *stopButton;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QSpinBox *totalSpinBox;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_3;
    QProgressBar *progressBar;

    void setupUi(QWidget *LoopControlWidget)
    {
        if (LoopControlWidget->objectName().isEmpty())
            LoopControlWidget->setObjectName(QStringLiteral("LoopControlWidget"));
        LoopControlWidget->resize(172, 113);
        verticalLayout = new QVBoxLayout(LoopControlWidget);
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        frame = new QFrame(LoopControlWidget);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMinimumSize(QSize(0, 0));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        lcdNumber = new QLCDNumber(frame);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lcdNumber->sizePolicy().hasHeightForWidth());
        lcdNumber->setSizePolicy(sizePolicy1);
        lcdNumber->setMinimumSize(QSize(0, 0));
        lcdNumber->setFrameShape(QFrame::StyledPanel);
        lcdNumber->setLineWidth(0);
        lcdNumber->setMidLineWidth(0);
        lcdNumber->setDigitCount(2);
        lcdNumber->setMode(QLCDNumber::Dec);
        lcdNumber->setSegmentStyle(QLCDNumber::Flat);

        horizontalLayout->addWidget(lcdNumber);


        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(LoopControlWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy2);
        frame_2->setMinimumSize(QSize(0, 25));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout_2->setContentsMargins(2, 2, 2, 2);
        startButton = new QPushButton(frame_2);
        startButton->setObjectName(QStringLiteral("startButton"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(startButton);

        stopButton = new QPushButton(frame_2);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        sizePolicy3.setHeightForWidth(stopButton->sizePolicy().hasHeightForWidth());
        stopButton->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(stopButton);


        verticalLayout->addWidget(frame_2);

        frame_4 = new QFrame(LoopControlWidget);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        sizePolicy2.setHeightForWidth(frame_4->sizePolicy().hasHeightForWidth());
        frame_4->setSizePolicy(sizePolicy2);
        frame_4->setMinimumSize(QSize(0, 20));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_4);
        horizontalLayout_4->setSpacing(4);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout_4->setContentsMargins(2, 0, 2, 0);
        label_2 = new QLabel(frame_4);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        totalSpinBox = new QSpinBox(frame_4);
        totalSpinBox->setObjectName(QStringLiteral("totalSpinBox"));

        horizontalLayout_4->addWidget(totalSpinBox);


        verticalLayout->addWidget(frame_4);

        frame_3 = new QFrame(LoopControlWidget);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        sizePolicy2.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy2);
        frame_3->setMinimumSize(QSize(0, 20));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_3);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout_3->setContentsMargins(2, 2, 2, 2);
        progressBar = new QProgressBar(frame_3);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy4);
        progressBar->setValue(24);

        horizontalLayout_3->addWidget(progressBar);


        verticalLayout->addWidget(frame_3);

        verticalLayout->setStretch(0, 10);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 1);

        retranslateUi(LoopControlWidget);

        QMetaObject::connectSlotsByName(LoopControlWidget);
    } // setupUi

    void retranslateUi(QWidget *LoopControlWidget)
    {
        LoopControlWidget->setWindowTitle(QApplication::translate("LoopControlWidget", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("LoopControlWidget", "current count:", Q_NULLPTR));
        startButton->setText(QApplication::translate("LoopControlWidget", "Start", Q_NULLPTR));
        stopButton->setText(QApplication::translate("LoopControlWidget", "Stop", Q_NULLPTR));
        label_2->setText(QApplication::translate("LoopControlWidget", "total count:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoopControlWidget: public Ui_LoopControlWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOOPCONTROLWIDGET_H
