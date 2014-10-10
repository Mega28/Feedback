#ifndef NEWCOURSEDIALOG_H
#define NEWCOURSEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <memory>

namespace Ui {
class NewCourseDialog;
}
namespace Feedback {
    class CourseInfo;

}

class NewCourseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewCourseDialog(QWidget *parent = 0);
    ~NewCourseDialog();

    void courseDirectoryButtonClicked();
    void courseDirectoryLineEditChanged();
    std::shared_ptr<Feedback::CourseInfo> getCourseInfo();
private:
    Ui::NewCourseDialog *ui;
    QPalette* mLineEditPalette;
    QPushButton* mOkButton;
};

#endif // NEWCOURSEDIALOG_H
