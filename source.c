#include "helper.h"
#include "source.h"

static DiffItem* head = NULL;
static DiffItem* foot = NULL;
static int lcs[MAX_SIZE][MAX_SIZE];

void diff_push(char* line, int pos, DiffAction action)
{
	DiffItem* new_item = (DiffItem*)malloc(sizeof(DiffItem));
	new_item->diff_action = action;
	new_item->line_number = pos;
	new_item->prev = NULL;
	new_item->next = NULL;
	new_item->line = line;

	if (head == NULL) head = new_item;

	if (foot != NULL) {
		DiffItem* old_foot = foot;
		new_item->prev = old_foot;
		old_foot->next = new_item;
	}
	foot = new_item;
}

void print_diff()
{
	DiffItem* curr = foot;
	while (curr != NULL) {
		printf("%2d (%c) | %.50s\n", curr->line_number, curr->diff_action ? '+' : '-', curr->line);
		curr = curr->prev;
		if (curr == head->prev) break;
	}
}

void print_lcs_matrix(int row_max, int col_max)
{
	for (int i = 0; i <= row_max; ++i) {
		for (int j = 0; j <= col_max; ++j) {
			printf("%2d ", lcs[i][j]);
		}
		printf("\n");
	}
}

void generate_diff(Array* a1, Array* a2, int i, int j)
{
	while (i != 0 && j != 0)
	{
		if (!strcmp(string_at(a1, i - 1), string_at(a2, j - 1))) {
			i--; j--; continue;
		}

		if (lcs[i - 1][j] > lcs[i][j - 1]) {
			diff_push(string_at(a1, i - 1), i, DELETE);
			i--; continue;
		}
		diff_push(string_at(a2, j - 1), j, INSERT);
		j--;
	}

	while (i > 0) { diff_push(string_at(a1, i - 1), i, DELETE); i--; }
	while (j > 0) { diff_push(string_at(a2, j - 1), j, INSERT); j--; }
}

void generate_lcs_matrix(Array* a1, Array* a2)
{
	for (int i = 0; i <= a1->size; ++i)
	{
		for (int j = 0; j <= a2->size; ++j)
		{
			if (i == 0 || j == 0) lcs[i][j] = 0;
			else if (!strcmp(string_at(a1, i - 1), string_at(a2, j - 1)))
				lcs[i][j] = 1 + lcs[i - 1][j - 1];
			else
				lcs[i][j] = (lcs[i - 1][j] > lcs[i][j - 1]) ? lcs[i - 1][j] : lcs[i][j - 1];
		}
	}
}

int main()
{
	char filepath1[MAX_FILE_PATH_LEN], filepath2[MAX_FILE_PATH_LEN];
	printf("Path to original file: ");
	int res1 = scanf("%s", filepath1);
	printf("Path to modified file: ");
	int res2 = scanf("%s", filepath2);

	if (res1 != 1 || res2 != 1) {
		printf("ERROR: Failed to read file paths provided.");
		exit(1);
	}

	char* s1 = read_file(filepath1);
	char* s2 = read_file(filepath2);

	Array* a1 = split(s1, '\n');
	Array* a2 = split(s2, '\n');

	memset(lcs, -1, sizeof(lcs));
	generate_lcs_matrix(a1, a2);
	generate_diff(a1, a2, a1->size, a2->size);
	print_diff();

	free_string_arr(a1);
	free_string_arr(a2);
	return 0;
}
