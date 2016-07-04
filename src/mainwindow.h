#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qnetworkreply.h"
#include "seriesbox.h"

enum Column
{
   NAME, CHAPTER, DATE, VOLUME, FOLDER, URL, DIGIT, EXT, WEEKLY
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
    void SeriesInfo(QStringList, int);

private slots:
    void slotTab1AddButton();
    void slotOpenFolder();
    void slotTab1OpenFolder();
    void slotTab1PrintPdf();
    void slotTab1OpenSeriesFolder();
    void AddLineStatusTable(QStringList NewLine);
    void ModifyStatusTable(QStringList NewLine, int Index);
    void TestUrl(QUrl url);
    void slotTab1Setting();
    void slotUpdateFolder();
    void slotTab1Pdf();
    void slotTab1Search();
    void slotTab1SearchOne();
    void slotTab1Delete();
    void messageErreur(QNetworkReply::NetworkError);
    void enregistrer();
    void downloadNextImage(bool lastStatus);
    QStringList GetLineInfos(int Idx);

private:
    Ui::MainWindow *ui;
    bool erreurTrouvee = false;
    SeriesBox CurrentSerie;
    QString GeneralFolder;
    int DownloadSeriesIdx = 0;
    int NumberOfSeriesSearch = 0;

    struct TestType
    {
       bool ExtJpg2 = false;
       bool ExtJpg3 = false;
       bool ExtJpg4 = false;
       bool ExtPng2 = false;
       bool ExtPng3 = false;
       bool ExtPng4 = false;
       bool SearchURL = false;
    };

    TestType CurrentStatus;
};

#endif // MAINWINDOW_H
