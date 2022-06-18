#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

struct node
{
    char ch;
    node *next;
    node(char c, node *n = nullptr)
        : ch(c), next(n)
    {
    }
};

node *addChar(node *head, char ch)
{
    if (!head)
    {
        head = new node(ch);
    }
    else
    {
        node *temp = head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new node(ch);
    }
    return head;
}
node *readFileToList(node *head, string filename)
{
    ifstream ifs;
    ifs.open(filename.c_str());
    char ch;
    while (ifs >> ch)
    {
        head = addChar(head, ch);
    }
    return head;
}

void printList(node *list)
{
    node *temp = list;
    while (temp)
    {
        cout << temp->ch;
        temp = temp->next;
    }
    cout << endl;
}

bool charExists(node *head, char c)
{
    node *temp = head;
    while (temp)
    {
        if (temp->ch == c)
            return true;
        temp = temp->next;
    }
    return false;
}

node *deleteChar(node *head, char c, bool &isDeleted)
{
    while (charExists(head, c))
    {
        if (head->ch == c)
        {
            node *temp = head;
            head = head->next;
            isDeleted = true;
            delete temp;
        }
        else
        {
            node *prev = head;
            node *temp = head;
            while (temp->ch != c)
            {
                prev = temp;
                temp = temp->next;
            }
            prev->next = temp->next;
            isDeleted = true;
            delete temp;
        }
    }
    return head;
}

node *insertChar(node *head, char target, char after, bool & isFirst)
{
    if (!charExists(head, after))
    {
        node *add = new node(target, head);
        head = add;
        isFirst = true;
        return head;
    }
    else
    {
        node *temp = head;
        while (temp->ch != after)
        {
            temp = temp->next;
        }
        node *add = new node(target, temp->next);
        temp->next = add;
        return head;
    }
}

int similarity(node *list1, node *list2)
{
    node *temp1 = list1;
    node *temp2 = list2;
    int sim = 0;
    while (temp1 && temp2)
    {
        if (temp1->ch == temp2->ch)
            sim++;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return sim;
}

bool isLower(char ch)
{
    return (ch >= 'a' && ch <= 'z');
}

node * makeEmpty(node * head)
{
    while(head)
    {
        node * temp = head;
        head = head->next;
        delete temp;
    }
    return nullptr;
}

int main()
{
    string filename1, filename2;
    ifstream i;
    cout << "Please enter the file 1 name: ";
    cin >> filename1;
    i.open(filename1.c_str());
    while (i.fail())
    {
        cout << "Please enter the file 1 name: ";
        cin >> filename1;
        i.open(filename1.c_str());
    }
    i.close();
    cout << "Please enter the file 2 name: ";
    cin >> filename2;
    i.open(filename2.c_str());
    while (i.fail())
    {
        cout << "Please enter the file 2 name: ";
        cin >> filename2;
        i.open(filename2.c_str());
    }
    i.close();
    node *list1 = nullptr;
    node *list2 = nullptr;
    list1 = readFileToList(list1, filename1);
    list2 = readFileToList(list2, filename2);
    cout << "List1: ";
    printList(list1);
    cout << "List2: ";
    printList(list2);
    bool ended = false;
    cin.ignore();
    while (!ended)
    {
        string input, command;
        char arg1, arg2;
        cout << endl << "Enter a command and its corresponding argument(s), if any: ";
        getline(cin, input);
        istringstream iss(input);
        iss >> command;
        if (command == "sim")
        {
            cout << "Displaying the contents of the two lists:" << endl;
            cout << "List1: ";
            printList(list1);
            cout << "List2: ";
            printList(list2);
            cout << "There is/are " << similarity(list1,list2) << " letter(s) matched in the same positions in both lists." << endl;
        }
        else if (command == "del1")
        {
            iss >> arg1;
            if (isLower(arg1))
            {
                bool isdel = false;
                list1 = deleteChar(list1, arg1, isdel);
                if (isdel)
                {
                    cout << "Deleting all occurrences of " << arg1 << " in List1." << endl;
                    cout << "The current content of List1 is: ";
                    printList(list1);
                }
                else
                {
                    cout << "No deletion as the value " << arg1 << " was not found in the list" << endl;
                }
            }
            else
            {
                cout << "Invalid arguments." << endl;
            }
        }
        else if (command == "del2")
        {
            iss >> arg1;
            if (isLower(arg1))
            {
                bool isdel = false;
                list2 = deleteChar(list2, arg1, isdel);
                if (isdel)
                {
                    cout << "Deleting all occurrences of " << arg1 << " in List2." << endl;
                    cout << "The current content of List2 is: ";
                    printList(list2);
                }
                else
                {
                    cout << "No deletion as the value " << arg1 << " was not found in the list" << endl;
                }
            }
            else
            {
                cout << "Invalid arguments." << endl;
            }
        }
        else if (command == "insert1")
        {
            iss >> arg1 >> arg2;
            if (isLower(arg1) && isLower(arg2))
            {
                cout << "Inserting " << arg1 << " after " << arg2 << " in List1." << endl;
                bool isFirst = false;
                list1 = insertChar(list1,arg1,arg2,isFirst);
                if(isFirst)
                {
                    cout << "The node with " << arg2 << " value does not exist. Therefore, Inserting " << arg1 << " at the beginning of the list." << endl;
                }
                else
                {
                    cout << "The node with " << arg1 << " has been inserted after the first occurrence of a node with " << arg2 << " value." << endl;
                }
                cout << "The current content of List1 is: ";
                printList(list1);
            }
            else
            {
                cout << "Invalid arguments." << endl;
            }
        }
        else if (command == "insert2")
        {
            iss >> arg1 >> arg2;
            if (isLower(arg1) && isLower(arg2))
            {
                cout << "Inserting " << arg1 << " after " << arg2 << " in List2." << endl;
                bool isFirst = false;
                list2 = insertChar(list2,arg1,arg2,isFirst);
                if(isFirst)
                {
                    cout << "The node with " << arg2 << " value does not exist. Therefore, Inserting " << arg1 << " at the beginning of the list." << endl;
                }
                else
                {
                    cout << "The node with " << arg1 << " has been inserted after the first occurrence of a node with " << arg2 << " value." << endl;
                }
                cout << "The current content of List2 is: ";
                printList(list2);
            }
            else
            {
                cout << "Invalid arguments." << endl;
            }
        }
        else if (command == "exit")
        {
            cout << "Clearing the two lists and saying Goodbye!" << endl;
            list1 = makeEmpty(list1);
            list2 = makeEmpty(list2);
            ended = true;
        }
        else
        {
            cin.clear();
            cout << "Invalid command." << endl;
        }
    }
	system("pause");
    return 0;
}