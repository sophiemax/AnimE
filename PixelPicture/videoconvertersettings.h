#ifndef VIDEOCONVERTERSETTINGS_H
#define VIDEOCONVERTERSETTINGS_H

#include <QDialog>

namespace Ui {
class VideoConverterSettings;
}

class VideoConverterSettings : public QDialog
{
    Q_OBJECT

public:
    explicit VideoConverterSettings(QWidget *parent = 0);
    ~VideoConverterSettings();

    bool trim = false, import = false;
    int from = 0, to = 0;

private slots:
    void on_trimButton_toggled(bool checked);

    void on_OKButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::VideoConverterSettings *ui;
};

#endif // VIDEOCONVERTERSETTINGS_H
