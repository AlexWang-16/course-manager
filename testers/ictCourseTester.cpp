//Name:Alex Wang
//Student# 118 540 152
//Email: awang63@myseneca.ca

#include <iostream>
#include <cstring>
#include <fstream>
#include "ScmApp.h"
#include "Course.h"
#include "ICTCourse.h"

using namespace std;
using namespace sict;
int main() {
	///*Test: No argument constructor test. Expecting: matrix.*/
	//ICTCourse a;
	//a.noArgConstructorTest();
	//cout << endl;

	///*Test: 5 argument constructor test. Expecting: computer system to be zenit, course code: btp200, course title: C++, credits: 1, study load 1*/
	//ICTCourse b ("zenit", "btp200", "C++", 1, 1);
	//b.fiveArgConstructorTest("matrip", "btp200", "C++", 1, 1);

	//ICTCourse TL("zenit", "btc240abc", "communication", 2, 1);
	//TL.fiveArgConstructorTLTest("zenit", "btc240", "communication", 2, 1);
	//cout << endl;

	///*Test: cout an ICTCourse*/
	//ICTCourse seeout("zenit", "btc240", "communication", 2, 1);
	//cout << seeout;

	/* Test file write operation*/
	/*cout << "Test: File write operation." << endl;
	ICTCourse fwrite("zenit", "btc240", "communication", 2, 1);
	fstream file("test.txt", ios::in | ios::out | ios::trunc);
	cout << "Status: file opened..." << endl;
	fwrite.store(file, true);
	cout << "Running store function..." << endl;*/

	/* Test file read operation*/
	cout << "Test: File read operation." << endl;
	ICTCourse fread("btd210", "database", 3, 4, "matrix");
	fstream file1("test.txt", ios::out|ios::trunc);
	cout << "Status: File opened..." << endl;
	cout << "Writing new course data to file..." << endl;
	fread.store(file1,true);
	file1.close();
	file1.open("test.txt", ios::in);
	cout << "Reading course data back to file..." << endl;
 	fread.load(file1);
	cout << fread;
	cout << endl;

	return 0;
}