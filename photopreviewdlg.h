/*
  photo_prev: Application to assist in sorting through photographs.
  Copyright (C) 2008  Jeremiah LaRocco

  This file is part of photo_prev.

  photo_prev is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Foobar is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PHOTO_PREVIEW_DLG_H
#define PHOTO_PREVIEW_DLG_H

#include <QDialog>

class QAction;
class QLabel;
class QLineEdit;
class QPushButton;
class QScrollArea;
class QString;

class PhotoPreviewDlg : public QDialog {
  Q_OBJECT;

 public:
  PhotoPreviewDlg(QWidget *parent = 0);
  private slots:
  void chooseInputDir();
  void chooseAcceptDir();
  void chooseRejectDir();

void accept_button();

void reject_button();

void skip_button();

void ftw_button();

void actual_size_button();
 
 void update_extension_list();
 void inputDirChange();
 
 private:
  void setupConnections();
  void criticalErr(QString errMsg);
  void updatePreview();
 
  QLabel *input_dir_lbl;
  QLineEdit *input_dir_tb;
  QPushButton *input_dir_choose;
  
  QPushButton *accept_dir_choose;  
  QLabel *accept_dir_lbl;
  QLineEdit *accept_dir_tb;

  QLabel *reject_dir_lbl;
  QLineEdit *reject_dir_tb;
  QPushButton *reject_dir_choose;

  QLabel *fname_lbl_lbl;
  QLabel *fname_lbl;

  QImage curImage;
  QLabel *img_lbl;
  QScrollArea *img_scroller;
  
  QPushButton *accept_image;
  QPushButton *reject_image;
  QPushButton *skip_image;
  
  QPushButton *fit_to_window;
  QPushButton *normal_size;
  QLabel *zoom_lbl;

  QLabel *extensions_lbl;
  QLineEdit *extensions_tb;

  QStringList files;
  QStringList::size_type curIdx;
  void buildImageList(QString where);

  QStringList extensions;

  bool ftw;
  
};

#endif
