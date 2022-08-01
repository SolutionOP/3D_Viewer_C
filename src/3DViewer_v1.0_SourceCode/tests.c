#include <check.h>
#include "3d_viewer.h"
#include <stdio.h>

// PARSER TESTS

START_TEST(test_first_open) {
    counts test_struct = {0, 0, 0, 0, 0, 0, 0, NULL, NULL};
    int flag = 0;
    flag = first_open("sdfdsfds", &test_struct);
    ck_assert_int_eq(flag, 0);
    test_struct.count_facets_in_stroke = 0;
    test_struct.count_of_facets = 0;
    test_struct.count_of_vertexes = 0;

    flag = first_open("../models/cube.obj", &test_struct);
    ck_assert_int_eq(flag, 1);
    ck_assert_int_eq(test_struct.count_facets_in_stroke, 36);
    ck_assert_int_eq(test_struct.count_of_facets, 12);
    ck_assert_int_eq(test_struct.count_of_vertexes, 8);
    test_struct.count_facets_in_stroke = 0;
    test_struct.count_of_facets = 0;
    test_struct.count_of_vertexes = 0;

    flag = first_open("../models/lamp.obj", &test_struct);
    ck_assert_int_eq(flag, 1);
    ck_assert_int_eq(test_struct.count_facets_in_stroke, 66035);
    ck_assert_int_eq(test_struct.count_of_facets, 4404);
    ck_assert_int_eq(test_struct.count_of_vertexes, 4440);
    test_struct.count_facets_in_stroke = 0;
    test_struct.count_of_facets = 0;
    test_struct.count_of_vertexes = 0;
}
END_TEST

START_TEST(test_second_open) {
    counts test_struct = {0, 0, 0, 0, 0, 0, 0, NULL, NULL};
    int test_index[72] = {4, 0, 0, 3, 3, 4, 4, 3, 3, 7, 7, 4, 2, 6, 6, 7, 7, 2,
                          2, 7, 7, 3, 3, 2, 1, 5, 5, 2, 2, 1, 5, 6, 6, 2, 2, 5,
                          0, 4, 4, 1, 1, 0, 4, 5, 5, 1, 1, 4, 4, 7, 7, 5, 5, 4,
                          7, 6, 6, 5, 5, 7, 0, 1, 1, 2, 2, 0, 0, 2, 2, 3, 3, 0};
    double test_ver[24] = {1, -1, -1, 1, -1, 1, -1, -1, 1, -1, -1, -1,
                           1, 1,  -1, 1, 1,  1, -1, 1,  1, -1, 1,  -1};
    first_open("../models/cube.obj", &test_struct);
    second_open("../models/cube.obj", &test_struct);
    for (int i = 0; i < test_struct.count_facets_in_stroke * 2; i++) {
        ck_assert_int_eq(test_struct.matrix_index[i], test_index[i]);
    }
    for (int j = 0; j < test_struct.count_of_vertexes * 3; j++) {
        ck_assert_int_eq(test_struct.matrix_v[j], test_ver[j]);
    }
    free_matrix(&test_struct);
}
END_TEST

START_TEST(test_cpy) {
    counts test_struct = {0, 0, 0, 0, 0, 0, 0, NULL, NULL};
    counts test_new_struct = {0, 0, 0, 0, 0, 0, 0, NULL, NULL};
    first_open("../models/cube.obj", &test_struct);
    second_open("../models/cube.obj", &test_struct);
    cpy_struct(test_struct, &test_new_struct);
    for (int i = 0; i < test_struct.count_facets_in_stroke * 2; i++) {
        ck_assert_int_eq(test_struct.matrix_index[i],
                         test_new_struct.matrix_index[i]);
    }
    for (int j = 0; j < test_struct.count_of_vertexes * 3; j++) {
        ck_assert_int_eq(test_struct.matrix_v[j], test_new_struct.matrix_v[j]);
    }
    free_matrix(&test_struct);
    free_matrix(&test_new_struct);
}
END_TEST

// AFFINE TRANSFORMATIONS TEST

START_TEST(test_translate) {
    double *vertices = (double *)malloc(12 * sizeof(double));
    vertices[0] = 4;
    vertices[1] = -5;
    vertices[2] = 6;
    vertices[3] = 7;
    vertices[4] = -8;
    vertices[5] = 9;
    vertices[6] = 0;
    vertices[7] = 1;
    vertices[8] = -2;
    vertices[9] = -3;
    vertices[10] = 4;
    vertices[11] = -5;
    translate(vertices, 4, Y, -2);
    double result[12] = {4, -7, 6, 7, -10, 9, 0, -1, -2, -3, 2, -5};
    for (int i = 0; i < 12; i++) {
        ck_assert_double_eq(vertices[i], result[i]);
    }
    free(vertices);
}
END_TEST

