#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

#include "../include/acorn.hpp"

QT_BEGIN_NAMESPACE

namespace jay_io
{

class QtAcorn: public QMainWindow
{
        public slots:
                QMainWindow *ui;
                QWidget *centralwidget;

                QLineEdit *topSearchLineEdit;
                QPushButton *topSearchPushButton;

                QLineEdit *historySearchLineEdit;
                QListWidget *historyListView;
                QPushButton *historyPurgePushButton;

                QPushButton *aboutPushButton;
                QPushButton *donatePushButton;

                QTabWidget *mainTabWidget;

                QWidget *dictLookUpTab;
                QTextBrowser *dictLookUpTextBrowser;

                QWidget *wildcSearchTab;
                QLabel *wildcMatchesLabel;
                QListView *wildcMatchesListView;
                QTextBrowser *wildcSearchLookUpTextBrowser;
                QLabel *wildcLookUpLabel;

        public:
                void handleTopSearchPushButton()
                {
                        QString entry = this -> topSearchLineEdit -> text();
                        jay_io::Acorn acorn(ACORN_MODE_EXECMD);
                        jay_io::Word_Log wlog = acorn.lookUpQuery(entry.toStdString());
                        this -> dictLookUpTextBrowser -> setHtml(QString(wlog.toHtml().c_str()));;
                }


        public:
                QtAcorn(QMainWindow *parent): ui(parent)
                {
                        this -> setupUi(ui);
                        connect(topSearchPushButton, &QPushButton::released, this, &QtAcorn::handleTopSearchPushButton);
                        ui -> show();
                }

        void setupUi(QMainWindow *MainWindow)
        {
                if (MainWindow -> objectName().isEmpty())
                        MainWindow -> setObjectName(QString::fromUtf8("MainWindow"));
                MainWindow -> resize(803, 600);

                QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
                sizePolicy.setHorizontalStretch(0);
                sizePolicy.setVerticalStretch(0);
                MainWindow -> setSizePolicy(sizePolicy);
                MainWindow -> setMinimumSize(QSize(803, 600));
                MainWindow -> setMaximumSize(QSize(803, 600));

                centralwidget = new QWidget(MainWindow);
                centralwidget -> setObjectName(QString::fromUtf8("centralwidget"));

                topSearchLineEdit = new QLineEdit(centralwidget);
                topSearchLineEdit -> setObjectName(QString::fromUtf8("topSearchLineEdit"));
                topSearchLineEdit -> setGeometry(QRect(10, 10, 481, 30));
                topSearchPushButton = new QPushButton(centralwidget);
                topSearchPushButton -> setObjectName(QString::fromUtf8("topSearchPushButton"));
                topSearchPushButton -> setGeometry(QRect(500, 10, 91, 30));
                QIcon icon69; QString iconThemeName = QString::fromUtf8("edit-find");
                if (QIcon::hasThemeIcon(iconThemeName))
                        icon69 = QIcon::fromTheme(iconThemeName);
                else
                        icon69.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
                topSearchPushButton -> setIcon(icon69);

                historyListView = new QListWidget(centralwidget);
                historyListView -> setObjectName(QString::fromUtf8("historyListView"));
                historyListView -> setGeometry(QRect(610, 51, 181, 496));
                historySearchLineEdit = new QLineEdit(centralwidget);
                historySearchLineEdit -> setObjectName(QString::fromUtf8("historySearchLineEdit"));
                historySearchLineEdit -> setGeometry(QRect(610, 10, 141, 30));

                donatePushButton = new QPushButton(centralwidget);
                donatePushButton -> setObjectName(QString::fromUtf8("donatePushButton"));
                donatePushButton -> setGeometry(QRect(705, 560, 86, 30));
                QIcon icon1; iconThemeName = QString::fromUtf8("emblem-favorite-symbolic");
                if (QIcon::hasThemeIcon(iconThemeName))
                       icon1 = QIcon::fromTheme(iconThemeName);
                else
                        icon1.addFile(QString::fromUtf8("../../../"), QSize(), QIcon::Normal, QIcon::Off);
                donatePushButton -> setIcon(icon1);

                aboutPushButton = new QPushButton(centralwidget);
                aboutPushButton -> setObjectName(QString::fromUtf8("aboutPushButton"));
                aboutPushButton -> setGeometry(QRect(610, 560, 86, 30));
                QIcon icon2; iconThemeName = QString::fromUtf8("help-about-symbolic");
                if (QIcon::hasThemeIcon(iconThemeName))
                    icon2 = QIcon::fromTheme(iconThemeName);
                else
                    icon2.addFile(QString::fromUtf8("../../../"), QSize(), QIcon::Normal, QIcon::Off);
                aboutPushButton -> setIcon(icon2);

                dictLookUpTab = new QWidget();
                dictLookUpTab -> setObjectName(QString::fromUtf8("dictLookUpTab"));
                QIcon icon; QString iconThemeName1 = QString::fromUtf8("edit-find");
                if (QIcon::hasThemeIcon(iconThemeName1))
                        icon = QIcon::fromTheme(iconThemeName1);
                else
                        icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);

