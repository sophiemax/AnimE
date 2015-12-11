#include "colorconverteroptions.h"
#include "ui_colorconverteroptions.h"

ColorConverterOptions::ColorConverterOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorConverterOptions)
{
    ui->setupUi(this);
}

ColorConverterOptions::~ColorConverterOptions()
{
    delete ui;
}

void ColorConverterOptions::on_inverzButton_clicked()
{
    option = ColorConverterOptions::Options::inverz;
    accept();
}

void ColorConverterOptions::on_bnwButton_clicked()
{
    option = ColorConverterOptions::Options::blackandwhite;
    accept();
}

void ColorConverterOptions::on_greyScaleButton_clicked()
{
    option = ColorConverterOptions::Options::greyscale;
    accept();
}

void ColorConverterOptions::on_filterButton_clicked()
{
    option = ColorConverterOptions::Options::filter;
    accept();
}

void ColorConverterOptions::on_sepiaButton_clicked()
{
    option = ColorConverterOptions::Options::sepia;
    accept();
}

void ColorConverterOptions::on_contrastButton_clicked()
{
    option = ColorConverterOptions::Options::contrast;
    accept();
}

void ColorConverterOptions::on_srButton_clicked()
{
    option = ColorConverterOptions::Options::shiftright;
    accept();
}

void ColorConverterOptions::on_slButton_clicked()
{
    option = ColorConverterOptions::Options::shiftleft;
    accept();
}

void ColorConverterOptions::on_cancelButton_clicked()
{
    cancelled = true;
    accept();
}
