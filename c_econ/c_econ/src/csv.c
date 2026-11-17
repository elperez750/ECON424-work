#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv.h"

Dataset *dataset_load(const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) return NULL;

    char line[1024];
    if (!fgets(line, sizeof line, f)) { fclose(f); return NULL; }

    Dataset *ds = calloc(1, sizeof *ds);
    if (!ds) { fclose(f); return NULL; }

    line[strcspn(line, "\r\n")] = '\0';
    for (char *tok = strtok(line, ","); tok && ds->ncols < CSV_MAX_COLS;
         tok = strtok(NULL, ",")) {
        strncpy(ds->names[ds->ncols], tok, CSV_NAME_LEN - 1);
        ds->ncols++;
    }

    int rows = 0;
    while (fgets(line, sizeof line, f))
        if (line[0] != '\n' && line[0] != '\r' && line[0] != '\0') rows++;
    ds->nrows = rows;

    for (int c = 0; c < ds->ncols; c++) ds->data[c] = malloc((size_t)rows * sizeof(double));

    rewind(f);
    fgets(line, sizeof line, f);               /* skip header */
    for (int i = 0; i < rows && fgets(line, sizeof line, f); i++) {
        int c = 0;
        for (char *tok = strtok(line, ",\r\n"); tok && c < ds->ncols;
             tok = strtok(NULL, ",\r\n"))
            ds->data[c++][i] = strtod(tok, NULL);
    }
    fclose(f);
    return ds;
}

const double *dataset_col(const Dataset *ds, const char *name) {
    for (int c = 0; c < ds->ncols; c++)
        if (strcmp(ds->names[c], name) == 0) return ds->data[c];
    return NULL;
}

void dataset_free(Dataset *ds) {
    if (!ds) return;
    for (int c = 0; c < ds->ncols; c++) free(ds->data[c]);
    free(ds);
}
