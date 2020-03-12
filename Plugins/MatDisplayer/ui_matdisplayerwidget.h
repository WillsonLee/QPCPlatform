/********************************************************************************
** Form generated from reading UI file 'matdisplayerwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATDISPLAYERWIDGET_H
#define UI_MATDISPLAYERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MatDisplayerWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *imageLabel;

    void setupUi(QWidget *MatDisplayerWidget)
    {
        if (MatDisplayerWidget->objectName().isEmpty())
            MatDisplayerWidget->setObjectName(QStringLiteral("MatDisplayerWidget"));
        MatDisplayerWidget->resize(414, 327);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MatDisplayerWidget->sizePolicy().hasHeightForWidth());
        MatDisplayerWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(MatDisplayerWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(-1, -1, 0, -1);
        imageLabel = new QLabel(MatDisplayerWidget);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));
        sizePolicy.setHeightForWidth(imageLabel->sizePolicy().hasHeightForWidth());
        imageLabel->setSizePolicy(sizePolicy);
        imageLabel->setScaledContents(true);

        gridLayout->addWidget(imageLabel, 0, 0, 1, 1);


        retranslateUi(MatDisplayerWidget);

        QMetaObject::connectSlotsByName(MatDisplayerWidget);
    } // setupUi

    void retranslateUi(QWidget *MatDisplayerWidget)
    {
        MatDisplayerWidget->setWindowTitle(QApplication::translate("MatDisplayerWidget", "Form", Q_NULLPTR));
        imageLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MatDisplayerWidget: public Ui_MatDisplayerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATDISPLAYERWIDGET_H
