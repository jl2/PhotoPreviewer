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

#include <QtGui>

#include "photopreviewdlg.h"

PhotoPreviewDlg::PhotoPreviewDlg(QWidget *parent) : QDialog(parent) {

  ftw = false;
  buildImageList(QDir::currentPath());

  setWindowTitle(tr("Photo Previewer"));

  // Setup GUI here...

  QVBoxLayout *theLayout = new QVBoxLayout;
  QHBoxLayout *input_layout = new QHBoxLayout;
  QHBoxLayout *accept_layout = new QHBoxLayout;
  QHBoxLayout *reject_layout = new QHBoxLayout;
  QHBoxLayout *fname_layout = new QHBoxLayout;
  QHBoxLayout *ar_buttons_layout = new QHBoxLayout;
  QHBoxLayout *zoom_layout = new QHBoxLayout;
  QHBoxLayout *extensions_layout = new QHBoxLayout;

  QCompleter *input_completer = new QCompleter(this);
  input_completer->setCompletionMode(QCompleter::InlineCompletion);
  QDirModel *indm = new QDirModel(input_completer);
  indm->index(QDir::currentPath());
  indm->setFilter(QDir::AllDirs | QDir::Dirs
		   | QDir::NoDotAndDotDot | QDir::CaseSensitive);

  input_completer->setModel(indm);
  input_completer->setCompletionPrefix(QDir::currentPath());
  
  input_dir_lbl = new QLabel(tr("Accept directory"));
  input_dir_tb = new QLineEdit(QDir::currentPath());
  input_dir_tb->setCompleter(input_completer);
  input_dir_choose = new QPushButton(QIcon(":/icons/fileopen.png"),"");
  input_layout->addWidget(input_dir_lbl);
  input_layout->addWidget(input_dir_tb);
  input_layout->addWidget(input_dir_choose);

  
  QCompleter *accept_completer = new QCompleter(this);
  accept_completer->setCompletionMode(QCompleter::InlineCompletion);
  QDirModel *accdm = new QDirModel(accept_completer);
  accdm->index(QDir::currentPath());
  accdm->setFilter(QDir::AllDirs | QDir::Dirs
		   | QDir::NoDotAndDotDot | QDir::CaseSensitive);

  accept_completer->setModel(accdm);
  accept_completer->setCompletionPrefix(QDir::currentPath()+tr("/accept"));

  
  QCompleter *reject_completer = new QCompleter(this);
  reject_completer->setCompletionMode(QCompleter::InlineCompletion);
  QDirModel *outdm = new QDirModel(accept_completer);
  outdm->index(QDir::currentPath());
  outdm->setFilter(QDir::AllDirs | QDir::Dirs
		   | QDir::NoDotAndDotDot | QDir::CaseSensitive);
  reject_completer->setModel(outdm);
  reject_completer->setCompletionPrefix(QDir::currentPath()+tr("/reject"));
  
  accept_dir_lbl = new QLabel(tr("Accept directory"));
  accept_dir_tb = new QLineEdit(QDir::currentPath() + tr("/accept"));
  accept_dir_tb->setCompleter(accept_completer);
  accept_dir_choose = new QPushButton(QIcon(":/icons/fileopen.png"),"");
  accept_layout->addWidget(accept_dir_lbl);
  accept_layout->addWidget(accept_dir_tb);
  accept_layout->addWidget(accept_dir_choose);
  
  reject_dir_lbl = new QLabel(tr("Reject directory"));
  reject_dir_tb = new QLineEdit(QDir::currentPath() + tr("/reject"));
  reject_dir_tb->setCompleter(reject_completer);
  reject_dir_choose = new QPushButton(QIcon(":/icons/fileopen.png"),"");
  reject_layout->addWidget(reject_dir_lbl);
  reject_layout->addWidget(reject_dir_tb);
  reject_layout->addWidget(reject_dir_choose);


  fname_lbl_lbl = new QLabel(tr("File name: "));
  fname_lbl = new QLabel(tr(""));
  fname_layout->addWidget(fname_lbl_lbl);
  fname_layout->addWidget(fname_lbl);
  
  accept_image = new QPushButton(tr("Accept"));
  reject_image = new QPushButton(tr("Reject"));
  skip_image = new QPushButton(tr("Skip"));
  ar_buttons_layout->addWidget(accept_image);
  ar_buttons_layout->addWidget(reject_image);
  ar_buttons_layout->addWidget(skip_image);
  
  fit_to_window = new QPushButton(tr("Fit To Window"));
  normal_size = new QPushButton(tr("Actual Size"));
  zoom_lbl = new QLabel(tr("Zoom: 100%"));
  zoom_layout->addWidget(fit_to_window);
  zoom_layout->addWidget(normal_size);
  zoom_layout->addWidget(zoom_lbl);

  extensions_lbl = new QLabel(tr("Extensions to move"));
  extensions_tb = new QLineEdit(tr(".jpg,.JPG,.cr2,.CR2"));
  extensions_layout->addWidget(extensions_lbl);
  extensions_layout->addWidget(extensions_tb);
  
  img_lbl = new QLabel;

  if (files.size()>0) {
    updatePreview();
  }
  
  img_scroller = new QScrollArea;
  img_scroller->setBackgroundRole(QPalette::Dark);
  img_scroller->setWidget(img_lbl);
  
  theLayout->addLayout(input_layout);
  theLayout->addLayout(accept_layout);
  theLayout->addLayout(reject_layout);
  theLayout->addLayout(fname_layout);
  theLayout->addWidget(img_scroller);
  theLayout->addLayout(ar_buttons_layout);
  theLayout->addLayout(zoom_layout);
  theLayout->addLayout(extensions_layout);
  setLayout(theLayout);
  setupConnections();
  update_extension_list();
}

