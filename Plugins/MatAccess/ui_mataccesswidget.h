/********************************************************************************
** Form generated from reading UI file 'mataccesswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATACCESSWIDGET_H
#define UI_MATACCESSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MatAccessWidget
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *rowLabel;
    QSpinBox *rowSpin;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *colLabel;
    QSpinBox *colSpin;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *chaLabel;
    QSpinBox *channelSpin;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLabel *depthLabel;

    void setupUi(QWidget *MatAccessWidget)
    {
        if (MatAccessWidget->objectName().isEmpty())
            MatAccessWidget->setObjectName(QStringLiteral("MatAccessWidget"));
        MatAccessWidget->resize(130, 94);
        verticalLayout = new QVBoxLayout(MatAccessWidget);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        frame = new QFrame(MatAccessWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        rowLabel = new QLabel(frame);
        rowLabel->setObjectName(QStringLiteral("rowLabel"));

        horizontalLayout->addWidget(rowLabel);

        rowSpin = new QSpinBox(frame);
        rowSpin->setObjectName(QStringLiteral("rowSpin"));

        horizontalLayout->addWidget(rowSpin);


        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(MatAccessWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        colLabel = new QLabel(frame_2);
        colLabel->setObjectName(QStringLiteral("colLabel"));

        horizontalLayout_2->addWidget(colLabel);

        colSpin = new QSpinBox(frame_2);
        colSpin->setObjectName(QStringLiteral("colSpin"));

        horizontalLayout_2->addWidget(colSpin);


        verticalLayout->addWidget(frame_2);

        widget = new QWidget(MatAccessWidget);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setSpacing(2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        chaLabel = new QLabel(widget);
        chaLabel->setObjectName(QStringLiteral("chaLabel"));

        horizontalLayout_3->addWidget(chaLabel);

        channelSpin = new QSpinBox(widget);
        channelSpin->setObjectName(QStringLiteral("channelSpin"));

        horizontalLayout_3->addWidget(channelSpin);


        verticalLayout->addWidget(widget);

        frame_3 = new QFrame(MatAccessWidget);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_3);
        horizontalLayout_4->setSpacing(4);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(frame_3);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_4->addWidget(label);

        depthLabel = new QLabel(frame_3);
        depthLabel->setObjectName(QStringLiteral("depthLabel"));

        horizontalLayout_4->addWidget(depthLabel);


        verticalLayout->addWidget(frame_3);


        retranslateUi(MatAccessWidget);

        QMetaObject::connectSlotsByName(MatAccessWidget);
    } // setupUi

    void retranslateUi(QWidget *MatAccessWidget)
    {
        MatAccessWidget->setWindowTitle(QApplication::translate("MatAccessWidget", "Form", Q_NULLPTR));
        rowLabel->setText(QApplication::translate("MatAccessWidget", "Row:", Q_NULLPTR));
        colLabel->setText(QApplication::translate("MatAccessWidget", "Column:", Q_NULLPTR));
        chaLabel->setText(QApplication::translate("MatAccessWidget", "Channel:", Q_NULLPTR));
        label->setText(QApplication::translate("MatAccessWidget", "Depth:", Q_NULLPTR));
        depthLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MatAccessWidget: public Ui_MatAccessWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATACCESSWIDGET_H
