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
    void AddLineStatusTable(QString NewLine);
    void slotTab1Setting();
    void slotTab1Pdf();
    void slotTab1Search();
    void slotTab1Delete();
private:
    Ui::MainWindow *ui;
    enum Column
    {
       NAME, CHAPTER, DATE, VOLUME, FOLDER, URL
    };
};

#endif // MAINWINDOW_H
