#ifndef VERTICESIZE_H
#define VERTICESIZE_H

#include <QDialog>

namespace Ui {
class VerticeSize;
}

class VerticeSize : public QDialog
{
    Q_OBJECT

public:
    explicit VerticeSize(QWidget *parent = nullptr);
    ~VerticeSize();

private slots:
    void on_doubleSpinBox_verticesSize_valueChanged(double size);

private:
    Ui::VerticeSize *ui;

signals:
    void setVerticesSize(double size);
};

#endif // VERTICESIZE_H
