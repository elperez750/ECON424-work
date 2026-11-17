#ifndef CSV_H
#define CSV_H
/* PROVIDED: loads a CSV file (header row + numeric columns). Plumbing only. */

#define CSV_MAX_COLS 16
#define CSV_NAME_LEN 32

typedef struct {
    int nrows;
    int ncols;
    char names[CSV_MAX_COLS][CSV_NAME_LEN];
    double *data[CSV_MAX_COLS];      /* data[c][i] = value in column c, row i */
} Dataset;

Dataset *dataset_load(const char *path);                 /* NULL on failure */
const double *dataset_col(const Dataset *ds, const char *name);  /* NULL if missing */
void dataset_free(Dataset *ds);

#endif
