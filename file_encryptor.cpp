#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Function to encrypt or decrypt a file using XOR encryption
void xor_encrypt_decrypt(const string &input_file, const string &output_file, const string &key) {
    ifstream in(input_file, ios::binary);
    if (!in) {
        cerr << "Error: Could not open the input file." << endl;
        return;
    }

    ofstream out(output_file, ios::binary);
    if (!out) {
        cerr << "Error: Could not open the output file." << endl;
        return;
    }

    // Convert key to a vector of bytes (ASCII values)
    vector<unsigned char> key_bytes(key.begin(), key.end());
    size_t key_length = key_bytes.size();
    size_t key_index = 0;

    // Encrypt/Decrypt the file by XORing each byte with the key
    char byte;
    while (in.get(byte)) {
        byte ^= key_bytes[key_index];  // XOR the byte with the current key byte
        out.put(byte);
        key_index = (key_index + 1) % key_length;  // Move to the next key byte
    }

    in.close();
    out.close();

    cout << "File " << (input_file == output_file ? "encrypted" : "decrypted") << " successfully!" << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        cerr << "Usage: " << argv[0] << " <encrypt/decrypt> <input_file> <output_file> <key>" << endl;
        return 1;
    }

    string operation = argv[1];
    string input_file = argv[2];
    string output_file = argv[3];
    string key = argv[4];

    if (operation == "encrypt") {
        xor_encrypt_decrypt(input_file, output_file, key);
    } else if (operation == "decrypt") {
        xor_encrypt_decrypt(input_file, output_file, key);
    } else {
        cerr << "Invalid operation. Use 'encrypt' or 'decrypt'." << endl;
        return 1;
    }

    return 0;
}
