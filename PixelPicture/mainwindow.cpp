#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "playtool.h"
#include <QIcon>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QIcon *icon = new QIcon(":/icon/icons/Anime_ikon.png");

    setWindowTitle("AnimE");
    setWindowIcon(*icon);

    scene = new PixelScene(this);
    ui->graphicsView->setScene(scene);
    //setCentralWidget(ui->graphicsView);
    //QBrush brush(Qt::black);
    //scene->setBackgroundBrush(brush);

    controller = new Controller(scene);

    activeAction = ui->actionPen;
    activeAction->setChecked(true);

    settings = new ImportSettings(this);
    settings->converter = controller->getImageConverter();

    pen = new PenTool(this);
    line = new LineTool(this);
    rectangle = new RectangleTool(this);
    ellipse = new EllipseTool(this);
    eraser = new EraserTool(this);
    fill = new FillTool(this);

    pen->setController(controller);
    line->setController(controller);
    rectangle->setController(controller);
    ellipse->setController(controller);
    eraser->setController(controller);
    fill->setController(controller);

    scene->setActivePaintTool(pen);

    PlayTool *playTool = controller->getPlayTool();

    renamelayer = new RenameLayer(this);

    createLayerDisplay();

    connect(renamelayer, &RenameLayer::accepted, this, &MainWindow::changeName);
    connect(renamelayer, &RenameLayer::rejected, this, &MainWindow::leaveName);


    connect(playTool, &PlayTool::positionChanged, this, &MainWindow::animationSliderUpdate);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete settings;
    delete renamelayer;
    delete scroll;
    delete scene;

    delete pen;
    delete line;
    delete rectangle;
    delete ellipse;
    delete eraser;
    delete fill;

    delete controller;
}

void MainWindow::createLayerDisplay()
{
    scroll = new QScrollArea();
    container = new QWidget(scroll);
    layergrid = new QGridLayout(container);

    scroll->setWidget(container);

    container->setLayout(layergrid);
    container->setMinimumSize(scroll->width(), scroll->height());
    container->setFixedWidth(142);
    container->setFixedHeight(23*1);
    ui->gridLayout->addWidget(scroll, 0, 0);

    layergrid->setSpacing(0);
    layergrid->setVerticalSpacing(0);
    layergrid->setContentsMargins (0, 0, 0, 0);

    QPushButton *transparency = new QPushButton("Tr");
    transparency->setFixedWidth(23);
    transparency->setCheckable(true);
    transparency->setChecked(true);
    transparencybuttons.append(transparency);

    QPushButton *layer0 = new QPushButton("Layer0");
    layer0->setCheckable(true);
    activelayerButton = layer0;
    activelayerButton->setChecked(true);
    layerbuttons.append(layer0);

    layergrid->addWidget(layer0,0,1,1,1);
    layergrid->addWidget(transparency,0,0,1,1);

    connect(layer0, &QPushButton::clicked, this, &MainWindow::layoutbuttonClicked);
    connect(transparency,&QPushButton::toggled,this,&MainWindow::transparencybuttonToggled);
}

void MainWindow::clearLayerDisplay()
{
    while (!layerbuttons.isEmpty())
        delete layerbuttons.takeFirst();
    while (!transparencybuttons.isEmpty())
        delete transparencybuttons.takeFirst();
}

void MainWindow::newLayerDisplay()
{
    clearLayerDisplay();

    QPushButton *transparency = new QPushButton("Tr");
    transparency->setFixedWidth(23);
    transparency->setCheckable(true);
    transparency->setChecked(true);
    transparencybuttons.append(transparency);

    QPushButton *layer0 = new QPushButton("Layer0");
    layer0->setCheckable(true);
    activelayerButton = layer0;
    activelayerButton->setChecked(true);
    layerbuttons.append(layer0);

    layergrid->addWidget(layer0,0,1,1,1);
    layergrid->addWidget(transparency,0,0,1,1);

    container->setFixedHeight(23);

    connect(layer0, &QPushButton::clicked, this, &MainWindow::layoutbuttonClicked);
    connect(transparency,&QPushButton::toggled,this,&MainWindow::transparencybuttonToggled);

}

