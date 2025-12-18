#include "algo.h"

//! KEYS

int k_altCC = 0;
int k_wood = 0;
int k_exohr_1[/*define*/][8] = {
		
};
int k_exohr_2[/*define*/][8] = {
	
};

//!

void encrypt() {
    int n;
    char* msg = readFromFile("input.txt", n);
    
    if (msg == nullptr) {
        cout << "Failed to read input file!" << endl;
        return;
    }

    cout << "Encrypting message from input.txt...\n";
    
    ofstream outFile("output.txt");
    if (!outFile.is_open()) {
        cout << "Error creating output file!" << endl;
        delete[] msg;
        return;
    }
    
    srand(static_cast<unsigned int>(time(nullptr)));

    char* decoy1 = generateRandomAlphanumeric(n);
    char* decoy2 = generateRandomAlphanumeric(n);
    char* decoy3 = generateRandomAlphanumeric(n);
    char* decoy4 = generateRandomAlphanumeric(n);

    altCC(msg, k_altCC, n);
    altCC(decoy1, k_altCC, n);
    altCC(decoy2, k_altCC, n);
    altCC(decoy3, k_altCC, n);
    altCC(decoy4, k_altCC, n);

    char* morning_wood = wood(msg, k_wood, n);
    char* morning_wood_d1 = wood(decoy1, k_wood, n);
    char* morning_wood_d2 = wood(decoy2, k_wood, n);
    char* morning_wood_d3 = wood(decoy3, k_wood, n);
    char* morning_wood_d4 = wood(decoy4, k_wood, n);
    
    int c_i = strlen(morning_wood);
    int msg_i[c_i];
    int d1_i[c_i];
    int d2_i[c_i];
    int d3_i[c_i];
    int d4_i[c_i];

    for (int i = 0; i < c_i; i++) {
        msg_i[i] = (int)morning_wood[i];
    }
    for (int i = 0; i < c_i; i++) {
        d1_i[i] = (int)morning_wood_d1[i];
    }
    for (int i = 0; i < c_i; i++) {
        d2_i[i] = (int)morning_wood_d2[i];
    }
    for (int i = 0; i < c_i; i++) {
        d3_i[i] = (int)morning_wood_d3[i];
    }
    for (int i = 0; i < c_i; i++) {
        d4_i[i] = (int)morning_wood_d4[i];
    }
    
    int** bin = vTBin(msg_i, c_i);
    int** bin_d1 = vTBin(d1_i, c_i);
    int** bin_d2 = vTBin(d2_i, c_i);
    int** bin_d3 = vTBin(d3_i, c_i);
    int** bin_d4 = vTBin(d4_i, c_i);

    bin = exohr(bin, k_exohr_1, c_i);
    bin_d1 = exohr(bin_d1, k_exohr_1, c_i);
    bin_d2 = exohr(bin_d2, k_exohr_1, c_i);
    bin_d3 = exohr(bin_d3, k_exohr_1, c_i);
    bin_d4 = exohr(bin_d4, k_exohr_1, c_i);

    bin = exohr(bin, k_exohr_2, c_i);
    bin_d1 = exohr(bin_d1, k_exohr_2, c_i);
    bin_d2 = exohr(bin_d2, k_exohr_2, c_i);
    bin_d3 = exohr(bin_d3, k_exohr_2, c_i);
    bin_d4 = exohr(bin_d4, k_exohr_2, c_i);

    int* msg_i_pX = BinTv(bin, c_i);
    int* d1_i_pX = BinTv(bin_d1, c_i);
    int* d2_i_pX = BinTv(bin_d2, c_i);
    int* d3_i_pX = BinTv(bin_d3, c_i);
    int* d4_i_pX = BinTv(bin_d4, c_i);

    long long* r_msg = raisa_a_bitch(msg_i_pX,c_i);
    long long* r_d1 = raisa_a_bitch(d1_i_pX,c_i);
    long long* r_d2 = raisa_a_bitch(d2_i_pX,c_i);
    long long* r_d3 = raisa_a_bitch(d3_i_pX,c_i);
    long long* r_d4 = raisa_a_bitch(d4_i_pX,c_i);

    // Output only the final RSA result
    printLongVecToFile(outFile, r_d1, c_i);outFile << " ";
    printLongVecToFile(outFile, r_d2, c_i);outFile << " ";
    printLongVecToFile(outFile, r_d3, c_i);outFile << " ";
    printLongVecToFile(outFile, r_d4, c_i);outFile << " ";
    printLongVecToFile(outFile, r_msg, c_i);

    outFile.close();
    cout << "Encryption ballin. Output saved to output.txt\n";

    delete[] msg;
    delete[] decoy1;
    delete[] decoy2;
    delete[] decoy3;
    delete[] decoy4;
    delete[] morning_wood;
    delete[] morning_wood_d1;
    delete[] morning_wood_d2;
    delete[] morning_wood_d3;
    delete[] morning_wood_d4;
    freeBinM(bin, c_i);
    freeBinM(bin_d1, c_i);
    freeBinM(bin_d2, c_i);
    freeBinM(bin_d3, c_i);
    freeBinM(bin_d4, c_i);
    delete[] msg_i_pX;
    delete[] d1_i_pX;
    delete[] d2_i_pX;
    delete[] d3_i_pX;
    delete[] d4_i_pX;
    delete[] r_msg;
    delete[] r_d1;
    delete[] r_d2;
    delete[] r_d3;
    delete[] r_d4;
}

