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

    //beállítjuk a lineedit tartalmát az eredeti névre
    void setLineEdit(QString s);

private slots:
    //a szerkesztés végén lefutó függvény
    void on_lineEdit_editingFinished();

private:
    Ui::RenameLayer *ui;
};

#endif // RENAMELAYER_H
