#include "edgesthickness.h"
#include "ui_edgesthickness.h"

EdgesThickness::EdgesThickness(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EdgesThickness)
{
    ui->setupUi(this);
}

EdgesThickness::~EdgesThickness()
{
    delete ui;
}

void EdgesThickness::on_buttonBox_accepted()
{
    emit setEdgesThicknessTrigger(ui->doubleSpinBox_edgesThickness->value());
}

