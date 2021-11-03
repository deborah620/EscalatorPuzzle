/* Title: escalatorPuzzle.cpp
** Author: Deborah Miller
** Date: 9/24/2020
** Email: d169@umbc.edu
** Descrption: Escalator Puzzles, asks user what file to open,
**      opens that file and then states if it's valid or not, in a
**      valid file, the fist word has 6 characters, the second has 5
**      and the third has four, and each word has the same letters
**      as the one above it minus one
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

const int NUM_WORDS = 3;
const int CORRECT_WORD_LENGTH = 15;
const int MAX = 80;

bool loadFile(string fileName, string puzzleWords[], string listLetters[][MAX]);
void printWords(string puzzleWords[], int arryLength);
void checkAnswer(string puzzleWords[], string listLetters[][MAX], int arryLength);
void clearList(string puzzleWords[], string listLetters[][MAX], int arryLength);
void countLetters(string puzzleWords[], string listLetters[][MAX], int arryLength);

int main(){

  cout << "Welcome to Escalators" << endl;

  string puzzleWords[NUM_WORDS];
  string listLetters[NUM_WORDS][MAX];
  string fileName;
  bool playAgain;
  string checkAnother = " ";

  //plays the game unti the user no longer wants to check another file
  do{
    cout << "What is the file name of the list of words?" << endl;
    cin >> fileName;

    //load in file, if doesn't exist skip all the functions bellow
    if (loadFile(fileName, puzzleWords, listLetters)){
      printWords(puzzleWords, NUM_WORDS);
      countLetters(puzzleWords, listLetters, NUM_WORDS);
      clearList(puzzleWords, listLetters, NUM_WORDS);
    }

    //ask after a file is checked if user wants to check another
    checkAnother.clear();
    while(checkAnother != "y" && checkAnother != "Y" &&
          checkAnother != "n" && checkAnother != "N") {
      cout << "Check another list? (y/n)" << endl;
      cin >> checkAnother;
    }

    if (checkAnother == "n" || checkAnother == "N"){
      playAgain = false;
    }
    else if (checkAnother == "y" || checkAnother == "Y"){
      playAgain = true;
    }

  }while(playAgain);

  cout << "Thank you for using Escalators!" << endl;

  return 0;
}
//Pre-Condition: this function takes the name of the file the user wishes to open,
//               the empty array to store the puzzle words in and the empty 2D array to
//               store the lits of letters in
//Post-Condition: if the file the user wants to open exists the return is true, and it is opened and each word is stored in
//                the array puzzle name, the 2D array stores an array of the list of the letters in each word,
//                if the file doesn't exist the user is informed and the return is false
bool loadFile(string fileName, string puzzleWords[], string listLetters[][MAX]){

  string wordOne;
  string wordTwo;
  string wordThree;
  ifstream myFile (fileName);

  if (myFile.is_open()){


    myFile >> wordOne >> wordTwo >> wordThree;

    string firstWord[wordOne.length()];
    string secondWord[wordTwo.length()];
    string thirdWord[wordThree.length()];

    //adds each letter in each word to it's own array
    //all the letters in the first word are added to one array...
    for(int i = 0; i < wordOne.length(); i++)
      firstWord[i] = wordOne[i];

    for(int i = 0; i < wordTwo.length(); i++)
      secondWord[i] = wordTwo[i]; //and here lies the error of writing wordOne instead of wordTwo

    for(int i = 0; i < wordThree.length(); i++)
      thirdWord[i] = wordThree[i];

    //adds each array to the 2D array, listLetters
    for(int i = 0; i < wordOne.length(); i++)
      listLetters[0][i] = firstWord[i];

    for(int i = 0; i < wordTwo.length(); i++)
      listLetters[1][i] = secondWord[i];

    for(int i = 0; i < wordThree.length(); i++)
      listLetters[2][i] = thirdWord[i];

    //for simplicity later on in the project,
    //each word is also added to a separate array
    puzzleWords[0] = wordOne;
    puzzleWords[1] = wordTwo;
    puzzleWords[2] = wordThree;
  }
  else{
    cout << "No file found" << endl;
    return false;
  }
  myFile.close();

  return true;

}

//Pre-Condition: this function takes in the array of puzzle words and it's length
//               it is only called if the initial file the user wants to use exists
//Post-Condition: the function then displays each word and how many letters it contains
void printWords(string puzzleWords[], int arryLength){

  for(int i = 0; i < arryLength; i++){
    cout << (i + 1) << ". " << puzzleWords[i] << " (" <<  puzzleWords[i].length() << " letters)" << endl;
  }

}

//Pre-Condition: this function takes in the array of puzzle words,
//               the 2D array of the list of the letters and the array length
//               it is only called if the initial file the user wants to use exists
//Post-Condition: the function makes sure the first word is 6 letters long
//                the second word is 5 letters long, and the third word is 4 letters long
//                if any of that isn't true, the user is informed and if it's all true, it calls
//                the function checkAnswer()
void countLetters(string puzzleWords[], string listLetters[][MAX], int arryLength){

  int sum = 0;

  for(int i = 0; i < arryLength; i++){
    sum += puzzleWords[i].length();
  }

  //the sume should be 15 (6 + 5 + 4)
  if (sum != CORRECT_WORD_LENGTH){
    cout << "Words are not correct length" << endl;
    cout << "This list is not valid!" << endl;
  }
  else{
    checkAnswer(puzzleWords, listLetters, NUM_WORDS);
  }
}

//Pre-Condition: this function takes in the array of puzzle words,
//               the 2D array of the list of the letters and the array length
//               it is only called if each word in the game is the correct length
//Post-Condition: the function then makes sure that the second word has the same letters
//                as the first one minus one and the third word has the same letters as
//                the second minus one
void checkAnswer(string puzzleWords[], string listLetters[][MAX], int arryLength){
  int count = 0;

  //compares each letter in the second word (the second row in the 2D array)
  //to all the letters in the first word (the first row in the 2D array) and
  //once a match is found, count is increased by one and the loop stops
  for (int i = 0; i < puzzleWords[0].length(); i++) {
    for (int j = 0; j < puzzleWords[0].length(); j++) {
      if (listLetters[1][i] == listLetters[0][j]) {
        count++;
        break;

      }
    }
  }

  //compares each letter in the third word (the third row in the 2D array)
  //to all the letters in the second word (the second row in the 2D array) and
  //once a match is found, count is increased by one and the loop stops
  for (int i = 0; i < puzzleWords[1].length(); i++) {
    for (int j = 0; j < puzzleWords[1].length(); j++) {
      if (listLetters[2][i] == listLetters[1][j]) {
        count++;
        break;
      }
    }
  }

  //count should equal the length of the first word + the length of the second
  //because for every match it is increased and all the letters should be matching
  if (count != (puzzleWords[1].length() + puzzleWords[2].length())) {
    cout << "Words do not share appropriate letter frequency " << endl;
    cout << "This list is not valid!" << endl;
  }
  else{
    cout << "This list is valid!" << endl;
  }
}

//Pre-Condition: this function takes in the array of puzzle words,
//               the 2D array of the list of the letters and the array length
//               it is only called if the initial file the user wants to use exists
//Post-Condition: the function sets the arrays back to empty, to be ready for use if
//                the user wants the play again
void clearList(string  puzzleWords[], string listLetters[][MAX], int arryLength){

  for(int i = 0; i < arryLength; i++){
    puzzleWords[i] = "";

    for(int j = 0; j < MAX; j++){
      listLetters[i][j] = ' ';
    }
  }

}
