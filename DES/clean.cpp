#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main()
{
    ifstream inputFile("out_from_server.txt");
    ofstream outputFile("cleaned_output.txt");
    string s = "";
    string line;
    while (getline(inputFile, line))
    {
        if (s == "Slowly, a new text starts appearing on the screen. It reads ...")
            outputFile << line << endl;
        s = line;
    }
    inputFile.close();
    outputFile.close();

    cout << "Data has been written to output.txt" << endl;

    return 0;
}
