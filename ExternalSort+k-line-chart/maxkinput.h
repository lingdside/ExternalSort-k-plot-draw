#ifndef MAXKINPUT_H
#define MAXKINPUT_H

#include <QWidget>

namespace Ui {
class Maxkinput;
}

class Maxkinput : public QWidget
{
    Q_OBJECT

public:
    explicit Maxkinput(QWidget *parent = nullptr);
    ~Maxkinput();

private slots:
    void on_pushButton_clicked();

    void on_CLOSE_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Maxkinput *ui;
};

#endif // MAXKINPUT_H
