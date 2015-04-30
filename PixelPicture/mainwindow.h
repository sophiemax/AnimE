#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <iostream>

#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QColorDialog>
#include <QGridLayout>
#include "pixelscene.h"
#include "pixel.h"
#include "tool.h"
#include "ellipsetool.h"
#include "pentool.h"
#include "erasertool.h"
#include "importsettings.h"
#include "animationtool.h"
#include "renamelayer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_primaryColorButton_clicked();

    void on_windowToggle_toggled(bool checked);

    void on_ellipseButton_clicked();

    void on_penButton_clicked();

    void on_secondaryColorButton_clicked();

    void on_eraserButton_clicked();

    void on_clearLayerButton_clicked();

    void on_importButton_clicked();

    void on_importSettingsButton_clicked();

    void on_newFrameButton_clicked();

    void on_playButton_clicked();

    void on_animationSlider_sliderMoved(int position);

    void on_importvideoButton_clicked();

    void on_renameButton_clicked();

    void changeName();

    void leaveName();

    void on_addlayerButton_clicked();

    void layoutbuttonClicked();

    void transparencybuttonToggled(bool toggled);

private:
    Ui::MainWindow *ui;
    ImportSettings *settings;
    RenameLayer *renamelayer;

    PixelScene *scene;

    int pixelSize = 5, gapWidth = 5, gapHeight = 15;
    int windowWidth = 2, windowHeight = 2, windowXNumber = 16, windowYNumber = 13;
    int beginX = 0, beginY = 20;

    PenTool *pen;
    EllipseTool *ellipse;
    EraserTool *eraser;
    AnimationTool* animation;

    QGridLayout *layergrid;
    QString newname;
    QPushButton *activelayerButton;
    QWidget *container;
    QList<QPushButton*> layerbuttons;
    QList<QPushButton*> transparencybuttons;

};

#endif // MAINWINDOW_H
