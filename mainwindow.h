#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTableWidget>

#include <KXmlGuiWindow>

class MainWindow : public KXmlGuiWindow
{
  public:
    MainWindow(QWidget *parent=0);

  private:
    void setupActions();
    void ReadTransactions();
    QTableWidget *balance_sheet;
};

#endif
