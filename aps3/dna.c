#include <stdio.h>

#include "dna.h"

void load_string(FILE *file, int *p, char *s, int t) {
    if (fscanf(file, "%d", p) != 1) {
        fprintf(stderr, "erro ao ler string do teste %d\n", t);
    }

    char c;
    do {
        c = getc(file);
    } while (c != '\n');

    fgets(s, *p + 1, file);
}

// essa tem que ser recursiva
int mlcs_w(char a[], int n, char b[], int m, int length[MAX_SIZE + 1][MAX_SIZE + 1]) {
    if ((n == 0) || (m == 0)) {
        length[n][m] = 0;
    }

    if (length[n][m] != -1) {
        return length[n][m];
    }

    if (a[n - 1] == b[m - 1]) {
        length[n][m] = mlcs_w(a, n - 1, b, m - 1, length) + 1;
    } else {
        int x = mlcs_w(a, n - 1, b, m, length);
        int y = mlcs_w(a, n, b, m - 1, length);
        if (x > y) {
            length[n][m] = x;
        } else {
            length[n][m] = y;
        }
    }

    return length[n][m];
}

int mlcs(char a[], int n, char b[], int m) {
    int length[MAX_SIZE + 1][MAX_SIZE + 1];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            length[i][j] = -1;
        }
    }

    length[n][m] = mlcs_w(a, n, b, m, length);

    return length[n][m];
}

int dlcs(char a[], int n, char b[], int m) {
    int length[MAX_SIZE + 1][MAX_SIZE + 1];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            length[i][j] = 0;
        }
    }

    if ((n == 0) || (m == 0)) {
        length[n][m] = 0;
        return length[n][m];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) {
                length[i][j] = length[i - 1][j - 1] + 1;
            } else {
                int x = length[i - 1][j];
                int y = length[i][j - 1];
                if (x > y) {
                    length[i][j] = x;
                } else {
                    length[i][j] = y;
                }
            }
        }
    }

    return length[n][m];
}
