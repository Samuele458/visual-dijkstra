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

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QListWidget>
#include <QListWidgetItem>
#include <QStackedWidget>
#include <QHBoxLayout>

#include "common/settingsmanager.h"
#include "widgets/settingspage.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    SettingsDialog( SettingsManager* settings, QWidget* parent = nullptr);

    SettingsManager* getSettingsManager() const;

private slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);

private:
    void createIcons();

    SettingsManager* settings;

    //left sidebar with icons, each one for a specific settings page
    QListWidget* contentsList;

    QStackedWidget* pagesWidget;

    QHBoxLayout* mainLayout;
    QHBoxLayout* buttonsBar;
    QVBoxLayout* rightSideLayout;

    QPushButton* saveButton;
    QPushButton* cancelButton;


};

#endif // SETTINGSDIALOG_H
