#include<iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
#include<cstdlib>
#include<stdlib.h>
using namespace std;

//Sneak game functions:
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}
void Draw()
{
    cout<<"Snake Game: "<<endl;
    system("cls"); //system("clear");
    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "o";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }


            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    //if (x > width || x < 0 || y > height || y < 0)
    //	gameOver = true;
    if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;
    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

//Hangman game functions:
void PrintMessage(string message, bool printTop = true, bool printBottom = true)
{
    if (printTop)
    {
        cout << "@*********************************@" << endl;
        cout << "#";
    }
    else
    {
        cout << "#";
    }
    bool front = true;
    for (int i = message.length(); i < 33; i++)
    {
        if (front)
        {
            message = " " + message;
        }
        else
        {
            message = message + " ";
        }
        front = !front;
    }
    cout << message.c_str();

    if (printBottom)
    {
        cout << "#" << endl;
        cout << "@*********************************@" << endl;
    }
    else
    {
        cout << "#" << endl;
    }
}
void DrawHangman(int guessCount = 0)
{
    if (guessCount >= 1)
        {
            system("Color A");
            PrintMessage("&", false, false);
        }
    else
        PrintMessage("", false, false);

    if (guessCount >= 2)
        PrintMessage("|", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount >= 3){
        system("Color 6");
        PrintMessage("O", false, false);
    }
    else
        PrintMessage("", false, false);

    if (guessCount == 4)
        PrintMessage("/  ", false, false);

    if (guessCount == 5)
        PrintMessage("/| ", false, false);

    if (guessCount >= 6)
        PrintMessage("/|\\", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount >= 7)
        {
            system("Color 4");
            PrintMessage("|", false, false);
        }
    else
        PrintMessage("", false, false);

    if (guessCount == 8)
        PrintMessage("/", false, false);

    if (guessCount >= 9)
    {
        system("Color C");
        PrintMessage("/ \\", false, false);
    }

    else
        PrintMessage("", false, false);
}
void PrintLetters(string input, char from, char to)
{
    string s;
    for (char i = from; i <= to; i++)
    {
        if (input.find(i) == string::npos)
        {
            s += i;
            s += " ";
        }
        else
            s += "  ";
    }
    PrintMessage(s, false, false);
}
void PrintAvailableLetters(string taken)
{
    PrintMessage("Available letters");
    PrintLetters(taken, 'A', 'M');
    PrintLetters(taken, 'N', 'Z');
}
bool PrintWordAndCheckWin(string word, string guessed)
{
    bool won = true;
    string s;
    for (int i = 0; i < word.length(); i++)
    {
        if (guessed.find(word[i]) == string::npos)
        {
            won = false;
            s += "_ ";
        }
        else
        {
            s += word[i];
            s += " ";
        }
    }
    PrintMessage(s, false);
    return won;
}
string LoadRandomWord(string path)
{
    int lineCount = 0;
    string word;
    vector<string> v;
    ifstream reader(path.c_str());
    if (reader.is_open())
    {
        while (std::getline(reader, word))
            v.push_back(word);

        int randomLine = rand() % v.size();

        word = v.at(randomLine);
        reader.close();
    }
    return word;
}
int TriesLeft(string word, string guessed)
{
    int error = 0;
    for (int i = 0; i < guessed.length(); i++)
    {
        if (word.find(guessed[i]) == string::npos)
            error++;
    }
    return error;
}


int main()
{
    Print:

    int input;
    system("Color FC");
    cout<<"\t\t\t\t\t ~Mini game~\t\t\t\t\t\n\n\n\n"<<endl;
    cout<<"\t\tAvailable Games :"<<endl;
    cout<<"\t\t1. Snake Game"<<endl;
    cout<<"\t\t2. Hangman Game"<<endl;
    cout<<"\n\n\n\t\tWhich Game you Want to play:  ";
    cin>>input;

    switch(input)
    {
    case 1:
    {
        system("Color E0");
        Setup();
        while (!gameOver)
        {
            Draw();
            Input();
            Logic();
            Sleep(50); //sleep(10);
        }
        return 0;
        goto Print;
        break;

    }
    case 2:
    {
        system("Color 03");
        srand(time(0));
        string guesses;
        string wordToGuess;
        wordToGuess = LoadRandomWord("words.txt");
        int tries = 0;
        bool win = false;
        do
        {
            system("cls");
            PrintMessage("HANGMAN");
            DrawHangman(tries);
            PrintAvailableLetters(guesses);
            PrintMessage("Guess the word");
            win = PrintWordAndCheckWin(wordToGuess, guesses);

            if (win)
                break;

            char x;
            cout << ">";
            cin >> x;

            if (guesses.find(x) == string::npos)
                guesses += x;

            tries = TriesLeft(wordToGuess, guesses);

        }
        while (tries < 10);
        {
            if (win)
                PrintMessage("YOU WON!");
            else
                PrintMessage("GAME OVER");

                system("pause");
        }

        getchar();
        return 0;
        break;
        goto Print;
    }
    default:
        system("Color FA");
        cout<<"\n\nThat game is not Available."<<endl;


    }
    cout<<"\n\n\n Thank you for playing our game"<<endl;

}
