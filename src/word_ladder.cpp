#include "../header/word_ladder.hpp"

WordLadder::WordLadder(const string &filename) {
  // holds words from the filename
  string word ;               

  // open the file 
  ifstream inFS(filename) ;   
  // check if the file is open
  if( !inFS.is_open() || inFS.fail() ) {
    throw runtime_error("Could not open dictionary file.");
  }

  // fill up the list  
  while( inFS >> word ){
    
    if( word.size() != 5 ) {
      cout << "'" << word << "' in the dictionary does not have 5 characters." << endl;
      exit(1);
    }

    // push back new words to fill up the list
    if(!this->exist(word)) {
      dict.push_back(word);   
    }   
  }

  // sort the list in ascending order 
  dict.sort();

  // close filename 
  inFS.close();
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {
  // check if either word passed in does not exists 
  if ( ! exist( start ) ) {
    cout << "The word \"" << start << "\" is not in the dictionary." << endl;
    exit(1);
  } 
  if (! exist( end ) ) {
    cout << "The word \"" << end << "\" is not in the dictionary." << endl;
    exit(1);
  } 

  // open the file where to write the result 
  ofstream ouFS( outputFile );  

  // check if the file to output is open 
  if( !ouFS.is_open() ) {
    cout << "Could not open output file" ;
    exit(1); 
  }
  
  // if the words are the same 
  if( start.compare(end) == 0) {
    ouFS << start; 
    ouFS.close();
    return; 
  }
  
  stack <string> wordStack ;        // declare a stack of strings 
  queue<stack<string>> wordQueue;   // declare a queue of stacks  

  string wStack;                    // holds words in the stack
  string word;                      // holds the words from the dictionary
  
  // (1) create a Stack containing just the first word in the ladder
  wordStack.push(start);

  // (2) enqueue this Stack on to a Queue of Stacks
  wordQueue.push(wordStack); 

  // (3) while this Queue of Stacks is not empty
  while ( !wordQueue.empty() ) {                                       
      
    // (3.1) get the word on top of the front Stack of this Queue 
    wStack = wordQueue.front().top(); 
    
    // (3.2) for each word in the dictionary
    list<string> tempList = dict;   // create a temp list 
    for (auto i = tempList.cbegin(); i != tempList.cend(); ++i) {
        word = *i;

      // (3.2.1 )check if the word if off by 1 character from top
      if(offCharacters(word, wStack) == 1) {

        // (3.2.1.1) create a new stack = copy of front stack + push *i 
        stack<string> newStack = wordQueue.front();
        newStack.push(word); 

        // (3.2.1.2) check if the word is the same as end word ladder 
        if(end.compare(word) == 0) {
          
          // write content of newStack to the output file and return
          list<string> outputList; 
          while ( !newStack.empty() ) {
            outputList.push_back( newStack.top() ); // put the word ladder into a list
            newStack.pop();        // delete the top word from stack   
          }
    
          // output the list of the word ladder result to the ouput file
          while( ! outputList.empty() ) {
            ouFS << outputList.back() ;       // output to the file word Ladder 
            outputList.pop_back();            // delete words from the list

            if(outputList.size() > 0) { 
              ouFS << " -> ";
            }
          }
            
          ouFS.close();   // close the outputFile
          return; 

        } else {  // (3.2.1.3)

          // enqueue the new stack 
          wordQueue.push(newStack) ;

          // remove the *i word from the dict 
          this->dict.remove(word); 
        }
      } 
    }

    // (3.3) dequeue the front stack
    wordQueue.pop();
  }
  // (4) if the queue is empty word ladder does not exist
  if(wordQueue.empty()) {
    ouFS 
      << "No word ladder found to get from the word '" 
      << start << "' to the word '" << end 
      << "'." << endl
    ;
  }

  // close the outputfile 
  ouFS.close();
}

bool WordLadder::exist(const string &word) {
  for (auto i = dict.cbegin(); i != dict.cend(); ++i) {
    if( word.compare(*i) == 0 ) {
      return true;
    }
  }
  return false; 
}

int WordLadder::offCharacters(const string & word1 , const string word2 ) {
  int count = 0;
  for (unsigned i = 0; i < word1.size() ; ++i) {
    if ( word1[i] != word2[i] ) {                
      count++;                      // num of characters off B/W words 
    } 
  }
  return count;
}