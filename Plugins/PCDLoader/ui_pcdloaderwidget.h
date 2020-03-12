/********************************************************************************
** Form generated from reading UI file 'pcdloaderwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PCDLOADERWIDGET_H
#define UI_PCDLOADERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PCDLoaderWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *comboBox;

    void setupUi(QWidget *PCDLoaderWidget)
    {
        if (PCDLoaderWidget->objectName().isEmpty())
            PCDLoaderWidget->setObjectName(QStringLiteral("PCDLoaderWidget"));
        PCDLoaderWidget->resize(142, 80);
        verticalLayout = new QVBoxLayout(PCDLoaderWidget);
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        groupBox = new QGroupBox(PCDLoaderWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(3, 1, 3, 1);
        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);
        lineEdit->setMinimumSize(QSize(0, 0));
        lineEdit->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setMaximumSize(QSize(25, 16777215));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(PCDLoaderWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setFlat(false);
        groupBox_2->setCheckable(false);
        groupBox_2->setChecked(false);
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(3, 1, 3, 1);
        comboBox = new QComboBox(groupBox_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);
        comboBox->setMinimumSize(QSize(0, 0));

        horizontalLayout_2->addWidget(comboBox);


        verticalLayout->addWidget(groupBox_2);


        retranslateUi(PCDLoaderWidget);

        QMetaObject::connectSlotsByName(PCDLoaderWidget);
    } // setupUi

    void retranslateUi(QWidget *PCDLoaderWidget)
    {
        PCDLoaderWidget->setWindowTitle(QApplication::translate("PCDLoaderWidget", "Form", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("PCDLoaderWidget", "File Name", Q_NULLPTR));
        pushButton->setText(QApplication::translate("PCDLoaderWidget", "...", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("PCDLoaderWidget", "Point Type", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PCDLoaderWidget: public Ui_PCDLoaderWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PCDLOADERWIDGET_H
