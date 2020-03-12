/********************************************************************************
** Form generated from reading UI file 'histogramwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTOGRAMWIDGET_H
#define UI_HISTOGRAMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HistogramWidget
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *spinBoxChannels;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBoxNorm;
    QCheckBox *checkBoxAccumu;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radioButtonLeft;
    QRadioButton *radioButtonMiddle;
    QRadioButton *radioButtonRight;
    QGroupBox *groupBox_1;
    QGridLayout *gridLayout;
    QFrame *frame_3;
    QGridLayout *gridLayout_3;
    QLineEdit *lineEditMax1;
    QLabel *label_3;
    QLineEdit *lineEditMin1;
    QLabel *label_4;
    QCheckBox *checkBoxAuto1;
    QLabel *label_2;
    QSpinBox *spinBoxBins1;
    QLabel *label_8;
    QComboBox *comboBoxChannel1;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QSpinBox *spinBoxBins2;
    QComboBox *comboBoxChannel2;
    QLabel *label_9;
    QFrame *frame_4;
    QGridLayout *gridLayout_4;
    QLineEdit *lineEditMin2;
    QLabel *label_6;
    QLineEdit *lineEditMax2;
    QLabel *label_7;
    QCheckBox *checkBoxAuto2;

    void setupUi(QWidget *HistogramWidget)
    {
        if (HistogramWidget->objectName().isEmpty())
            HistogramWidget->setObjectName(QStringLiteral("HistogramWidget"));
        HistogramWidget->resize(177, 362);
        verticalLayout = new QVBoxLayout(HistogramWidget);
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        frame = new QFrame(HistogramWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(4);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        spinBoxChannels = new QSpinBox(frame);
        spinBoxChannels->setObjectName(QStringLiteral("spinBoxChannels"));
        spinBoxChannels->setMinimum(1);
        spinBoxChannels->setMaximum(2);

        horizontalLayout->addWidget(spinBoxChannels);


        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(HistogramWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setSpacing(4);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        checkBoxNorm = new QCheckBox(frame_2);
        checkBoxNorm->setObjectName(QStringLiteral("checkBoxNorm"));

        horizontalLayout_2->addWidget(checkBoxNorm);

        checkBoxAccumu = new QCheckBox(frame_2);
        checkBoxAccumu->setObjectName(QStringLiteral("checkBoxAccumu"));

        horizontalLayout_2->addWidget(checkBoxAccumu);


        verticalLayout->addWidget(frame_2);

        groupBox = new QGroupBox(HistogramWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout_3 = new QHBoxLayout(groupBox);
        horizontalLayout_3->setSpacing(4);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(2, 2, 2, 2);
        radioButtonLeft = new QRadioButton(groupBox);
        radioButtonLeft->setObjectName(QStringLiteral("radioButtonLeft"));

        horizontalLayout_3->addWidget(radioButtonLeft);

        radioButtonMiddle = new QRadioButton(groupBox);
        radioButtonMiddle->setObjectName(QStringLiteral("radioButtonMiddle"));

        horizontalLayout_3->addWidget(radioButtonMiddle);

        radioButtonRight = new QRadioButton(groupBox);
        radioButtonRight->setObjectName(QStringLiteral("radioButtonRight"));

        horizontalLayout_3->addWidget(radioButtonRight);


        verticalLayout->addWidget(groupBox);

        groupBox_1 = new QGroupBox(HistogramWidget);
        groupBox_1->setObjectName(QStringLiteral("groupBox_1"));
        gridLayout = new QGridLayout(groupBox_1);
        gridLayout->setSpacing(4);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(2, 2, 2, 2);
        frame_3 = new QFrame(groupBox_1);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setMinimumSize(QSize(0, 0));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(2);
        gridLayout_3->setVerticalSpacing(4);
        gridLayout_3->setContentsMargins(2, 2, 2, 2);
        lineEditMax1 = new QLineEdit(frame_3);
        lineEditMax1->setObjectName(QStringLiteral("lineEditMax1"));

        gridLayout_3->addWidget(lineEditMax1, 2, 1, 1, 1);

        label_3 = new QLabel(frame_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_3->addWidget(label_3, 1, 0, 1, 1);

        lineEditMin1 = new QLineEdit(frame_3);
        lineEditMin1->setObjectName(QStringLiteral("lineEditMin1"));

        gridLayout_3->addWidget(lineEditMin1, 1, 1, 1, 1);

        label_4 = new QLabel(frame_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_3->addWidget(label_4, 2, 0, 1, 1);

        checkBoxAuto1 = new QCheckBox(frame_3);
        checkBoxAuto1->setObjectName(QStringLiteral("checkBoxAuto1"));

        gridLayout_3->addWidget(checkBoxAuto1, 0, 0, 1, 2);


        gridLayout->addWidget(frame_3, 4, 0, 1, 2);

        label_2 = new QLabel(groupBox_1);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        spinBoxBins1 = new QSpinBox(groupBox_1);
        spinBoxBins1->setObjectName(QStringLiteral("spinBoxBins1"));
        spinBoxBins1->setMinimum(1);
        spinBoxBins1->setMaximum(10000);

        gridLayout->addWidget(spinBoxBins1, 1, 1, 1, 1);

        label_8 = new QLabel(groupBox_1);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 0, 0, 1, 1);

        comboBoxChannel1 = new QComboBox(groupBox_1);
        comboBoxChannel1->setObjectName(QStringLiteral("comboBoxChannel1"));

        gridLayout->addWidget(comboBoxChannel1, 0, 1, 1, 1);

        frame_3->raise();
        spinBoxBins1->raise();
        label_2->raise();
        label_8->raise();
        comboBoxChannel1->raise();

        verticalLayout->addWidget(groupBox_1);

        groupBox_2 = new QGroupBox(HistogramWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(4);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(2, 2, 2, 2);
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

        spinBoxBins2 = new QSpinBox(groupBox_2);
        spinBoxBins2->setObjectName(QStringLiteral("spinBoxBins2"));
        spinBoxBins2->setMinimum(1);
        spinBoxBins2->setMaximum(10000);

        gridLayout_2->addWidget(spinBoxBins2, 1, 1, 1, 1);

        comboBoxChannel2 = new QComboBox(groupBox_2);
        comboBoxChannel2->setObjectName(QStringLiteral("comboBoxChannel2"));

        gridLayout_2->addWidget(comboBoxChannel2, 0, 1, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 0, 0, 1, 1);

        frame_4 = new QFrame(groupBox_2);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setMinimumSize(QSize(0, 0));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame_4);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setHorizontalSpacing(2);
        gridLayout_4->setVerticalSpacing(4);
        gridLayout_4->setContentsMargins(2, 2, 2, 2);
        lineEditMin2 = new QLineEdit(frame_4);
        lineEditMin2->setObjectName(QStringLiteral("lineEditMin2"));

        gridLayout_4->addWidget(lineEditMin2, 1, 1, 1, 1);

        label_6 = new QLabel(frame_4);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_4->addWidget(label_6, 1, 0, 1, 1);

        lineEditMax2 = new QLineEdit(frame_4);
        lineEditMax2->setObjectName(QStringLiteral("lineEditMax2"));

        gridLayout_4->addWidget(lineEditMax2, 3, 1, 1, 1);

        label_7 = new QLabel(frame_4);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_4->addWidget(label_7, 2, 0, 2, 2);

        checkBoxAuto2 = new QCheckBox(frame_4);
        checkBoxAuto2->setObjectName(QStringLiteral("checkBoxAuto2"));

        gridLayout_4->addWidget(checkBoxAuto2, 0, 0, 1, 2);


        gridLayout_2->addWidget(frame_4, 2, 0, 1, 2);

        frame_4->raise();
        label_5->raise();
        spinBoxBins2->raise();
        label_9->raise();
        comboBoxChannel2->raise();

        verticalLayout->addWidget(groupBox_2);


        retranslateUi(HistogramWidget);

        QMetaObject::connectSlotsByName(HistogramWidget);
    } // setupUi

    void retranslateUi(QWidget *HistogramWidget)
    {
        HistogramWidget->setWindowTitle(QApplication::translate("HistogramWidget", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("HistogramWidget", "number of channels:", Q_NULLPTR));
        checkBoxNorm->setText(QApplication::translate("HistogramWidget", "normalize", Q_NULLPTR));
        checkBoxAccumu->setText(QApplication::translate("HistogramWidget", "accumulate", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("HistogramWidget", "Bins", Q_NULLPTR));
        radioButtonLeft->setText(QApplication::translate("HistogramWidget", "Left", Q_NULLPTR));
        radioButtonMiddle->setText(QApplication::translate("HistogramWidget", "Middle", Q_NULLPTR));
        radioButtonRight->setText(QApplication::translate("HistogramWidget", "Right", Q_NULLPTR));
        groupBox_1->setTitle(QApplication::translate("HistogramWidget", "First channel", Q_NULLPTR));
        label_3->setText(QApplication::translate("HistogramWidget", "min:", Q_NULLPTR));
        label_4->setText(QApplication::translate("HistogramWidget", "max:", Q_NULLPTR));
        checkBoxAuto1->setText(QApplication::translate("HistogramWidget", "Auto determin", Q_NULLPTR));
        label_2->setText(QApplication::translate("HistogramWidget", "bins:", Q_NULLPTR));
        label_8->setText(QApplication::translate("HistogramWidget", "channel:", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("HistogramWidget", "Second channel", Q_NULLPTR));
        label_5->setText(QApplication::translate("HistogramWidget", "bins:", Q_NULLPTR));
        label_9->setText(QApplication::translate("HistogramWidget", "channel:", Q_NULLPTR));
        label_6->setText(QApplication::translate("HistogramWidget", "min:", Q_NULLPTR));
        label_7->setText(QApplication::translate("HistogramWidget", "max:", Q_NULLPTR));
        checkBoxAuto2->setText(QApplication::translate("HistogramWidget", "Auto determin", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class HistogramWidget: public Ui_HistogramWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTOGRAMWIDGET_H
