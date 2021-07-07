#ifndef QCUSTOMPLOTWIN_H
#define QCUSTOMPLOTWIN_H

#include <QMainWindow>
#include "stock.h"

QT_BEGIN_NAMESPACE
namespace Ui { class QCustomPlotWin; }
QT_END_NAMESPACE

class QCustomPlotWin : public QMainWindow
{
    Q_OBJECT

public:
    QCustomPlotWin(QVector<Stock> Rec,QWidget *parent = nullptr);
    ~QCustomPlotWin();

private:
    Ui::QCustomPlotWin *ui;
};
#endif // QCUSTOMPLOTWIN_H
