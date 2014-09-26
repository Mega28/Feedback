#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Model.h"
#include "../ErrorHandler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public ErrorHandler
{
    Q_OBJECT

public:
    explicit MainWindow(Model* model,QWidget *parent = 0 );
    ~MainWindow();
    void showAbout();
    virtual void showMsg(std::string const& error, ERROR_LVL level);


    void showStudentsWindow();
    void showNewCourse();
private:
    Ui::MainWindow *ui;
    Model* mModel;
};

#endif // MAINWINDOW_H
