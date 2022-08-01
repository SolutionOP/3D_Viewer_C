#include <stdio.h>

#include "3d_viewer.h"

int first_open(char* file_name, counts* count) {
    int res = 1;
    FILE* obj_file = fopen(file_name, "r");
    if (obj_file) {
        size_t N;
        char* file_str = NULL;
        char* p_str = NULL;
        while (getline(&file_str, &N, obj_file) != EOF) {
            p_str = file_str;
            if (file_str[0] == 'v' && file_str[1] == ' ') {
                count->count_of_vertexes++;
            } else if (file_str[0] == 'f' && file_str[1] == ' ') {
                count->count_of_facets++;
                while (*p_str) {
                    if (is_digit(*p_str)) {
                        count->count_facets_in_stroke++;
                    }
                    p_str++;
                }
            }
        }
        if (file_str != NULL) {
            free(file_str);
        }
        fclose(obj_file);
    } else {
        res = 0;
    }
    return res;
}

int is_digit(char symbol) {
    int res = 0;
    if (symbol >= '0' && symbol <= '9') {
        res = 1;
    }
    return res;
}

void second_open(char* file_name, counts* count) {
    FILE* obj_file = fopen(file_name, "r");
    size_t N;
    char* file_str = NULL;
    int f_str = 0;
    int i = 0;
    int j = 0;
    double x_tmp = 0, y_tmp = 0, z_tmp = 0;
    int one_index;
    char* p_str = NULL;
    create_matrix_v(count);
    create_matrix_index(count);
    while (getline(&file_str, &N, obj_file) != EOF) {
        p_str = file_str;
        if (file_str[0] == 'v' && file_str[1] == ' ') {
            sscanf(file_str, "v %lf %lf %lf", &x_tmp, &y_tmp, &z_tmp);
            if (i == 0) {
                count->x_min = x_tmp;
                count->y_min = y_tmp;
                count->x_max = x_tmp;
                count->y_max = y_tmp;
            }
            check_max_min(count, x_tmp, y_tmp);
            count->matrix_v[i] = x_tmp;
            i++;
            count->matrix_v[i] = y_tmp;
            i++;
            count->matrix_v[i] = z_tmp;
            i++;
        } else if (file_str[0] == 'f' && file_str[1] == ' ') {
            int n = 0;
            while (*p_str) {
                if (is_digit(*p_str)) {
                    int digit = (int)strtod(p_str, &p_str);
                    digit -= 1;
                    if (n == 0) {
                        one_index = digit;
                        count->matrix_index[j * 2] = digit;
                    } else {
                        count->matrix_index[(j * 2) - 1] = digit;
                        count->matrix_index[j * 2] = digit;
                    }
                    if (*p_str == '\n') {
                        count->matrix_index[(j * 2) + 1] = one_index;
                    }
                    j++;
                    n = 1;
                }
                if (*p_str != '\0') {
                    p_str++;
                }
            }
            f_str++;
        }
    }
    if (file_str != NULL) {
        free(file_str);
    }
    fclose(obj_file);
}

void create_matrix_v(counts* count) {
    count->matrix_v =
        (double*)calloc(count->count_of_vertexes * 3, sizeof(double));
}

void create_matrix_index(counts* count) {
    count->matrix_index =
        (unsigned int*)calloc(count->count_facets_in_stroke * 2, sizeof(int));
}

void free_matrix(counts* count) {
    count->count_facets_in_stroke = 0;
    count->count_of_facets = 0;
    count->count_of_vertexes = 0;
    free(count->matrix_v);
    free(count->matrix_index);
}

void cpy_matrix(counts old_struct, counts* new_struct) {
    cpy_matrix_v(old_struct, new_struct);
    cpy_matrix_index(old_struct, new_struct);
}

void cpy_matrix_v(counts old_struct, counts* new_struct) {
    for (int i = 0; i < old_struct.count_of_vertexes * 3; i++)
        new_struct->matrix_v[i] = old_struct.matrix_v[i];
}

void cpy_matrix_index(counts old_struct, counts* new_struct) {
    for (int j = 0; j < old_struct.count_facets_in_stroke * 2; j++)
        new_struct->matrix_index[j] = old_struct.matrix_index[j];
}

void cpy_counts(counts old, counts* new) {
    new->count_facets_in_stroke = old.count_facets_in_stroke;
    new->count_of_facets = old.count_of_facets;
    new->count_of_vertexes = old.count_of_vertexes;
    new->x_max = old.x_max;
    new->x_min = old.x_min;
    new->y_max = old.y_max;
    new->y_min = old.y_min;
}

void cpy_struct(counts old, counts* new) {
    cpy_counts(old, new);
    create_matrix_v(new);
    create_matrix_index(new);
    cpy_matrix(old, new);
}

void check_max_min(counts* count, double x_tmp, double y_tmp) {
    if (count->x_max < x_tmp) {
        count->x_max = x_tmp;
    }
    if (count->x_min > x_tmp) {
        count->x_min = x_tmp;
    }
    if (count->y_max < y_tmp) {
        count->y_max = y_tmp;
    }
    if (count->y_min > y_tmp) {
        count->y_min = y_tmp;
    }
}

