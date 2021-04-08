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

#include "settingsdialog.h"

SettingsDialog::SettingsDialog( SettingsManager* settings, QWidget* parent ) :
    QDialog( parent)
{
    this->settings = settings;

    contentsList = new QListWidget;
    contentsList->setViewMode(QListView::IconMode);
    contentsList->setIconSize(QSize(80,80));
    contentsList->setMovement(QListView::Static);
    contentsList->setMaximumWidth(128);
    contentsList->setSpacing(12);

    pagesWidget = new QStackedWidget;
    pagesWidget->addWidget( new StylePage(this->settings) );
    pagesWidget->addWidget( new DefaultPage(this->settings) );

    saveButton = new QPushButton("Save");
    connect( saveButton, SIGNAL(clicked()), this, SLOT(saveButtonClicked()));

    cancelButton = new QPushButton("Cancel");
    connect( cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));

    buttonsBar = new QHBoxLayout;
    buttonsBar->addStretch();
    buttonsBar->addWidget(cancelButton);
    buttonsBar->addWidget(saveButton);

    rightSideLayout = new QVBoxLayout;
    rightSideLayout->addWidget(pagesWidget);
    rightSideLayout->addStretch();
    rightSideLayout->addLayout(buttonsBar);

    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(contentsList);
    mainLayout->addLayout(rightSideLayout);

    createIcons();
    contentsList->setCurrentRow(0);

    this->setLayout(mainLayout);

}

SettingsManager *SettingsDialog::getSettingsManager() const
{
    return this->settings;
}

void SettingsDialog::createIcons()
{
    QListWidgetItem* styleButton = new QListWidgetItem(contentsList);
    styleButton->setIcon(QIcon(":/data/icons/paintbrush.png"));
    styleButton->setText("Style");
    styleButton->setTextAlignment(Qt::AlignHCenter);
    styleButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);


    QListWidgetItem* defaultButton = new QListWidgetItem(contentsList);
    defaultButton->setIcon(QIcon(":/data/icons/gear.png"));
    defaultButton->setText("General");
    defaultButton->setTextAlignment(Qt::AlignHCenter);
    defaultButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    connect(contentsList, &QListWidget::currentItemChanged, this, &SettingsDialog::changePage);
}

void SettingsDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsList->row(current));
}

void SettingsDialog::saveButtonClicked() {
    for( int i = 0; this->pagesWidget->widget(i) != nullptr; ++i ) {
        ((SettingsPage*)pagesWidget->widget(i))->saveState();
    }
    this->close();
}

void SettingsDialog::cancelButtonClicked() {
    this->close();
}
