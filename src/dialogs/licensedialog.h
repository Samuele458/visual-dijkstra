/*          Visual Dijkstra
 *    Copyright (C) 2021 Samuele Girgenti
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * 	     --  CONTACTS --
 *   Email:      samuele.girgenti458@gmail.com
 *   Github:     https://github.com/Samuele458
 */

#ifndef LICENSEDIALOG_H
#define LICENSEDIALOG_H

#include <QMainWindow>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QFile>
#include <QFont>

class LicenseDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LicenseDialog(QWidget *parent = nullptr);
protected slots:
    void ok_button_clicked();

private:

    //widgets
    QVBoxLayout* MainLayout;
    QLabel* TitleLabel;
    QTextEdit* LicenseEdit;
    QHBoxLayout* ButtonsLayout;
    QPushButton* OkButton;

};

#endif // LICENSEDIALOG_H
