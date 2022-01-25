
#include "/public/read.h" //Kerney's rad input library
#include <stack>
#include <boost/multiprecision/cpp_int.hpp> //Bigint
#include <boost/multiprecision/cpp_dec_float.hpp> //Bigfloat
#include <boost/multiprecision/miller_rabin.hpp> //Prime testing
#include <boost/math/constants/constants.hpp> //Has pi
using namespace std;
using namespace boost::random;
using namespace boost::multiprecision;

//You must write these functions
void generate();
void encode();
void decode();
void encrypt();
void decrypt();

int main()
{
	//TUTORIAL
	//This is how you make a bigint
	//cpp_int x("324234233423432422344"); //Arbitrary precision integer

	cout << "Welcome to RSA CSCI 26!\n";
	cout << "Pick an option:\n" <<
		"0. Generate Primes\n" <<
		"1. Encode a string\n" <<
		"2. Decode a string\n" <<
		"3. Encrypt a string\n" <<
		"4. Decrypt a string\n" <<
		"(Anything else to quit)\n";
	auto choice = read_opt<int>(); //Requires --std=c++17 to compile
	if (!choice) exit(0);
	else if (choice == 0) generate();
	else if (choice == 1) encode();
	else if (choice == 2) decode();
	else if (choice == 3) encrypt();
	else if (choice == 4) decrypt();
	else exit(0);
}

//Computes modular inverse given T and E
//Credit - http://stackoverflow.com/questions/12826114/euclids-extended-algorithm-c
cpp_int calculate_inverse(cpp_int t, cpp_int e) {
	cpp_int a,b,q,x,lastx,y,lasty,temp,temp1,temp2,temp3;
	a = t;
	b = e;
	if (b>a) {//we switch them
		swap(b,a);
	}

	x=0;
	y=1;
	lastx=1;
	lasty=0;
	while (b!=0) {
		q= a/b;
		temp1= a%b;
		a=b;
		b=temp1;

		temp2=x;
		x=lastx-q*x;
		lastx=temp2;

		temp3=y;
		y=lasty-q*y;
		lasty=temp3;
	}

	while (lasty < 0) lasty += t;
	return lasty;
}

cpp_int findPrime(cpp_int num) {
	const int NUM_OF_TRIALS = 100;
	bool isPrime = miller_rabin_test(num, NUM_OF_TRIALS);
	while (!isPrime) {
		if (num <= 2 && num >= 0) num+=1;
		else if (num % 2 == 0) num += 1;
		else num += 2;
		isPrime = miller_rabin_test(num, NUM_OF_TRIALS);
//		cout << boolalpha << isPrime << endl;
	}
	return num;
}

//Generate P and Q, the two primes used to make your private key
void generate() {
	cpp_int p,q,e,n,t,d;
	p = read<cpp_int>("Please enter the first number you want to start looking for primes at:\n");
	q = read<cpp_int>("Please enter the second number you want to start looking for primes at:\n");
	//YOU: Find the first prime >= p and q
	p = findPrime(p);
	q = findPrime(q);
	cout << "P: " << p << endl;
	cout << "Q: " << q << endl;
	//YOU: Using P and Q, compute the RSA numbers.
	n = p * q;
	//E is done for you
	if (n > 65537) e = 65537;
	else if (n > 17) e = 17;
	else if (n > 7) e = 7;
	else e = 3;

	t = (p - 1) * (q - 1);
	d = calculate_inverse(t,e);
	cout << "E: " << e << endl;
	cout << "N: " << n << endl;
	cout << "T: " << t << endl;
	cout << "D: " << d << endl;
}

//Convert an ASCII into a bigint
void encode() {
	string s = readline("What string would you like to encode?\n");
	cpp_int result = 0;
	//YOU: encode the string here
	cout << "M:\n";
	for (size_t i = 0; i < s.size(); i++) {
		result += int(s[i]);
		if (i < s.size() - 1)
			result <<= 8;
	}
	cout << result << endl;
}

//Convert a bigint into an ASCII string
void decode() {
	cpp_int x = read("What int would you like to decode?\n");
	stack<char> stack_of_letters;
	string retval;
	//YOU: Decode x into the string retval here
	cout << "Your message is:\n";
	while (x != 0) {
//		cout << char(x % 256) << endl;
		stack_of_letters.push(char(x%256));
		x >>= 8;
	}

	while (stack_of_letters.size()) {
		retval += stack_of_letters.top();
		stack_of_letters.pop();
	}
	cout << retval << endl;
}

void encrypt() {
	cpp_int e = read("Please enter E:\n");
	cpp_int n = read("Please enter N:\n");
	cpp_int m = read("Please enter M:\n");
	if (m > n) {
		cout << "Sorry, M cannot be bigger than N.\n";
		exit(1);
	}
	cout << "S:\n";
	cpp_int s = powm(m,e,n);
	//YOU: Do RSA encrypt here, should be one line of code
	cout << s << endl;
}

void decrypt() {
	cpp_int d = read("Please enter D:\n");
	cpp_int n = read("Please enter N:\n");
	cpp_int s = read("Please enter S:\n");
	if (s > n) {
		cout << "Sorry, S cannot be bigger than N.\n";
		exit(1);
	}
	cout << "M:\n";
	cpp_int m = powm(s,d,n);
	//YOU: Do RSA decrypt here, should be one line of code
	cout << m << endl;
}
