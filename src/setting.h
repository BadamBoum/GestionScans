#ifndef SETTING_H
#define SETTING_H

#include <QWidget>

namespace Ui {
class Setting;
}

class Setting : public QWidget
{
   Q_OBJECT

public:
   explicit Setting(QWidget *parent = 0);
   ~Setting();

signals:
    void ModifySerie(QStringList);

public slots:
    void FillWindow(QStringList Datas);

private slots:
    void slotOkButton();
    void slotCancelButton();

private:
   Ui::Setting *ui;
};

#endif // SETTING_H
