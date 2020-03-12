/********************************************************************************
** Form generated from reading UI file 'pcimagemaskwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PCIMAGEMASKWIDGET_H
#define UI_PCIMAGEMASKWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PCImageMaskWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *xOffsetEdit;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *yOffsetEdit;
    QCheckBox *offsetCheckBox;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *gsdEdit;
    QCheckBox *gsdCheckBox;
    QGroupBox *maskTypeGroup;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *radioButtonBinary;
    QRadioButton *radioButtonMulti;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *inverseCheckBox;

    void setupUi(QWidget *PCImageMaskWidget)
    {
        if (PCImageMaskWidget->objectName().isEmpty())
            PCImageMaskWidget->setObjectName(QStringLiteral("PCImageMaskWidget"));
        PCImageMaskWidget->resize(188, 168);
        verticalLayout = new QVBoxLayout(PCImageMaskWidget);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        groupBox = new QGroupBox(PCImageMaskWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(groupBox);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        frame_3 = new QFrame(frame);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_3);
        verticalLayout_3->setSpacing(1);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        frame_4 = new QFrame(frame_3);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_4);
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(frame_4);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        xOffsetEdit = new QLineEdit(frame_4);
        xOffsetEdit->setObjectName(QStringLiteral("xOffsetEdit"));

        horizontalLayout_2->addWidget(xOffsetEdit);


        verticalLayout_3->addWidget(frame_4);

        frame_5 = new QFrame(frame_3);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_5);
        horizontalLayout_3->setSpacing(2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(frame_5);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        yOffsetEdit = new QLineEdit(frame_5);
        yOffsetEdit->setObjectName(QStringLiteral("yOffsetEdit"));

        horizontalLayout_3->addWidget(yOffsetEdit);


        verticalLayout_3->addWidget(frame_5);


        horizontalLayout->addWidget(frame_3);

        offsetCheckBox = new QCheckBox(frame);
        offsetCheckBox->setObjectName(QStringLiteral("offsetCheckBox"));

        horizontalLayout->addWidget(offsetCheckBox);


        verticalLayout_2->addWidget(frame);

        frame_2 = new QFrame(groupBox);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_2);
        horizontalLayout_4->setSpacing(2);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(1, 1, 1, 1);
        label_4 = new QLabel(frame_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        gsdEdit = new QLineEdit(frame_2);
        gsdEdit->setObjectName(QStringLiteral("gsdEdit"));

        horizontalLayout_4->addWidget(gsdEdit);

        gsdCheckBox = new QCheckBox(frame_2);
        gsdCheckBox->setObjectName(QStringLiteral("gsdCheckBox"));

        horizontalLayout_4->addWidget(gsdCheckBox);


        verticalLayout_2->addWidget(frame_2);


        verticalLayout->addWidget(groupBox);

        maskTypeGroup = new QGroupBox(PCImageMaskWidget);
        maskTypeGroup->setObjectName(QStringLiteral("maskTypeGroup"));
        horizontalLayout_5 = new QHBoxLayout(maskTypeGroup);
        horizontalLayout_5->setSpacing(2);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(1, 1, 1, 1);
        radioButtonBinary = new QRadioButton(maskTypeGroup);
        radioButtonBinary->setObjectName(QStringLiteral("radioButtonBinary"));

        horizontalLayout_5->addWidget(radioButtonBinary);

        radioButtonMulti = new QRadioButton(maskTypeGroup);
        radioButtonMulti->setObjectName(QStringLiteral("radioButtonMulti"));

        horizontalLayout_5->addWidget(radioButtonMulti);


        verticalLayout->addWidget(maskTypeGroup);

        groupBox_3 = new QGroupBox(PCImageMaskWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        horizontalLayout_6 = new QHBoxLayout(groupBox_3);
        horizontalLayout_6->setSpacing(2);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(1, 1, 1, 1);
        inverseCheckBox = new QCheckBox(groupBox_3);
        inverseCheckBox->setObjectName(QStringLiteral("inverseCheckBox"));

        horizontalLayout_6->addWidget(inverseCheckBox);


        verticalLayout->addWidget(groupBox_3);


        retranslateUi(PCImageMaskWidget);

        QMetaObject::connectSlotsByName(PCImageMaskWidget);
    } // setupUi

    void retranslateUi(QWidget *PCImageMaskWidget)
    {
        PCImageMaskWidget->setWindowTitle(QApplication::translate("PCImageMaskWidget", "Form", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("PCImageMaskWidget", "Registration parameters", Q_NULLPTR));
        label->setText(QApplication::translate("PCImageMaskWidget", "Offset:", Q_NULLPTR));
        label_2->setText(QApplication::translate("PCImageMaskWidget", "X:", Q_NULLPTR));
        xOffsetEdit->setText(QString());
        label_3->setText(QApplication::translate("PCImageMaskWidget", "Y:", Q_NULLPTR));
        yOffsetEdit->setText(QString());
#ifndef QT_NO_TOOLTIP
        offsetCheckBox->setToolTip(QApplication::translate("PCImageMaskWidget", "auto offset calculate minimum x,y coord as offset", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        offsetCheckBox->setText(QApplication::translate("PCImageMaskWidget", "Auto", Q_NULLPTR));
        label_4->setText(QApplication::translate("PCImageMaskWidget", "Image GSD:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        gsdCheckBox->setToolTip(QApplication::translate("PCImageMaskWidget", "auto GSD calculate by range of the point cloud and size of the image", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        gsdCheckBox->setText(QApplication::translate("PCImageMaskWidget", "Auto", Q_NULLPTR));
        maskTypeGroup->setTitle(QApplication::translate("PCImageMaskWidget", "Mask type", Q_NULLPTR));
        radioButtonBinary->setText(QApplication::translate("PCImageMaskWidget", "binary", Q_NULLPTR));
        radioButtonMulti->setText(QApplication::translate("PCImageMaskWidget", "multi label", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("PCImageMaskWidget", "Others", Q_NULLPTR));
        inverseCheckBox->setText(QApplication::translate("PCImageMaskWidget", "inverse", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PCImageMaskWidget: public Ui_PCImageMaskWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PCIMAGEMASKWIDGET_H
