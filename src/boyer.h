//
// Created by USER on 7/8/2023.
//
#ifndef PROYECTOALGORITMOS_BOYER_H
#define PROYECTOALGORITMOS_BOYER_H
#include <iostream>
#include <string>
#include "vector"
#include <chrono>
#include <ctime>
#include <unistd.h>
#include <fstream>

using namespace std;

vector<int> calcularSaltos(const string& patron) {
    int m = int(patron.size());
    vector<int> saltos(256, m);

    for (int i = 0; i < m - 1; i++) {
        saltos[patron[i]] = m - 1 - i;
    }

    return saltos;
}

vector<int> BoyerMoore(const string& texto, const string& patron) {
    vector<int> pos;
    int n = int(texto.length());
    int m = int(patron.length());
    vector<int> saltos = calcularSaltos(patron);

    int i = m - 1;
    while (i < n) {
        int j = m - 1;
        while (j >= 0 && texto[i] == patron[j]) {
            i--;
            j--;
        }

        if (j == -1) {
            pos.push_back(i+1);
            i=i+1;
        }

        i += max(saltos[texto[i]], m - 1 - j);
    }

    return pos;
}


#endif //PROYECTOALGORITMOS_BOYER_H
