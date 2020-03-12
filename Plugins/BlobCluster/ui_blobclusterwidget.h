/********************************************************************************
** Form generated from reading UI file 'blobclusterwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLOBCLUSTERWIDGET_H
#define UI_BLOBCLUSTERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BlobClusterWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QRadioButton *fourRadioButton;
    QRadioButton *eightRadioButton;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *depthComboBox;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *algorithmComboBox;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *speckleCheckBox;
    QLabel *label_2;
    QSpinBox *areaSpinBox;
    QLabel *label_3;

    void setupUi(QWidget *BlobClusterWidget)
    {
        if (BlobClusterWidget->objectName().isEmpty())
            BlobClusterWidget->setObjectName(QStringLiteral("BlobClusterWidget"));
        BlobClusterWidget->resize(205, 129);
        verticalLayout = new QVBoxLayout(BlobClusterWidget);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        groupBox = new QGroupBox(BlobClusterWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 1, 2, 1);
        fourRadioButton = new QRadioButton(groupBox);
        fourRadioButton->setObjectName(QStringLiteral("fourRadioButton"));

        horizontalLayout->addWidget(fourRadioButton);

        eightRadioButton = new QRadioButton(groupBox);
        eightRadioButton->setObjectName(QStringLiteral("eightRadioButton"));

        horizontalLayout->addWidget(eightRadioButton);


        verticalLayout->addWidget(groupBox);

        frame = new QFrame(BlobClusterWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setSpacing(3);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(2, 1, 2, 1);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        depthComboBox = new QComboBox(frame);
        depthComboBox->setObjectName(QStringLiteral("depthComboBox"));

        horizontalLayout_2->addWidget(depthComboBox);


        verticalLayout->addWidget(frame);

        frame_3 = new QFrame(BlobClusterWidget);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_3);
        horizontalLayout_4->setSpacing(3);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(2, 1, 2, 1);
        label_4 = new QLabel(frame_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        algorithmComboBox = new QComboBox(frame_3);
        algorithmComboBox->setObjectName(QStringLiteral("algorithmComboBox"));

        horizontalLayout_4->addWidget(algorithmComboBox);


        verticalLayout->addWidget(frame_3);

        frame_2 = new QFrame(BlobClusterWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_2);
        horizontalLayout_3->setSpacing(2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(2, 1, 2, 1);
        speckleCheckBox = new QCheckBox(frame_2);
        speckleCheckBox->setObjectName(QStringLiteral("speckleCheckBox"));

        horizontalLayout_3->addWidget(speckleCheckBox);

        label_2 = new QLabel(frame_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        areaSpinBox = new QSpinBox(frame_2);
        areaSpinBox->setObjectName(QStringLiteral("areaSpinBox"));
        areaSpinBox->setMinimum(1);
        areaSpinBox->setMaximum(10000);

        horizontalLayout_3->addWidget(areaSpinBox);

        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);


        verticalLayout->addWidget(frame_2);


        retranslateUi(BlobClusterWidget);

        QMetaObject::connectSlotsByName(BlobClusterWidget);
    } // setupUi

    void retranslateUi(QWidget *BlobClusterWidget)
    {
        BlobClusterWidget->setWindowTitle(QApplication::translate("BlobClusterWidget", "Form", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("BlobClusterWidget", "Neighbors", Q_NULLPTR));
        fourRadioButton->setText(QApplication::translate("BlobClusterWidget", "4-neighbors", Q_NULLPTR));
        eightRadioButton->setText(QApplication::translate("BlobClusterWidget", "8-neighbors", Q_NULLPTR));
        label->setText(QApplication::translate("BlobClusterWidget", "Output depth:", Q_NULLPTR));
        label_4->setText(QApplication::translate("BlobClusterWidget", "Algorithm:", Q_NULLPTR));
        speckleCheckBox->setText(QApplication::translate("BlobClusterWidget", "speckles\n"
"removal", Q_NULLPTR));
        label_2->setText(QApplication::translate("BlobClusterWidget", "(<=", Q_NULLPTR));
        label_3->setText(QApplication::translate("BlobClusterWidget", "pixels)", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BlobClusterWidget: public Ui_BlobClusterWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLOBCLUSTERWIDGET_H
