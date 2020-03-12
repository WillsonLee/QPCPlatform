/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_N;
    QAction *actionLoad_L;
    QAction *actionWrap_W;
    QAction *actionManage_M;
    QAction *actiondoc;
    QAction *actiontutorial;
    QAction *actionabout;
    QAction *actionToolBox;
    QAction *actionOutputs;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuapperance;
    QMenu *menuplugins;
    QMenu *menuHelp_H;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *toolBox;
    QWidget *toolBoxContent;
    QHBoxLayout *horizontalLayout_2;
    QTreeWidget *toolsTree;
    QDockWidget *workspaceDock;
    QWidget *varDisplay;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1230, 801);
        MainWindow->setStyleSheet(QLatin1String("QMainWindow#MainWindow{\n"
"background-color:rgb(240, 240, 240)\n"
"}\n"
"QWidget#centralWidget{\n"
"background-color:white;\n"
"}"));
        actionNew_N = new QAction(MainWindow);
        actionNew_N->setObjectName(QStringLiteral("actionNew_N"));
        actionLoad_L = new QAction(MainWindow);
        actionLoad_L->setObjectName(QStringLiteral("actionLoad_L"));
        actionWrap_W = new QAction(MainWindow);
        actionWrap_W->setObjectName(QStringLiteral("actionWrap_W"));
        actionManage_M = new QAction(MainWindow);
        actionManage_M->setObjectName(QStringLiteral("actionManage_M"));
        actiondoc = new QAction(MainWindow);
        actiondoc->setObjectName(QStringLiteral("actiondoc"));
        actiontutorial = new QAction(MainWindow);
        actiontutorial->setObjectName(QStringLiteral("actiontutorial"));
        actionabout = new QAction(MainWindow);
        actionabout->setObjectName(QStringLiteral("actionabout"));
        actionToolBox = new QAction(MainWindow);
        actionToolBox->setObjectName(QStringLiteral("actionToolBox"));
        actionToolBox->setCheckable(true);
        actionOutputs = new QAction(MainWindow);
        actionOutputs->setObjectName(QStringLiteral("actionOutputs"));
        actionOutputs->setCheckable(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1230, 23));
        menuapperance = new QMenu(menuBar);
        menuapperance->setObjectName(QStringLiteral("menuapperance"));
        menuplugins = new QMenu(menuBar);
        menuplugins->setObjectName(QStringLiteral("menuplugins"));
        menuHelp_H = new QMenu(menuBar);
        menuHelp_H->setObjectName(QStringLiteral("menuHelp_H"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBox = new QDockWidget(MainWindow);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        toolBoxContent = new QWidget();
        toolBoxContent->setObjectName(QStringLiteral("toolBoxContent"));
        horizontalLayout_2 = new QHBoxLayout(toolBoxContent);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        toolsTree = new QTreeWidget(toolBoxContent);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        toolsTree->setHeaderItem(__qtreewidgetitem);
        toolsTree->setObjectName(QStringLiteral("toolsTree"));
        toolsTree->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        toolsTree->setColumnCount(1);
        toolsTree->header()->setVisible(false);

        horizontalLayout_2->addWidget(toolsTree);

        toolBox->setWidget(toolBoxContent);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), toolBox);
        workspaceDock = new QDockWidget(MainWindow);
        workspaceDock->setObjectName(QStringLiteral("workspaceDock"));
        workspaceDock->setFeatures(QDockWidget::AllDockWidgetFeatures);
        varDisplay = new QWidget();
        varDisplay->setObjectName(QStringLiteral("varDisplay"));
        horizontalLayout = new QHBoxLayout(varDisplay);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget = new QTableWidget(varDisplay);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setShowGrid(true);
        tableWidget->setColumnCount(6);

        horizontalLayout->addWidget(tableWidget);

        workspaceDock->setWidget(varDisplay);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(8), workspaceDock);

        menuBar->addAction(menuapperance->menuAction());
        menuBar->addAction(menuplugins->menuAction());
        menuBar->addAction(menuHelp_H->menuAction());
        menuapperance->addAction(actionToolBox);
        menuapperance->addAction(actionOutputs);
        menuplugins->addAction(actionNew_N);
        menuplugins->addAction(actionLoad_L);
        menuplugins->addAction(actionWrap_W);
        menuplugins->addAction(actionManage_M);
        menuHelp_H->addAction(actiondoc);
        menuHelp_H->addAction(actiontutorial);
        menuHelp_H->addSeparator();
        menuHelp_H->addAction(actionabout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "QPCPlatform", Q_NULLPTR));
        actionNew_N->setText(QApplication::translate("MainWindow", "Create New(&N)", Q_NULLPTR));
        actionLoad_L->setText(QApplication::translate("MainWindow", "Load Plugin(&L)", Q_NULLPTR));
        actionWrap_W->setText(QApplication::translate("MainWindow", "Wrap Plugin(&W)", Q_NULLPTR));
        actionManage_M->setText(QApplication::translate("MainWindow", "Manage(&M)", Q_NULLPTR));
        actiondoc->setText(QApplication::translate("MainWindow", "doc", Q_NULLPTR));
        actiontutorial->setText(QApplication::translate("MainWindow", "tutorial", Q_NULLPTR));
        actionabout->setText(QApplication::translate("MainWindow", "about", Q_NULLPTR));
        actionToolBox->setText(QApplication::translate("MainWindow", "ToolBox", Q_NULLPTR));
        actionOutputs->setText(QApplication::translate("MainWindow", "Outputs", Q_NULLPTR));
        menuapperance->setTitle(QApplication::translate("MainWindow", "View(&V)", Q_NULLPTR));
        menuplugins->setTitle(QApplication::translate("MainWindow", "Plugins(&P)", Q_NULLPTR));
        menuHelp_H->setTitle(QApplication::translate("MainWindow", "Help(&H)", Q_NULLPTR));
        toolBox->setWindowTitle(QApplication::translate("MainWindow", "ToolBox", Q_NULLPTR));
        workspaceDock->setWindowTitle(QApplication::translate("MainWindow", "All Outputs", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
