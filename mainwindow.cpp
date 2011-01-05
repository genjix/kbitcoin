#include "mainwindow.h"

#include <stdio.h>
// temporary!
#include <iostream>
using std::cout;
using std::cerr;

#include <qjson/parser.h>
 
#include <KApplication>
#include <KAction>
#include <KLocale>
#include <KActionCollection>
#include <KStandardAction>
 
MainWindow::MainWindow(QWidget *parent)
    : KXmlGuiWindow(parent)
{
    balance_sheet = new QTableWidget;
    balance_sheet->setColumnCount(5);
    QStringList header;
    header << "Status" << "Date" << "Description" << "Credit" << "Balance";
    balance_sheet->setHorizontalHeaderLabels(header);
    ReadTransactions();

    setCentralWidget(balance_sheet);
 
    setupActions();
}

bool ReadCommand(QByteArray &out, const char* cmd)
{
    FILE *output = popen(cmd, "r");
    if (!output) {
        // error!
        cerr << "Error: couldn't list transactions.\n";
        return false;
    }
    char buf[BUFSIZ];
    while(fgets(buf, BUFSIZ, output) != NULL) {
        //out.append(buf, BUFSIZ);
        out.append(buf);
    }
    pclose(output);
    return true;
}

void MainWindow::ReadTransactions()
{
    QByteArray json;
    if (!ReadCommand(json, "bitcoind listtransactions \"\"")) {
        cerr << "Error: couldn't run command.";
        return;
    }

    QJson::Parser parser;
    bool ok;

    //const char *a_json = "{\"hello\": \"jon\", \"djd\": \"test\"}";
    const char *a_json = "[\"vel\", \"dkdjk\", \"third\"]";
    QVariant result = parser.parse(a_json, &ok).toMap();
    if (!ok) {
        cerr << "Error: an error occurred during parsing";
        return;
    }

    foreach (QVariant transaction, result.toList()) {
        //cout << transaction.toMap()["amount"].toInt();
        cout << transaction.toString().toUtf8().data() << "\n";
    }

    balance_sheet->insertRow(0);
    balance_sheet->setItem(0, 0, new QTableWidgetItem("Blaaa!"));
}
 
void MainWindow::setupActions()
{
  KAction* clearAction = new KAction(this);
  clearAction->setText(i18n("&Clear"));
  clearAction->setIcon(KIcon("document-new"));
  clearAction->setShortcut(Qt::CTRL + Qt::Key_W);
  actionCollection()->addAction("clear", clearAction);
  //connect(clearAction, SIGNAL(triggered(bool)),
  //        balance_sheet, SLOT(clear()));
 
  KStandardAction::quit(kapp, SLOT(quit()),
                        actionCollection());
 
  setupGUI(Default, "kbitcoinui.rc");
}
