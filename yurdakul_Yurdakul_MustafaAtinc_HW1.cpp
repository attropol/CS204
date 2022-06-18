#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct cell
{
    char letter; // letter inside the cell
    char color;  // color of the cell 
    cell()
    {
        letter = '-';
        color = '-';
    }
};

bool find(vector<string> vec, string elmt)
{
    bool check = false;
    for (int i = 0; i < vec.size(); i++)
    {
        if(vec[i]==elmt)
            check = true;
    }
    return check;
}

void display(vector<vector<cell> > v)
{
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[0].size(); j++)
        {
            cout << "|| " << v[i][j].letter << " , " << v[i][j].color;
        }
        cout << " ||" << endl;
    }
    
}

bool letterCounts(string guess)
{
    vector<int> chars(26,0);
    for (int i = 0; i < guess.length(); i++)
    {
        chars[guess[i]-'a']++;
    }
    for (int i = 0; i < chars.size(); i++)
    {
        if(chars[i]>1)
            return false;
    }
    return true;
}

bool sameGreens(vector<vector<cell> > data,int counter,string guess)
{
    for (int i = 0; i < guess.length(); i++)
    {
        if(data[counter-1][i].color=='G' && guess[i]!=data[counter-1][i].letter)
            return false;
    }
    return true;
}

bool inputCheck(vector<vector<cell> > data, string guess, int counter, vector<string> prevGuesses, string word)
{
    if(guess.length()>word.length())
    {
        cout << "The word is too long!" << endl;
        return false;
    }
    else if(guess.length()<word.length())
    {
        cout << "The word is too short!" << endl;
        return false;
    }
    else
    {
        bool islower = true;
        for (int i = 0; i < guess.length(); i++)
        {
            if(guess[i]<='z' && guess[i]>='a')
            {
                //do nothing
            }
            else
            {
                islower = false;
            } 
        }
        if(!islower)
        {
            cout << "Your input has illegal letters!" << endl;
            return false;
        }
        else
        {
            if(!letterCounts(guess))
            {
                cout << "Your input has a duplicate letter!" << endl;
                return false;
            }
            else
            {
                if(counter>0)
                {
                    if(find(prevGuesses,guess))
                    {
                        cout << "You've already tried this word!" << endl;
                        return false;
                    }
                    else
                    {
                        if(!sameGreens(data,counter,guess))
                        {
                            cout << "You did not use the green letter in your word!" << endl;
                            return false;
                        }
                        return true;
                    }
                    
                }
            }
            
        }
    }
    return true;
}

void insertWord(vector<vector<cell> > & v, string word, string guess)
{
    int place  = 0;
    for (int i = v.size()-1; i >=0; i--)
    {
        if(v[i][0].letter=='-')
            place = i;
    }
    for (int i = 0; i < word.length(); i++)
    {
        v[place][i].letter = guess[i];
        if(guess[i]==word[i])
            v[place][i].color = 'G';
        else if(word.find(guess[i])!=string::npos)
            v[place][i].color = 'Y';
        else
            v[place][i].color = 'B';
    }
}

int main()
{
    cout << "Welcome to SWordle!" << endl;
    string filename;
    ifstream ifs;
    cout << "Please enter the file name: " ;
    cin >> filename;
    ifs.open(filename.c_str());
    while(ifs.fail())
    {
        cout << "Couldn't find the file!\nPlease enter the file name: ";
        cin >> filename;
        ifs.open(filename.c_str());
    }
    string line1, line2;
    getline(ifs,line1);
    getline(ifs,line2);
    int rows;
    string word;
    istringstream iss1(line1);
    istringstream iss2(line2);
    iss1 >> rows;
    iss2 >> word;
    vector<vector<cell> > data(rows,vector<cell>(word.length()));
    bool ended = false;
    int counter = 0;
    string guess;
    vector<string> prevGuesses;
    cout << "The word that you will guess has " << word.length() << " letters and you have " << rows << " attempts." << endl;
    while(!ended)
    {
        cout << "What's your guess? ";
        cin >> guess;
        if(inputCheck(data,guess,counter,prevGuesses,word))
        {
            insertWord(data,word,guess);
            display(data);
            counter++;
            prevGuesses.push_back(guess);
        }
        if(counter==rows)
            ended = true;
        if(word==guess)
            ended = true;
    }
    if(word==guess)
        cout << "You win!" << endl;
    else
        cout << "You lose!" << endl;
	system("pause");
    return 0;
}