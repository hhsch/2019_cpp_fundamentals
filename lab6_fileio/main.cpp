#include <iostream>
#include <iomanip> // setprecision
#include <fstream> // ifstream
#include <string>
#include <cstring> // strtok
#include <vector>
#include <stdexcept> // invalid_argument

#define MAX_BUFLEN 256

// Stand-in header
class Set {
public:
  Set(std::string _set_number, std::string _theme, std::string _name,
      int _minifigs, int _pieces, float _price)
    : set_number( _set_number), // Just to initialize const data
      theme(_theme),
      name(_name),
      minifigs(_minifigs),
      pieces(_pieces),
      price(_price)
  {}
  
  const std::string set_number;
  const std::string theme;
  const std::string name;
  const int minifigs;
  const int pieces;
  const float price;
};

Set find_highest_price(std::vector<Set> &sets);
Set find_lowest_price(std::vector<Set> &sets);
Set find_highest_minifigs(std::vector<Set> &sets);
Set find_highest_pieces(std::vector<Set> &sets);
std::vector<Set> search_name(std::vector<Set> &sets, std::string term);
std::vector<Set> search_theme(std::vector<Set> &sets, std::string term);
float sum_price(std::vector<Set> &sets);
int sum_minifigs(std::vector<Set> &sets);
int sum_pieces(std::vector<Set> &sets);

void print_long(Set &set);
void print_short(Set &set);

void parse_file(std::vector<Set> &sets, const char *filename);
void add_set(std::vector<Set> &sets, char *line);
std::vector<std::string> parse_line(char *line);

// End of header

int main()
{
  /* Disclaimer: menu format code pre-provided by zyBooks*/
  std::cout << std::fixed << std::setprecision(2);
  std::cout << "Which file(s) to open?\n";
  std::cout << "1. lego1.csv" << std::endl;
  std::cout << "2. lego2.csv" << std::endl;
  std::cout << "3. lego3.csv" << std::endl;
  std::cout << "4. All 3 files" << std::endl;
  int option;
  std::cin >> option;

  // Container of set data
  std::vector<Set> sets;

  switch(option) {
  case 1:
    parse_file(sets, "lego1.csv");
    break;
  case 2:
    parse_file(sets, "lego2.csv");
    break;
  case 3:
    parse_file(sets, "lego3.csv");
    break;
  case 4:
    parse_file(sets, "lego1.csv");
    parse_file(sets, "lego2.csv");
    parse_file(sets, "lego3.csv");
    break;
  }

  std::cout << "Total number of sets: " << sets.size() << std::endl;

  /* Menu
     std::cout << "1. Most Expensive set" << std::endl;
     std::cout << "2. Largest piece count" << std::endl;
     std::cout << "3. Search for set name containing..." << std::endl;
     std::cout << "4. Search themes..." << std::endl;
     std::cout << "5. Part count information" << std::endl;
     std::cout << "6. Price information" << std::endl;
     std::cout << "7. Minifigure information" << std::endl;
     std::cout << "8. If you bought one of everything..." << std::endl;
     std::cout << "0. Exit" << std::endl;
  */
  
  int choice;
  std::cin >> choice;
  std::cin.get();  // Clear newline character for any later input
   
  switch(choice) {
  case 1: {
    Set highest_price = find_highest_price(sets);

    std::cout << "The most expensive set is:" << std::endl;
    print_long(highest_price);
    
    break;
  }
    
  case 2: {
    Set highest_pieces = find_highest_pieces(sets);

    std::cout << "The set with the highest parts count: " << std::endl;
    print_long(highest_pieces);
    
    break;
  }
    
  case 3: {
    char term_c[MAX_BUFLEN];
    std::cin.getline(term_c, MAX_BUFLEN);
    std::string term(term_c);

    std::vector<Set> matches = search_name(sets, term);

    if (matches.empty()) {
      std::cout << "No sets found matching that search term" << std::endl;
    } else {
      std::cout << "Sets matching \"" << term << "\":" << std::endl;
      for (std::vector<Set>::iterator i = matches.begin(); i != matches.end(); ++i) {
	print_short(*i);
      }
    }
	
    break;
  }
    
  case 4: {
    char term_c[MAX_BUFLEN];
    std::cin.getline(term_c, MAX_BUFLEN);
    std::string term(term_c);

    std::vector<Set> matches = search_theme(sets, term);

    if (matches.empty()) {
      std::cout << "No sets found matching that search term" << std::endl;
    } else {
      std::cout << "Sets matching \"" << term << "\":" << std::endl;
      for (std::vector<Set>::iterator i = matches.begin(); i != matches.end(); ++i) {
	print_short(*i);
      }
    }
	    
    break;
  }
    
  case 5: {
    int num_sets = sets.size();
    int num_pieces = sum_pieces(sets);

    std::cout << "Average part count for " << num_sets << " sets: ";
    std::cout << num_pieces / num_sets << std::endl;
      
    break;
  }
    
  case 6: {
    int num_sets = sets.size();
    float total_price = sum_price(sets);
    Set highest_price = find_highest_price(sets);
    Set lowest_price = find_lowest_price(sets);

    std::cout << "Average price for " << num_sets << " sets: $";
    std::cout << total_price / ((float) num_sets) << std::endl;
    std::cout << std::endl;
      
    std::cout << "Least expensive set: " << std::endl;
    print_long(lowest_price);
    std::cout << std::endl;

    std::cout << "Most expensive set: " << std::endl;
    print_long(highest_price);
      
    break;
  }
    
  case 7: {
    int num_sets = sets.size();
    int num_minifigs = sum_minifigs(sets);
    Set highest_minifigs = find_highest_minifigs(sets);

    std::cout << "Average number of minifigures: ";
    std::cout << num_minifigs / num_sets << std::endl;

    std::cout << "Set with the most minifigures: " << std::endl;
    print_long(highest_minifigs);
      
    break;
  }
    
  case 8: {
    float total_price = sum_price(sets);
    int num_minifigs = sum_minifigs(sets);
    int num_pieces = sum_pieces(sets);

    std::cout << "If you bought one of everything..." << std::endl;
    std::cout << std::endl;
    std::cout << "It would cost: $" << total_price << std::endl;
    std::cout << "You would have " << num_pieces << " pieces in your collection" << std::endl;
    std::cout << "You would have an army of " << num_minifigs << " minifigures!" << std::endl;
      
    break;
  }

  case 0: {
    return 0;
  }
  } // End of switch
}

