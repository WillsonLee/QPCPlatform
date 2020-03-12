/********************************************************************************
** Form generated from reading UI file 'matloaderwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATLOADERWIDGET_H
#define UI_MATLOADERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MatLoaderWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *fileLineEdit;
    QLabel *label_2;
    QPushButton *openPushButton;
    QComboBox *modeComboBox;

    void setupUi(QWidget *MatLoaderWidget)
    {
        if (MatLoaderWidget->objectName().isEmpty())
            MatLoaderWidget->setObjectName(QStringLiteral("MatLoaderWidget"));
        MatLoaderWidget->resize(304, 141);
        gridLayout = new QGridLayout(MatLoaderWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(MatLoaderWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        fileLineEdit = new QLineEdit(MatLoaderWidget);
        fileLineEdit->setObjectName(QStringLiteral("fileLineEdit"));
        fileLineEdit->setReadOnly(true);

        gridLayout->addWidget(fileLineEdit, 0, 1, 1, 1);

        label_2 = new QLabel(MatLoaderWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        openPushButton = new QPushButton(MatLoaderWidget);
        openPushButton->setObjectName(QStringLiteral("openPushButton"));
        openPushButton->setMaximumSize(QSize(25, 16777215));

        gridLayout->addWidget(openPushButton, 0, 2, 1, 1);

        modeComboBox = new QComboBox(MatLoaderWidget);
        modeComboBox->setObjectName(QStringLiteral("modeComboBox"));

        gridLayout->addWidget(modeComboBox, 1, 1, 1, 2);


        retranslateUi(MatLoaderWidget);

        QMetaObject::connectSlotsByName(MatLoaderWidget);
    } // setupUi

    void retranslateUi(QWidget *MatLoaderWidget)
    {
        MatLoaderWidget->setWindowTitle(QApplication::translate("MatLoaderWidget", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("MatLoaderWidget", "FileName:", Q_NULLPTR));
        label_2->setText(QApplication::translate("MatLoaderWidget", "Read Mode:", Q_NULLPTR));
        openPushButton->setText(QApplication::translate("MatLoaderWidget", "...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MatLoaderWidget: public Ui_MatLoaderWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATLOADERWIDGET_H
