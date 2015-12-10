#include "videoconvertersettings.h"
#include "ui_videoconvertersettings.h"
#include "QTextStream"

VideoConverterSettings::VideoConverterSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VideoConverterSettings)
{
    ui->setupUi(this);
}

VideoConverterSettings::~VideoConverterSettings()
{
    delete ui;
}

void VideoConverterSettings::on_trimButton_toggled(bool checked)
{
    trim = checked;
}

void VideoConverterSettings::on_OKButton_clicked()
{
    import = true;
    if(trim)
    {
       from = ui->fromLine->text().toInt();
       to = ui->toLine->text().toInt();
    }
    accept();
}

void VideoConverterSettings::on_cancelButton_clicked()
{
    import = false;
    accept();
}
