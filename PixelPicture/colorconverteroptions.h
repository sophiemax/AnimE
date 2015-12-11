#ifndef COLORCONVERTEROPTIONS_H
#define COLORCONVERTEROPTIONS_H

#include <QDialog>

namespace Ui {
class ColorConverterOptions;
}

class ColorConverterOptions : public QDialog
{
    Q_OBJECT

public:

    enum class Options
    {
        inverz,
        blackandwhite,
        greyscale,
        filter,
        sepia,
        contrast,
        shiftright,
        shiftleft
    };

    explicit ColorConverterOptions(QWidget *parent = 0);
    ~ColorConverterOptions();

    Options option;
    bool cancelled = false;

private slots:
    void on_inverzButton_clicked();

    void on_bnwButton_clicked();

    void on_greyScaleButton_clicked();

    void on_filterButton_clicked();

    void on_sepiaButton_clicked();

    void on_contrastButton_clicked();

    void on_srButton_clicked();

    void on_slButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::ColorConverterOptions *ui;
};

#endif // COLORCONVERTEROPTIONS_H
