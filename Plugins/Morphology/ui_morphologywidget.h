/********************************************************************************
** Form generated from reading UI file 'morphologywidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MORPHOLOGYWIDGET_H
#define UI_MORPHOLOGYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MorphologyWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_11;
    QComboBox *morphTypeCombo;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *shapeComboBox;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *widthSpin;
    QLabel *label_3;
    QSpinBox *heightSpin;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLabel *label_5;
    QSpinBox *anchorXSpin;
    QLabel *label_6;
    QSpinBox *anchorYSpin;
    QLabel *label_7;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_8;
    QSpinBox *iterSpin;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_9;
    QComboBox *borderTypeCombo;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_10;
    QLineEdit *borderValueEdit;

    void setupUi(QWidget *MorphologyWidget)
    {
        if (MorphologyWidget->objectName().isEmpty())
            MorphologyWidget->setObjectName(QStringLiteral("MorphologyWidget"));
        MorphologyWidget->resize(236, 232);
        verticalLayout = new QVBoxLayout(MorphologyWidget);
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        groupBox_4 = new QGroupBox(MorphologyWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        horizontalLayout_7 = new QHBoxLayout(groupBox_4);
        horizontalLayout_7->setSpacing(2);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(1, 1, 1, 1);
        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_7->addWidget(label_11);

        morphTypeCombo = new QComboBox(groupBox_4);
        morphTypeCombo->setObjectName(QStringLiteral("morphTypeCombo"));

        horizontalLayout_7->addWidget(morphTypeCombo);


        verticalLayout->addWidget(groupBox_4);

        groupBox = new QGroupBox(MorphologyWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(1, 1, 1, 1);
        frame_3 = new QFrame(groupBox);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_3);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(frame_3);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        shapeComboBox = new QComboBox(frame_3);
        shapeComboBox->setObjectName(QStringLiteral("shapeComboBox"));

        horizontalLayout->addWidget(shapeComboBox);


        verticalLayout_2->addWidget(frame_3);

        frame = new QFrame(groupBox);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        widthSpin = new QSpinBox(frame);
        widthSpin->setObjectName(QStringLiteral("widthSpin"));
        widthSpin->setMinimum(2);

        horizontalLayout_2->addWidget(widthSpin);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QStringLiteral("label_3"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_3, 0, Qt::AlignHCenter);

        heightSpin = new QSpinBox(frame);
        heightSpin->setObjectName(QStringLiteral("heightSpin"));
        heightSpin->setMinimum(2);

        horizontalLayout_2->addWidget(heightSpin);


        verticalLayout_2->addWidget(frame);

        frame_2 = new QFrame(groupBox);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_2);
        horizontalLayout_3->setSpacing(2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(frame_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        label_5 = new QLabel(frame_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5, 0, Qt::AlignRight);

        anchorXSpin = new QSpinBox(frame_2);
        anchorXSpin->setObjectName(QStringLiteral("anchorXSpin"));
        anchorXSpin->setMinimum(-1);
        anchorXSpin->setValue(-1);

        horizontalLayout_3->addWidget(anchorXSpin);

        label_6 = new QLabel(frame_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_3->addWidget(label_6, 0, Qt::AlignHCenter);

        anchorYSpin = new QSpinBox(frame_2);
        anchorYSpin->setObjectName(QStringLiteral("anchorYSpin"));
        anchorYSpin->setMinimum(-1);
        anchorYSpin->setValue(-1);

        horizontalLayout_3->addWidget(anchorYSpin);

        label_7 = new QLabel(frame_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_3->addWidget(label_7, 0, Qt::AlignLeft);


        verticalLayout_2->addWidget(frame_2);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(MorphologyWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_2);
        horizontalLayout_4->setSpacing(2);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(1, 1, 1, 1);
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_4->addWidget(label_8);

        iterSpin = new QSpinBox(groupBox_2);
        iterSpin->setObjectName(QStringLiteral("iterSpin"));
        iterSpin->setMinimum(1);

        horizontalLayout_4->addWidget(iterSpin);


        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(MorphologyWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setSpacing(1);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(1, 1, 1, 1);
        frame_5 = new QFrame(groupBox_3);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_5);
        horizontalLayout_5->setSpacing(2);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(frame_5);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_5->addWidget(label_9);

        borderTypeCombo = new QComboBox(frame_5);
        borderTypeCombo->setObjectName(QStringLiteral("borderTypeCombo"));

        horizontalLayout_5->addWidget(borderTypeCombo);


        verticalLayout_3->addWidget(frame_5);

        frame_4 = new QFrame(groupBox_3);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        horizontalLayout_6 = new QHBoxLayout(frame_4);
        horizontalLayout_6->setSpacing(2);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(frame_4);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_6->addWidget(label_10);

        borderValueEdit = new QLineEdit(frame_4);
        borderValueEdit->setObjectName(QStringLiteral("borderValueEdit"));

        horizontalLayout_6->addWidget(borderValueEdit);


        verticalLayout_3->addWidget(frame_4);


        verticalLayout->addWidget(groupBox_3);


        retranslateUi(MorphologyWidget);

        QMetaObject::connectSlotsByName(MorphologyWidget);
    } // setupUi

    void retranslateUi(QWidget *MorphologyWidget)
    {
        MorphologyWidget->setWindowTitle(QApplication::translate("MorphologyWidget", "Form", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("MorphologyWidget", "Morphology", Q_NULLPTR));
        label_11->setText(QApplication::translate("MorphologyWidget", "morphology type:", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MorphologyWidget", "Kernel", Q_NULLPTR));
        label->setText(QApplication::translate("MorphologyWidget", "shape:", Q_NULLPTR));
        label_2->setText(QApplication::translate("MorphologyWidget", "size:", Q_NULLPTR));
        label_3->setText(QApplication::translate("MorphologyWidget", "\303\227", Q_NULLPTR));
        label_4->setText(QApplication::translate("MorphologyWidget", "anchor:", Q_NULLPTR));
        label_5->setText(QApplication::translate("MorphologyWidget", "(", Q_NULLPTR));
        label_6->setText(QApplication::translate("MorphologyWidget", ",", Q_NULLPTR));
        label_7->setText(QApplication::translate("MorphologyWidget", ")", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MorphologyWidget", "Iterations", Q_NULLPTR));
        label_8->setText(QApplication::translate("MorphologyWidget", "number of iterations:", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MorphologyWidget", "Border", Q_NULLPTR));
        label_9->setText(QApplication::translate("MorphologyWidget", "border type:", Q_NULLPTR));
        label_10->setText(QApplication::translate("MorphologyWidget", "border value:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        borderValueEdit->setToolTip(QApplication::translate("MorphologyWidget", "value divided by comma", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class MorphologyWidget: public Ui_MorphologyWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MORPHOLOGYWIDGET_H
