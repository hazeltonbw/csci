#include "/public/read.h" //Kerney's rad input library
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/multiprecision/cpp_int.hpp> //Bigint
#include <boost/multiprecision/cpp_dec_float.hpp> //Bigfloat
#include <boost/multiprecision/miller_rabin.hpp> //Prime testing
#include <boost/math/constants/constants.hpp> //Has pi
#include <boost/numeric/conversion/int_float_mixture_enum.hpp>
#include <type_traits>
using namespace std;
using namespace boost::random;
using namespace boost::multiprecision;
using boost::multiprecision::cpp_dec_float_100;
using boost::math::constants::pi;

typedef cpp_int BIGINT;
typedef cpp_dec_float_100 BIGFLOAT;

//You will have to write these functions
void addition();
void subtraction();
void multiplication();
void division();
void mod();
void factorial();
void exponential();
void exponential_modulus();
void prime_testing();
void volume();
void integral();

int main()
{
	//Set precision to 100 digits
	cout << std::setprecision(std::numeric_limits<cpp_dec_float_100>::digits10);

	//TUTORIAL
	//This is how you make a bigint
//	BIGINT x("324234233423432422344"); //Arbitrary precision integer
//	cout << pow(x,2) << endl; //x squared
	//cout << powm(x,2,10) << endl; //x squared modulus 10

	//This is how you make a big float
	//cpp_dec_float_100 x = 2 * pi<cpp_dec_float_100>(); //100 digits of precision in a float
	//cout << x << endl;

	system("figlet BIG MATH | lolcat --seed=32");
	cout << "Pick an option:\n" <<
		"0. Addition\n" <<
		"1. Subtraction\n" <<
		"2. Multiplication\n" <<
		"3. Division\n" <<
		"4. Modulus\n" <<
		"5. Factorial\n" <<
		"6. Exponentiation\n" <<
		"7. Exponentiation & Modulus\n" <<
		"8. Prime Testing\n" <<
		"9. Volume of a cylinder\n" <<
		"10. Integral\n" <<
		"(Anything else to quit)\n";
	auto choice = read_opt<int>();
	if (!choice) exit(0);
	else if (choice == 0) addition();
	else if (choice == 1) subtraction();
	else if (choice == 2) multiplication();
	else if (choice == 3) division();
	else if (choice == 4) mod();
	else if (choice == 5) factorial();
	else if (choice == 6) exponential();
	else if (choice == 7) exponential_modulus();
	else if (choice == 8) prime_testing();
	else if (choice == 9) volume();
	else if (choice == 10) integral();
}

//Example of how to do it
void addition() {
	BIGINT first  = read("Please enter the first integer:\n");
	BIGINT second = read("Please enter the second integer:\n");
	cout << first << " + " << second << " = " << (first + second) << endl;
}

//YOU: Write all these functions
void subtraction() {
	BIGINT first = read("Please enter the first integer:\n");
	BIGINT second = read("Please enter the second integer:\n");
	cout << first << " - " << second << " = " << (first - second) << endl;
}

void multiplication() {
	BIGINT first = read("Please enter the first integer:\n");
	BIGINT second = read("Please enter the second integer:\n");
	cout << first << " * " << second << " = " << (first * second) << endl;
}

void division() {
	BIGINT first = read("Please enter the first integer:\n");
	BIGINT second = read("Please enter the second integer:\n");
	if (second == 0){ cout << "Can't divide by 0! \n"; exit(EXIT_FAILURE);}
	cout << first << " / " << second << " = " << (first / second) << endl;
}

void mod() {
	BIGINT first = read("Please enter the first integer:\n");
	BIGINT second = read("Please enter the second integer:\n");
	if (second == 0){ cout << "Can't divide by 0! \n"; exit(EXIT_FAILURE);}
	cout << first << " % " << second << " = " << (first % second) << endl;
}

BIGINT factorial_helper(BIGINT x) {
	return x <= 1 ? BIGINT(1) : x * factorial_helper(x-1);
}
//The 0 is a placeholder for you to replace with the answer
void factorial() {
	BIGINT first  = read("Please enter the first integer:\n");
	//Output first!
	BIGINT answer = factorial_helper(first);
	cout << first << "! = " << answer << endl;
}

void exponential() {
	BIGINT first = read("Please enter the first integer:\n");
	BIGINT second = read("Please enter the second integer:\n");
	cout << first << " ^ " << second << " = " << pow(first,static_cast<int>(second)) << endl;
}

void exponential_modulus() {
	BIGINT first  = read("Please enter the first integer:\n");
	BIGINT second = read("Please enter the second integer:\n");
	BIGINT third  = read("Please enter the third integer:\n");
	//Output (first ^ second) % third
	cout << "(" << first << " ^ " << second << ") % " << third << " = " << powm(first, second, third) << endl;
}

//You can write your own test or use a library function to determine primality
void prime_testing() {
	BIGINT first  = read("Please enter the first integer:\n");
	//If first is a prime, print the first, otherwise print the second
	//fermats little theorem
	// miller-rabin test --- more accurate
	bool isPrime = miller_rabin_test(first, 25);
	if (isPrime)
		cout << first << " is a prime.\n";
	else
		cout << first << " is not a prime.\n";
}

//Compute volume of cylinder
void volume() {
	BIGFLOAT height = read("Please enter the first float:\n");
	BIGFLOAT radius = read("Please enter the second float:\n");
	cout << "A cylinder of height " << height << " and radius " << radius << " has a volume of " << pi<cpp_dec_float_100>() * height * radius * radius << endl;
}

//Compute the integral of cos(x) / (1+abs(x) using a left Riemann sum with a width of 0.001
//abs(sin(end)) is a placeholder you need to replace with the answer

void integral() {
	BIGFLOAT start = read("Please enter the start point of the integral:\n");
	BIGFLOAT end = read("Please enter the end point of the float:\n");
	const BIGFLOAT PRECISION = 1e-3;
	if (start >= end) {
		cout << "The starting point must be less than the ending point.\n";
		exit(0);
	}
	BIGFLOAT sum = 0;

	for (BIGFLOAT x = start; x <= end; x += PRECISION) {
		sum += cos(x) / (1 + abs(x));
	}
	sum *= PRECISION;
	cout << "The area under the curve of cos(x) / (1+abs(x)) from " << start << " to " << end << " is " << sum << endl;

}
