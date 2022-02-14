#include <iostream>
#include <cmath>
#include "Functions.h"

using namespace std;

void QuadraticRoot()
{
  double a, b, c, disc;

  cout << "Enter a, b, c: ";
  cin >> a;
  cin >> b;
  cin >> c;
  cout << endl;

  disc = pow(b, 2) - 4*a*c;

  if (disc < 0)
    {
      cout << "The equation has no real roots.";
    }
  else if (disc > 0)
    {
      cout << "The equation has two roots: ";
      cout << solve(a, b, disc, true) << " and " << solve(a, b, disc, false);
    }
  else
    {
      cout << "The equation has one root: ";
      cout << solve(a, b, disc, true);
    }
}

double solve(double a, double b, double disc, bool positive)
{
  if (positive)
    return (-b + sqrt(disc)) / (2*a);
  else
    return (-b - sqrt(disc)) / (2*a);
}

void GradeCalculator()
{
  int num_students;
  int best_score = 0;

  cout << "Enter the number of students: ";
  cin >> num_students;
  cout << endl;
  int *grades = (int *) malloc(sizeof(int) * num_students);

  cout << "Enter " << num_students << " scores: " << endl;
  for (int i = 0; i < num_students; i++)
    {
      cin >> grades[i];
      if (grades[i] > best_score)
	best_score = grades[i];
    }

  for (int i = 0; i < num_students; i++)
    {
      cout << "Student " << i+1 << " - Score: " << grades[i];
      cout << ", Letter: " << letter_grade(grades[i], best_score) << endl;
    }

  free(grades);
}

string letter_grade(int grade, int best_score)
{
  if (grade >= best_score - 10)
    return "A";
  if (grade >= best_score - 20) // Only runs if grade < best_score - 10
    return "B";
  if (grade >= best_score - 30)
    return "C";
  if (grade >= best_score - 40)
    return "D";
  else
    return "F";
}

void CreditCardValidator()
{
  long long card_num;

  cout << "Enter a credit card number: ";
  cin >> card_num;
  cout << endl;

  if (isValid(card_num))
      cout << card_num << " is valid.";
  else
    cout << card_num << " is invalid.";
}

int *digit_array(long long number)
{
  int *digits = (int *) malloc(sizeof(int) * getSize(number));

  for (int i = getSize(number) - 1; i >= 0; i--)
    {
      digits[i] = number % 10;
      number /= 10;
    }

  return digits;
}

bool isValid(long long number)
{
  bool length = false;
  bool prefix = false;
  bool checksum = false;
  const int prefixes[] = {4, 5, 37, 6};
  const int num_prefixes = 4;

  /* Length validation */
  if (13 <= getSize(number) && getSize(number) <= 16)
    length = true;

  /* Prefix validation */
  for (int i = 0; i < num_prefixes; i++)
    {
      if (prefixMatched(number, prefixes[i]))
	{
	  prefix = true;
	  break;
	}
    }

  /* Checksum validation */
  if ((sumOfDoubleEvenPlace(number) + sumOfOddPlace(number)) % 10 == 0)
    checksum = true;


  if (length && prefix && checksum)
    return true;
  else
    return false;
}

int sumOfDoubleEvenPlace(long long number)
{
  int *digits = digit_array(number);
  int sum = 0;

  for (int i = 0; i < getSize(number); i += 2)
    {
      sum += getDigit(digits[i]);
    }

  free(digits);

  return sum;
}

int getDigit(int number)
{
  number *= 2;

  if (getSize(number) == 1)
    {
      return number;
    }
  else
    {
      return (number % 10) + (number / 10);
    }
}

int sumOfOddPlace(long long number)
{
  int *digits = digit_array(number);
  int sum = 0;

  for (int i = 1; i < getSize(number); i += 2)
    {
      sum += digits[i];
    }

  free(digits);

  return sum;
}

bool prefixMatched(long long number, int digit)
{
  if (getPrefix(number, getSize((long long) digit)) == digit)
    return true;
  else
    return false;
}

int getSize(long long number)
{
  int size = 0;

  while (number != 0)
    {
      number /= 10;
      size += 1;
    }
  return size;
}

long getPrefix(long long number, int numDigits)
{
  int *digits = digit_array(number);
  long prefix = 0;

  for (int i = 0; i < numDigits; i++)
    {
      prefix += digits[i]*pow(10, i);
    }

  free(digits);

  return prefix;
}
