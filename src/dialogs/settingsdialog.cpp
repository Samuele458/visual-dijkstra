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
    pagesWidget->addWidget( new StylePage(this->settings,"style") );

    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(contentsList);
    mainLayout->addWidget(pagesWidget);

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
}

void SettingsDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsList->row(current));
}
