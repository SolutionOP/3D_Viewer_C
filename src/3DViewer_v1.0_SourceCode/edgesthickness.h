#ifndef EDGESTHICKNESS_H
#define EDGESTHICKNESS_H

#include <QDialog>

namespace Ui {
class EdgesThickness;
}

class EdgesThickness : public QDialog
{
    Q_OBJECT

public:
    explicit EdgesThickness(QWidget *parent = nullptr);
    ~EdgesThickness();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::EdgesThickness *ui;

signals:
    void setEdgesThicknessTrigger(double thickness);
};

#endif // EDGESTHICKNESS_H
