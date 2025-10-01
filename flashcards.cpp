////////////////
////INCLUDES////
////////////////

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <stack>

/////////////
////USING////
/////////////

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::time;
using std::srand;
using std::rand;
using std::vector;
using std::ifstream;
using std::stack;

/////////////////
////CONSTANTS////
/////////////////

const int MAX = 1024;
const int HEX = 16;
const string DIGITS = "012345689ABCDEFGHIJKLMNOPQRSTUIWXYZabcdefghijklmnopqrstuvwxyz+/";

///////////////
////GLOBALS////
///////////////

size_t questionCount = 0;

//////////////////
////PROTOTYPES////
//////////////////

/* 
 * NAME 
 *   scanTextFile - insert each line of a text file into an array of strings
 * DESCRIPTION
 *   scanTextFile takes two parameters, an array of strings, and a string for the file.
 *   This array of strings will be where ecah line of the text file will be inserted into.
 *   The file string is the path within the working directory where the text file will be located.
 *  It would be easier for the user if I could get this to return an array of strings instead of taking one as a parameter but it's almost been 3 hours since I started this and I'll never get any studying done at this rate.
 */
void
scanTextFile(string arrOut[MAX], string file);

/*
 * NAME
 *   initBools - initialize an array of booleans to value
 * DESCRIPTION
 *   initBools takes one parameter, a boolean value.
 *   The funcion will return an array of booleans that is initialized to all be the same value as value.
 */
bool*
initBools(bool value);

/*
 * NAME
 *   askQuestions - ask questions
 * DESCRIPTION
 *   ask questions :>
 *   Not sure why I felt the need to turn this into a seperate function but here we are.
 */
void
askQuestions(string* questions, string* answers);

/*
 * NAME
 *   chooseIndex - chooses random unchosen number
 * DESCRIPTION
 *   chooseIndex takes one parameter, an array of booleans.
 *   The function will return an integer, this integer will be chosen at random as is guarenteed to not have been chosen since the beginning of the askQuestions function.
 */
int
chooseIndex(bool chosen[MAX]);

/*
 *
 */
string
convertDecimalToHex (size_t decimal);

// TODO
string
convertDecimalToBase (size_t decimal, int base);

/////////////////
////FUNCTIONS////
/////////////////

int
main()
{
  string questions[MAX];
  scanTextFile(questions, "questions.txt");

  string answers[MAX];
  scanTextFile(answers, "answers.txt");

  // TODO
  // Add feature that creates problems for you
  // e.g. B2U (random number)
  // Will probably be done by making this array of strings one that will be scanned to determine keyword like "B2U" from the question, and then generating a random B2U problem
  //string randomized[MAX];
  //scanTextFile(randomize, "randomize.txt");

  // questionCount will be off by realQuestionCount * numberOfTimesScanTextFileIsCalled + numberOfTimesScanTextFileIsCalled - 1, this will correct that
  questionCount /= 2;
  --questionCount;

  askQuestions(questions, answers);

  return EXIT_SUCCESS;
}

void
scanTextFile(string arrOut[MAX], string file)
{
  //static string arrOut[MAX];
  ifstream fileIn(file);

  if (fileIn.is_open())
  {
    string line;

    for (int i = 0; !fileIn.fail() || i >= MAX; ++i, ++questionCount)
      getline(fileIn, arrOut[i]);

    fileIn.close();
  }
  else
    cout << file << " isn't open" << endl;
  //return arrOut;
}

bool*
initBools(bool value)
{
  static bool arrOut[MAX];

  for (int i = 0; i < MAX; ++i)
    arrOut[i] = value;

  return arrOut;
}
  
void
askQuestions(string* questions, string* answers)
{
  bool* answered = initBools(false);

  // Set "seed" for random questions
  srand(time(0));

  int randomQuestion;
  for (size_t questionsAnswered = 0; questionsAnswered < questionCount; ++questionsAnswered)
  {
    randomQuestion = chooseIndex(answered);

    // Ask question
    cout << questionsAnswered + 1 << ". " << questions[randomQuestion];

    // Wait user enter
    // TODO Add some feature to keep track of number of correct and wrong answers
    cin.get();

    // Print answer
    cout << answers[randomQuestion] << endl;

    // Set question to answered
    answered[randomQuestion] = true;
    cout << endl;
  }
}

int
chooseIndex(bool chosen[MAX])
{
  int randomIndex;

  do
  {
    randomIndex = rand() % questionCount;
  } while (chosen[randomIndex]);

  return randomIndex;
}

string
convertDecimalToHex (size_t decimal)
{
  return convertDecimalToBase (decimal, HEX);
}

string
convertDecimalToBase (size_t decimal, int base)
{
  stack<char> s;

  do
  {
    s.push(DIGITS[decimal % base]);
    decimal /= base;
  } while(decimal > 0);

  string output = "";

  while (!s.empty())
  {
    output += s.top();
    s.pop();
  }

  return output;
}
