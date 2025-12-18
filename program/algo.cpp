#include "algo.h"

void printVec(int msg[], int len)
{
    for (int i = 0; i < len-1; i++) {
        cout << msg[i] << " ";
    }
    cout << msg[len-1];
}

void printVecToFile(ofstream& file, int msg[], int len)
{
    for (int i = 0; i < len-1; i++) {
        file << msg[i] << " ";
    }
    file << msg[len-1];
}

void printLongVecToFile(ofstream& file, long long msg[], int len)
{
    for (int i = 0; i < len-1; i++) {
        file << msg[i] << " ";
    }
    file << msg[len-1];
}

char* rMaPS(int n)
{
    char* message = new char[n + 1];
    cout << "Input message: ";
	cin.get();
	cin.get(message, n+1);
    message[n] = '\0';
    return message;
}

char* readFromFile(const char* filename, int& len)
{
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        len = 0;
        return nullptr;
    }
    
    // Read entire content
    file.seekg(0, ios::end);
    len = file.tellg();
    file.seekg(0, ios::beg);
    
    char* message = new char[len + 1];
    file.read(message, len);
    message[len] = '\0';
    
    file.close();
    return message;
}

void altCC(char msg[], int key, int len)
{
    int k = key;
    for (int i = 0; i < len; i++) {
        msg[i] += k;
        k *= -1;
    }
}

void altCC_decrypt(char msg[], int key, int len)
{
    int k = key;
    for (int i = 0; i < len; i++) {
        msg[i] -= k;
        k *= -1;
    }
}

char* wood(char msg[], int key, int len)
{
    int m = 1;
    while (key*m < len) {
        m++;
    }
    int counter = 0;
    char matrix[key][m];
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < m; j++) {
            if (counter >= len) {
                matrix[i][j] = 'z';
            } else {
                matrix[i][j] = msg[counter];
                counter++;
            }
        }
    }
    counter = 0;
    int wood_vec_size = key*m;
    char* morning_wood = new char[wood_vec_size + 1];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < key; j++) {
            morning_wood[counter++] = matrix[j][i];
        }
    }

    morning_wood[wood_vec_size] = '\0';

    return morning_wood;
}

char* wood_decrypt(char msg[], int key, int len)
{
    int m = len / key;
    char matrix[key][m];
    
    int counter = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < key; j++) {
            matrix[j][i] = msg[counter++];
        }
    }
    
    char* decrypted = new char[len + 1];
    counter = 0;
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < m; j++) {
            decrypted[counter++] = matrix[i][j];
        }
    }
    
    // Remove padding 'z' characters
    int real_len = len;
    while (real_len > 0 && decrypted[real_len - 1] == 'z') {
        real_len--;
    }
    decrypted[real_len] = '\0';
    
    return decrypted;
}

char* generateRandomAlphanumeric(int n) {
    char* arr = new char[n + 1];

    for (int i = 0; i < n; i++) {
        double r = static_cast<double>(rand()) / RAND_MAX;

        if (r < 0.75) {
            // Generate letter
            if (rand() % 2 == 0)
                arr[i] = 'A' + rand() % 26; // uppercase
            else
                arr[i] = 'a' + rand() % 26; // lowercase
        } else {
            // Generate digit
            arr[i] = '0' + rand() % 10;
        }
    }

    arr[n] = '\0';
    return arr;
}

int** vTBin(int* ascii, int rows)
{
    int** matrix = new int*[rows];

    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[8];

        for (int j = 0; j < 8; j++) {
            int shift = 8 - 1 - j;      // MSB → LSB
            matrix[i][j] = (ascii[i] >> shift) & 1;
        }
    }

    return matrix;
}

void printBinM(int** matrix, int rows)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 8; j++) {
            cout << matrix[i][j];
        }
        cout << endl;
    }
}

void freeBinM(int** matrix, int rows)
{
    for (int i = 0; i < rows; i++)
        delete[] matrix[i];
    delete[] matrix;
}

int* BinTv(int** binMatrix, int rows)
{
    int* asciiCodes = new int[rows];

    for (int i = 0; i < rows; i++) {
        int val = 0;

        for (int j = 0; j < 8; j++) {
            val <<= 1;
            val |= binMatrix[i][j];
        }

        asciiCodes[i] = val;
    }

    return asciiCodes;
}

long long* raisa_a_bitch(int* ascii, int len)
{
    long long p = 1033;
    long long q = 6967;
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    long long e = 999983; // Public Key
    long long d = 0; // Private Key

    // Compute d such that (d * e) % phi == 1
    for (long long i = 2; i <= 1000000000; i++) {
        if ((i * e) % phi == 1) {
            d = i;
            break;
        }
    }

    // Local modular exponentiation (fast)
    auto modExp = [&](long long base, long long exp, long long mod) {
        long long result = 1;
        base %= mod;

        while (exp > 0) {
            if (exp & 1)
                result = (result * base) % mod;

            base = (base * base) % mod;
            exp >>= 1;
        }
        return result;
    };

    long long* encrypted = new long long[len];

    for (int i = 0; i < len; i++) {
        encrypted[i] = modExp(ascii[i], e, n);
    }
    
    return encrypted;
}

int* raisa_a_bitch_decrypt(long long* encrypted, int len)
{
    long long p = 1033;
    long long q = 6967;
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    long long e = 999983; // Public Key
    long long d = 0; // Private Key

    // Compute d such that (d * e) % phi == 1
    for (long long i = 2; i <= 1000000000; i++) {
        if ((i * e) % phi == 1) {
            d = i;
            break;
        }
    }

    // Local modular exponentiation (fast)
    auto modExp = [&](long long base, long long exp, long long mod) {
        long long result = 1;
        base %= mod;

        while (exp > 0) {
            if (exp & 1)
                result = (result * base) % mod;

            base = (base * base) % mod;
            exp >>= 1;
        }
        return result;
    };

    int* decrypted = new int[len];

    for (int i = 0; i < len; i++) {
        decrypted[i] = (int)modExp(encrypted[i], d, n);
    }
    
    return decrypted;
}

void rongrongTime(long long msg[], int len)
{
    for (int i = 0; i < len-1; i++) {
        cout << msg[i] << " ";
    }
    cout << msg[len-1];
}