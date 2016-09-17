//Name:Alex Wang
//Student# 118 540 152
//Email: awang63@myseneca.ca

#include <iostream>
#include <iomanip>
#include "GenEdCourse.h"
using namespace sict;
using namespace std;
int main() {
	
	/*Test: testing empty constructor*/
	/*GenEdCourse a;
	a.initSelfTest();
	cout << endl;*/

	/*Test: testing five argument constructor for proper initialization*/
	/*GenEdCourse b("btc140", "english", 1, 1, 2);
	b.fiveArgConstructorTest();
	cout << endl;*/

	/*Test: Printing a GenEdCourse*/
	/*cout << "Test: Displaying a GenEdCourse" << endl;
	cout << setw(PRINT_DASH_WIDTH) << setfill('-') << "-" << endl;
	cout << b << endl;
	cout << setw(PRINT_DASH_WIDTH) << setfill('-') << "-" << endl << endl;
	return 0;*/

	/* Test file read operation*/
	cout << "Test: File read operation." << endl;
	GenEdCourse fread("btc", "communication", 2, 3, 2);
	fstream file1("test.txt", ios::in|ios::out | ios::trunc);
	cout << "Status: File opened..." << endl;
	cout << "Writing new course data to file..." << endl;
	fread.store(file1, true);
	file1.close();
	file1.open("test.txt", ios::in);
	cout << "Reading course data back to file..." << endl;
	fread.load(file1);
	cout << fread << endl;

}