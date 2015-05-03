#ifndef IMPORTSETTINGS_H
#define IMPORTSETTINGS_H

#include <QDialog>
#include "imageconvertertool.h"

namespace Ui {
class ImportSettings;
}

class ImportSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ImportSettings(QWidget *parent = 0);
    ~ImportSettings();

    ImageConverterTool *converter;

private slots:
    void on_onlypixels_clicked();

    void on_wholeimage_clicked();

    void on_topleft_clicked();

    void on_center_clicked();

    void on_corners_clicked();

    void on_average_clicked();

    void on_blackisclear_toggled(bool checked);

private:
    Ui::ImportSettings *ui;
};

#endif // IMPORTSETTINGS_H
