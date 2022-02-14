#include <iostream>
#include <iomanip> // setprecision
#include <fstream> // istream
#include <string>
#include <vector>

#define MAX_BUFLEN 256

// Stand-in header
class Weapon {
public:
  Weapon() {
    name = "";
    strength = 0;
    power = 0;
  }

  
  Weapon(std::string _name, int _strength, float _power) {
    name = _name;
    strength = _strength;
    power = _power;
  }

  std::string name;
  int strength;
  float power;
};

class Ship {
public:
  Ship() {
    name = "";
    classname = "";
    length = 0;
    shield = 0;
    warp = 0;
    weapons = std::vector<Weapon> {};
  }
    
  Ship(std::string _name, std::string _classname, short _length,
       int _shield, float _warp, std::vector<Weapon> _weapons)
  {
    name = _name;
    classname = _classname;
    length = _length;
    shield = _shield;
    warp = _warp;
    weapons = _weapons;
  }
  
  std::string name;
  std::string classname;
  short length;
  int shield;
  float warp;
  std::vector<Weapon> weapons;
};

Ship find_ship_with_strongest_weapon(std::vector<Ship> &ships);
Weapon find_strongest_weapon(Ship ship);
bool has_weapons(Ship ship);
Ship find_strongest_ship(std::vector<Ship> &ships);
Ship find_weakest_ship(std::vector<Ship> &ships);
int ship_strength(Ship ship);
std::vector<Ship> find_unarmed(std::vector<Ship> &ships);

void print_ship(Ship ship);
void print_weapons(std::vector<Weapon> &weapons);
void print_all(std::vector<Ship> &ships);

void parse_file(std::vector<Ship> &ships, const char *filename);
void add_ship(std::vector<Ship> &ships, std::ifstream &file);
void add_weapon(std::vector<Weapon> &weapons, std::ifstream &file);

std::string read_str(std::ifstream &file);

template <class numT>
numT read_num(std::ifstream &file);

// End of header

int main()
{
  /* Disclaimer: menu format code pre-provided by zyBooks*/
  std::cout << std::fixed << std::setprecision(1);

  /*
  std::cout << "Which file(s) to open?\n";
  std::cout << "1. friendlyships.shp" << std::endl;
  std::cout << "2. enemyships.shp" << std::endl;
  std::cout << "3. Both files" << std::endl;
  */
  
  int option;
  std::cin >> option;

  // Container of ship data
  std::vector<Ship> ships;

  switch(option) {
  case 1:
    parse_file(ships, "friendlyships.shp");
    break;
  case 2:
    parse_file(ships, "enemyships.shp");
    break;
  case 3:
    parse_file(ships, "friendlyships.shp");
    parse_file(ships, "enemyships.shp");
    break;
  }

  /*
  // Menu
  std::cout << "1. Print all ships" << std::endl;
  std::cout << "2. Starship with the strongest weapon" << std::endl;
  std::cout << "3. Strongest starship overall" << std::endl;
  std::cout << "4. Weakest ship (ignoring unarmed)" << std::endl;
  std::cout << "5. Unarmed ships" << std::endl;
  */
	
  int choice;
  std::cin >> choice;
  std::cin.get();  // Clear newline character for any later input
   
  switch(choice) {
  case 1: {
    print_all(ships);
    
    break;
  }
    
  case 2: {
    Ship ship_with_strongest_weapon = find_ship_with_strongest_weapon(ships);

    print_ship(ship_with_strongest_weapon);
    
    break;
  }
    
  case 3: {
    Ship strongest_ship = find_strongest_ship(ships);

    print_ship(strongest_ship);
	
    break;
  }
    
  case 4: {
    Ship weakest_ship = find_weakest_ship(ships);

    print_ship(weakest_ship);
	    
    break;
  }
    
  case 5: {
    std::vector<Ship> unarmed = find_unarmed(ships);

    print_all(unarmed);
      
    break;
  }
  } // End of switch

  return 0;
}

/* Search Helpers */
Ship find_ship_with_strongest_weapon(std::vector<Ship> &ships) {
  Ship ship_with_strongest_weapon;
  Weapon strongest_weapon;

  // First find a ship with weapons
  for (auto i = ships.begin(); i != ships.end(); ++i) {
    if ( has_weapons(*i) ) {
      ship_with_strongest_weapon = *i;
      strongest_weapon = find_strongest_weapon(ship_with_strongest_weapon);
      break;
    }
  }

  // Find ship with strongest weapon
  for (auto i = ships.begin(); i != ships.end(); ++i) {
    if ( has_weapons(*i) ) {
      Weapon maybe_strongest_weapon = find_strongest_weapon(*i);

      if ( maybe_strongest_weapon.strength > strongest_weapon.strength) {
	ship_with_strongest_weapon = *i;
	strongest_weapon = maybe_strongest_weapon;
      }
    }
  }

  return ship_with_strongest_weapon;
}

