// Copyright (C) 2016 The Regents of the University of California
//
// Created by David W. Shattuck, Ph.D.
//
// This file is part of BrainSuite16a1.
//
// BrainSuite16a1 is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; version 2.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
// USA.
//

#ifndef BRAINSUITEWINDOW_T_H
#define BRAINSUITEWINDOW_T_H

template <class CurrentDialogType, class NextDialogType>
void BrainSuiteWindow::swapDialogs(CurrentDialogType *currentDialog, std::unique_ptr<NextDialogType> &nextDialog)
{
  if (!nextDialog)
  {
    nextDialog.reset(new NextDialogType(this));
  }
  if (nextDialog)
  {
    if (currentDialog)
    {
      nextDialog->move(currentDialog->pos());
      currentDialog->hide();
    }
    nextDialog->show();
    nextDialog->raise();
  }
}

template <class DialogType> void BrainSuiteWindow::showDialog(std::unique_ptr<DialogType> &dialog)
{
  if (!dialog)
    dialog.reset(new DialogType(this));
  if (dialog)
  {
    dialog->setWindowFlags(dialog->windowFlags() | Qt::Tool);
    dialog->show();
  }
}

#endif // BRAINSUITEWINDOW_T_H

