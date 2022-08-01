#include "verticesize.h"
#include "ui_verticesize.h"

VerticeSize::VerticeSize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerticeSize)
{
    ui->setupUi(this);
}

VerticeSize::~VerticeSize()
{
    delete ui;
}

void VerticeSize::on_doubleSpinBox_verticesSize_valueChanged(double size)
{
    emit setVerticesSize(size);
}

