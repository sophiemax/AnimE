#ifndef CHANGEFRAMESPEED_H
#define CHANGEFRAMESPEED_H

#include <QDialog>

namespace Ui {
class ChangeFrameSpeed;
}

class ChangeFrameSpeed : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeFrameSpeed(QWidget *parent = 0);
    ~ChangeFrameSpeed();

    float speed = 1.0;

private slots:
    void on_OKButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::ChangeFrameSpeed *ui;
};

#endif // CHANGEFRAMESPEED_H
