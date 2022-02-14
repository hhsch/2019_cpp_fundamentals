#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

// Header
void ReadWordsFromFile(std::map<std::string, int> &words, std::string filename);
std::string Sanitize(std::string str);
bool ValidLetter(char ch);
void WordList(std::map<std::string, int> &words);
void MostCommonWord(std::map<std::string, int> &words);
void LongerThan(std::map<std::string, int> &words, unsigned int X);
void SearchForWord(std::map<std::string, int> &words, std::string word);

int main() {
  std::map<std::string, int> words;

  std::cout << "Select a file to open (1-4)" << std::endl;
  int option;
  std::cin >> option;
  std::string filename = "ipsum";
  filename.append(std::to_string(option));
  filename.append(".txt");

  std::cout << "File name: " << filename << std::endl;
  ReadWordsFromFile(words, filename);

  std::cout << "Choose an operation: " << std::endl;
	
  std::cout << "1. Display word list" << std::endl;
  std::cout << "2. Most common word" << std::endl;
  std::cout << "3. Words longer than (X) characters" << std::endl;
  std::cout << "4. Search for a particular word (ignore case!)" << std::endl;
	
  std::cin >> option;
  if (option == 1) {
    WordList(words);
  } else if (option == 2) {
    MostCommonWord(words);
  } else if (option == 3) {
    unsigned int X;
    std::cin >> X;
    LongerThan(words, X);
  } else if (option == 4) {
    std::string word;
    std::cin >> word;
    SearchForWord(words, word);
  }

  return 0;
}

void ReadWordsFromFile(std::map<std::string, int> &words, std::string filename) {
  std::ifstream file(filename);

  while (!file.eof()) {
    std::string nextraw;
    file >> nextraw;

    std::string nextclean = Sanitize(nextraw);
    
    if (nextclean != "") {
      words[nextclean] += 1;
    }
  }

}

std::string Sanitize(std::string str) {
  // Clean front
  while (str.compare("") != 0 && !ValidLetter(str[0])) {
    str.erase(0);
  }

  // Clean back
  while (str.compare("") != 0 && !ValidLetter(str[str.length() -1])) {
    str.erase(str.length() - 1);
  }

  // Convert to lowercase
  for (unsigned int i = 0; i < str.length(); ++i) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      str[i] += ('a' - 'A');
    }
  }

  return str;
}

bool ValidLetter(char ch) {
  if (ch >= 'a' && ch <= 'z') { return true; }
  else if (ch >= 'A' && ch <= 'Z') { return true; }
  else { return false; }
}

void WordList(std::map<std::string, int> &words) {
  int wordcount = 0;
  for (auto i = words.begin(); i != words.end(); ++i) {
    std::cout << i->first << " " << i->second << std::endl;
    wordcount += 1;
  }
  std::cout << "Word count: " << wordcount << std::endl;
}

void MostCommonWord(std::map<std::string, int> &words) {
  // Copy everything to multimap
  std::multimap<int, std::string> reverse;
  for (auto i = words.begin(); i != words.end(); ++i) {
    reverse.insert( std::pair<int, std::string> (i->second, i->first) );
  }

  // Pick out top word
  auto i = reverse.rbegin();
  int longcount = i->first;
  while (i->first == longcount) {
    ++i;
  }
  --i;
  std::cout << "Most commonly used word: ";
  std::cout << i->second << " " << i->first << std::endl;
}

void LongerThan(std::map<std::string, int> &words, unsigned int X) {
  std::cout << "Words longer than " << X << ":" << std::endl;
  for (auto i = words.begin(); i != words.end(); ++i) {
    if (i->first.length() > X) {
      std::cout << i->first << std::endl;
    }
  }
}

void SearchForWord(std::map<std::string, int> &words, std::string word) {
  std::string search = Sanitize(word);
  for (auto i = words.begin(); i != words.end(); ++i) {
    if (search.compare(i->first) == 0) {
      std::cout << search << " found in file " <<  i->second << " times." << std::endl;
    }
  }
}
