#ifndef GLVIEW_HPP
#define GLVIEW_HPP

#define GL_SILENCE_DEPRECATION

#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QtMath>
#include <QColor>

extern "C" {
    #include "3d_viewer.h"
}

class glView : public QOpenGLWidget
{
    Q_OBJECT

private:
    char* filePath;
    void parsingObject();
    void setRotation();
    QPoint mPos;
    void draw();
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    counts count_v = {0,0,0,0,0,0,0, NULL, NULL};
    counts count_copy = {0,0,0,0,0, 0, 0, NULL, NULL};

public:
    glView(QWidget* parent = nullptr);
    QString qPath = NULL;
    double xTran, yTran, zTran;
    double xRot, yRot, zRot;
    double scale_value;
    int defaultFarValue = 3000;
    int farValue = defaultFarValue;
    QColor backgroundColor;
    float backgroundRed, backgroundGreen, backgroundBlue, backgroundAlpha;
    QColor edgesColor;
    float edgeRed, edgeGreen, edgeBlue;
    QColor verticesColor;
    float verticeRed, verticeGreen, verticeBlue;
    float edgesThickness;
    bool dashedEdges;
    int projection = 2;
    int verticesType;
    float verticeSize;
    bool isProjection = false;

public slots:
    void changeProjection(int proj);
    void updateFrame();
    void changeFarValue();
    void openObjFile();

signals:
    void mouseRotTrigger(double x, double y);
    void statusTrigger(int vertices, int edges);
    void changeProjectionVariant();
};

#endif // GLVIEW_HPP
