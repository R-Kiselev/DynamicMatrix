#include "func.h"

int main() {
	SetConsoleOutputCP(1251);

	struct matrix matrix;

	matrix = get_matrix(&matrix);
	print_array(matrix);

	delete_columns_with_minimal_value_under_diagonal(&matrix);
	print_array(matrix);

	if (check_results(matrix)) {
		printf("���������� ��������.\n");
	}
	else {
		printf("������� �� �������� ������ ���� ���������� �� ��������. \n");
	}

	free_matrix(&matrix);
}