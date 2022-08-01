#include "3d_viewer.h"
#include <math.h>

void translate(double *vertices, int count, axis_t axis, double a) {
    for (int i = 0 + axis; i < count * 3; i += 3) {
        vertices[i] += a;
    }
}

void rotate_by_ox(double *vertices, int count, double angle) {
    for (int i = 0; i < count * 3; i += 3) {
        double y = vertices[i + 1];
        double z = vertices[i + 2];
        vertices[i + 1] = y*cos(angle) - z*sin(angle);
        vertices[i + 2] = y*sin(angle) + z*cos(angle);
    }
}

void rotate_by_oy(double *vertices, int count, double angle) {
    for (int i = 0; i < count * 3; i += 3) {
        double x = vertices[i];
        double z = vertices[i + 2];
        vertices[i] = x*cos(angle) + z*sin(angle);
        vertices[i + 2] = -x*sin(angle) + z*cos(angle);
    }
}

void rotate_by_oz(double *vertices, int count, double angle) {
    for (int i = 0; i < count * 3; i += 3) {
        double x = vertices[i];
        double y = vertices[i + 1];
        vertices[i] = x*cos(angle) - y*sin(angle);
        vertices[i + 1] = x*sin(angle) + y*cos(angle);
    }
}

void scale(double *vertices, int count, double a) {
    for (int i = 0; i < count * 3; i++) {
        double value = vertices[i];
        vertices[i] = value * a;
    }
}
