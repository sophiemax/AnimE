#ifndef RENAMELAYER_H
#define RENAMELAYER_H

#include <QDialog>

namespace Ui {
class RenameLayer;
}

class RenameLayer : public QDialog
{
    Q_OBJECT

public:
    explicit RenameLayer(QWidget *parent = 0);
    ~RenameLayer();

    QString name;

    void setLineEdit(QString s);

private slots:
    void on_lineEdit_editingFinished();

private:
    Ui::RenameLayer *ui;
};

#endif // RENAMELAYER_H
