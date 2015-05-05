#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <iostream>

#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QColorDialog>
#include <QGridLayout>
#include <QScrollArea>
#include "pixelscene.h"
#include "animation.h"
#include "pixel.h"
#include "tool.h"
#include "ellipsetool.h"
#include "pentool.h"
#include "linetool.h"
#include "rectangletool.h"
#include "erasertool.h"
#include "filltool.h"
#include "importsettings.h"
#include "animationtool.h"
#include "renamelayer.h"
#include "controller.h"
#include "exporttool.h"
#include "importtool.h"

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

    void on_importPictureButton_clicked();

    void on_importSettingsButton_clicked();

    void on_newFrameButton_clicked();

    void on_playButton_clicked();

    void on_importvideoButton_clicked();

    void on_renameButton_clicked();

    void changeName();

    void leaveName();

    void on_addlayerButton_clicked();

    void layoutbuttonClicked();

    void transparencybuttonToggled(bool toggled);

    void on_removeButton_clicked();

    void on_lineButton_clicked();

    void on_movelayerupButton_clicked();

    void on_movelayerdownButton_clicked();

    void on_rectangleButton_clicked();

    void on_animationSlider_valueChanged(int position);

    void on_fillButton_clicked();

    void animationSliderUpdate(int time);

    void on_copyFrameButton_clicked();

    void on_moveUpButton_clicked();

    void on_moveDownButton_clicked();

    void on_moveLeftButton_clicked();

    void on_moveRightButton_clicked();

    void on_moveFrameUpButton_clicked();

    void on_moveFrameDownButton_clicked();

    void on_moveFrameLeftButton_clicked();

    void on_moveFrameRightButton_clicked();

    void on_exportButton_clicked();

    void on_importButton_clicked();

private:
    Ui::MainWindow *ui;
    ImportSettings *settings;
    RenameLayer *renamelayer;

    PixelScene *scene;

    int pixelSize = 5, gapWidth = 5, gapHeight = 15;
    int windowWidth = 2, windowHeight = 2, windowXNumber = 16, windowYNumber = 13;
    int beginX = 0, beginY = 20;

    QPushButton *activeButton;

    PenTool *pen;
    LineTool *line;
    RectangleTool *rectangle;
    EllipseTool *ellipse;
    EraserTool *eraser;
    FillTool *fill;
    AnimationTool* animationtool;

    Controller *controller;
    ExportTool *exporter;
    ImportTool *importer;

    QGridLayout *layergrid;
    QString newname;
    QPushButton *activelayerButton;
    QScrollArea *scroll;
    QWidget *container;
    QList<QPushButton*> layerbuttons;
    QList<QPushButton*> transparencybuttons;

    void createLayerDisplay();
    void clearLayerDisplay();
    void newLayerDisplay();
    void updateLayerDisplay();

};

#endif // MAINWINDOW_H
