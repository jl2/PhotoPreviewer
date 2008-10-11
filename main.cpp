
#include <QApplication>

#include "photopreviewdlg.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  PhotoPreviewDlg window;

  window.show();
  
  return app.exec();
}
