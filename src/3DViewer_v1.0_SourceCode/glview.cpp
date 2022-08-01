#include "glview.hpp"
#include "mainwindow.h"

glView::glView(QWidget* parent) : QOpenGLWidget(parent)
{
    setWindowTitle("Pomogite mne");
    setGeometry(400, 200, 800, 600);

    xTran = 0;
    yTran = 0;
    zTran = 0;

    xRot = 0;
    yRot = 0;
    zRot = 0;

    scale_value = 0;

}

void glView::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
}

void glView::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, qPow(farValue, 2));
}
void glView::draw()
{
    glVertexPointer(3, GL_DOUBLE, 0, count_copy.matrix_v);
    glEnableClientState(GL_VERTEX_ARRAY);
    if (verticesType) {
        if (verticesType == 1)
            glEnable(GL_POINT_SMOOTH);
        else
            glDisable(GL_POINT_SMOOTH);
        glPointSize(verticeSize);
        verticesColor.getRgbF(&verticeRed, &verticeGreen, &verticeBlue);
        glColor3d(verticeRed, verticeGreen, verticeBlue);
        glDrawArrays(GL_POINTS, 0, count_copy.count_of_vertexes);
    }
        edgesColor.getRgbF(&edgeRed, &edgeGreen, &edgeBlue);
        glColor3d(edgeRed, edgeGreen, edgeBlue);
        glLineWidth(edgesThickness);
        glLineStipple(1, 0x00F0);
        if (dashedEdges)
            glEnable(GL_LINE_STIPPLE);
        else
            glDisable(GL_LINE_STIPPLE);
        glDrawElements(GL_LINES, count_copy.count_facets_in_stroke * 2, GL_UNSIGNED_INT, count_copy.matrix_index);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void glView::openObjFile()
{
    if (count_v.matrix_v) {
        free_matrix(&count_copy);
        free_matrix(&count_v);
    }
    if (!qPath.isNull())
    {
        QByteArray ba = qPath.toLatin1();
        filePath = ba.data();
        parsingObject();
    }
}

void glView::parsingObject()
{
    if (first_open(filePath, &count_v)) {
        second_open(filePath, &count_v);
        cpy_struct(count_v, &count_copy);
        emit statusTrigger(count_v.count_of_vertexes, count_v.count_of_facets);
        isProjection = true;
        updateFrame();
    }
}

void glView::setRotation()
{
    if (xRot)
        rotate_by_ox(count_copy.matrix_v, count_v.count_of_vertexes, xRot);
    if (yRot)
        rotate_by_oy(count_copy.matrix_v, count_v.count_of_vertexes, yRot);
    if (zRot)
        rotate_by_oz(count_copy.matrix_v, count_v.count_of_vertexes, zRot);
    if (xTran)
        translate(count_copy.matrix_v, count_v.count_of_vertexes, X, xTran);
    if (yTran)
        translate(count_copy.matrix_v, count_v.count_of_vertexes, Y, yTran);
    if (zTran)
        translate(count_copy.matrix_v, count_v.count_of_vertexes, Z, zTran);
    if (scale_value)
        scale(count_copy.matrix_v, count_v.count_of_vertexes, scale_value);
}

void glView::paintGL()
{
    if (isProjection) changeProjection(projection);
    backgroundColor.getRgbF(&backgroundRed, &backgroundGreen, &backgroundBlue, &backgroundAlpha);
    glClearColor(backgroundRed, backgroundGreen, backgroundBlue, backgroundAlpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0, 0, -3);
    if(count_copy.matrix_v) {
        setRotation();
        draw();
        cpy_matrix_v(count_v, &count_copy);
    }
}

void glView::changeProjection(int proj)
{
    isProjection = false;
    float fov = 60.0 * M_PI / 180;
    float near = 5 * (count_v.y_max / (2 * tan(fov / 2)));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (proj == 1)
    {
        glOrtho(count_v.x_min * 2, count_v.x_max * 2, count_v.y_min * 2, count_v.y_max * 2, near, farValue);
        glTranslated(0, 0, -near * 3);
    }
    else
    {
        glFrustum(count_v.x_min * 0.5, count_v.x_max * 0.5, count_v.y_min * 0.5, count_v.y_max * 0.5, near, farValue);
        glTranslated(0, 0, -near * 3);
    }
}

void glView::updateFrame()
{
    update();
}

void glView::changeFarValue()
{
    resizeGL(640, 800);
}

void glView::mousePressEvent(QMouseEvent* mo)
{
    mPos = mo->pos();
}

void glView::mouseMoveEvent(QMouseEvent* mo)
{
        double xMouseRot = (0.001 / M_PI*(mo->pos().y() - mPos.y()) + xRot);
        double yMouseRot = (0.001 / M_PI*(mo->pos().x() - mPos.x()) + yRot);
        double x = (xMouseRot*180) / M_PI;
        double y = (yMouseRot*180) / M_PI;

        emit mouseRotTrigger(x, y);
}
