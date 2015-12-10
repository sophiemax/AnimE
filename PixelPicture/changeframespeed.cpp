#include "changeframespeed.h"
#include "ui_changeframespeed.h"

ChangeFrameSpeed::ChangeFrameSpeed(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeFrameSpeed)
{
    ui->setupUi(this);
}

ChangeFrameSpeed::~ChangeFrameSpeed()
{
    delete ui;
}

void ChangeFrameSpeed::on_OKButton_clicked()
{
    speed = ui->speedLine->text().toFloat();
    accept();
}

void ChangeFrameSpeed::on_cancelButton_clicked()
{
    speed = 1.0;
    accept();
}
