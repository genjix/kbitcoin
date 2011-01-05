#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KLocale>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    int bitcoind_return = system("bitcoind");

  KAboutData aboutData("kbitcoin", 0,
      ki18n("KBitcoin"), "0.5",
      ki18n("Bitcoin interface"),
      KAboutData::License_GPL,
      ki18n("Copyright (c) 2007 Genjix"));
  KCmdLineArgs::init(argc, argv, &aboutData);

  KApplication app;

  MainWindow* window = new MainWindow();
  window->show();

  return app.exec();
}
