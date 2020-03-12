/********************************************************************************
** Form generated from reading UI file 'proppagewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPPAGEWIDGET_H
#define UI_PROPPAGEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PropPageWidget
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *topWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QLineEdit *pluginDescriptionLineEdit;
    QLabel *typeTipLabel;
    QWidget *tableHolderWidget;
    QHBoxLayout *horizontalLayout;
    QTableWidget *inputsTableWidget;
    QTableWidget *outsTableWidget;
    QWidget *numbersHolderWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QSpinBox *numInputSpinBox;
    QLabel *label_2;
    QSpinBox *numOutSpinBox;
    QWidget *fourthWidget;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *hasWidgetCheckBox;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QLineEdit *includeLineEdit;
    QPushButton *includePushButton;
    QWidget *fifthWidget;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *embededCheckBox;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_4;
    QLineEdit *dependLineEdit;
    QPushButton *dependPushButton;

    void setupUi(QWidget *PropPageWidget)
    {
        if (PropPageWidget->objectName().isEmpty())
            PropPageWidget->setObjectName(QStringLiteral("PropPageWidget"));
        PropPageWidget->resize(476, 286);
        verticalLayout = new QVBoxLayout(PropPageWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        topWidget = new QWidget(PropPageWidget);
        topWidget->setObjectName(QStringLiteral("topWidget"));
        horizontalLayout_2 = new QHBoxLayout(topWidget);
        horizontalLayout_2->setSpacing(4);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(topWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_2->addWidget(label_6);

        pluginDescriptionLineEdit = new QLineEdit(topWidget);
        pluginDescriptionLineEdit->setObjectName(QStringLiteral("pluginDescriptionLineEdit"));

        horizontalLayout_2->addWidget(pluginDescriptionLineEdit);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 5);

        verticalLayout->addWidget(topWidget);

        typeTipLabel = new QLabel(PropPageWidget);
        typeTipLabel->setObjectName(QStringLiteral("typeTipLabel"));

        verticalLayout->addWidget(typeTipLabel);

        tableHolderWidget = new QWidget(PropPageWidget);
        tableHolderWidget->setObjectName(QStringLiteral("tableHolderWidget"));
        horizontalLayout = new QHBoxLayout(tableHolderWidget);
        horizontalLayout->setSpacing(4);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        inputsTableWidget = new QTableWidget(tableHolderWidget);
        inputsTableWidget->setObjectName(QStringLiteral("inputsTableWidget"));

        horizontalLayout->addWidget(inputsTableWidget);

        outsTableWidget = new QTableWidget(tableHolderWidget);
        outsTableWidget->setObjectName(QStringLiteral("outsTableWidget"));

        horizontalLayout->addWidget(outsTableWidget);


        verticalLayout->addWidget(tableHolderWidget);

        numbersHolderWidget = new QWidget(PropPageWidget);
        numbersHolderWidget->setObjectName(QStringLiteral("numbersHolderWidget"));
        horizontalLayout_3 = new QHBoxLayout(numbersHolderWidget);
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(numbersHolderWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        numInputSpinBox = new QSpinBox(numbersHolderWidget);
        numInputSpinBox->setObjectName(QStringLiteral("numInputSpinBox"));

        horizontalLayout_3->addWidget(numInputSpinBox);

        label_2 = new QLabel(numbersHolderWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        numOutSpinBox = new QSpinBox(numbersHolderWidget);
        numOutSpinBox->setObjectName(QStringLiteral("numOutSpinBox"));

        horizontalLayout_3->addWidget(numOutSpinBox);


        verticalLayout->addWidget(numbersHolderWidget);

        fourthWidget = new QWidget(PropPageWidget);
        fourthWidget->setObjectName(QStringLiteral("fourthWidget"));
        horizontalLayout_4 = new QHBoxLayout(fourthWidget);
        horizontalLayout_4->setSpacing(4);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        hasWidgetCheckBox = new QCheckBox(fourthWidget);
        hasWidgetCheckBox->setObjectName(QStringLiteral("hasWidgetCheckBox"));
        hasWidgetCheckBox->setChecked(true);

        horizontalLayout_4->addWidget(hasWidgetCheckBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        label_3 = new QLabel(fourthWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        includeLineEdit = new QLineEdit(fourthWidget);
        includeLineEdit->setObjectName(QStringLiteral("includeLineEdit"));
        includeLineEdit->setReadOnly(true);

        horizontalLayout_4->addWidget(includeLineEdit);

        includePushButton = new QPushButton(fourthWidget);
        includePushButton->setObjectName(QStringLiteral("includePushButton"));
        includePushButton->setMaximumSize(QSize(25, 16777215));

        horizontalLayout_4->addWidget(includePushButton);


        verticalLayout->addWidget(fourthWidget);

        fifthWidget = new QWidget(PropPageWidget);
        fifthWidget->setObjectName(QStringLiteral("fifthWidget"));
        horizontalLayout_5 = new QHBoxLayout(fifthWidget);
        horizontalLayout_5->setSpacing(4);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        embededCheckBox = new QCheckBox(fifthWidget);
        embededCheckBox->setObjectName(QStringLiteral("embededCheckBox"));

        horizontalLayout_5->addWidget(embededCheckBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        label_4 = new QLabel(fifthWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_5->addWidget(label_4);

        dependLineEdit = new QLineEdit(fifthWidget);
        dependLineEdit->setObjectName(QStringLiteral("dependLineEdit"));
        dependLineEdit->setReadOnly(true);

        horizontalLayout_5->addWidget(dependLineEdit);

        dependPushButton = new QPushButton(fifthWidget);
        dependPushButton->setObjectName(QStringLiteral("dependPushButton"));
        dependPushButton->setMaximumSize(QSize(25, 16777215));

        horizontalLayout_5->addWidget(dependPushButton);


        verticalLayout->addWidget(fifthWidget);


        retranslateUi(PropPageWidget);

        QMetaObject::connectSlotsByName(PropPageWidget);
    } // setupUi

    void retranslateUi(QWidget *PropPageWidget)
    {
        PropPageWidget->setWindowTitle(QApplication::translate("PropPageWidget", "Form", Q_NULLPTR));
        label_6->setText(QApplication::translate("PropPageWidget", "plugin description:", Q_NULLPTR));
        typeTipLabel->setText(QApplication::translate("PropPageWidget", "data types should be exactly correct, description is not necessary", Q_NULLPTR));
        label->setText(QApplication::translate("PropPageWidget", "input number:", Q_NULLPTR));
        label_2->setText(QApplication::translate("PropPageWidget", "output number:", Q_NULLPTR));
        hasWidgetCheckBox->setText(QApplication::translate("PropPageWidget", "has widget", Q_NULLPTR));
        label_3->setText(QApplication::translate("PropPageWidget", "include path:", Q_NULLPTR));
        includePushButton->setText(QApplication::translate("PropPageWidget", "...", Q_NULLPTR));
        embededCheckBox->setText(QApplication::translate("PropPageWidget", "embeded widget", Q_NULLPTR));
        label_4->setText(QApplication::translate("PropPageWidget", "depend path:", Q_NULLPTR));
        dependPushButton->setText(QApplication::translate("PropPageWidget", "...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PropPageWidget: public Ui_PropPageWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPPAGEWIDGET_H