Weapon find_strongest_weapon(Ship ship) {
  Weapon strongest_weapon = ship.weapons[0];
  
  for (auto i = ship.weapons.begin(); i != ship.weapons.end(); ++i) {
    if (i->strength > strongest_weapon.strength) {
      strongest_weapon = *i;
    }
  }

  return strongest_weapon;
}

bool has_weapons(Ship ship) {
  if (ship.weapons.size() == 0) {
    return false;
  } else {
    return true;
  }
}

Ship find_strongest_ship(std::vector<Ship> &ships) {
  Ship strongest_ship = ships[0];
  
  for (auto i = ships.begin(); i != ships.end(); ++i) {
    if (ship_strength(*i) > ship_strength(strongest_ship)) {
      strongest_ship = *i;
    }
  }

  return strongest_ship;
}

Ship find_weakest_ship(std::vector<Ship> &ships) {
  Ship weakest_ship;

  for (auto i = ships.begin(); i != ships.end(); ++i) {
    if (ship_strength(*i) > 0) {
      weakest_ship = *i;
      break;
    }
  }
  
  for (auto i = ships.begin(); i != ships.end(); ++i) {
    if (ship_strength(*i) > 0 && ship_strength(*i) < ship_strength(weakest_ship)) {
      weakest_ship = *i;
    }
  }

  return weakest_ship;
}

int ship_strength(Ship ship) {
  int total_strength = 0;

  if (ship.weapons.size() == 0) {
    return 0;
  }
  
  for (auto i = ship.weapons.begin(); i != ship.weapons.end(); ++i) {
    total_strength += i->strength;
  }

  return total_strength;
}

std::vector<Ship> find_unarmed(std::vector<Ship> &ships) {
  std::vector<Ship> unarmed;

  for (auto i = ships.begin(); i != ships.end(); ++i) {
    if ( !has_weapons(*i) ) {
      unarmed.push_back(*i);
    }
  }

  return unarmed;
}

/* Display Helpers */
void print_ship(Ship ship) {
  std::cout << "Name: " << ship.name << std::endl;
  std::cout << "Class: " << ship.classname  << std::endl;
  std::cout << "Length: " << ship.length  << std::endl;
  std::cout << "Shield capacity: " << ship.shield << std::endl;
  std::cout << "Maximum Warp: " << ship.warp << std::endl;
  std::cout << "Armaments: " << std::endl;
  print_weapons(ship.weapons);
}

void print_weapons(std::vector<Weapon> &weapons) {
  int num_weapons = weapons.size();
  int total_strength = 0;
  
  if (num_weapons == 0) {
    std::cout << "Unarmed" << std::endl;
  } else {
    for (auto i = weapons.begin(); i != weapons.end(); ++i) {
      std::cout << i->name << ", " << i->strength << ", " << i->power << std::endl;
      total_strength += i->strength;
    }
    
    std::cout << "Total firepower: " << total_strength << std::endl;
  }
}

void print_all(std::vector<Ship> &ships) {
  for (auto i = ships.begin(); i != ships.end(); ++i) {
    print_ship(*i);
    std::cout << std::endl;
  }
}

/* File Input Helpers */
// Add set data found in file to vector of Sets
void parse_file(std::vector<Ship> &ships, const char *filename) {
  std::ifstream file;
  file.open(filename);

  int num_ships = read_num<int>(file);

  for (int i = 0; i < num_ships; ++i) {
    add_ship(ships, file);
  }

  file.close();
}

// Turns the binary data into a Ship object
void add_ship(std::vector<Ship> &ships, std::ifstream &file) {

  std::string _name = read_str(file);
  std::string _classname = read_str(file);
  short _length = read_num<short>(file);
  int _shield = read_num<int>(file);
  float _warp = read_num<float>(file);

  std::vector<Weapon> _weapons;
  int num_weapons = read_num<int>(file);
  for (int i = 0; i < num_weapons; ++i) {
    add_weapon(_weapons, file);
  }
  
  // Add new Ship object to vector
  Ship new_ship(_name, _classname, _length, _shield, _warp, _weapons);
  ships.push_back(new_ship);
}

void add_weapon(std::vector<Weapon> &weapons, std::ifstream &file) {

  std::string _name = read_str(file);
  int _strength = read_num<int>(file);
  float _power = read_num<float>(file);

  Weapon new_weapon(_name, _strength, _power);
  weapons.push_back(new_weapon);
}

/* Read Helpers */
std::string read_str(std::ifstream &file) {
  int length = read_num<int>(file);
  char *c_str = new char[length];
  file.read(c_str, length);
  std::string str(c_str);
  delete[] c_str;
  return str;
}

template <class numT>
numT read_num(std::ifstream &file) {
numT num = 0;

file.read((char *) &num, sizeof(numT));
    
  return num;
}
