#ifndef SRC_3D_VIEWER_H_
#define SRC_3D_VIEWER_H_

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct counts {
    int count_of_vertexes;
    int count_of_facets;
    int count_facets_in_stroke;
    double x_min, x_max, y_min, y_max;
    double* matrix_v;
    unsigned int* matrix_index;
} counts;

typedef enum { X = 0, Y, Z } axis_t;

// PARSER

int first_open(char* file_name, counts* count);
int is_digit(char symbol);
void second_open(char* file_name, counts* count);
void max_f_in_str(counts* count, char* file_name);
void create_matrix_v(counts* count);
void create_matrix_index(counts* count);
void to_index_matrix(counts* count);
void free_matrix(counts* count);
void cpy_struct(counts old_struct, counts* new_struct);
void cpy_matrix(counts old_struct, counts* new_struct);
void cpy_matrix_v(counts old_struct, counts* new_struct);
void cpy_matrix_index(counts old_struct, counts* new_struct);
void check_max_min(counts* count, double x_tmp, double y_tmp);

// AFFINE_TRANSFORMATIONS

void translate(double* vertices, int count, axis_t axis, double a);
void rotate_by_ox(double* vertices, int count, double angle);
void rotate_by_oy(double* vertices, int count, double angle);
void rotate_by_oz(double* vertices, int count, double angle);
void scale(double* vertices, int count, double a);

#endif  // SRC_3D_VIEWER_H