void MainWindow::updateLayerDisplay()
{
    clearLayerDisplay();
    for(int i = 0; i < controller->numberofLayers(); i++)
    {
        QPushButton *transparency = new QPushButton("Tr");
        transparency->setFixedWidth(23);
        transparency->setCheckable(true);
        transparency->setChecked(!controller->getTransparency(i));
        transparencybuttons.append(transparency);

        QPushButton *layer = new QPushButton(controller->getLayerName(i));
        layer->setCheckable(true);
        layerbuttons.append(layer);

        layergrid->addWidget(layer,i,1,1,1);
        layergrid->addWidget(transparency,i,0,1,1);

        connect(layer, &QPushButton::clicked, this, &MainWindow::layoutbuttonClicked);
        connect(transparency,&QPushButton::toggled,this,&MainWindow::transparencybuttonToggled);
    }
    activelayerButton = layerbuttons[0];
    activelayerButton->setChecked(true);
    //TODO: activeAnimation->activeFrame->canvas->activeLayer = activeAnimation->activeFrame->canvas->layers[0];
    container->setFixedHeight(layerbuttons.size() * 23);
}

//ezeket inkább majd toolbuttonnel

//Ha valid színt kap, akkor beállítja következő színnek a kapottat
void MainWindow::on_primaryColorButton_clicked()
{
    QColor color = QColorDialog::getColor(controller->getPrimaryColor(), this);
    if( color.isValid() )
    {
        controller->setPrimaryColor(color);
    }
}
void MainWindow::on_windowToggle_toggled(bool checked)
{
    controller->setWindowToggled(checked);
}

void MainWindow::on_secondaryColorButton_clicked()
{
    QColor color = QColorDialog::getColor(controller->getSecondaryColor(), this);
    if( color.isValid() )
    {
        controller->setSecondaryColor(color);
    }
}

void MainWindow::animationSliderUpdate(int time)
{
    //on_animationSlider_valueChanged(time/controller->getTimesum()*100);
    int val = time/controller->getTimesum()*100-1;
    ui->animationSlider->setValue(val);
}

void MainWindow::on_clearLayerButton_clicked()
{
    controller->clearLayer();
}

void MainWindow::on_renameButton_clicked()
{
    renamelayer->show();
    renamelayer->setLineEdit(activelayerButton->text());
}

void MainWindow::changeName()
{
    if(renamelayer->name != "")
    {
        activelayerButton->setText(renamelayer->name);
        controller->setLayerName(renamelayer->name);
    }
}

void MainWindow::leaveName()
{
    activelayerButton->setText(controller->getLayerName());
}

void MainWindow::on_addlayerButton_clicked()
{
    int index = layerbuttons.indexOf(activelayerButton);

    activelayerButton->setChecked(false);

    controller->addLayer();
    controller->setLayerName("Layer" + QString::number(layerbuttons.size()));

    QPushButton *lbutton = new QPushButton("Layer" + QString::number(layerbuttons.size()));
    QPushButton *tbutton = new QPushButton("Tr");

    lbutton->setCheckable(true);
    activelayerButton = lbutton;
    activelayerButton->setChecked(true);
    tbutton->setCheckable(true);
    tbutton->setChecked(true);
    tbutton->setFixedWidth(23);

    connect(lbutton, &QPushButton::clicked, this, &MainWindow::layoutbuttonClicked);
    connect(tbutton, &QPushButton::toggled, this, &MainWindow::transparencybuttonToggled);

    layerbuttons.insert(index,lbutton);
    transparencybuttons.insert(index,tbutton);
    container->setFixedHeight(23*layerbuttons.size());
    for(int j = layerbuttons.size()-1; j >index-1; j--)
    {
        layergrid->addWidget(transparencybuttons[j],j,0);
        layergrid->addWidget(layerbuttons[j],j,1);
    }
}

void MainWindow::layoutbuttonClicked()
{
    int index = 0;
    activelayerButton->setChecked(false);

    while(layerbuttons[index] != sender())
        index++;
    activelayerButton = layerbuttons[index];
    activelayerButton->setChecked(true);

    controller->setActiveLayer(index);
}

void MainWindow::transparencybuttonToggled(bool toggled)
{
    int index = 0;

    while(transparencybuttons[index] != sender())
        index++;
    transparencybuttons[index]->setChecked(toggled);

    controller->setLayerTransparency(!toggled);
}

