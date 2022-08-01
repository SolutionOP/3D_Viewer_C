#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("3DViewer_v1.0");

    edgeThicknessWindow = new EdgesThickness;
    edgeThicknessWindow->setWindowTitle("Edges Thickness");

    verticeSizeWindow = new VerticeSize;
    verticeSizeWindow->setWindowTitle("Vertices Size");

    settings = new QSettings("Ppettigr & co.", "3DViewer_v1.0", this);
    loadSettings();

    ui->statusbar->addPermanentWidget(ui->label_edges);
    ui->statusbar->addPermanentWidget(ui->label_vertices);
    ui->statusbar->addPermanentWidget(ui->label_fileName);

    connect(ui->glWindow, &glView::mouseRotTrigger, this, &MainWindow::setRotFieldsValues);
    connect(ui->glWindow, &glView::statusTrigger, this, &MainWindow::setStatus);
    connect(this, &MainWindow::openTrigger, ui->glWindow, &glView::openObjFile);
    connect(edgeThicknessWindow, &EdgesThickness::setEdgesThicknessTrigger, this, &MainWindow::setThickness);
    connect(verticeSizeWindow, &VerticeSize::setVerticesSize, this, &MainWindow::setVerticesSize);
}

MainWindow::~MainWindow()
{   
    saveSettings();
    delete ui;
}


void MainWindow::saveSettings()
{
    settings->setValue("backgroundColor", ui->glWindow->backgroundColor);
    settings->setValue("edgesColor", ui->glWindow->edgesColor);
    settings->setValue("verticesColor", ui->glWindow->verticesColor);
    settings->setValue("edgesThickness", ui->glWindow->edgesThickness);
    settings->setValue("edgesType", ui->glWindow->dashedEdges);
    settings->setValue("projectionValue", ui->glWindow->projection);
    settings->setValue("verticesType", ui->glWindow->verticesType);
    settings->setValue("verticesSize", ui->glWindow->verticeSize);
}

void MainWindow::loadSettings()
{
    QVariant backgoundColorSetting = settings->value("backgroundColor", QColor(Qt::black));
    ui->glWindow->backgroundColor = backgoundColorSetting.value<QColor>();
    QVariant edgesColorSetting = settings->value("edgesColor", QColor(Qt::white));
    ui->glWindow->edgesColor = edgesColorSetting.value<QColor>();
    QVariant verticesColorSetting = settings->value("verticesColor", QColor(Qt::red));
    ui->glWindow->verticesColor = verticesColorSetting.value<QColor>();
    QVariant edgesThicknessSetting = settings->value("edgesThickness", 1);
    ui->glWindow->edgesThickness = edgesThicknessSetting.value<double>();
    QVariant edgesTypeSetting = settings->value("edgesType", false);
    ui->glWindow->dashedEdges = edgesTypeSetting.value<bool>();
    QVariant projectionSetting = settings->value("projectionValue", 2);
    ui->glWindow->projection = projectionSetting.value<int>();
    QVariant verticesTypeSetting = settings->value("verticesType", 2);
    ui->glWindow->verticesType = verticesTypeSetting.value<int>();
    QVariant verticesSizeSetting = settings->value("verticesSize", 5);
    ui->glWindow->verticeSize = verticesSizeSetting.value<double>();
}

void MainWindow::on_actionOpen_triggered() {
    QString filePath = NULL;
    filePath = QFileDialog::getOpenFileName(this, NULL, "/~", "OBJ (*.obj)");
    if (!filePath.isNull()) {
        int namePos = filePath.lastIndexOf('/') + 1;
        QString fileName;
        fileName = "File Name:  " + filePath.sliced(namePos) + "  ";
        ui->label_fileName->setText(fileName);
        ui->glWindow->qPath = filePath;
        ui->doubleSpinBox_rotateX->setValue(0);
        ui->doubleSpinBox_rotateY->setValue(0);
        ui->doubleSpinBox_rotateZ->setValue(0);
        ui->doubleSpinBox_translateX->setValue(0);
        ui->doubleSpinBox_translateY->setValue(0);
        ui->doubleSpinBox_translateZ->setValue(0);
        ui->doubleSpinBox_scale->setValue(1);
        emit openTrigger();
    }
}


void MainWindow::on_doubleSpinBox_translateX_valueChanged(double arg1) {
    ui->glWindow->xTran = arg1;
    ui->glWindow->updateFrame();
}


void MainWindow::on_doubleSpinBox_translateY_valueChanged(double arg1)
{
    ui->glWindow->yTran = arg1;
    ui->glWindow->updateFrame();
}


void MainWindow::on_doubleSpinBox_translateZ_valueChanged(double arg1)
{
    ui->glWindow->zTran = arg1;
    if (arg1 < 0)
    {
        ui->glWindow->farValue = ui->glWindow->defaultFarValue - arg1;
        ui->glWindow->changeFarValue();
    }
    ui->glWindow->updateFrame();
}


