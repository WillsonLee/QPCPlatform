/********************************************************************************
** Form generated from reading UI file 'mattofilewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATTOFILEWIDGET_H
#define UI_MATTOFILEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MatToFileWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QLineEdit *nameLineEdit;
    QPushButton *okButton;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *pathLineEdit;
    QPushButton *pathButton;

    void setupUi(QWidget *MatToFileWidget)
    {
        if (MatToFileWidget->objectName().isEmpty())
            MatToFileWidget->setObjectName(QStringLiteral("MatToFileWidget"));
        MatToFileWidget->resize(153, 81);
        verticalLayout = new QVBoxLayout(MatToFileWidget);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        groupBox = new QGroupBox(MatToFileWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        nameLineEdit = new QLineEdit(groupBox);
        nameLineEdit->setObjectName(QStringLiteral("nameLineEdit"));

        horizontalLayout->addWidget(nameLineEdit);

        okButton = new QPushButton(groupBox);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setMaximumSize(QSize(45, 16777215));

        horizontalLayout->addWidget(okButton);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(MatToFileWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pathLineEdit = new QLineEdit(groupBox_2);
        pathLineEdit->setObjectName(QStringLiteral("pathLineEdit"));
        pathLineEdit->setReadOnly(true);

        horizontalLayout_2->addWidget(pathLineEdit);

        pathButton = new QPushButton(groupBox_2);
        pathButton->setObjectName(QStringLiteral("pathButton"));
        pathButton->setMaximumSize(QSize(25, 16777215));

        horizontalLayout_2->addWidget(pathButton);


        verticalLayout->addWidget(groupBox_2);


        retranslateUi(MatToFileWidget);

        QMetaObject::connectSlotsByName(MatToFileWidget);
    } // setupUi

    void retranslateUi(QWidget *MatToFileWidget)
    {
        MatToFileWidget->setWindowTitle(QApplication::translate("MatToFileWidget", "Form", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MatToFileWidget", "File Name", Q_NULLPTR));
        nameLineEdit->setText(QApplication::translate("MatToFileWidget", "untitled.jpg", Q_NULLPTR));
        okButton->setText(QApplication::translate("MatToFileWidget", "OK", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MatToFileWidget", "Path", Q_NULLPTR));
        pathButton->setText(QApplication::translate("MatToFileWidget", "...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MatToFileWidget: public Ui_MatToFileWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATTOFILEWIDGET_H
