#include <iostream>
#include "Functions.h"

using namespace std;

/* Program driver */
int main()
{
  int option;

  cout << "1. Quadratic Root" << endl;
  cout << "2. Grade Calculator" << endl;
  cout << "3. Credit Card Validator" << endl;
  cout << "Enter a number: " << endl;

  cin >> option;

  /* Verify input */
  if (!option)
    {
      cout << "Invalid input!";
      return 1;
    }
  else if(option < 1 || 3 < option)
    {
      cout << "Input out of range!";
      return 1;
    }

  switch (option)
    {
    case 1:
      QuadraticRoot();
      break;

    case 2:
      GradeCalculator();
      break;

    case 3:
      CreditCardValidator();
      break;

    default:
      cout << "Input out of range!";
    }

  return 0;
}