void MainWindow::on_doubleSpinBox_rotateX_valueChanged(double arg1)
{
    double x = (arg1*M_PI)/180;
    ui->glWindow->xRot = x;
    ui->glWindow->updateFrame();
    if (arg1 == 360 || arg1 == -360)
        ui->doubleSpinBox_rotateX->setValue(0);
}


void MainWindow::on_doubleSpinBox_rotateY_valueChanged(double arg1)
{
    double y = (arg1*M_PI)/180;
    ui->glWindow->yRot = y;
    ui->glWindow->updateFrame();
    if (arg1 == 360 || arg1 == -360)
        ui->doubleSpinBox_rotateY->setValue(0);
}


void MainWindow::on_doubleSpinBox_rotateZ_valueChanged(double arg1)
{
    double z = (arg1*M_PI)/180;
    ui->glWindow->zRot = z;
    ui->glWindow->updateFrame();
    if (arg1 == 360 || arg1 == -360)
        ui->doubleSpinBox_rotateZ->setValue(0);

}


void MainWindow::on_doubleSpinBox_scale_valueChanged(double arg1)
{
    ui->glWindow->scale_value = arg1;
    ui->glWindow->updateFrame();
}

 void MainWindow::setRotFieldsValues(double x, double y)
{
     ui->doubleSpinBox_rotateX->setValue(x);
     ui->doubleSpinBox_rotateY->setValue(y);
 }

 void MainWindow::setStatus(int vertices, int edges) {
     QString vertices_str = "Vertices:  " + QString::number(vertices) + "  ";
     QString edges_str = "Edges:  " + QString::number(edges) + "  ";
     ui->label_vertices->setText(vertices_str);
     ui->label_edges->setText(edges_str);
 }

void MainWindow::setThickness(double thickness)
 {
    ui->glWindow->edgesThickness = thickness;
}

void MainWindow::setVerticesSize(double size)
{
    ui->glWindow->verticeSize = size;
}

void MainWindow::on_actionSet_Background_Color_triggered()
{
    ui->glWindow->backgroundColor = QColorDialog::getColor(Qt::black, this, "Choose Background Color");
}


void MainWindow::on_actionSet_edges_color_triggered()
{
    ui->glWindow->edgesColor = QColorDialog::getColor(Qt::white, this, "Choose Edges Color");
}


void MainWindow::on_actionSet_vertices_color_triggered()
{
    ui->glWindow->verticesColor = QColorDialog::getColor(Qt::red, this, "Choose Vertices Color");
}


void MainWindow::on_actionSet_thickness_triggered()
{
    edgeThicknessWindow->show();
}


void MainWindow::on_actionSolid_triggered()
{
    ui->glWindow->dashedEdges = false;
    ui->glWindow->updateFrame();
}


void MainWindow::on_actionDashed_triggered()
{
    ui->glWindow->dashedEdges = true;
    ui->glWindow->updateFrame();
}

void MainWindow::on_actionParallel_triggered()
{
    ui->glWindow->projection = 1;
    ui->glWindow->isProjection = true;
    ui->glWindow->updateFrame();
}
void MainWindow::on_action_none_triggered()
{
    ui->glWindow->verticesType = 0;
    ui->glWindow->updateFrame();
}


void MainWindow::on_actionCentral_triggered()
{
    ui->glWindow->projection = 2;
    ui->glWindow->isProjection = true;
    ui->glWindow->updateFrame();
}

void MainWindow::on_actioncircle_triggered()
{
    ui->glWindow->verticesType = 1;
    ui->glWindow->updateFrame();
}


void MainWindow::on_actionSquare_triggered()
{
    ui->glWindow->verticesType = 2;
    ui->glWindow->updateFrame();
}


void MainWindow::on_actionSet_size_triggered()
{
    verticeSizeWindow->show();
}


void MainWindow::on_actionSave_current_image_as_triggered()
{
    QString savePath = NULL;
    savePath = QFileDialog::getSaveFileName(this, NULL, NULL, "JPEG (*.jpeg) ;; BMP (*.bmp)");
    if (!savePath.isNull()) ui->glWindow->grabFramebuffer().save(savePath, NULL, 100);
}

void MainWindow::on_pushButton_screencast_clicked()
{
        gif = new QGifImage;
        frame = new QImage;
        timer = new QTimer(this);
        time = 0;
        connect(timer, SIGNAL(timeout()), this, SLOT(saveGifFrame()));
        timer->start(100);
}

void MainWindow::saveGifFrame()
{
    time++;
    *frame = ui->glWindow->grabFramebuffer();
    gif->addFrame(*frame);
    if (time == 50) {
        timer->stop();
        gifSavePath = NULL;
        gifSavePath = QFileDialog::getSaveFileName(this, NULL, NULL, "GIF (*.gif)");
        if (!gifSavePath.isNull())
            gif->save(gifSavePath);
    }
}
