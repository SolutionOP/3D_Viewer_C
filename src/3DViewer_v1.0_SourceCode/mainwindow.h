#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QColorDialog>
#include <QSettings>
#include "glview.hpp"
#include "edgesthickness.h"
#include "verticesize.h"
#include "qgifimage.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void saveSettings();
    void loadSettings();


private slots:

    void on_actionOpen_triggered();

    void on_doubleSpinBox_translateX_valueChanged(double arg1);

    void on_doubleSpinBox_translateY_valueChanged(double arg1);

    void on_doubleSpinBox_translateZ_valueChanged(double arg1);

    void on_doubleSpinBox_rotateZ_valueChanged(double arg1);

    void on_doubleSpinBox_rotateX_valueChanged(double arg1);

    void on_doubleSpinBox_rotateY_valueChanged(double arg1);

    void on_doubleSpinBox_scale_valueChanged(double arg1);

    void on_actionSet_Background_Color_triggered();

    void on_actionSet_edges_color_triggered();

    void on_actionSet_vertices_color_triggered();

    void on_actionSet_thickness_triggered();

    void on_actionSolid_triggered();

    void on_actionDashed_triggered();

    void on_actionParallel_triggered();

    void on_actionCentral_triggered();
    void on_action_none_triggered();

    void on_actioncircle_triggered();

    void on_actionSquare_triggered();

    void on_actionSet_size_triggered();

    void on_actionSave_current_image_as_triggered();

    void on_pushButton_screencast_clicked();

private:
    Ui::MainWindow *ui;
    QSettings* settings;
    EdgesThickness* edgeThicknessWindow;
    VerticeSize* verticeSizeWindow;
    QGifImage *gif;
    QImage *frame;
    QTimer *timer;
    QString gifSavePath;
    int time;

public slots:
    void saveGifFrame();
    void setRotFieldsValues(double x, double y);
    void setStatus(int vertices, int edges);
    void setThickness(double thickness);
    void setVerticesSize(double size);

signals:
    void openTrigger();
};
#endif // MAINWINDOW_H
