/* Main functions */
void QuadraticRoot();
void GradeCalculator();
void CreditCardValidator();

/* Helpers for QuadraticRoot */
double solve(double, double, double, bool);  // Solves quadratic formula

/* Helpers for GradeCalculator */
std::string letter_grade(int, int); // Turns a number grade into a letter

/* Helpers for CreditCardValidator */
bool isValid(long long); // Checks that card number is valid
int sumOfDoubleEvenPlace(long long); // Funny-sum even card slots
int getDigit(int); // Funny-sum
int sumOfOddPlace(long long); // Sum odd slots of card
bool prefixMatched(long long, int); // Match card to provider
int getSize(long long); // Check number of digits
long getPrefix(long long, int); // Get first digits of number

int *digit_array(long long); // Turns a number into an array of digits