                dictLookUpTextBrowser = new QTextBrowser(dictLookUpTab);
                dictLookUpTextBrowser -> setObjectName(QString::fromUtf8("dictLookUpTextBrowser"));
                dictLookUpTextBrowser -> setGeometry(QRect(10, 10, 576, 496));
                dictLookUpTextBrowser -> setReadOnly(true);

                mainTabWidget = new QTabWidget(centralwidget);
                mainTabWidget -> setObjectName(QString::fromUtf8("mainTabWidget"));
                mainTabWidget -> setGeometry(QRect(0, 50, 601, 546));
                mainTabWidget -> setTabPosition(QTabWidget::North);
                mainTabWidget -> setTabShape(QTabWidget::Rounded);
                mainTabWidget -> setElideMode(Qt::ElideNone);

                wildcSearchTab = new QWidget();
                wildcSearchTab -> setObjectName(QString::fromUtf8("wildcSearchTab"));
                QIcon icon3; iconThemeName = QString::fromUtf8("dialog-question-symbolic");
                if (QIcon::hasThemeIcon(iconThemeName))
                    icon3 = QIcon::fromTheme(iconThemeName);
                else
                    icon3.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);

                wildcMatchesListView = new QListView(wildcSearchTab);
                wildcMatchesListView -> setObjectName(QString::fromUtf8("wildcMatchesListView"));
                wildcMatchesListView -> setGeometry(QRect(10, 40, 181, 466));

                wildcSearchLookUpTextBrowser = new QTextBrowser(wildcSearchTab);
                wildcSearchLookUpTextBrowser -> setObjectName(QString::fromUtf8("wildcSearchLookUpTextBrowser"));
                wildcSearchLookUpTextBrowser -> setGeometry(QRect(205, 40, 381, 466));

                wildcMatchesLabel = new QLabel(wildcSearchTab);
                wildcMatchesLabel -> setObjectName(QString::fromUtf8("wildcMatchesLabel"));
                wildcMatchesLabel -> setGeometry(QRect(10, 10, 171, 21));

                wildcLookUpLabel = new QLabel(wildcSearchTab);
                wildcLookUpLabel -> setObjectName(QString::fromUtf8("wildcLookUpLabel"));
                wildcLookUpLabel -> setGeometry(QRect(205, 10, 171, 21));

                historyPurgePushButton = new QPushButton(centralwidget);
                historyPurgePushButton -> setObjectName(QString::fromUtf8("historyPurgePushButton"));
                historyPurgePushButton -> setGeometry(QRect(760, 10, 31, 30));
                QIcon icon10; iconThemeName = QString::fromUtf8("edit-delete-symbolic");
                if (QIcon::hasThemeIcon(iconThemeName))
                    icon10 = QIcon::fromTheme(iconThemeName);
                else
                    icon10.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
                historyPurgePushButton -> setIcon(icon10);

                mainTabWidget -> addTab(dictLookUpTab, icon, QString());
                mainTabWidget -> addTab(wildcSearchTab, icon3, QString());

                MainWindow -> setCentralWidget(centralwidget);

                retranslateUi(MainWindow);

                mainTabWidget -> setCurrentIndex(1);

                QMetaObject::connectSlotsByName(MainWindow);
        }

        void retranslateUi(QMainWindow *MainWindow)
        {
                MainWindow -> setWindowTitle(QCoreApplication::translate("MainWindow", "Acorn 1.0.0", nullptr));
                topSearchLineEdit -> setPlaceholderText(QCoreApplication::translate("MainWindow", "Search word", nullptr));
                topSearchPushButton -> setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
                historySearchLineEdit -> setPlaceholderText(QCoreApplication::translate("MainWindow", "Search history", nullptr));
                donatePushButton -> setText(QCoreApplication::translate("MainWindow", "Donate", nullptr));
                aboutPushButton -> setText(QCoreApplication::translate("MainWindow", "About", nullptr));
                mainTabWidget -> setTabText(mainTabWidget -> indexOf(dictLookUpTab), QCoreApplication::translate("MainWindow", "Dictionary Look Up", nullptr));
                wildcMatchesLabel -> setText(QCoreApplication::translate("MainWindow", "Wildcard matches:", nullptr));
                wildcLookUpLabel -> setText(QCoreApplication::translate("MainWindow", "Look up:", nullptr));
                mainTabWidget -> setTabText(mainTabWidget -> indexOf(wildcSearchTab), QCoreApplication::translate("MainWindow", "Wildcard Word Search", nullptr));
        }

};

}

QT_END_NAMESPACE

#endif // MAINWINDOW_H
