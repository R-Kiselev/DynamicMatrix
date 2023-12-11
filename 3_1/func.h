#pragma once

struct matrix {
	int** matrix;
	int rows;
	int columns;
	int mode;
};

struct matrix get_matrix(struct matrix* );

void print_array(struct matrix);

void delete_columns_with_minimal_value_under_diagonal(struct matrix*);

void free_matrix(struct matrix*);

//void check_results(struct matrix);