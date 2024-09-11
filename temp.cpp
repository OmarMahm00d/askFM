#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ofstream file("output.txt", ios::app);
    string line {"I do love Egypt"};
    file << "," << line << endl;
    file.close();
}