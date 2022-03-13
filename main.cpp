#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    string dir;
    string op;
    ifstream MyReadFile("gcc.trace");

    while (getline(MyReadFile, dir))
    {
        //cout << dir << endl;
        op = dir[9];
        cout << op << endl;
    }
    MyReadFile.close();
}