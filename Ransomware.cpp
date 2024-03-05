#include <iostream>
#include <fstream>
#include <string>
#include <io.h> // for _findfirst and _findnext

using namespace std;

void encryptFiles(const string& folderPath);
void decryptFiles(const string& folderPath, const string& key);

int main() {
    string folderPath = "./Migu";
    string key;
    char choice;

    // Prompt user to enter encryption key
    cout << "Enter encryption key: ";
    getline(cin, key);

    // Prompt user to choose encryption or decryption
    cout << "Choose operation:" << endl;
    cout << "1. Encrypt files" << endl;
    cout << "2. Decrypt files" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case '1':
            encryptFiles(folderPath);
            break;
        case '2':
            // Prompt for key before decryption
            string inputKey;
            cout << "Enter decryption key: ";
            cin.ignore(); // Clear newline character from buffer
            getline(cin, inputKey);
            if (inputKey == key) {
                decryptFiles(folderPath, key);
            } else {
                cout << "Invalid decryption key. Access denied." << endl;
            }
            break;
        
    }

    return 0;
}
// Function to encrypt files in the specified folder
void encryptFiles(const string& folderPath) {
    // Find first file in the directory
    _finddata_t fileData;
    long handle = _findfirst(string(folderPath + "/*").c_str(), &fileData);

    // Check if any file was found
    if (handle == -1) {
        cout << "\nError: No files found in '" << folderPath << "' folder.";
        return;
    }

    do {
        // Skip "." and ".." directories
        if (strcmp(fileData.name, ".") == 0 || strcmp(fileData.name, "..") == 0) {
            continue;
        }

        string fileName = folderPath + "/" + fileData.name;

        // Open the file for encryption
        ifstream fin(fileName.c_str(), ios::binary); // Use c_str() to convert string to const char*
        if (!fin) {
            cout << "\nError: Unable to open file '" << fileName << "' for reading.";
            continue; // Move to the next file
        }

        // Open a temporary file for writing encrypted content
        ofstream fout("tmp.txt", ios::binary);
        if (!fout) {
            cout << "\nError: Unable to create temporary file 'tmp.txt' for writing.";
            fin.close();
            continue; // Move to the next file
        }

        // Encrypt the content of the file
        char ch;
        while (fin.get(ch)) {
            ch += 100; // Example encryption algorithm (add 100 to ASCII value)
            fout.put(ch);
        }

        // Close the files
        fin.close();
        fout.close();

        // Replace the original file with the encrypted content
        remove(fileName.c_str());
        rename("tmp.txt", fileName.c_str());

        cout << "\nFile '" << fileName << "' encrypted successfully.";

    } while (_findnext(handle, &fileData) == 0);

    _findclose(handle); // Close the search handle

    // Create a README.txt file outside the Migu folder
    string readmeFilePath = "README.txt"; // Adjust the path as necessary
    ofstream readmeFile(readmeFilePath.c_str()); // Use c_str() to convert string to const char*
    if (readmeFile.is_open()) {
        readmeFile << "I have your Miku." << endl;
        readmeFile << "Say 'I love Hatsune Miku' 100 times to get her back. Mwahahaha." << endl;
        readmeFile.close();
        
    }

    cout << "\nEncryption process completed for files in '" << folderPath << "' folder.";
    cout << endl;
}



// Function to decrypt files in the specified folder
void decryptFiles(const string& folderPath, const string& key) {
    // Find first file in the directory
    _finddata_t fileData;
    long handle = _findfirst(string(folderPath + "/*").c_str(), &fileData);

    // Check if any file was found
    if (handle == -1) {
        cout << "\nError: No files found in '" << folderPath << "' folder.";
        return;
    }

    do {
        // Skip "." and ".." directories
        if (strcmp(fileData.name, ".") == 0 || strcmp(fileData.name, "..") == 0) {
            continue;
        }

        string fileName = folderPath + "/" + fileData.name;

        // Open the file for decryption
        ifstream fin(fileName.c_str(), ios::binary); // Use c_str() to convert string to const char*
        if (!fin) {
            cout << "\nError: Unable to open file '" << fileName << "' for reading.";
            continue; // Move to the next file
        }

        // Open a temporary file for writing decrypted content
        ofstream fout("tmp.txt", ios::binary);
        if (!fout) {
            cout << "\nError: Unable to create temporary file 'tmp.txt' for writing.";
            fin.close();
            continue; // Move to the next file
        }

        // Decrypt the content of the file
        char ch;
        while (fin.get(ch)) {
            ch -= 100; // Example decryption algorithm (subtract 100 from ASCII value)
            fout.put(ch);
        }

        // Close the files
        fin.close();
        fout.close();

        // Replace the original file with the decrypted content
        remove(fileName.c_str());
        rename("tmp.txt", fileName.c_str());

        cout << "\nFile '" << fileName << "' decrypted successfully.";

    } while (_findnext(handle, &fileData) == 0);

    _findclose(handle); // Close the search handle

    cout << "\nDecryption process completed for files in '" << folderPath << "' folder.";
    cout << endl;
}
