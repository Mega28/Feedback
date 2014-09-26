#ifndef NEWSTUDENTDIALOG_H
#define NEWSTUDENTDIALOG_H

#include <QDialog>

namespace Ui {
class NewStudentDialog;
}

class NewStudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewStudentDialog(QWidget *parent = 0);
    QString getSeat();
    QString getFirstName();
    QString getLastName();
    QString getEmail();
    QString getYear();
    QString getSection();
    ~NewStudentDialog();

private:
    Ui::NewStudentDialog *ui;
};

#endif // NEWSTUDENTDIALOG_H
