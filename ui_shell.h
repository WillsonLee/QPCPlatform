/********************************************************************************
** Form generated from reading UI file 'shell.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHELL_H
#define UI_SHELL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Shell
{
public:
    QHBoxLayout *horizontalLayout_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QFrame *leftWidget;
    QFrame *middleWidget;
    QVBoxLayout *verticalLayout;
    QFrame *titleFrame;
    QVBoxLayout *verticalLayout_2;
    QLabel *titleLabel;
    QFrame *centralFrame;
    QGridLayout *gridLayout;
    QProgressBar *progressBar;
    QFrame *rightWidget;

    void setupUi(QWidget *Shell)
    {
        if (Shell->objectName().isEmpty())
            Shell->setObjectName(QStringLiteral("Shell"));
        Shell->resize(462, 338);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Shell->sizePolicy().hasHeightForWidth());
        Shell->setSizePolicy(sizePolicy);
        Shell->setBaseSize(QSize(100, 70));
        Shell->setContextMenuPolicy(Qt::CustomContextMenu);
        Shell->setAutoFillBackground(true);
        Shell->setStyleSheet(QLatin1String("QWidget#Shell{\n"
"background-color:rgb(240, 240, 240)\n"
"border-radius:15px\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(Shell);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(Shell);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(0);
        frame->setMidLineWidth(1);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        leftWidget = new QFrame(frame);
        leftWidget->setObjectName(QStringLiteral("leftWidget"));
        leftWidget->setMaximumSize(QSize(15, 16777215));
        leftWidget->setFrameShape(QFrame::StyledPanel);
        leftWidget->setFrameShadow(QFrame::Raised);
        leftWidget->setLineWidth(0);
        leftWidget->setMidLineWidth(1);

        horizontalLayout->addWidget(leftWidget);

        middleWidget = new QFrame(frame);
        middleWidget->setObjectName(QStringLiteral("middleWidget"));
        middleWidget->setFrameShape(QFrame::Box);
        middleWidget->setFrameShadow(QFrame::Raised);
        middleWidget->setLineWidth(0);
        middleWidget->setMidLineWidth(1);
        verticalLayout = new QVBoxLayout(middleWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleFrame = new QFrame(middleWidget);
        titleFrame->setObjectName(QStringLiteral("titleFrame"));
        titleFrame->setFrameShape(QFrame::Box);
        titleFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(titleFrame);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        titleLabel = new QLabel(titleFrame);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));
        titleLabel->setAutoFillBackground(true);
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(titleLabel);


        verticalLayout->addWidget(titleFrame);

        centralFrame = new QFrame(middleWidget);
        centralFrame->setObjectName(QStringLiteral("centralFrame"));
        centralFrame->setFrameShape(QFrame::Box);
        centralFrame->setFrameShadow(QFrame::Raised);
        centralFrame->setLineWidth(1);
        gridLayout = new QGridLayout(centralFrame);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(2, 2, 2, 2);

        verticalLayout->addWidget(centralFrame);

        progressBar = new QProgressBar(middleWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setEnabled(true);
        progressBar->setToolTipDuration(1000);
        progressBar->setValue(24);
        progressBar->setTextVisible(false);

        verticalLayout->addWidget(progressBar);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 8);
        verticalLayout->setStretch(2, 1);

        horizontalLayout->addWidget(middleWidget);

        rightWidget = new QFrame(frame);
        rightWidget->setObjectName(QStringLiteral("rightWidget"));
        rightWidget->setMaximumSize(QSize(15, 16777215));
        rightWidget->setStyleSheet(QLatin1String("QFrame#frame{\n"
"background-color:#0f00f0\n"
"}"));
        rightWidget->setFrameShape(QFrame::StyledPanel);
        rightWidget->setFrameShadow(QFrame::Raised);
        rightWidget->setLineWidth(0);
        rightWidget->setMidLineWidth(1);

        horizontalLayout->addWidget(rightWidget);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 6);
        horizontalLayout->setStretch(2, 2);

        horizontalLayout_2->addWidget(frame);


        retranslateUi(Shell);

        QMetaObject::connectSlotsByName(Shell);
    } // setupUi

    void retranslateUi(QWidget *Shell)
    {
        Shell->setWindowTitle(QApplication::translate("Shell", "Form", Q_NULLPTR));
        titleLabel->setText(QApplication::translate("Shell", "TextLabel", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        progressBar->setToolTip(QApplication::translate("Shell", "20", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class Shell: public Ui_Shell {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHELL_H
