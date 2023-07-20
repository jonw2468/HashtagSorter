/*****
 ** File:    HashtagSorter.cpp
 ** Project: Project 1 - Hashtag Analyzer
 ** Author:  Jon Woods
 ** Date:    9/29/22
 ** Section: 20/22
 ** Email:   jwoods6@umbc.edu
 **
 ** The following program reads a file of hashtags specified by the first
 ** command line argument, then uses a second command line to read a file of
 ** tweets with hashtags before each one. It then parses the tweets for each
 ** hastag and displays all tweets with a match before displaying how many
 ** tweets contain each hashtag.
*****/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


bool isEmpty(string f);
void analyze(string file1, string file2);
int countTweets(string file[]);
int matchAndCount(string hash, string line1, string line2);
void showCount(string tags[], int nums[]);

const int MAX_SIZE = 20; // exact length of arrays for tweets and messages; 20 hashtags and up to 10 tweets

// main
// Stores user inputs to call analyzing functions and control looping of the analyzer
int main() {
  string f1; // input value w/ name of the first file (w/ hashtags)
  string f2; // input value w/ name of the second file (w/ tweets)
  string keepGoing; // input value of whether to run the analyzer again, either "y" or "n"

  cout << "Welcome to the Hashtag Analyzer\nYou will choose a file of hashtags to search for\nThen you will choose a file to search for the hashtags" << endl;
  do {
    cout << "\nPlease enter the file with the hashtags you would like to use:" << endl;
    getline(cin, f1);
    // reprompt user for f1 until it corresponds with a non-empty file
    while (isEmpty(f1)) {
      cout << "This file is empty. Please enter a new file name for the hashtags." << endl;
      getline(cin, f1);
    }
    cout << "Please enter the file with the messages you would like to use:" << endl;
    getline(cin, f2);
    // reprompt user for f1 until it corresponds with a non-empty file
    while (isEmpty(f2)) {
      cout << "This file is empty. Please enter a new file name for the messages." << endl;
      getline(cin, f2);
    }
    
    analyze(f1, f2); // compare hashtags stored by a valid f1 to tweets stored by a valid f2
    
    // user inputs whether to repeat the loop, "y" for yes or "n" for no
    cout << "\nWould you like to analyze another set of tweets? (y/n) ";
    getline(cin, keepGoing);
    // reprompt user for keepGoing until it its value is "y" or "n" 
    while (keepGoing != "y" && keepGoing != "n") {
      cout << "Please type either y or n. ";
      getline(cin, keepGoing);
    }
  } while (keepGoing == "y"); // re-run analyzer every time user inputs "y" for keepGoing
  
  cout << "Thank you for using the hashtag analyzer!" << endl;
  return 0;
}


// isEmpty
// Given file name, returns whether that file is empty
bool isEmpty(string f) {
  fstream inputStream; // stream for file named by f
  inputStream.open(f); // read file named by f
  // file named by f is empty if inputStream remains closed
  if (inputStream.is_open()) {
    return false;
  } else {
    return true;
  }
}

// analyze
// Given two names of non-empty files, searches file2 for matching hashtags w/ file1
void analyze(string file1, string file2) {
  fstream inputHash; // stream for file with hashtags (named by f1)
  inputHash.open(file1); // read file with hashtags
  string hashes[MAX_SIZE]; // array storing hashtags in the file
  cout << "\nYour hashtags are imported!" << endl;
  // assign every element of the array, one line of file input per element
  for (int h = 0; h < MAX_SIZE; h++) {
    getline(inputHash, hashes[h]);
  }
  inputHash.close(); // stop streaming for hashtags when every index has been evaluated
  cout << MAX_SIZE << " hashtags loaded." << endl;
  
  fstream inputTweet; // stream for file with hashtags (named by f1)
  inputTweet.open(file2); // read file with tweets
  cout << "Your tweets are imported!" << endl;
  string tweets[MAX_SIZE]; // array storing tweets in the file and a hashtag for each tweet
  // assign every element of the array, one line of file input per element
  for (int h = 0; h < MAX_SIZE; h++) {
    getline(inputTweet, tweets[h]);
  }
  inputTweet.close(); // stop streaming for tweets when every index has been evaluated
  int numTweets = countTweets(tweets); // number of tweets found in the file
  cout << numTweets << " tweets loaded." << endl;
  
  cout << "\nTweets with matching hashtags:" << endl;
  int hashUses[MAX_SIZE] = {0}; // number of times each element of hashes appears in a tweet
  // check every 2-element, non-empty message of the tweets array
  for (int i = 0; i < numTweets*2; i += 2) {
    // check every element of the hashtags array
    for (int j = 0; j < MAX_SIZE; j++) {
      hashUses[j] += matchAndCount(hashes[j], tweets[i], tweets[i+1]);
      // increment usage value of the hashtag at index j based on comparison to the tweet starting at index i
    }
  }
  
  showCount(hashes, hashUses); //display each hashtag and its usage value as determined by the rest of the function
}

// countTweets
// Given string array of tweets, returns the number of tweets in the array
int countTweets(string file[]) {
  int elements = 0; // num of non-empty elements counted
  // increment value of elements by 1 until an element is empty OR nonexistent
  while (elements < MAX_SIZE && file[elements] != "") {
    elements++;
  }
  return elements/2; // 2 array elements per tweet
}

// matchAndCount
// Given 2 hashtags (hash, line1) and a tweet (line2), checks whether hash and line1 have the same hashtag.
// Displays the tweet and returns an increment of 1 to the calling value if so, does nothing otherwise
int matchAndCount(string hash, string line1, string line2) {
  if (hash == line1) {
    cout << line1 << " " << line2 << endl;
    return 1; // add 1 to the calling value
  } else {
    return 0; // return 0 to keep calling value the same
  }
}

// showCount
// Given string array of hashtags and int array of usage values, displays each hashtag and its respective usage value by element index
void showCount(string tags[], int nums[]) {
  cout << "\nTotal uses per hashtag:" << endl;
  // show every element in the arrays
  for (int i = 0; i < MAX_SIZE; i++) {
    cout << tags[i] << " - " << nums[i] << endl;
  }
}
