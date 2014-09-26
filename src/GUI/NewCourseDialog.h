#ifndef NEWCOURSEDIALOG_H
#define NEWCOURSEDIALOG_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class NewCourseDialog;
}

class NewCourseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewCourseDialog(QWidget *parent = 0);
    ~NewCourseDialog();

    void courseDirectoryButtonClicked();
    void courseDirectoryLineEditChanged();
    QString getCourseName();
    QString getCourseCode();
    QString getFileName();
    QString getDirectory();
private:
    Ui::NewCourseDialog *ui;
    QPalette* mLineEditPalette;
    QPushButton* mOkButton;
};

#endif // NEWCOURSEDIALOG_H
