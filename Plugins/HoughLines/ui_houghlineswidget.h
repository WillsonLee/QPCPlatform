/********************************************************************************
** Form generated from reading UI file 'houghlineswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOUGHLINESWIDGET_H
#define UI_HOUGHLINESWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HoughLinesWidget
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *rhoDoubleSpin;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDoubleSpinBox *thetaDoubleSpin;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpinBox *threshSpin;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSlider *minLengthSlider;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QSlider *maxGapSlider;

    void setupUi(QWidget *HoughLinesWidget)
    {
        if (HoughLinesWidget->objectName().isEmpty())
            HoughLinesWidget->setObjectName(QStringLiteral("HoughLinesWidget"));
        HoughLinesWidget->resize(215, 150);
        verticalLayout = new QVBoxLayout(HoughLinesWidget);
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        frame = new QFrame(HoughLinesWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        rhoDoubleSpin = new QDoubleSpinBox(frame);
        rhoDoubleSpin->setObjectName(QStringLiteral("rhoDoubleSpin"));
        rhoDoubleSpin->setMaximum(20);
        rhoDoubleSpin->setValue(1);

        horizontalLayout->addWidget(rhoDoubleSpin);


        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(HoughLinesWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setSpacing(3);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(2, 2, 2, 2);
        label_2 = new QLabel(frame_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        thetaDoubleSpin = new QDoubleSpinBox(frame_2);
        thetaDoubleSpin->setObjectName(QStringLiteral("thetaDoubleSpin"));
        thetaDoubleSpin->setMaximum(30);
        thetaDoubleSpin->setValue(1);

        horizontalLayout_2->addWidget(thetaDoubleSpin);


        verticalLayout->addWidget(frame_2);

        frame_3 = new QFrame(HoughLinesWidget);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_3);
        horizontalLayout_3->setSpacing(3);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(2, 2, 2, 2);
        label_3 = new QLabel(frame_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        threshSpin = new QSpinBox(frame_3);
        threshSpin->setObjectName(QStringLiteral("threshSpin"));
        threshSpin->setMinimum(1);
        threshSpin->setMaximum(10000);

        horizontalLayout_3->addWidget(threshSpin);


        verticalLayout->addWidget(frame_3);

        frame_4 = new QFrame(HoughLinesWidget);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_4);
        horizontalLayout_4->setSpacing(3);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(2, 2, 2, 2);
        label_4 = new QLabel(frame_4);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        minLengthSlider = new QSlider(frame_4);
        minLengthSlider->setObjectName(QStringLiteral("minLengthSlider"));
        minLengthSlider->setMinimum(2);
        minLengthSlider->setMaximum(100);
        minLengthSlider->setValue(6);
        minLengthSlider->setOrientation(Qt::Horizontal);
        minLengthSlider->setInvertedAppearance(false);
        minLengthSlider->setInvertedControls(false);
        minLengthSlider->setTickPosition(QSlider::NoTicks);

        horizontalLayout_4->addWidget(minLengthSlider);


        verticalLayout->addWidget(frame_4);

        frame_5 = new QFrame(HoughLinesWidget);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_5);
        horizontalLayout_5->setSpacing(3);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(2, 2, 2, 2);
        label_5 = new QLabel(frame_5);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        maxGapSlider = new QSlider(frame_5);
        maxGapSlider->setObjectName(QStringLiteral("maxGapSlider"));
        maxGapSlider->setMaximum(100);
        maxGapSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(maxGapSlider);


        verticalLayout->addWidget(frame_5);


        retranslateUi(HoughLinesWidget);

        QMetaObject::connectSlotsByName(HoughLinesWidget);
    } // setupUi

    void retranslateUi(QWidget *HoughLinesWidget)
    {
        HoughLinesWidget->setWindowTitle(QApplication::translate("HoughLinesWidget", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("HoughLinesWidget", "rho:", Q_NULLPTR));
        label_2->setText(QApplication::translate("HoughLinesWidget", "theta(in angle):", Q_NULLPTR));
        label_3->setText(QApplication::translate("HoughLinesWidget", "threshold(minimum vote):", Q_NULLPTR));
        label_4->setText(QApplication::translate("HoughLinesWidget", "min length:", Q_NULLPTR));
        label_5->setText(QApplication::translate("HoughLinesWidget", "maximum gap:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class HoughLinesWidget: public Ui_HoughLinesWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOUGHLINESWIDGET_H