START_TEST(test_rotate_ox) {
    double *vertices = (double *)malloc(12 * sizeof(double));
    vertices[0] = 4;
    vertices[1] = -5;
    vertices[2] = 6;
    vertices[3] = 7;
    vertices[4] = -8;
    vertices[5] = 9;
    vertices[6] = 0;
    vertices[7] = 1;
    vertices[8] = -2;
    vertices[9] = -3;
    vertices[10] = 4;
    vertices[11] = -5;
    rotate_by_ox(vertices, 4, 1);
    double result[12] = {4, -7.750337438188, -0.965541088832, 7, -11.895657310216, -1.869047125652, 0,
     2.223244275484, -0.239133626928, -3, 6.368564147512, 0.664372409892};
    for (int i = 0; i < 12; i++)
        ck_assert_double_eq_tol(vertices[i], result[i], 1e-11);
    free(vertices);
}
END_TEST

START_TEST(test_rotate_oy) {
    double *vertices = (double *)malloc(12 * sizeof(double));
    vertices[0] = 4;
    vertices[1] = -5;
    vertices[2] = 6;
    vertices[3] = 7;
    vertices[4] = -8;
    vertices[5] = 9;
    vertices[6] = 0;
    vertices[7] = 1;
    vertices[8] = -2;
    vertices[9] = -3;
    vertices[10] = 4;
    vertices[11] = -5;
    rotate_by_oy(vertices, 4, 1);
    double result[12] = {7.21003513232, -5, -0.124070104024, 11.355355004348, -8, -1.027576140844,
     -1.682941969616, 1, -1.080604611736, -5.828261841644, 4, -0.177098574916};
    for (int i = 0; i < 12; i++)
        ck_assert_double_eq_tol(vertices[i], result[i], 1e-11);
    free(vertices);
}
END_TEST

START_TEST(test_rotate_oz) {
    double *vertices = (double *)malloc(12 * sizeof(double));
    vertices[0] = 4;
    vertices[1] = -5;
    vertices[2] = 6;
    vertices[3] = 7;
    vertices[4] = -8;
    vertices[5] = 9;
    vertices[6] = 0;
    vertices[7] = 1;
    vertices[8] = -2;
    vertices[9] = -3;
    vertices[10] = 4;
    vertices[11] = -5;
    rotate_by_oz(vertices, 4, 1);
    double result[12] = {6.368564147512, 0.664372409892, 6, 10.51388401954, 1.567878446712, 9,
     -0.841470984808, 0.540302305868, -2, -4.986790856836, -0.363203730952, -5};
    for (int i = 0; i < 12; i++)
        ck_assert_double_eq_tol(vertices[i], result[i], 1e-11);
    free(vertices);
}
END_TEST

START_TEST(test_scale) {
    double *vertices = (double *)malloc(12 * sizeof(double));
    vertices[0] = 4;
    vertices[1] = -5;
    vertices[2] = 6;
    vertices[3] = 7;
    vertices[4] = -8;
    vertices[5] = 9;
    vertices[6] = 0;
    vertices[7] = 1;
    vertices[8] = -2;
    vertices[9] = -3;
    vertices[10] = 4;
    vertices[11] = -5;
    scale(vertices, 4, 2);
    double result[12] = {8, -10, 12, 14, -16, 18, 0, 2, -4, -6, 8, -10};
    for (int i = 0; i < 12; i++) {
        ck_assert_double_eq(vertices[i], result[i]);
    }
    free(vertices);
}
END_TEST

int main(void) {
    Suite *parser = suite_create("Parser tests");

    TCase *parse_first = tcase_create("First open");
    tcase_add_test(parse_first, test_first_open);
    TCase *parse_second = tcase_create("Second open");
    tcase_add_test(parse_second, test_second_open);
    TCase *copy_struct = tcase_create("Copy Data Struct");
    tcase_add_test(copy_struct, test_cpy);

    suite_add_tcase(parser, parse_first);
    suite_add_tcase(parser, parse_second);
    suite_add_tcase(parser, copy_struct);

    Suite *affine = suite_create("Affine Transformations");

    TCase *translate = tcase_create("Translate");
    tcase_add_test(translate, test_translate);
    TCase *rotate_ox = tcase_create("Rotate_oX");
    tcase_add_test(rotate_ox, test_rotate_ox);
    TCase *rotate_oy = tcase_create("Rotate_oY");
    tcase_add_test(rotate_oy, test_rotate_oy);
    TCase *rotate_oz = tcase_create("Rotate_oZ");
    tcase_add_test(rotate_oz, test_rotate_oz);
    TCase *scale = tcase_create("Scale");
    tcase_add_test(scale, test_scale);

    suite_add_tcase(affine, translate);
    suite_add_tcase(affine, rotate_ox);
    suite_add_tcase(affine, rotate_oy);
    suite_add_tcase(affine, rotate_oz);
    suite_add_tcase(affine, scale);

    SRunner *runner = srunner_create(parser);
    srunner_add_suite(runner, affine);

    srunner_run_all(runner, CK_NORMAL);
    int failed_count = srunner_ntests_failed(runner);
    srunner_free(runner);

    return failed_count == 0 ? 0 : 1;
}
