#include <iostream>
#include "Course.h"

using namespace sict;
using namespace std;
int main() {
	//Initializing Empty constructor
	Course a;
	a.displayStatus("Empty Constructor");
	a.initSelfTest();

	/*Trying to add items to an empty constructor to see if 
	all setters work*/
	char aaa001 [7] = "AAA001";
	char communication[14] = "Communication";
	cout << "Testing Adding a course from an empty constructed course." << endl;
	a.setCourseCode("AAA001");
	a.setCourseTitle("Communication");
	a.setCredits(1);
	a.setStudyLoad(1);
	testSetter(a, aaa001, communication, 1, 1);

	//Initilaizing a 4 argument constructor. Expecting BTP 200, C++ , 1, 1 course.
	Course fourArgument("BTP200", "C++", 1, 1);
	fourArgument.displayStatus("4 Argument Constructor");
	fourArgument.initSelfTest(false);

	//Initialzing a course with no credit. Expecting: empty Course.
	Course fourArgument_noCredit("BTP200", "C++", 0, 1);
	fourArgument_noCredit.displayStatus("4 Argument Constructor w/ no credit");
	fourArgument_noCredit.initSelfTest();

	//Initializing a course with negative credits. Expecting empty course.
	Course fourArgument_negCredit("BTP200", "C++", -1, 1);
	fourArgument_negCredit.displayStatus("4 Argument Constructor w/ negative credit");
	fourArgument_negCredit.initSelfTest();

	//Initalzing a course with no studyLoad. Expecting: empty Course.
	Course fourArgument_noStudyLoad("BTP200", "C++", 1, 0);
	fourArgument_noStudyLoad.displayStatus("4 Argument Constructor w/ no studyLoad");
	fourArgument_noStudyLoad.initSelfTest();

	//Initialzing a course with negative studyLoad
	Course fourArgument_negStudyLoad("BTP200", "C++", 1, -1);
	fourArgument_negStudyLoad.displayStatus("4 Argument Constructor w/ negative studyLoad");
	fourArgument_negStudyLoad.initSelfTest();

	//Initialzing a course with nullptr as course code. Expecting: empty course
	Course fourArgument_nullCourseCode(nullptr, "C++", 1, 1);
	fourArgument_nullCourseCode.displayStatus("4 Argument Constructor w/ nullptr course code");
	fourArgument_nullCourseCode.initSelfTest();

	//Initalzing a course with empty string as course code. Expecting: empty course.
	Course fourArgument_emptyCourseCode("", "C++", 1, 1);
	fourArgument_emptyCourseCode.displayStatus("4 Argument constructor with empty course code");
	fourArgument_emptyCourseCode.initSelfTest();

	//Initialzing a course with nullptr for course title. Expecting: empty course.
	Course fourArgument_nullCourseTitle("BTP200", nullptr, 1, 1);
	fourArgument_nullCourseTitle.displayStatus("4 Argument Constructor w/ nullptr course title");
	fourArgument_nullCourseTitle.initSelfTest();

	//Intialzing a course with empty course title. Expecting: empty course.
	Course fourArgument_emptyCourseTitle("BTP200", "", 1, 1);
	fourArgument_emptyCourseTitle.displayStatus("4 Argument Constructor w/ empty course title");
	fourArgument_emptyCourseTitle.initSelfTest();

	//Testing "=" operator
	Course equalOperator("BTD220", "Database", 1, 1);
	Course equalOperatorCopy = equalOperator;
	cout << "Testing \"=\" operator. Expecting course code: BTD220, course title: Database, credits: 1, study load: 1." << endl;
	if (strcmp(equalOperatorCopy.getCourseCode(), "BTD220") != 0) {
		cout << "Result: Fail. Course code was " << equalOperatorCopy.getCourseCode() << endl;
	}
	else if (strcmp(equalOperatorCopy.getCourseTitle(), "Database") != 0) {
		cout << "Result: Fail. Course title was " << equalOperatorCopy.getCourseTitle() << endl;
	}
	else if (equalOperatorCopy.getCredits() != 1) {
		cout << "Result: Fail. Credits was " << equalOperatorCopy.getCredits() << endl;
	}
	else if (equalOperatorCopy.getStudyLoad() != 1) {
		cout << "Result: Fail. Study load was " << equalOperatorCopy.getStudyLoad() << endl;
	}
	else {
		cout << "Result: Pass" << endl;
	}
	cout		<< endl;

	//Testing "==" operator. Expecting: True
	Course cmpOperator("BTD210", "Database", 2, 2);
	cmpOperator.displayStatus("== Operator test. Expecting result to be true.");
	if (cmpOperator == "BTD210") {
		cout << "Result: Pass!" << endl << endl;
	}
	else {
		cout << endl << "Result: Failed!" << endl << endl;
	}

	//Test "+=" operator w/ positive number. Expecting: 3
	Course plusEqualOperator("BTD210", "Database", 1, 2);
	plusEqualOperator += 1;
	plusEqualOperator.displayStatus("+= operator w/ positive num. Expecting studyLoad = 3");
	if (plusEqualOperator.getStudyLoad() == 3)
		cout << "Result: Pass!" << endl << endl;
	else
		cout << "Result: Failed!" << endl << endl;

	//Test "+=" operator w/ positive number. Expecting: 2
	Course negPlusEqualOperator("BTD210", "Database", 1, 3);
	negPlusEqualOperator += -1;
	negPlusEqualOperator.displayStatus("+= operator w/ negative num. Expecting studyLoad = 2");
	if (negPlusEqualOperator.getStudyLoad() == 2)
		cout << "Result: Pass!" << endl << endl;
	else
		cout << "Result: Failed!" << endl << endl;

	//Testing display function. CourseTitle should truncate after "CS" of CSS
	Course displayTest("BTI220", "JavaScript, HTML, CSS internet web", 1, 1);
	cout << displayTest;
	
	return 0;
}

