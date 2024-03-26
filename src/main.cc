#include <QApplication>

#include "view/glwidget.h"
#include "view/mainwindow.h"

using namespace s21;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