void PhotoPreviewDlg::setupConnections() {
  
  connect(input_dir_choose, SIGNAL(clicked()),
	  this, SLOT(chooseInputDir()));
  
  connect(accept_dir_choose, SIGNAL(clicked()),
	  this, SLOT(chooseAcceptDir()));
  
  connect(reject_dir_choose, SIGNAL(clicked()),
	  this, SLOT(chooseRejectDir()));

  connect(accept_image, SIGNAL(clicked()),
	  this, SLOT(accept_button()));
  connect(reject_image, SIGNAL(clicked()),
	  this, SLOT(reject_button()));
  connect(skip_image, SIGNAL(clicked()),
	  this, SLOT(skip_button()));
  connect(fit_to_window, SIGNAL(clicked()),
	  this, SLOT(ftw_button()));
  connect(normal_size, SIGNAL(clicked()),
	  this, SLOT(actual_size_button()));
  
  connect(extensions_tb, SIGNAL(textChanged(const QString &)),
	  this, SLOT(update_extension_list()));
  connect(input_dir_tb, SIGNAL(editingFinished()),
	  this, SLOT(inputDirChange()));

}

void PhotoPreviewDlg::criticalErr(QString errMsg) {
  QMessageBox::critical(this,
			tr("Error"),
			errMsg,
			QMessageBox::Ok,
			QMessageBox::NoButton,
			QMessageBox::NoButton);
}

void PhotoPreviewDlg::chooseInputDir() {
  QString fileName =
    QFileDialog::getExistingDirectory(this,
				      tr("Choose an input directory"),
				      input_dir_tb->text());
				 
  if (fileName == tr("")) {
    return;
  }
  input_dir_tb->setText(fileName);
  buildImageList(fileName);
  curIdx = 0;
  updatePreview();
}

void PhotoPreviewDlg::inputDirChange() {
  if (input_dir_tb->text() == tr("")) {
    return;
  }
  if (QDir(input_dir_tb->text()).exists()) {
    buildImageList(input_dir_tb->text());
    curIdx = 0;
    updatePreview();
  }
}


