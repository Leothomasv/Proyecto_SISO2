#define STDC_FORMAT_MACROS
#ifdef _MSC_VER
#define CRT_SECURE_NO_WARNINGS
#endif
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <unistd.h>
#include <curses.h>

using namespace std;

ofstream DatosFile("Datos.txt", ios::trunc);
 
long maxMemoryLength = 140000,memmoryLength =0;
int pageCount = 0;

struct traceRecord
{
    string memAddress;
    char operationType;
    traceRecord(): memAddress(""), operationType(' ') {}
};
struct Node {
    traceRecord data;
    struct Node* next;
    Node(traceRecord newData)
    {
        data = newData;
        next = new Node();
    }
    Node(){}
    inline void toString()
    {
        // cout << data.memAddress << " <- " << data.operationType<<endl;
        DatosFile << data.memAddress << " <- " << data.operationType << endl;
    }
};

struct NodeList
{
    Node* origin;
    Node* lastNode;
    long listSize;
};
bool existNode(Node* node, NodeList* list)
{
    Node* currNode = list->origin;
    while (currNode != list->lastNode)
    {
        if (node->data.memAddress == currNode->data.memAddress 
            && node->data.operationType == currNode->data.operationType)
        {
            return true;
        }
        currNode = currNode->next;
    }
    return false;
}

traceRecord hydrateRecord(traceRecord traceLine, string line) {
    vector<string> words{};
    stringstream sstream(line);
    std::string word;
    while (std::getline(sstream, word, ' ')) {
        word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
        words.push_back(word);
    }
    traceLine.memAddress = words.at(0);
    traceLine.operationType = words.at(1).at(0);
    return traceLine;
}

void DisplayMemOperations(NodeList* nodes)
{
    Node* currNode = nodes->origin;
    while (currNode != nodes->lastNode)
    {
        currNode->toString();
        currNode = currNode->next;
    }
    cout << "Linked List Size:" << nodes->listSize << endl;
};

void displayPercentage(){  
    
    cout << "\33[5;150H" << "Used memory : " << ( memmoryLength *100) /maxMemoryLength << "%" << endl;
    cout << "\33[6;150H" << "Pages : " << pageCount << endl;
}

void memLoader()
{
    std::fstream fh;
    std::string filename;
    NodeList* nodeList = new NodeList();
    cout << "Archivo a leer" << endl;
    cin >> filename;
    
    fh.open(filename + ".trace", std::fstream::in | std::fstream::binary);
    if (fh.is_open())
    {
        std::string line;
        while (std::getline(fh, line))
    	{
	        if (nodeList->listSize>10000)
	        {
                DisplayMemOperations(nodeList);
                nodeList = new NodeList();
                pageCount++;
	        }
            traceRecord traceLine;
            traceLine = hydrateRecord(traceLine, line);
            Node* newNode = new Node(traceLine);
            if (nodeList->origin == NULL)
            {
                nodeList->origin = newNode;
                nodeList->lastNode = newNode;
            }
            else
            {
	            if (existNode(newNode, nodeList)==false)
	            {
                    //usleep(1000);
                    nodeList->lastNode->next = newNode;
                    nodeList->lastNode = newNode;
                    nodeList->listSize += 1;
                    memmoryLength +=1;
	            }
            }
            displayPercentage();
        }
    }
    fh.close();
}


NodeList* cleanOperations(NodeList* nodes)
{
    NodeList* cleanList = new NodeList();
    Node* currNode = nodes->origin;
    cleanList->lastNode = currNode;
    cleanList->origin = currNode;
    long count{ 1 };
	while (currNode != nodes->lastNode)
	{
		if (existNode(currNode,cleanList)==false)
		{
            cleanList->lastNode->next = currNode;
            cleanList->lastNode = currNode;
            cleanList->listSize += 1;
		}
        count++;
        currNode = currNode->next;
	}
    cleanList->listSize = count - 1;
    return cleanList;
}

int main() {
	memLoader();
    return 0;
}