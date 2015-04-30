#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QIcon *icon = new QIcon("C:/Users/Picimaci/Documents/ImportingPicture/palinkaVSviz.jpg");

    setWindowTitle("AnimE");
    setWindowIcon(*icon);

    pen = new PenTool(this);
    line = new LineTool(this);
    ellipse = new EllipseTool(this);
    eraser = new EraserTool(this);

    scene = new PixelScene(this);
    scene->activeTool = pen;
    ui->graphicsView->setScene(scene);

    settings = new ImportSettings(this);
    settings->scene = scene;
    settings->converter = scene->imageconverter;

    renamelayer = new RenameLayer(this);

    animation = new AnimationTool(scene);

    createLayerDisplay();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pen;
    delete ellipse;
    delete eraser;
    scene->destruct();
    delete scene;
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

    activelayerButton = layer0;
    layerbuttons.append(layer0);

    layergrid->addWidget(layer0,0,1,1,1);
    layergrid->addWidget(transparency,0,0,1,1);

    connect(renamelayer, &RenameLayer::accepted, this, &MainWindow::changeName);
    connect(renamelayer, &RenameLayer::rejected, this, &MainWindow::leaveName);
    connect(layer0, &QPushButton::clicked, this, &MainWindow::layoutbuttonClicked);
    connect(transparency,&QPushButton::toggled,this,&MainWindow::transparencybuttonToggled);
}

//ezeket inkább majd toolbuttonnel

//Ha valid színt kap, akkor beállítja következő színnek a kapottat
void MainWindow::on_primaryColorButton_clicked()
{
    QColor color = QColorDialog::getColor(scene->primaryColor, this);
    if( color.isValid() )
    {
        scene->primaryColor = color;
    }
}
void MainWindow::on_windowToggle_toggled(bool checked)
{
    scene->windowToggled = checked;
}

void MainWindow::on_ellipseButton_clicked()
{
    scene -> activeTool = ellipse;
}

void MainWindow::on_penButton_clicked()
{
    scene -> activeTool = pen;
}

void MainWindow::on_lineButton_clicked()
{
    scene->activeTool = line;
}

void MainWindow::on_secondaryColorButton_clicked()
{
    QColor color = QColorDialog::getColor(scene->secondaryColor, this);
    if( color.isValid() )
    {
        scene->secondaryColor = color;
    }
}

void MainWindow::on_eraserButton_clicked()
{
    scene->activeTool = eraser;
}

void MainWindow::on_clearLayerButton_clicked()
{
    scene->clearLayer();
}

void MainWindow::on_importButton_clicked()
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
        scene->importImage(image);
    }
}

void MainWindow::on_importSettingsButton_clicked()
{
    settings->show();
}

void MainWindow::on_newFrameButton_clicked()
{
    scene->addFrame();
    scene->timesum += 1000.0;
}

void MainWindow::on_playButton_clicked()
{
    animation->play();
}

void MainWindow::on_animationSlider_sliderMoved(int position)
{
    float labelpos = ui->animationSlider->x() + position / 100.0 * ui->animationSlider->width();
    float timepos = position /100.0 * scene->timesum;
    int i = 0;
    float sum = scene->frames[i]->timespan;
    while(sum < timepos)
    {
        i++;
        sum += scene->frames[i]->timespan;
    }
    scene->activeCanvas = scene->frames[i]->canvas;
    scene->updateScene();

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

void MainWindow::on_importvideoButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), QString(),
                tr("All (*.avi *.mkv *.mp4)"));

    if (!fileName.isEmpty()) {
        scene->importVideo(fileName);
    }
}

void MainWindow::on_renameButton_clicked()
{
    renamelayer->show();
}

void MainWindow::changeName()
{
    activelayerButton->setText(renamelayer->name);
}

void MainWindow::leaveName()
{

}

void MainWindow::on_addlayerButton_clicked()
{
    int i = layerbuttons.indexOf(activelayerButton);

    scene->activeCanvas->addLayer(i);
    scene->updateScene();
    QPushButton *lbutton = new QPushButton("New Layer");
    QPushButton *tbutton = new QPushButton("Tr");

    activelayerButton = lbutton;
    tbutton->setCheckable(true);
    tbutton->setChecked(true);
    tbutton->setFixedWidth(23);

    connect(lbutton, &QPushButton::clicked, this, &MainWindow::layoutbuttonClicked);
    connect(tbutton, &QPushButton::toggled, this, &MainWindow::transparencybuttonToggled);

    renamelayer->show();
    layerbuttons.insert(i,lbutton);
    transparencybuttons.insert(i,tbutton);
    container->setFixedHeight(23*layerbuttons.size());
    for(int j = layerbuttons.size()-1; j >i-1; j--)
    {
        layergrid->addWidget(transparencybuttons[j],j,0);
        layergrid->addWidget(layerbuttons[j],j,1);
    }

}

void MainWindow::layoutbuttonClicked()
{
    int index = 0;
    while(layerbuttons[index] != sender())
        index++;
    activelayerButton = layerbuttons[index];
    scene->activeCanvas->activeLayer = scene->activeCanvas->layers[index];
    scene->updateScene();
}

void MainWindow::transparencybuttonToggled(bool toggled)
{
    int index = 0;
    while(transparencybuttons[index] != sender())
        index++;
    transparencybuttons[index]->setChecked(toggled);
    scene->activeCanvas->layers[index]->transparent = !toggled;
    scene->updateCombined();
    scene->updateScene();
}

void MainWindow::on_removeButton_clicked()
{
    if(layerbuttons.size() == 1)
    {
        scene->clearLayer();
        layerbuttons[0]->setText("New Layer");
        transparencybuttons[0]->setChecked(true);
        scene->activeCanvas->activeLayer->transparent = false;
    }
    else
    {
        int index = layerbuttons.indexOf(activelayerButton);
        if(index != 0)
            scene->activeCanvas->activeLayer = scene->activeCanvas->layers[index-1];
        else
            scene->activeCanvas->activeLayer = scene->activeCanvas->layers[1];
        scene->activeCanvas->layers.removeAt(index);
        layerbuttons.removeAt(index);
        transparencybuttons.removeAt(index);
        for(int j = layerbuttons.size()-1; j >index-1; j--)
        {
            layergrid->addWidget(transparencybuttons[j],j,0);
            layergrid->addWidget(layerbuttons[j],j,1);
        }
        scene->updateCombined();
        scene->updateScene();
        container->setFixedHeight(layerbuttons.size()*23);
    }
}

void MainWindow::on_moveupButton_clicked()
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

        scene->activeCanvas->switchLayers(index-1,index);

        scene->updateCombined();
        scene->updateScene();
    }
}

void MainWindow::on_movedownButton_clicked()
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

        scene->activeCanvas->switchLayers(index+1,index);

        scene->updateCombined();
        scene->updateScene();
    }
}
