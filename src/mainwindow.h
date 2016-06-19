#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qnetworkreply.h"

enum Column
{
   NAME, CHAPTER, DATE, VOLUME, FOLDER, URL
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void SeriesInfo(QStringList);

private slots:
    void slotTab1AddButton();
    void AddLineStatusTable(QStringList NewLine);
    void ModifyStatusTable(QStringList NewLine);
    void slotTab1Setting();
    void slotTab1Pdf();
    void slotTab1Search();
    void slotTab1Delete();
    void loadImage();
    QStringList GetLineInfos(int Idx);
    void messageErreur(QNetworkReply::NetworkError);
    void enregistrer();

private:
    Ui::MainWindow *ui;
    bool erreurTrouvee = false;
};

#endif // MAINWINDOW_H
