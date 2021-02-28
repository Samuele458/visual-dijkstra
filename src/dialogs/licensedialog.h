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
