#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string dir;
    string op;
    ifstream MyReadFile("gcc.trace");
    while (getline(MyReadFile, dir))
    {
        cout << dir << endl;
    }
    MyReadFile.close();
}