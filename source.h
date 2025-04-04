#pragma once

#ifndef DIFF_H
#define DIFF_H

#define MAX_SIZE			10000
#define MAX_FILE_PATH_LEN	300

typedef enum { DELETE, INSERT } DiffAction;

struct DiffItem {
	DiffAction diff_action;
	int line_number;
	char* line;
	struct DiffItem* prev;
	struct DiffItem* next;
};

typedef struct DiffItem DiffItem;

void diff_push(char* line, int pos, DiffAction action);
void print_diff();
void print_lcs_matrix(int row_max, int col_max);
void generate_lcs_matrix(Array* a1, Array* a2);
void generate_diff(Array* a1, Array* a2, int i, int j);

#endif