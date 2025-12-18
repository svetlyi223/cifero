#ifndef ALGO_H
#define ALGO_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <limits.h>
#include <cstdlib>
#include <ctime>
using namespace std;

void printVec(int msg[], int len);
void printVecToFile(ofstream& file, int msg[], int len);
void printLongVecToFile(ofstream& file, long long msg[], int len);

char* rMaPS(int n); //? rMaPS = read Message and Payload Size
char* readFromFile(const char* filename, int& len);

void altCC(char msg[], int key, int len); //? altC = alternative Caesar
void altCC_decrypt(char msg[], int key, int len);

char* wood(char msg[], int key, int len);
char* wood_decrypt(char msg[], int key, int len);

char* generateRandomAlphanumeric(int n);

int** vTBin(int* ascii, int rows);
void printBinM(int** matrix, int rows);
void freeBinM(int** matrix, int rows);

//!
template <size_t KEY_ROWS>
int** exohr(int** matrix, int (&key)[KEY_ROWS][8], int rows)
{
    int** result = new int*[rows];
    for (int i = 0; i < rows; i++) {
        result[i] = new int[8];
        int keyRow = i % KEY_ROWS;
        for (int j = 0; j < 8; j++) {
            result[i][j] = matrix[i][j] ^ key[keyRow][j];
        }
    }

    return result;
}
//!

int* BinTv(int** binMatrix, int rows);

long long* raisa_a_bitch(int* ascii, int len);
int* raisa_a_bitch_decrypt(long long* encrypted, int len);

void rongrongTime(long long msg[], int len);

#endif
