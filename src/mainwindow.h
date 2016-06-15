#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void slotTab1AddButton();
    void slotTab1Setting();
    void slotTab1Pdf();
    void slotTab1Search();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
