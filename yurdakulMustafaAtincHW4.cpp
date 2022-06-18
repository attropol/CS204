#include "DynStackYurdakulMustafaAtinc.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

void readFile(ifstream & is)
{
    string filename;
    int count = 0;
    bool gotit = false;
    while(!gotit)
    {
        if(count>0)
            cout << "File not found." << endl;
        cout << "Please enter the file name: ";
        cin >> filename;
        is.open(filename.c_str());
        if(!is.fail())
            gotit=true;
        count++;
    }
}

bool isOpen(char ch){return ((ch=='(') || (ch=='{') || (ch=='['));}
bool isClose(char ch){return ((ch==')') || (ch=='}') || (ch==']'));}
bool isMatching(char ch1, char ch2)
{
    if(ch1=='(' && ch2==')')
        return true;
    if(ch1=='{' && ch2=='}')
        return true;
    if(ch1=='[' && ch2==']')
        return true;
    return false;    
}

void printOpen(char ch, int line)
{cout << "Found the opening symbol " << ch << " at line " << line << endl;}

void printClose(char curr,int linecount,char charpopped,int linepopped)
{
    cout << "Found the closing symbol " << curr << " at line " << linecount << " which closes the opening symbol " << charpopped <<" at line " << linepopped << endl;
}

void printError1(char ch)
{cout << "ERROR!!! Found the closing symbol " << ch << " but there are no unclosed opening symbols!" << endl;}

void printError2(char curr,int linecount,char charpopped,int linepopped)
{
    cout << "ERROR!!! Found the closing symbol " << curr << " at line " << linecount << " but the last unclosed opening symbol is "<< charpopped<<" at line " << linepopped << endl;
}

void printRest(DynStack & stack)
{
    cout << "ERROR!!! The following opening symbols were not closed:" << endl;
    while(!stack.isEmpty())
    {
        char charpopped = ' ';
        int linepopped = 0;
        stack.pop(charpopped,linepopped);
        cout << "\tSymbol " << charpopped << " at line " << linepopped << endl;
    }
}

void Process(ifstream & is, DynStack & stack)
{
    string line;
    int linecount = 1;
    char curr;
    while(getline(is,line))
    {
        istringstream iss(line);
        while(iss.get(curr))
        {
            if(isOpen(curr))
            {
                stack.push(curr,linecount);
                printOpen(curr,linecount);
            }
            else if(isClose(curr))
            {
                if(stack.isEmpty())
                {
                    printError1(curr);
                    return;
                }
                else
                {
                    char charpopped = ' ';
                    int linepopped = 0;
                    stack.pop(charpopped,linepopped);
                    if(!isMatching(charpopped,curr))
                    {
                        printError2(curr,linecount,charpopped,linepopped);
                        return;
                    }
                    else
                    {
                        printClose(curr,linecount,charpopped,linepopped);
                    }
                    
                }
            }
        }

        linecount++;
    }
    if(stack.isEmpty())
    {
        cout << "File processed successfully. No errors were found." << endl;
        return;
    }
    printRest(stack);
}

int main()
{
    ifstream is;
    readFile(is);
    DynStack stack;
    Process(is,stack);
    return 0;
}