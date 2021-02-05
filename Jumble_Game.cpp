#include "iostream"
#include "string"
#include "cstdlib"
#include "ctime"
#include "fstream"
#include "map"
#define size_of_ending 10

using namespace std;
struct Quest
{
    string theword, jumble, theHint;
    Quest(){};
};

void starting(string jumble);
Quest randstring();
void process(Quest com);
bool more();
void ending(int x);

int main()
{
start:

    Quest com = randstring();

    starting(com.jumble);

    process(com);

    if (more())

        goto start;
        
    return 0;
}

//Gen jumble
Quest randstring()
{
    //Load data
    ifstream file;
    file.open("jumbledct.txt", ios::in); //source
    enum fields
    {
        word,
        HINT,
        NUM_FIELDS,
    };
    int n;
    file >> n;
    const int NUM_wordS = n;

    string wordS[NUM_wordS][NUM_FIELDS];

    string data;

    getline(file, data);
    while (!file.eof())
    {
        for (int i = 0; i < NUM_wordS; i++)
        {
            getline(file, data, ',');
            wordS[i][0] = data;
            file.ignore();
            getline(file, data, ';');
            wordS[i][1] = data;
            getline(file, data);
        }
    }

    //word to guess
    Quest com;

    srand((time(0)));
    int choice = (rand() % NUM_wordS);
    string theword = wordS[choice][word];
    string theHint = wordS[choice][HINT];

    //jumble the word
    com.theword = theword;
    com.theHint = theHint;
    string jumble = theword;
    int length = jumble.size();
    for (int i = 0; i < length; i++)
    {
        int index1 = (rand() % length);
        int index2 = (rand() % length);

        swap(jumble[index1], jumble[index2]);
    }
    com.jumble = jumble;
    file.close();
    return com;
}
//Welcome!
void starting(string jumble)
{

    cout << "\t\tWelcome the word Jumble Game!\n\n";
    cout << "Unscramble the letters to make the a word.\n\n";
    cout << "Enter 'hint' for a hint.\n\n";
    cout << "Enter 'quit' to quit the game.\n\n";
    cout << "The word jumble is: " << jumble << "\n";
}
//Game run
void process(Quest com)
{
    //game loop
    string guess;
    cout << "\nYour guess: ";
    cin >> guess;
    while ((guess != com.theword) && (guess != "quit"))
    {
        if (guess == "hint")
        {
            cout << com.theHint;
        }
        else
        {
            ending(0);
        }
        cout << "\nYour guess: ";
        cin >> guess;
    }
    if (guess == com.theword)
    {
        ending(1);
    }
}
//One more game
bool more()
{
    cout << "\nOne more game? (y/n) \n";
    char x;
tryAgain:
    cin >> x;
    if (x == 'n')
    {
        cout << "\n__Thank for playing!__\n";
        return 0;
    }
    else if (x == 'y')
    {
        return 1;
    }
    else
    {
        cout << "\n\nWrong input. Try again: ";
        goto tryAgain;
    }
}
//End
void ending(int x)
{
    string win[size_of_ending] = {"Well done!", "Excellent!",
                                  "Amazing! Goodjob em!",
                                  "Wonderful!",
                                  "Fantastic!",
                                  "You are a genius!", "Brilliant!!", "Clever!", "Congratulations!", "Nothing can stop you now!"};

    string lost[size_of_ending] = {"Nice try, but..", "One more guess...", "Sorry, that is not it", "Good guess, but..",
                                   "Bad call!", "Dumb idea!", "Wrong call!", "Bad move!", "Try again", "Wrong choice"};

    srand((time(0)));
    int choice = (rand() % size_of_ending);
    if (x == 1)
        cout << "\n"
             << win[choice] << "\n";
    else
        cout << "\n"
             << lost[choice] << "\n";
}
