#include <math.h>

#include "geometry.h"

double DELTA = 0.000001;


double modulo(double numero) {
    if (numero > 0.0) {
        return numero;
    } else {
        return (-1) * numero;
    }
}

int em_cima_de_ponto(point p, point a, point b) {
    if ((a.x == b.x) && (a.y == b.y)) {
        if ((a.x == p.x) && (a.y == p.y)) {
            return 2;
        }
        return 0;
    }
    if ((a.x == p.x) && (a.y == p.y)) {
        return 2;
    }
    if ((b.x == p.x) && (b.y == p.y)) {
        return 2;
    }
    return 3;
}

int esta_na_reta(point p, point a, point b, int maior_y, int menor_y, int maior_x, int menor_x) {

    // horz
    if ((a.y - b.y) == 0) {
        if ((p.x < maior_x) && (p.x >= menor_x) && (p.y == a.y)) {
            return 2; // está exatamente sobre a aresta, sendo ela horizontal
        } else {
            return 0;
        }
    } else if ((a.x - b.x) == 0) {
        if ((p.y <= maior_y) && (p.y > menor_y) && (p.x == a.x)) {
            return 2; // está exatamente sobre a aresta, sendo ela vertical
        } else {
            return 0;
        }
    } else {
        double m = 0;
        m = (double)(b.y - a.y) / (b.x - a.x);
        // m = 5;
        double b_eq_reta = a.y - (m * a.x);
        double x_calc = (p.y - b_eq_reta) / m;
        double diferenca_xs = modulo(p.x - x_calc);
        if (diferenca_xs < DELTA) {
            if (p.x > x_calc) {
                return 0;
            } else {
                if ((x_calc >= menor_x) && (x_calc <= maior_x)) {
                    if ((p.y <= maior_y) && (p.y >= menor_y)) {
                        return 2;
                    }
                }
            }
        }
    }
    return 3;
}

int atras_da_reta(point p, point a, point b, int menor_y, int maior_y, int menor_x, int maior_x) {
    if ((a.y - b.y) == 0) {
        return 0;
    } else if ((a.x - b.x) == 0) {
        if ((p.y <= maior_y) && (p.y > menor_y) && (p.x < a.x)) {
            return 1; // está exatamente sobre a aresta, sendo ela vertical
        }
    } else {
        double m = 0;
        m = (double)(b.y - a.y) / (b.x - a.x);
        double b_eq_reta = a.y - (m * a.x);
        double x_calc = (p.y - b_eq_reta) / m;
        if (p.x < x_calc) {
            if ((p.y > menor_y) && (p.y <= maior_y)) {
                return 1;
            }
        }
    }
    return 0;
}

int verify(point p, point a, point b) {
    int maior_y = a.y;
    int menor_y = b.y;
    if (b.y > a.y) {
        maior_y = b.y;
        menor_y = a.y;
    }
    int maior_x = a.x;
    int menor_x = b.x;
    if (b.x > a.x) {
        maior_x = b.x;
        menor_x = a.x;
    }


    int resultado_em_cima = em_cima_de_ponto(p, a, b);
    if (resultado_em_cima == 2) {
        return resultado_em_cima;
    }

    int resultado_na_reta = esta_na_reta(p, a, b, maior_y, menor_y, maior_x, menor_x);
    if (resultado_na_reta == 2) {
        return resultado_na_reta;
    }

    int resultado_atras_da_reta = atras_da_reta(p, a, b, menor_y, maior_y, menor_x, maior_x);
    if (resultado_atras_da_reta == 1) {
        return 1;
    }
    return 0;
}
int checa_par_ou_impar(int quantidade) {
    if (quantidade % 2 == 0) {
        return 0;
    }
    return 1; 
}

int inside(point p, point poly[], int n) {
    int resposta = 0;
    int resposta_final = 0;
    int quantidade = 0;

    for (int i = 0; i < n; i++) {
        resposta = verify(p, poly[i], poly[i + 1]);
        if (i == (n - 1)) {
            resposta = verify(p, poly[0], poly[i]);
        }
        if (resposta == 2) {
            return 1;
        }
        if (resposta == 1){
            quantidade = quantidade + 1;
        }
    }
    resposta_final = checa_par_ou_impar(quantidade);
    return resposta_final;
}
