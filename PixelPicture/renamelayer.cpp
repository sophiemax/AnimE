#include "renamelayer.h"
#include "ui_renamelayer.h"

RenameLayer::RenameLayer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RenameLayer)
{
    ui->setupUi(this);
    ui->lineEdit->setFocus();
}

RenameLayer::~RenameLayer()
{
    delete ui;
}

void RenameLayer::setLineEdit(QString s)
{
    ui->lineEdit->setText(s);
}

void RenameLayer::on_lineEdit_editingFinished()
{
    name = ui->lineEdit->text();
    accept();
}
