#ifndef ADD_H
#define ADD_H

#include <QWidget>

namespace Ui {
class Add;
}

class Add : public QWidget
{
    Q_OBJECT

public:
    explicit Add(QWidget *parent = 0);
    ~Add();

signals:
    void addNewSerie(QStringList);

private slots:
    void slotAddOkButton();
    void slotAddCancelButton();

private:
    Ui::Add *ui;
};

#endif // ADD_H
