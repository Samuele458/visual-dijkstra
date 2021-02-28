#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDesktopServices>
#include <QUrl>

#include "dialogs/licensedialog.h"

class AboutDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AboutDialog(QWidget *parent = nullptr);

    ~AboutDialog();

protected slots:
    void ok_button_clicked();
    void official_page_button_clicked();
    void license_button_clicked();

protected:


    //widgets
    QVBoxLayout* MainLayout;

    QGridLayout* InfoLayout;
    QLabel* VersionLeftLabel;
    QLabel* VersionRightLabel;
    QLabel* DateLeftLabel;
    QLabel* DateRightLabel;
    QLabel* LicenseLeftLabel;
    QLabel* LicenseRightLabel;
    QLabel* AuthorLeftLabel;
    QLabel* AuthorRightLabel;
    QLabel* EmailLeftLabel;
    QLabel* EmailRightLabel;
    QLabel* GithubLeftLabel;
    QLabel* GithubRightLabel;

    QHBoxLayout* ButtonsLayout;
    QPushButton* OfficialPageButton;
    QPushButton* LicenseButton;
    QPushButton* OkButton;

};

#endif // ABOUTDIALOG_H
