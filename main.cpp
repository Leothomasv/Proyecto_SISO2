#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;


struct Page
{
    int presente;
    int modificada;
    int num_pagina; 
};


int main()
{
    vector<char> operaciones;
    vector<string> direcciones;
    vector<string> dirs_desordenadas;
    vector<string> dirs_ordenadas;
    set<string> set_ordenar;
    unordered_map<string, Page> umap;
    string dir;
    char op;
    ifstream MyReadFile("gcc.trace");
    ofstream nuevoArch("ordenado.txt");

    Page *pagina = new Page;
    pagina->presente=32;
    umap["a"] = *pagina;
    for (auto x : umap)
    {
        cout << x.first <<" "<< x.second.presente <<endl;
        cout << umap.count(x.first); //0041f7a0
        
    }
    
    while (getline(MyReadFile, dir))
    {
        //cout << dir << endl;
        dirs_desordenadas.push_back(dir);
        //op = dir[9];
        //operaciones.push_back(op);
        //direcciones.push_back(dir.substr(0,7));
        
    }
    MyReadFile.close();
    unsigned tam = dirs_desordenadas.size();
    for (unsigned i = 0; i < tam; i++)
    {
        set_ordenar.insert(dirs_desordenadas[i]);
    }
    dirs_ordenadas.assign(set_ordenar.begin(), set_ordenar.end());

    for (string a : dirs_ordenadas)
    {
        op = a[9];
        operaciones.push_back(op);
        direcciones.push_back(a.substr(0,7));
    }
    
    
    for(string a : dirs_ordenadas){
        cout<<a<<endl;
        nuevoArch << a << endl;
    }

    
}