void decrypt() {
    ifstream inFile("output.txt");
    if (!inFile.is_open()) {
        cout << "Error opening output.txt for decryption!" << endl;
        return;
    }
    
    // Read all encrypted numbers from file
    long long temp;
    int count = 0;
    while (inFile >> temp) {
        count++;
    }
    
    // Reset file to beginning
    inFile.clear();
    inFile.seekg(0);
    
    long long* all_encrypted = new long long[count];
    for (int i = 0; i < count; i++) {
        inFile >> all_encrypted[i];
    }
    inFile.close();
    
    // Calculate the length of each message (total/5 since we have 5 payloads)
    int c_i = count / 5;
    
    // Extract the last payload (the real message)
    long long* encrypted = new long long[c_i];
    for (int i = 0; i < c_i; i++) {
        encrypted[i] = all_encrypted[4 * c_i + i];
    }
    
    delete[] all_encrypted;
    
    ofstream outFile("d_output.txt");
    if (!outFile.is_open()) {
        cout << "Error creating decrypted_output.txt!" << endl;
        delete[] encrypted;
        return;
    }
    
    cout << "\nDecrypting message from output.txt...\n";
    
    // RSA Decrypt
    int* ascii_decrypted = raisa_a_bitch_decrypt(encrypted, c_i);
    
    // XOR Decrypt (reverse order - apply k_exohr_2 then k_exohr_1)
    int** bin = vTBin(ascii_decrypted, c_i);
    bin = exohr(bin, k_exohr_2, c_i);
    bin = exohr(bin, k_exohr_1, c_i);
    
    int* ascii_after_xor = BinTv(bin, c_i);
    
    // Convert to char
    char* wood_encrypted = new char[c_i + 1];
    for (int i = 0; i < c_i; i++) {
        wood_encrypted[i] = (char)ascii_after_xor[i];
    }
    wood_encrypted[c_i] = '\0';
    
    // Wood Decrypt
    char* caesar_encrypted = wood_decrypt(wood_encrypted, k_wood, c_i);
    
    // Alternative Caesar Decrypt
    int original_len = strlen(caesar_encrypted);
    altCC_decrypt(caesar_encrypted, k_altCC, original_len);
    
    // Output only the final decrypted text
    outFile << caesar_encrypted;
    
    outFile.close();
    cout << "Decryption ballin. Output saved to d_output.txt\n";
    
    delete[] encrypted;
    delete[] ascii_decrypted;
    freeBinM(bin, c_i);
    delete[] ascii_after_xor;
    delete[] wood_encrypted;
    delete[] caesar_encrypted;
}

int main() {
    int choice;
    cout << "=================================\n";
    cout << "    CIPHER SQUARED SYSTEM\n";
    cout << "=================================\n";
    cout << "1. Encryption\n";
    cout << "2. Decryption\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;
    
    if (choice == 1) {
        encrypt();
    } else if (choice == 2) {
        decrypt();
    } else {
        cout << "Invalid choice!\n";
    }

    return 0;
}