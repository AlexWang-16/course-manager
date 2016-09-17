//Name:Alex Wang
//Student# 118 540 152
//Email: awang63@myseneca.ca

#include <iostream>
#include <cstring>
#include "ScmApp.h"

using namespace sict;
using namespace std;

int main() {
	//Testing to see if an empty ScmApp is initalized to safe empty state. Expecting True.
	ScmApp a;
	 initSelfTest(a);
	 cout << endl;

	//Testing pause()
	 a.pauseTest();

	//Test Menu with character
	 a.menuTestChar();
	 cout << endl;
	 
	//Test Menu with number lower than selection range
	 a.menuTestNumericMin();
	 cout << endl;

	//Test Menu with number higher than selection range
	 a.menuTestNumericMax();
	 cout << endl;

	//Test Menu with number within range but not zero
	 a.menuTestNumericOK();
	 cout << endl;

	//Test Menu with input selection zero
	 a.menuTestNumericZero();
	 cout << endl;


	return 0;
}