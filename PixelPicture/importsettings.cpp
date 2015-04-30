#include "importsettings.h"
#include "ui_importsettings.h"

ImportSettings::ImportSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportSettings)
{
    ui->setupUi(this);

    /*QButtonGroup *group = new QButtonGroup(this);
    group->addButton(ui->onlypixels);
    group->addButton(ui->wholeimage);
    group->setExclusive(true);*/
}

ImportSettings::~ImportSettings()
{
    delete ui;
}

void ImportSettings::on_onlypixels_clicked()
{
    scene->importsettingsresolution = PixelScene::ImportSettingsResolution::onlypixels;
    converter->importsettingsresolution = ImageConverterTool::ImportSettingsResolution::onlypixels;
}

void ImportSettings::on_wholeimage_clicked()
{
    scene->importsettingsresolution = PixelScene::ImportSettingsResolution::wholeimage;
    converter->importsettingsresolution = ImageConverterTool::ImportSettingsResolution::wholeimage;
}

void ImportSettings::on_topleft_clicked()
{
    converter->importsettingscolor = ImageConverterTool::ImportSettingsColor::topleft;
}

void ImportSettings::on_center_clicked()
{
    converter->importsettingscolor = ImageConverterTool::ImportSettingsColor::center;
}

void ImportSettings::on_corners_clicked()
{
    converter->importsettingscolor = ImageConverterTool::ImportSettingsColor::corners;
}

void ImportSettings::on_average_clicked()
{
    converter->importsettingscolor = ImageConverterTool::ImportSettingsColor::average;
}