void MainWindow::on_removeButton_clicked()
{
    controller->removeActiveLayer();
    if(layerbuttons.size() == 1)
    {
        transparencybuttons[0]->setChecked(true);
        layerbuttons[0]->setText("Layer0");
        controller->setLayerName("Layer0");
    }
    else
    {
        int index = layerbuttons.indexOf(activelayerButton);

        disconnect(layerbuttons[index], &QPushButton::clicked, this, &MainWindow::layoutbuttonClicked);
        disconnect(transparencybuttons[index], &QPushButton::toggled, this, &MainWindow::transparencybuttonToggled);

        //layergrid->removeWidget(layerbuttons.takeLast());

        layergrid->removeWidget(layerbuttons[index]);
        layergrid->removeWidget(transparencybuttons[index]);
        layerbuttons.removeAt(index);
        transparencybuttons.removeAt(index);

        if(index != 0)
        {
            activelayerButton = layerbuttons[index-1];
        }
        else
        {
            activelayerButton = layerbuttons[0];
        }
        activelayerButton->setChecked(true);
        updateLayerDisplay();
    }
}

void MainWindow::on_movelayerupButton_clicked()
{
    int index = layerbuttons.indexOf(activelayerButton);
    if(index != 0)
    {
        QPushButton* temp = layerbuttons[index-1];
        layerbuttons[index-1] = layerbuttons[index];
        layerbuttons[index] = temp;

        temp = transparencybuttons[index-1];
        transparencybuttons[index-1] = transparencybuttons[index];
        transparencybuttons[index] = temp;

        layergrid->addWidget(layerbuttons[index-1],index-1,1);
        layergrid->addWidget(layerbuttons[index],index,1);

        layergrid->addWidget(transparencybuttons[index-1],index-1,0);
        layergrid->addWidget(transparencybuttons[index],index,0);

        controller->switchLayers(index-1,index);
    }
}

void MainWindow::on_movelayerdownButton_clicked()
{
    int index = layerbuttons.indexOf(activelayerButton);
    if(index != layerbuttons.size()-1)
    {
        QPushButton* temp = layerbuttons[index+1];
        layerbuttons[index+1] = layerbuttons[index];
        layerbuttons[index] = temp;

        temp = transparencybuttons[index+1];
        transparencybuttons[index+1] = transparencybuttons[index];
        transparencybuttons[index] = temp;

        layergrid->addWidget(layerbuttons[index+1],index+1,1);
        layergrid->addWidget(layerbuttons[index],index,1);

        layergrid->addWidget(transparencybuttons[index+1],index+1,0);
        layergrid->addWidget(transparencybuttons[index],index,0);

        controller->switchLayers(index+1,index);
    }
}

void MainWindow::on_animationSlider_valueChanged(int position)
{
    float labelpos = ui->animationSlider->x() + position / 100.0 * ui->animationSlider->width();
    ui->animationSlider->setSliderPosition(position);
    float timepos = position /100.0 * controller->getTimesum();
    int i = 0;
    float sum = controller->getTimespan(i);
    while(sum < timepos)
    {
        i++;
        sum += controller->getTimespan(i);
    }
    if(i != controller->getActiveFrameIndex())
    {
        controller->setActiveFrame(i);
        updateLayerDisplay();
    }

    ui->animationLabel->setGeometry(labelpos,ui->animationLabel->y(),ui->animationLabel->width(),ui->animationLabel->height());
    int minute = timepos / 60000.0;
    int sec = timepos / 1000.0;
    int millisec = timepos-sec*1000;
    QString m(QString::number(minute));
    QString s(QString::number(sec));
    QString ms(QString::number(millisec));

    if(minute < 10)
        m.prepend("0");

    if(sec < 10)
        s.prepend("0");

    if(millisec < 10)
        s.prepend("00");
    else
        if(millisec < 100)
            s.prepend("0");
    QString label(m + ":" + s + ":" + ms);
    ui->animationLabel->setText(label);
}

void MainWindow::on_moveUpButton_clicked()
{
    controller->moveLayerUp();
}

void MainWindow::on_moveDownButton_clicked()
{
    controller->moveLayerDown();
}

void MainWindow::on_moveLeftButton_clicked()
{
    controller->moveLayerLeft();
}

void MainWindow::on_moveRightButton_clicked()
{
    controller->moveLayerRight();
}

void MainWindow::on_moveFrameUpButton_clicked()
{
    controller->moveFrameUp();
}

