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
private slots:
    void slotTab1Setting();
private slots:
    void slotTab1Pdf();
private slots:
    void slotTab1Search();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
