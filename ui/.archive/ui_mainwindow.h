/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWebKitWidgets/QWebView>
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
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *topSearchLineEdit;
    QPushButton *topSearchPushButton;
    QListWidget *historyListView;
    QLineEdit *historySearchLineEdit;
    QPushButton *donatePushButton;
    QPushButton *aboutPushButton;
    QTabWidget *wildcSearchMatchesTextEdit;
    QWidget *dictLookUpTab;
    QTextEdit *dictLookUpTextEdit;
    QWidget *wildcSearchTab;
    QListView *wildcMatchesListView;
    QTextBrowser *wildcSearchLookUpTextEdit;
    QLabel *wildcMatchesLabel;
    QLabel *wildcLookUpLabel;
    QWidget *wikitionaryTab;
    QFrame *wikitionaryContentFrame;
    QWebView *wikitionaryWebView;
    QPushButton *openBrowserPushButton;
    QPushButton *navHomePushButton;
    QPushButton *navRefreshPushButton;
    QPushButton *navBackPushButton;
    QPushButton *navForwardPushButton;
    QPushButton *historyPurgePushButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(803, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        topSearchLineEdit = new QLineEdit(centralwidget);
        topSearchLineEdit->setObjectName(QString::fromUtf8("topSearchLineEdit"));
        topSearchLineEdit->setGeometry(QRect(10, 10, 481, 30));
        topSearchPushButton = new QPushButton(centralwidget);
        topSearchPushButton->setObjectName(QString::fromUtf8("topSearchPushButton"));
        topSearchPushButton->setGeometry(QRect(500, 10, 91, 30));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("edit-find");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        topSearchPushButton->setIcon(icon);
        topSearchPushButton->setFlat(false);
        historyListView = new QListWidget(centralwidget);
        historyListView->setObjectName(QString::fromUtf8("historyListView"));
        historyListView->setGeometry(QRect(610, 51, 181, 496));
        historySearchLineEdit = new QLineEdit(centralwidget);
        historySearchLineEdit->setObjectName(QString::fromUtf8("historySearchLineEdit"));
        historySearchLineEdit->setGeometry(QRect(610, 10, 141, 30));
        donatePushButton = new QPushButton(centralwidget);
        donatePushButton->setObjectName(QString::fromUtf8("donatePushButton"));
        donatePushButton->setGeometry(QRect(705, 560, 86, 30));
        QIcon icon1;
        iconThemeName = QString::fromUtf8("emblem-favorite-symbolic");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8("../../../"), QSize(), QIcon::Normal, QIcon::Off);
        }
        donatePushButton->setIcon(icon1);
        aboutPushButton = new QPushButton(centralwidget);
        aboutPushButton->setObjectName(QString::fromUtf8("aboutPushButton"));
        aboutPushButton->setGeometry(QRect(610, 560, 86, 30));
        QIcon icon2;
        iconThemeName = QString::fromUtf8("help-about-symbolic");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QString::fromUtf8("../../../"), QSize(), QIcon::Normal, QIcon::Off);
        }
        aboutPushButton->setIcon(icon2);
        wildcSearchMatchesTextEdit = new QTabWidget(centralwidget);
        wildcSearchMatchesTextEdit->setObjectName(QString::fromUtf8("wildcSearchMatchesTextEdit"));
        wildcSearchMatchesTextEdit->setGeometry(QRect(0, 50, 601, 546));
        wildcSearchMatchesTextEdit->setTabPosition(QTabWidget::North);
        wildcSearchMatchesTextEdit->setTabShape(QTabWidget::Rounded);
        wildcSearchMatchesTextEdit->setElideMode(Qt::ElideNone);
        wildcSearchMatchesTextEdit->setDocumentMode(false);
        wildcSearchMatchesTextEdit->setTabsClosable(false);
        wildcSearchMatchesTextEdit->setMovable(false);
        wildcSearchMatchesTextEdit->setTabBarAutoHide(true);
        dictLookUpTab = new QWidget();
        dictLookUpTab->setObjectName(QString::fromUtf8("dictLookUpTab"));
        dictLookUpTextEdit = new QTextEdit(dictLookUpTab);
        dictLookUpTextEdit->setObjectName(QString::fromUtf8("dictLookUpTextEdit"));
        dictLookUpTextEdit->setGeometry(QRect(10, 10, 576, 496));
        dictLookUpTextEdit->setReadOnly(true);
        wildcSearchMatchesTextEdit->addTab(dictLookUpTab, icon, QString());
        wildcSearchTab = new QWidget();
        wildcSearchTab->setObjectName(QString::fromUtf8("wildcSearchTab"));
        wildcMatchesListView = new QListView(wildcSearchTab);
        wildcMatchesListView->setObjectName(QString::fromUtf8("wildcMatchesListView"));
        wildcMatchesListView->setGeometry(QRect(10, 40, 181, 466));
        wildcSearchLookUpTextEdit = new QTextBrowser(wildcSearchTab);
        wildcSearchLookUpTextEdit->setObjectName(QString::fromUtf8("wildcSearchLookUpTextEdit"));
        wildcSearchLookUpTextEdit->setGeometry(QRect(205, 40, 381, 466));
        wildcMatchesLabel = new QLabel(wildcSearchTab);
        wildcMatchesLabel->setObjectName(QString::fromUtf8("wildcMatchesLabel"));
        wildcMatchesLabel->setGeometry(QRect(10, 10, 171, 21));
        wildcLookUpLabel = new QLabel(wildcSearchTab);
        wildcLookUpLabel->setObjectName(QString::fromUtf8("wildcLookUpLabel"));
        wildcLookUpLabel->setGeometry(QRect(205, 10, 171, 21));
        QIcon icon3;
        iconThemeName = QString::fromUtf8("dialog-question-symbolic");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon3 = QIcon::fromTheme(iconThemeName);
        } else {
            icon3.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        wildcSearchMatchesTextEdit->addTab(wildcSearchTab, icon3, QString());
        wikitionaryTab = new QWidget();
        wikitionaryTab->setObjectName(QString::fromUtf8("wikitionaryTab"));
        wikitionaryContentFrame = new QFrame(wikitionaryTab);
        wikitionaryContentFrame->setObjectName(QString::fromUtf8("wikitionaryContentFrame"));
        wikitionaryContentFrame->setGeometry(QRect(10, 10, 576, 451));
        wikitionaryContentFrame->setStyleSheet(QString::fromUtf8("background-color: rgba(0,0,0,50);border: 1px solid black;border-color: rgba(0, 0, 0, 100);"));
        wikitionaryContentFrame->setFrameShape(QFrame::StyledPanel);
        wikitionaryContentFrame->setFrameShadow(QFrame::Sunken);
        wikitionaryWebView = new QWebView(wikitionaryContentFrame);
        wikitionaryWebView->setObjectName(QString::fromUtf8("wikitionaryWebView"));
        wikitionaryWebView->setGeometry(QRect(0, 0, 576, 451));
        wikitionaryWebView->setUrl(QUrl(QString::fromUtf8("https://en.wiktionary.org/wiki/pass_away")));
        wikitionaryWebView->setZoomFactor(0.800000011920929);
        wikitionaryWebView->setRenderHints(QPainter::LosslessImageRendering|QPainter::SmoothPixmapTransform|QPainter::TextAntialiasing);
        openBrowserPushButton = new QPushButton(wikitionaryTab);
        openBrowserPushButton->setObjectName(QString::fromUtf8("openBrowserPushButton"));
        openBrowserPushButton->setGeometry(QRect(435, 475, 151, 30));
        QIcon icon4;
        iconThemeName = QString::fromUtf8("window-new");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon4 = QIcon::fromTheme(iconThemeName);
        } else {
            icon4.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        openBrowserPushButton->setIcon(icon4);
        navHomePushButton = new QPushButton(wikitionaryTab);
        navHomePushButton->setObjectName(QString::fromUtf8("navHomePushButton"));
        navHomePushButton->setGeometry(QRect(10, 475, 91, 30));
        QIcon icon5;
        iconThemeName = QString::fromUtf8("go-home-symbolic");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon5 = QIcon::fromTheme(iconThemeName);
        } else {
            icon5.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        navHomePushButton->setIcon(icon5);
        navHomePushButton->setFlat(false);
        navRefreshPushButton = new QPushButton(wikitionaryTab);
        navRefreshPushButton->setObjectName(QString::fromUtf8("navRefreshPushButton"));
        navRefreshPushButton->setGeometry(QRect(110, 475, 91, 30));
        QIcon icon6;
        iconThemeName = QString::fromUtf8("view-refresh-symbolic");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon6 = QIcon::fromTheme(iconThemeName);
        } else {
            icon6.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        navRefreshPushButton->setIcon(icon6);
        navRefreshPushButton->setFlat(false);
        navBackPushButton = new QPushButton(wikitionaryTab);
        navBackPushButton->setObjectName(QString::fromUtf8("navBackPushButton"));
        navBackPushButton->setGeometry(QRect(210, 475, 91, 30));
        QIcon icon7;
        iconThemeName = QString::fromUtf8("go-previous-symbolic");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon7 = QIcon::fromTheme(iconThemeName);
        } else {
            icon7.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        navBackPushButton->setIcon(icon7);
        navBackPushButton->setFlat(true);
        navForwardPushButton = new QPushButton(wikitionaryTab);
        navForwardPushButton->setObjectName(QString::fromUtf8("navForwardPushButton"));
        navForwardPushButton->setGeometry(QRect(310, 475, 91, 30));
        QIcon icon8;
        iconThemeName = QString::fromUtf8("go-next-symbolic");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon8 = QIcon::fromTheme(iconThemeName);
        } else {
            icon8.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        navForwardPushButton->setIcon(icon8);
        navForwardPushButton->setFlat(true);
        QIcon icon9;
        iconThemeName = QString::fromUtf8("text-html-symbolic");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon9 = QIcon::fromTheme(iconThemeName);
        } else {
            icon9.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        wildcSearchMatchesTextEdit->addTab(wikitionaryTab, icon9, QString());
        historyPurgePushButton = new QPushButton(centralwidget);
        historyPurgePushButton->setObjectName(QString::fromUtf8("historyPurgePushButton"));
        historyPurgePushButton->setGeometry(QRect(760, 10, 31, 30));
        QIcon icon10;
        iconThemeName = QString::fromUtf8("edit-delete-symbolic");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon10 = QIcon::fromTheme(iconThemeName);
        } else {
            icon10.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        historyPurgePushButton->setIcon(icon10);
        historyPurgePushButton->setCheckable(false);
        historyPurgePushButton->setFlat(false);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        topSearchPushButton->setDefault(false);
        wildcSearchMatchesTextEdit->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
#if QT_CONFIG(whatsthis)
        MainWindow->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        topSearchLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Search word", nullptr));
        topSearchPushButton->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
#if QT_CONFIG(whatsthis)
        historySearchLineEdit->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        historySearchLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Search history", nullptr));
        donatePushButton->setText(QCoreApplication::translate("MainWindow", "Donate", nullptr));
        aboutPushButton->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        wildcSearchMatchesTextEdit->setTabText(wildcSearchMatchesTextEdit->indexOf(dictLookUpTab), QCoreApplication::translate("MainWindow", "Dictionary Look Up", nullptr));
        wildcSearchLookUpTextEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        wildcMatchesLabel->setText(QCoreApplication::translate("MainWindow", "Wildcard matches:", nullptr));
        wildcLookUpLabel->setText(QCoreApplication::translate("MainWindow", "Look up:", nullptr));
        wildcSearchMatchesTextEdit->setTabText(wildcSearchMatchesTextEdit->indexOf(wildcSearchTab), QCoreApplication::translate("MainWindow", "Wildcard Word Search", nullptr));
        openBrowserPushButton->setText(QCoreApplication::translate("MainWindow", "Open in browser", nullptr));
        navHomePushButton->setText(QCoreApplication::translate("MainWindow", "Home", nullptr));
        navRefreshPushButton->setText(QCoreApplication::translate("MainWindow", "Refresh", nullptr));
        navBackPushButton->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
        navForwardPushButton->setText(QCoreApplication::translate("MainWindow", "Forward", nullptr));
        wildcSearchMatchesTextEdit->setTabText(wildcSearchMatchesTextEdit->indexOf(wikitionaryTab), QCoreApplication::translate("MainWindow", "Wikitionary", nullptr));
        historyPurgePushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
