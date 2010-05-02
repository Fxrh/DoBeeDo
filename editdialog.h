/**************************************************************************
 *                                                                        *
 * Copyright (C) 2010 Felix Rohrbach <fxrh@gmx.de>                        *
 *                                                                        *
 * This program is free software; you can redistribute it and/or          *
 * modify it under the terms of the GNU General Public License            *
 * as published by the Free Software Foundation; either version 3         *
 * of the License, or (at your option) any later version.                 *
 *                                                                        *
 * This program is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 * GNU General Public License for more details.                           *
 *                                                                        *
 * You should have received a copy of the GNU General Public License      *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.  *
 *                                                                        *
 **************************************************************************/ 

#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <KDialog>

class QLabel;
class KLineEdit;
class KComboBox;
class QCheckBox;
class QPlainTextEdit;
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;

class TodoObject;
class KDatePicker;
class KPushButton;

class EditDialog : public KDialog
  /* Edit the contents of one todo item (represented by an TodoObject).
   * Call editTodo with a pointer to a TodoObject and execute the dialog.
   * If the dialog is accepted by the user, the data of the TodoObject
   * is changed.
   */
{
  Q_OBJECT
public:
  EditDialog( QWidget* parent = 0 );
  // call this before executing the dialog
  void editTodo( TodoObject* object );
  
public slots:
  // write back the inserted data to the TodoObject
  void accept();
  
private slots:
  // check if the categories have been changed
  void configChanged();
  
private:
  void setupUi();
  
  QLabel* nameLabel;
  KLineEdit* nameEdit;
  QLabel* priorityLabel;
  KComboBox* priorityBox;
  QLabel* categoryLabel;
  KComboBox* categoryBox;
  QLabel* descriptionLabel;
  QPlainTextEdit* descriptionEdit;
  QCheckBox* dateBox;
  KDatePicker* datePicker;
  QGridLayout* nameLayout;
  QVBoxLayout* dateLayout;
  QHBoxLayout* mainLayout;
  
  TodoObject* todo;
};

#endif //EDITDIALOG_H