void PhotoPreviewDlg::chooseAcceptDir() {
  QString fileName =
    QFileDialog::getExistingDirectory(this,
				      tr("Choose a directory"),
				      accept_dir_tb->text());
				 
  if (fileName == tr("")) {
    return;
  }
  accept_dir_tb->setText(fileName);
}

void PhotoPreviewDlg::chooseRejectDir() {
  QString fileName =
    QFileDialog::getExistingDirectory(this,
				      tr("Choose a directory"),
				      reject_dir_tb->text());
  if (fileName == tr("")) {
    return;
  }
  reject_dir_tb->setText(fileName);
}


void PhotoPreviewDlg::buildImageList(QString where) {

  QDir imgDir(where);
  QStringList filters;
  filters += "*.jpg";
  
  files = imgDir.entryList(filters, QDir::Files, QDir::IgnoreCase | QDir::Name);
  curIdx = 0;  
}

void PhotoPreviewDlg::accept_button() {
  if (curIdx >= files.size()) {
    return;
  }
  
  QDir id(input_dir_tb->text());
  QDir od(accept_dir_tb->text());

  foreach (QString ext, extensions) {
    QString fn = files[curIdx];
    int extIdx = fn.lastIndexOf(tr(".jpg"), -1, Qt::CaseInsensitive);
    fn.replace(extIdx, 4, ext);
    
    QFile tf(id.filePath(fn));
    if (tf.exists()) {
      tf.rename(od.filePath(fn));
    }
  }
  
  files.erase(files.begin());
  updatePreview();
}

void PhotoPreviewDlg::reject_button() {
  if (curIdx >= files.size()) {
    return;
  }
  
  QDir id(input_dir_tb->text());
  QDir od(reject_dir_tb->text());

  foreach (QString ext, extensions) {
    QString fn = files[curIdx];
    int extIdx = fn.lastIndexOf(tr(".jpg"), -1, Qt::CaseInsensitive);
    fn.replace(extIdx, 4, ext);

    QFile tf(id.filePath(fn));
    if (tf.exists()) {
      tf.rename(od.filePath(fn));
    }
  }

  files.erase(files.begin());
  updatePreview();
}

void PhotoPreviewDlg::skip_button() {
  if (curIdx < files.size()-1) {
    ++curIdx;
    updatePreview();
    return;
  }
  curIdx = 0;
  updatePreview();
}

void PhotoPreviewDlg::ftw_button() {
  ftw = true;
  updatePreview();
}

void PhotoPreviewDlg::actual_size_button() {
  ftw = false;
  updatePreview();
}

void PhotoPreviewDlg::update_extension_list() {
  QStringList exts = extensions_tb->text().split(",");
  
  if (exts.size()>0) {
    extensions.clear();
    QStringList::const_iterator iter;
    for (iter = exts.constBegin(); iter != exts.end(); ++iter) {
      extensions += *iter;
    }
  }
}

void PhotoPreviewDlg::updatePreview() {
  if (curIdx >= files.size()) {
    img_lbl->setPixmap(QPixmap());
    img_lbl->setText(tr("None"));
    fname_lbl->setText(tr("No files!"));
    return;
  }

  QDir id(input_dir_tb->text());

  QString infn = id.filePath(files[curIdx]);

  if (!curImage.load(infn)) {
    fname_lbl->setText(tr("Error!!"));
    img_lbl->setText(tr("Error!!"));
    criticalErr(tr("Error creating preview image for: ") + infn);
    return;
  }
  
  img_lbl->setText(tr(""));
  
  fname_lbl->setText(infn);
  

  
  if (ftw) {
    curImage = curImage.scaled( img_scroller->width()-4, img_scroller->height()-4, Qt::KeepAspectRatio, Qt::SmoothTransformation);
  }
  img_lbl->setPixmap(QPixmap::fromImage(curImage));  
  img_lbl->resize(curImage.size());
}
