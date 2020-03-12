/********************************************************************************
** Form generated from reading UI file 'colormapwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORMAPWIDGET_H
#define UI_COLORMAPWIDGET_H

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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <customlabel.h>

QT_BEGIN_NAMESPACE

class Ui_ColormapWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxMode;
    QHBoxLayout *horizontalLayout;
    QRadioButton *rdBttnRandom;
    QRadioButton *rdBttnScale;
    QGroupBox *groupBoxScale;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QSpinBox *spnBxBins;
    QCheckBox *chckBxAuto;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QComboBox *cmbBxColormap;
    QPushButton *pshBttnMinColor;
    QPushButton *pshBttnMaxColor;
    QGroupBox *groupBoxPreview;
    QHBoxLayout *horizontalLayout_2;
    CustomLabel *lblPreview;

    void setupUi(QWidget *ColormapWidget)
    {
        if (ColormapWidget->objectName().isEmpty())
            ColormapWidget->setObjectName(QStringLiteral("ColormapWidget"));
        ColormapWidget->resize(204, 153);
        verticalLayout = new QVBoxLayout(ColormapWidget);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        groupBoxMode = new QGroupBox(ColormapWidget);
        groupBoxMode->setObjectName(QStringLiteral("groupBoxMode"));
        horizontalLayout = new QHBoxLayout(groupBoxMode);
        horizontalLayout->setSpacing(4);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 1, 2, 1);
        rdBttnRandom = new QRadioButton(groupBoxMode);
        rdBttnRandom->setObjectName(QStringLiteral("rdBttnRandom"));

        horizontalLayout->addWidget(rdBttnRandom);

        rdBttnScale = new QRadioButton(groupBoxMode);
        rdBttnScale->setObjectName(QStringLiteral("rdBttnScale"));

        horizontalLayout->addWidget(rdBttnScale);


        verticalLayout->addWidget(groupBoxMode);

        groupBoxScale = new QGroupBox(ColormapWidget);
        groupBoxScale->setObjectName(QStringLiteral("groupBoxScale"));
        verticalLayout_2 = new QVBoxLayout(groupBoxScale);
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, 1, 2, 1);
        frame = new QFrame(groupBoxScale);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame);
        horizontalLayout_3->setSpacing(2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(2, 1, 2, 1);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        spnBxBins = new QSpinBox(frame);
        spnBxBins->setObjectName(QStringLiteral("spnBxBins"));
        spnBxBins->setMinimum(1);
        spnBxBins->setMaximum(2000);

        horizontalLayout_3->addWidget(spnBxBins);

        chckBxAuto = new QCheckBox(frame);
        chckBxAuto->setObjectName(QStringLiteral("chckBxAuto"));

        horizontalLayout_3->addWidget(chckBxAuto, 0, Qt::AlignHCenter);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 4);
        horizontalLayout_3->setStretch(2, 2);

        verticalLayout_2->addWidget(frame);

        frame_2 = new QFrame(groupBoxScale);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_2);
        horizontalLayout_4->setSpacing(2);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(2, 1, 2, 1);
        label_2 = new QLabel(frame_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        cmbBxColormap = new QComboBox(frame_2);
        cmbBxColormap->setObjectName(QStringLiteral("cmbBxColormap"));

        horizontalLayout_4->addWidget(cmbBxColormap);

        pshBttnMinColor = new QPushButton(frame_2);
        pshBttnMinColor->setObjectName(QStringLiteral("pshBttnMinColor"));
        pshBttnMinColor->setMaximumSize(QSize(20, 16777215));

        horizontalLayout_4->addWidget(pshBttnMinColor);

        pshBttnMaxColor = new QPushButton(frame_2);
        pshBttnMaxColor->setObjectName(QStringLiteral("pshBttnMaxColor"));
        pshBttnMaxColor->setMaximumSize(QSize(20, 16777215));

        horizontalLayout_4->addWidget(pshBttnMaxColor);

        horizontalLayout_4->setStretch(0, 2);
        horizontalLayout_4->setStretch(1, 3);
        horizontalLayout_4->setStretch(2, 1);
        horizontalLayout_4->setStretch(3, 1);

        verticalLayout_2->addWidget(frame_2);


        verticalLayout->addWidget(groupBoxScale);

        groupBoxPreview = new QGroupBox(ColormapWidget);
        groupBoxPreview->setObjectName(QStringLiteral("groupBoxPreview"));
        horizontalLayout_2 = new QHBoxLayout(groupBoxPreview);
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(6, 3, 6, 3);
        lblPreview = new CustomLabel(groupBoxPreview);
        lblPreview->setObjectName(QStringLiteral("lblPreview"));
        lblPreview->setMinimumSize(QSize(0, 20));

        horizontalLayout_2->addWidget(lblPreview);


        verticalLayout->addWidget(groupBoxPreview);


        retranslateUi(ColormapWidget);

        QMetaObject::connectSlotsByName(ColormapWidget);
    } // setupUi

    void retranslateUi(QWidget *ColormapWidget)
    {
        ColormapWidget->setWindowTitle(QApplication::translate("ColormapWidget", "Form", Q_NULLPTR));
        groupBoxMode->setTitle(QApplication::translate("ColormapWidget", "Mode", Q_NULLPTR));
        rdBttnRandom->setText(QApplication::translate("ColormapWidget", "Random Corlor", Q_NULLPTR));
        rdBttnScale->setText(QApplication::translate("ColormapWidget", "Color Scale", Q_NULLPTR));
        groupBoxScale->setTitle(QApplication::translate("ColormapWidget", "Color scale", Q_NULLPTR));
        label->setText(QApplication::translate("ColormapWidget", "bins:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chckBxAuto->setToolTip(QApplication::translate("ColormapWidget", "unique color for each gray level", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        chckBxAuto->setText(QApplication::translate("ColormapWidget", "auto", Q_NULLPTR));
        label_2->setText(QApplication::translate("ColormapWidget", "colormap:", Q_NULLPTR));
        pshBttnMinColor->setText(QString());
        pshBttnMaxColor->setText(QString());
        groupBoxPreview->setTitle(QApplication::translate("ColormapWidget", "Preview", Q_NULLPTR));
        lblPreview->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ColormapWidget: public Ui_ColormapWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORMAPWIDGET_H
