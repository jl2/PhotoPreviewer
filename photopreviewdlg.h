/*
  Copyright (C) 2008 Jeremiah LaRocco

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

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