/* Search Helpers */
Set find_highest_price(std::vector<Set> &sets) {
  std::vector<Set>::iterator highest_price = sets.begin();

  for (std::vector<Set>::iterator i = sets.begin(); i != sets.end(); ++i) {
    if (i->price > highest_price->price) {
      highest_price = i;
    }
  }

  return *highest_price;
}

Set find_lowest_price(std::vector<Set> &sets) {
  std::vector<Set>::iterator lowest_price = sets.begin();

  for (std::vector<Set>::iterator i = sets.begin(); i != sets.end(); ++i) {
    if (i->price < lowest_price->price) {
      lowest_price = i;
    }
  }

  return *lowest_price;
}

Set find_highest_minifigs(std::vector<Set> &sets) {
  std::vector<Set>::iterator highest_minifigs = sets.begin();

  for (std::vector<Set>::iterator i = sets.begin(); i != sets.end(); ++i) {
    if (i->minifigs > highest_minifigs->minifigs) {
      highest_minifigs = i;
    }
  }

  return *highest_minifigs;
}
 
Set find_highest_pieces(std::vector<Set> &sets) {
  std::vector<Set>::iterator highest_pieces = sets.begin();

  for (std::vector<Set>::iterator i = sets.begin(); i != sets.end(); ++i) {
    if (i->pieces > highest_pieces->pieces) {
      highest_pieces = i;
    }
  }

  return *highest_pieces;
}

std::vector<Set> search_name(std::vector<Set> &sets, std::string term) {
  std::vector<Set> matches;

  for (std::vector<Set>::iterator i = sets.begin(); i != sets.end(); ++i) {
    if (i->name.find(term) != std::string::npos) {
      matches.push_back(*i);
    }
  }

  return matches;
}

std::vector<Set> search_theme(std::vector<Set> &sets, std::string term) {
  std::vector<Set> matches;

  for (std::vector<Set>::iterator i = sets.begin(); i != sets.end(); ++i) {
    if (i->theme.find(term) != std::string::npos) {
      matches.push_back(*i);
    }
  }

  return matches;
}

float sum_price(std::vector<Set> &sets) {
  float sum = 0;
  
  for (std::vector<Set>::iterator i = sets.begin(); i != sets.end(); ++i) {
    sum += i->price;
  }

  return sum;
}

int sum_minifigs(std::vector<Set> &sets) {
  int sum = 0;
  
  for (std::vector<Set>::iterator i = sets.begin(); i != sets.end(); ++i) {
    sum += i->minifigs;
  }

  return sum;
} 

int sum_pieces(std::vector<Set> &sets) {
  int sum = 0;
  
  for (std::vector<Set>::iterator i = sets.begin(); i != sets.end(); ++i) {
    sum += i->pieces;
  }

  return sum;
} 
  
/* Display Helpers */
// Detailed information
void print_long(Set &set) {
  std::cout << "Name: " << set.name << std::endl;
  std::cout << "Number: " << set.set_number << std::endl;
  std::cout << "Theme: " << set.theme << std::endl;
  std::cout << "Price: $" << set.price << std::endl;
  std::cout << "Minifigures: " << set.minifigs << std::endl;
  std::cout << "Piece count: " << set.pieces << std::endl;
}

// Summary info
void print_short(Set &set) {
  std::cout << set.set_number << " " << set.name;
  std::cout << " $" << set.price << std::endl;
}

/* File Input Helpers */
// Add set data found in file to vector of Sets
void parse_file(std::vector<Set> &sets, const char *filename) {
  std::basic_ifstream<char> file;
  file.open(filename);

  char header[MAX_BUFLEN];
  file.getline(header, MAX_BUFLEN); // Discard headers

  char line[MAX_BUFLEN];
  while( file.getline(line, MAX_BUFLEN) ) {
    add_set(sets, line);
  }

  file.close();
}

// Adds the data from a line into a Set object
void add_set(std::vector<Set> &sets, char *line) {
  std::string _set_number, _theme, _name;
  int _minifigs, _pieces;
  float _price;
  
  std::vector<std::string> data = parse_line(line);

  _set_number = data[0];
  _theme = data[1];
  _name = data[2];
  
  try {
    _minifigs = stoi(data[3]);
  } catch (std::invalid_argument) {
    _minifigs = 0;
  }
  
  try {
    _pieces = stoi(data[4]);
  } catch (std::invalid_argument) {
    _pieces = 0;
  }
  
  try {
    _price = stof(data[5]);
  } catch (std::invalid_argument) {
    _price = 0.0;
  }

  // Add new Set object to vector
  Set new_set(_set_number, _theme, _name, _minifigs, _pieces, _price);
  sets.push_back(new_set);
}

// Parses the comma-delimited line into an iterable string format
std::vector<std::string> parse_line(char *line) {
  std::vector<std::string> tokens;
  
  char *token = std::strtok(line, ",");
  while (token != NULL) {
    // Grab the next value and put it in the return vector
    std::string new_token(token);
    tokens.push_back(new_token);

    token = std::strtok(NULL, ",");
  }

  return tokens;
}
