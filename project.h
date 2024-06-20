#ifndef PROJECT_H_INCLUDED
#define PROJECT_H_INCLUDED


#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;

// Node Class
class Node {
public:
    int roll;
    string Name;
    string Dept;
    float Marks;
    Node* next;
};

// Function Declarations
void Register();
bool Login(string &role);
void Insert_Record(int roll, string Name, string Dept, float Marks);
void Search_Record(int roll);
int Delete_Record(int roll);
void Show_Record();
void save_credentials();
void load_credentials();
void save_records();
void load_records();



#endif // PROJECT_H_INCLUDED
