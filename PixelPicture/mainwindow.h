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
#include "importsettings.h"
#include "renamelayer.h"
#include "videoconvertersettings.h"
#include "changeframespeed.h"
#include "colorconverteroptions.h"
#include "about.h"
#include "controller.h"
#include "pentool.h"
#include "erasertool.h"
#include "filltool.h"
#include "linetool.h"
#include "rectangletool.h"
#include "ellipsetool.h"

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

    void on_secondaryColorButton_clicked();

    void on_clearLayerButton_clicked();

    void on_renameButton_clicked();

    void changeName();

    void leaveName();

    void on_addlayerButton_clicked();

    void layoutbuttonClicked();

    void transparencybuttonToggled(bool toggled);

    void on_removeButton_clicked();

    void on_movelayerupButton_clicked();

    void on_movelayerdownButton_clicked();

    void on_animationSlider_valueChanged(int position);

    void animationSliderUpdate(int time);

    void on_moveUpButton_clicked();

    void on_moveDownButton_clicked();

    void on_moveLeftButton_clicked();

    void on_moveRightButton_clicked();

    void on_moveFrameUpButton_clicked();

    void on_moveFrameDownButton_clicked();

    void on_moveFrameLeftButton_clicked();

    void on_moveFrameRightButton_clicked();

    void on_actionOpen_triggered();

    void on_actionSaveAs_triggered();

    void on_actionPen_triggered();

    void on_actionEraser_triggered();

    void on_actionLine_triggered();

    void on_actionRectangle_triggered();

    void on_actionEllipse_triggered();

    void on_actionFill_triggered();

    void on_actionImport_Picture_triggered();

    void on_actionImport_video_triggered();

    void on_actionImport_Settings_triggered();

    void on_actionNew_Frame_triggered();

    void on_actionCopy_Frame_triggered();

    void on_actionPlay_triggered();

    void on_fillCheck_toggled(bool checked);

    void on_actionPause_triggered();

    void on_actionStop_triggered();

    void on_frameTimeTB_editingFinished();

    void on_actionForward_triggered();

    void on_actionRewind_triggered();

    void on_actionChange_Speed_triggered();

    void on_actionColorOptions_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    ImportSettings *settings;
    RenameLayer *renamelayer;
    VideoConverterSettings *videoSettings;
    ChangeFrameSpeed *speedchanger;
    ColorConverterOptions *options;
    About *about;

    //a kijelzőt megvalósító pixelscene
    PixelScene *scene;

    //az aktív action
    QAction *activeAction;

    //a rajzoló eszközök tárolása
    PenTool *pen;
    FillTool *fill;
    LineTool *line;
    RectangleTool *rectangle;
    EllipseTool *ellipse;
    EraserTool *eraser;

    //módosítások lekommunikálásához
    Controller *controller;

    //layerek megjelenítéséhez szükséges widgetek
    QGridLayout *layergrid;
    QPushButton *activelayerButton;
    QScrollArea *scroll;
    QWidget *container;

    //layerek gombjai és az átlátszóságukat kezelő gombok
    QList<QPushButton*> layerbuttons;
    QList<QPushButton*> transparencybuttons;

    PlayTool *play;

    //a layerek megjelenítését létrehozó, illetve frissítő függvények
    void createLayerDisplay();
    void clearLayerDisplay();
    void newLayerDisplay();
    void updateLayerDisplay();

};

#endif // MAINWINDOW_H
