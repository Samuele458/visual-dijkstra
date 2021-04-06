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


};

#endif // SETTINGSDIALOG_H
