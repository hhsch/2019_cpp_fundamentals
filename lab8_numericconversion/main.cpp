#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm> // std::sort
#include "Color.h"

void ReadFile(const char *filename, std::vector<Color> &outVector);
void SortColors(std::vector<Color> &colors);
void PrintColors(const std::vector<Color> &colors);

int main()
{
  std::cout << "1-6: Load colors1/2/3/4/5/6.txt" << std::endl;
  std::cout << "7. Load all 6 files" << std::endl;
  int choice;
  std::cin >> choice;

  std::vector<Color> colors;
  // Load the selected files
  if (choice >= 1 && choice <= 6)
    {
      std::string file = "colors" + std::to_string(choice) + ".txt";
      ReadFile(file.c_str(), colors);
	
    }
  else if (choice == 7)
    {
      for (int i = 1; i <= 6; i++)
	{
	  std::string file = "colors" + std::to_string(i) + ".txt";
	  ReadFile(file.c_str(), colors);
	}
    }

  // Sort and print the loaded data
  SortColors(colors);
  PrintColors(colors);

  return 0;
}

void ReadFile(const char *filename, std::vector<Color> &outVector)
{
  // TODO: Load the file and store the resulting colors in outVector.
  std::fstream file(filename, std::ios_base::in);

  while(!file.eof()) {
    Color c;
    
    //c.SetName
    std::string name;
    file >> name;
    c.SetName(name.c_str());
    
    //c.SetValue(); // This should also convert the values, internally
    int value;
    file >> value;
    c.SetValue(value);
    
    outVector.push_back(c);
  }

  file.close();
}

void SortColors(std::vector<Color> &colors)
{
  // TODO: Sort the colors in ascending order by name.
  // std::sort uses overloaded operator< in Color class
  std::sort(colors.begin(), colors.end());
}

void PrintColors(const std::vector<Color> &colors)
{
  for (unsigned int i = 0; i < colors.size(); i++)
    {
      std::cout << colors[i].GetName();
      for (unsigned int j = 0; j < 3 - colors[i].GetName().size() / 8; j++)
	std::cout << "\t";
      std::cout << colors[i].GetHexValue() << '\t' << (int)colors[i].GetR() << "," << (int)colors[i].GetG() << "," << (int)colors[i].GetB() << std::endl;
    }
  std::cout << "Number of colors: " << colors.size() << std::endl;
}
