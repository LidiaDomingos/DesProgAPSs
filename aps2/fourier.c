#include <math.h>

#include "fourier.h"

void nft(double complex s[MAX_SIZE], double complex t[MAX_SIZE], int n, int sign) {
    for (int k = 0; k < n; k++) {
        t[k] = 0;
        for (int j = 0; j < n; j++) {
            t[k] += s[j] * cexp(sign * 2 * PI * k * j * I / n);
        }
    }
}

void nft_forward(double complex s[MAX_SIZE], double complex t[MAX_SIZE], int n) {
    nft(s, t, n, -1);
}

void nft_inverse(double complex t[MAX_SIZE], double complex s[MAX_SIZE], int n) {
    nft(t, s, n, 1);
    for (int k = 0; k < n; k++) {
        s[k] /= n;
    }
}

void fft(double complex s[MAX_SIZE], double complex t[MAX_SIZE], int n, int sign) {
    if (n == 1) {
        t[0] = s[0];
        return;
    }
    
    double complex sp[n / 2];
    double complex si[n / 2];
    
    int j = 0;
    int w = 0;
    for (int i = 0; i < n; i++) {
        if ((i % 2) == 0) {
            sp[j] = s[i];
            j++;
        } else {
            si[w] = s[i];
            w++;
        }
    }

    double complex tp[n / 2];
    fft(sp, tp, n / 2, sign);
    double complex ti[n / 2];
    fft(si, ti, n / 2, sign);

    for (int k = 0; k < n / 2; k++) {
        t[k] = tp[k] + ti[k] * cexp(2 * PI * sign * k * I / n);
        t[k + n / 2] = tp[k] - ti[k] * cexp(2 * sign * PI * k * I / n);
    }
}

void fft_forward(double complex s[MAX_SIZE], double complex t[MAX_SIZE], int n) {
    fft(s, t, n, -1);
}

void fft_inverse(double complex t[MAX_SIZE], double complex s[MAX_SIZE], int n) {
    fft(t, s, n, 1);
    for (int k = 0; k < n; k++) {
        s[k] /= n;
    }
}

void fft_forward_2d(double complex matrix[MAX_SIZE][MAX_SIZE], int width, int height) {
    // int n = width*height
    // for (int x=0; x < width; x++){
    //     for (int y=0; y< height; y++){
    //         fft_forward(matrix[x], matrix[y], n);
    //         }
    //     }
    double complex coluna[MAX_SIZE];
    for (int i = 0; i < height; i++ ){
        fft_forward(matrix[i], matrix[i], width);
    }

    for (int i = 0; i < width; i++ ){
        for(int j = 0; j < height; j++){
            coluna[j] = matrix[j][i];        
        }
        fft_forward(coluna, coluna, height);
        for (int k = 0; k < height; k++){ 
            matrix[k][i] = coluna[k];
        }
    }


}

void fft_inverse_2d(double complex matrix[MAX_SIZE][MAX_SIZE], int width, int height) {
    double complex coluna[MAX_SIZE];
    for (int i = 0; i < height; i++ ){
        fft_inverse(matrix[i], matrix[i], width);
    }

    for (int i = 0; i < width; i++ ){
        for(int j = 0; j < height; j++){
            coluna[j] = matrix[j][i];        
        }
        fft_inverse(coluna, coluna, height);
        for (int k = 0; k < height; k++){ 
            matrix[k][i] = coluna[k];
        }
    }
}

void filter(double complex input[MAX_SIZE][MAX_SIZE], double complex output[MAX_SIZE][MAX_SIZE], int width, int height, int flip) {
    int center_x = width / 2;
    int center_y = height / 2;
    double variance = -2 * SIGMA * SIGMA;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int dx = center_x - (x + center_x) % width;
            int dy = center_y - (y + center_y) % height;
            double d = dx * dx + dy * dy;
            double g = exp(d / variance);
            if (flip) {
                g = 1 - g;
            }
            output[y][x] = g * input[y][x];
        }
    }
}

void filter_lp(double complex input[MAX_SIZE][MAX_SIZE], double complex output[MAX_SIZE][MAX_SIZE], int width, int height) {
    filter(input, output, width, height, 0);
}

void filter_hp(double complex input[MAX_SIZE][MAX_SIZE], double complex output[MAX_SIZE][MAX_SIZE], int width, int height) {
    filter(input, output, width, height, 1);
}
