#include "word_ladder.cpp"
#include <iostream>

int main() {
  string dictFile = "dict";
  string outFile  = "./output_files/output.txt";
  string wordBegin, wordEnd;

  cout << "Enter the first word: ";
  cin >> wordBegin;
  while (wordBegin.size() != 5) {
    cout << "Word must have exactly 5 characters.";
    cout << endl << "Please reenter the first word: ";
    cin >> wordBegin;
  }
   
  cout << "Enter the last word: ";
  cin >> wordEnd;
  while (wordEnd.size() != 5) {
    cout << "Word must have exactly 5 characters.";
    cout << endl << "Please reenter the last word: ";
    cin >> wordEnd;
  }
   
  try {
    WordLadder wl(dictFile);
    wl.outputLadder(wordBegin, wordEnd, outFile);
  } 

  catch (std::exception& error) {
    cout << error.what();
  }
  
  system("code ./output_files/output.txt");
  return 0;
}