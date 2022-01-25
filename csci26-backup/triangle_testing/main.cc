//YOU: PUT YOUR LAST NAME(S) HERE
#include <cmath>
#include <limits>
#include <iostream>
using namespace std;

//Enum is useful when you want to make large numbers of mutually exclusive constants
//This creates 5 constant integers, named EQUILATERAL (= 0), ISOCELES (= 1), etc.
//It also creates a new integer type that can only hold a value from 0 to 4.
enum triangle_t
{
	EQUILATERAL,
	ISOCELES,
	RIGHT,
	OTHER,
	ERROR
};
/* This is equivalent, kinda, to:
const int EQUILATERAL = 0;
const int ISOCELES = 1;
const int RIGHT = 2;
const int OTHER = 3;
const int ERROR = 4;
*/

void die()
{
	cout << "BAD INPUT!\n";
	exit(EXIT_FAILURE);
}
class Triangle
{
	double side1, side2, side3;
	triangle_t triangle_type;

public:
	Triangle(double side1, double side2, double side3)
	{
		this->side1 = side1;
		this->side2 = side2;
		this->side3 = side3;
		triangle_type = triangle_tester();
	}

	triangle_t triangle_tester()
	{
		//YOU: Do your work right here
		if (side1 <= 0.0 or side2 <= 0.0 or side3 <= 0.0)
			return ERROR;
		if (side1 == side2 and side2 == side3)
			return EQUILATERAL;
		if (side1 == side2 or side2 == side3)
			return ISOCELES;
		if (side1 + side2 <= side3)
			return ERROR;
		if (side2 + side3 <= side1)
			return ERROR;
		if (side1 + side3 <= side2)
			return ERROR;
		if (side1 * side1 + side2 * side2 == side3 * side3)
			return RIGHT;
		if (side2 * side2 + side3 * side3 == side1 * side1)
			return RIGHT;
		if (side3 * side3 + side1 * side1 == side2 * side2)
			return RIGHT;
		return OTHER;
	}

	triangle_t getTriangleType()
	{
		return triangle_type;
	}
};

int main()
{
	double side1 = 0.0, side2 = 0.0, side3 = 0.0;
	cin >> side1 >> side2 >> side3;
	Triangle bob(side1, side2, side3);
	triangle_t result = bob.getTriangleType();
	if (result == EQUILATERAL)
		cout << "equilateral";
	else if (result == ISOCELES)
		cout << "isoceles";
	else if (result == RIGHT)
		cout << "right";
	else if (result == OTHER)
		cout << "other";
	else if (result == ERROR)
		cout << "error";
	else
		cout << "This is unpossible!";
	cout << endl;
}
