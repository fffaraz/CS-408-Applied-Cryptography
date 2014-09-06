#include <iostream>
#include <string>
#include <fstream>

#include "playfair.h"

using namespace std;

void usage()
{
    cout << "Usage: playfair -e/-d key file" << endl;
}

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        usage();
        return 1;
    }

    string enc_dec = argv[1];
    string key = argv[2];
    string file = argv[3];

    if(enc_dec != "-e" && enc_dec != "-d")
    {
        usage();
        return 2;
    }

    ifstream input(file);
    if(!input.is_open())
    {
        cout << "File not found." << endl;
        return 3;
    }

    Playfair pf(key);
    if(!pf.isValid())
    {
        cout << "Invalid key." << endl;
        return 4;
    }

    string buffer;
    string output_str;
    string output_file;

    if(enc_dec == "-e")
    {
        cout << "Encrypting \"" << file << "\" using the key \"" << key << "\" ..." << endl;
        output_file = file + ".enc";
        input >> buffer;
        output_str += pf.encrypt(buffer);
    }

    if(enc_dec == "-d")
    {
        cout << "Decrypting \"" << file << "\" using the key \"" << key << "\" ..." << endl;
        output_file = file + ".dec";
        input >> buffer;
        output_str += pf.decrypt(buffer);
    }

    input.close();

    ofstream output(output_file);
    output << output_str;
    output.flush();
    output.close();

    cout << "Done." << endl;
    return 0;
}