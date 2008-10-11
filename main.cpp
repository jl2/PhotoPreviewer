/*
  photo_prev: Application to assist in sorting through photographs.
  Copyright (C) 2008  Jeremiah LaRocco

  This file is part of photo_prev.

  photo_prev is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  photo_prev is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with photo_prev.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QApplication>

#include "photopreviewdlg.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  PhotoPreviewDlg window;

  window.show();
  
  return app.exec();
}
