#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "func.h"

void get_size(int* rows, int* rows_length) {
	printf("Введите размер квадратной матрицы : ");
	scanf_s("%d", rows);

	*rows_length = *rows;
}

struct matrix get_matrix_manual(struct matrix* matrix) {
	get_size(&(matrix->rows), &(matrix->columns));

	matrix->matrix = (int**)malloc(sizeof(int*) * matrix->rows);

	for (int i = 0; i < matrix->rows; i++) {
		(matrix->matrix)[i] = (int*)malloc(sizeof(int) * matrix->columns);
		printf("Введите %d строку \n", i);
		for (int j = 0; j < matrix->columns; j++) {

			printf("Введите [%d][%d] элемент матрицы : ", i, j);
			scanf_s("%d", &((matrix->matrix)[i][j]));
		}
	}

	return *matrix;
}

void initialize_matrix_with_standard_array(struct matrix* matrix, int* standard_matrix) {
	matrix->matrix = (int**)malloc(sizeof(int*) * matrix->rows);
	for (int i = 0; i < matrix->rows; i++) {
		matrix->matrix[i] = (int*)malloc(sizeof(int) * matrix->columns);

		for (int j = 0; j < matrix->columns; j++) {
			matrix->matrix[i][j] = (standard_matrix + i * matrix->columns)[j];
		}
	}
}

struct matrix get_matrix_auto(struct matrix* matrix) {
	matrix->mode = 0;
	printf("Введите номер тестовой матрицы : 1, 2 \n");
	scanf_s("%d", &matrix->mode);

	switch (matrix->mode) {
	case 1:
		matrix->rows = 4;
		matrix->columns = 4;
		int standard_matrix[4][4] = { {1,2,4,4},
									  {2,3,4,5},
									  {5,6,7,8},
									  {9,8,7,3} };
		initialize_matrix_with_standard_array(matrix, *standard_matrix);
		return *matrix;
	case 2:
		matrix->rows = 5;
		matrix->columns = 5;
		int second_standard_matrix[5][5] = { {1,4,4,3,5},
											 {2,7,9,1,4},
											 {3,7,5,2,3},
											 {9,8,7,3,6} };
		initialize_matrix_with_standard_array(matrix, *second_standard_matrix);
		return *matrix;
	}
}

struct matrix get_matrix(struct matrix* matrix) {
	int mode = 0;
	printf("Ввести матрицу вручную (1) / ввести тестовую матрицу (2) ? : \n");
	scanf_s("%d", &mode);

	switch (mode) {
	case 1:
		return get_matrix_manual(matrix);
	case 2:
		return get_matrix_auto(matrix);
	}
}


void print_array(struct matrix matrix) {
	printf("Матрица : \n");
	if (matrix.columns != 0) {
		for (int i = 0; i < matrix.rows; i++) {
			for (int j = 0; j < matrix.columns; j++) {
				printf("%d ", (matrix.matrix)[i][j]);
			}
			printf("\n");
		}
	}
	else {
		printf("Пусто");
	}
	printf("\n");

}

int find_minimal_value_under_diagonal(struct matrix matrix) {
	int min = (matrix.matrix)[matrix.rows - 1][matrix.rows - 1];
	for (int i = 1; i < matrix.rows; i++) {
		for (int j = matrix.columns - 1; j > matrix.columns - i - 1; j--) {
			if ((matrix.matrix)[i][j] < min) {
				min = (matrix.matrix)[i][j];
			}
		}
	}
	return min;
}

void delete_element_from_row_of_dynamic_array(int** row, int length, int index_of_element) {
	if (index_of_element != length - 1) {
		for (int i = index_of_element; i + 1 < length; i++) {
			(*row)[i] = (*row)[i + 1];
		}
	}
	*row = realloc(*row, sizeof(int) * (length - 1));
}

void delete_column_of_dynamic_array(struct matrix* matrix, int column) {
	for (int i = 0; i < matrix->rows; i++) {
		delete_element_from_row_of_dynamic_array(&(matrix->matrix[i]), matrix->columns, column);
	}
	matrix->columns--;
}

void delete_columns_with_minimal_value_under_diagonal(struct matrix* matrix) {
	int min = find_minimal_value_under_diagonal(*matrix);

	for (int i = matrix->columns - 1; i >= 0; i--) {
		for (int j = 0; j < matrix->rows; j++) {
			if (matrix->matrix[j][i] == min) {
				delete_column_of_dynamic_array(matrix, i);
			}
		}
	}
}

void compare_results(struct matrix matrix, int** expected_results) {
	for (int i = 0; i < matrix.rows; i++) {
		for (int j = 0; j < matrix.columns; j++) {
			if (matrix.matrix[i][j] != expected_results[i][j]) {
				return 0;
			}
		}
	}
	return 1;
}

void check_results(struct matrix matrix) {
	switch (matrix.mode) {
	case 1:{
		int** first_expected_results[4];
		first_expected_results[0] = (int[]){ 1,4 };
		first_expected_results[1] = (int[]){ 2,4 };
		first_expected_results[2] = (int[]){ 5,7 };
		first_expected_results[3] = (int[]){ 9,7 };
		return compare_results(matrix, first_expected_results);
	}
	case 2: {
		if (matrix.columns == 0) {
			return 1;
		}
		else {
			return 0;
		}
	}
	default: 
		return 0;
	}
}

void free_matrix(struct matrix* matrix) {
	for (int i = 0; i < matrix->rows; i++) {
		free(matrix->matrix[i]);
	}
	free(matrix->matrix);
}