void MainWindow::on_moveFrameDownButton_clicked()
{
    controller->moveFrameDown();
}

void MainWindow::on_moveFrameLeftButton_clicked()
{
    controller->moveFrameLeft();
}

void MainWindow::on_moveFrameRightButton_clicked()
{
    controller->moveFrameRight();
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        controller->importFile(fileName);
        updateLayerDisplay();
        file.close();
    }
}

void MainWindow::on_actionSaveAs_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Open Image"), QString(),
                tr("Text(*.txt)"));
    controller->exportFile(fileName);
}

void MainWindow::on_actionPen_triggered()
{
    activeAction->setChecked(false);
    activeAction = ui->actionPen;
    activeAction->setChecked(true);
    controller->setActivePaintTool(pen); //pen
}

void MainWindow::on_actionEraser_triggered()
{
    activeAction->setChecked(false);
    activeAction = ui->actionEraser;
    activeAction->setChecked(true);
    controller->setActivePaintTool(eraser); //eraser
}

void MainWindow::on_actionLine_triggered()
{
    activeAction->setChecked(false);
    activeAction = ui->actionLine;
    activeAction->setChecked(true);
    controller->setActivePaintTool(line); //line
}

void MainWindow::on_actionRectangle_triggered()
{
    activeAction->setChecked(false);
    activeAction = ui->actionRectangle;
    activeAction->setChecked(true);
    controller->setActivePaintTool(rectangle); //rectangle
}

void MainWindow::on_actionEllipse_triggered()
{
    activeAction->setChecked(false);
    activeAction = ui->actionEllipse;
    activeAction->setChecked(true);
    controller->setActivePaintTool(ellipse); //ellipse
}

void MainWindow::on_actionFill_triggered()
{
    activeAction->setChecked(false);
    activeAction = ui->actionFill;
    activeAction->setChecked(true);
    controller->setActivePaintTool(fill); //fill
}

void MainWindow::on_actionImport_Picture_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), QString(),
                tr("All (*.bmp *.gif *.jpg *.jpeg *.png *.pbm *.ppm *.tiff *.xbm *.xpm);;"
                   "Windows Bitmap (*.bmp);;"
                   "Graphic Interchange Format (*.gif);;"
                   "Joint Photographic Experts Group (*.jpg  *.jpeg);;"
                   "Portable Network Graphics (*.png);;"
                   "Portable Bitmap (*.pbm);;"
                   "Portable Graymap (*.pgm);;"
                   "Portable Pixmap (*.ppm);;"
                   "Tagged Image File Format (*.tiff);;"
                   "X11 Bitmap (*.xbm);;"
                   "X11 Pixmap (*.xpm)"));

    if (!fileName.isEmpty()) {
        QImage image(fileName);
        controller->importImage(image);
    }
}

void MainWindow::on_actionImport_video_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), QString(),
                tr("All (*.avi *.mkv *.mp4)"));

    if (!fileName.isEmpty()) {
        controller->importVideo(fileName);
    }
}

void MainWindow::on_actionImport_Settings_triggered()
{
    settings->show();
}

void MainWindow::on_actionNew_Frame_triggered()
{
    controller->addFrame();
    newLayerDisplay();
}

void MainWindow::on_actionCopy_Frame_triggered()
{
    controller->copyFrame();
    on_animationSlider_valueChanged(controller->getCurrentTime()/controller->getTimesum() * 100);
}

void MainWindow::on_actionPlay_triggered()
{
    controller->playAnimation ();
}

void MainWindow::on_fillCheck_toggled(bool checked)
{
    ellipse->toggleFilled(checked);
    line->toggleFilled(checked);
}

void MainWindow::on_actionPause_triggered()
{
    controller->pauseAnimation();
}

void MainWindow::on_actionStop_triggered()
{
    controller->stopAnimation();
}

void MainWindow::on_frameTimeTB_editingFinished()
{
    //lekérjük az active animation indexét, ill active frame indexét, és az alapján beállítjuk az aktív frame timespanjét
    int activeAnimationIndex = controller->getActiveAnimationIndex();
    int frameIndex = controller->getActiveFrameIndex();
    controller->setTimespan(activeAnimationIndex, frameIndex, ui->frameTimeTB->text().toInt());

    controller->recalculateTimesum();
}
