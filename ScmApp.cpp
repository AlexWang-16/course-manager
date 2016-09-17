//Name:Alex Wang
//Student# 118 540 152
//Email: awang63@myseneca.ca

#include <stdio.h>
#include <iomanip>
#include <ctype.h>
#include <string>
#include "ScmApp.h"
#include "GenEdCourse.h"
#include "ICTCourse.h"
#include "Course.h"
using namespace sict;
using namespace std;

namespace sict{
	/*constructors*/
	ScmApp::ScmApp()
	{
		setEmpty();
	}

	ScmApp::ScmApp(const char* filename){
		if (filename && strlen(filename) > 0) {
			setEmpty();
			strncpy(filename_, filename, 254);
			filename_[255] = 0;
		}
		else {
			cout << "Error: filename is nullptr or empty. Please check filename and try again. ScmApp now defaulting to safe empty state." << endl;
			setEmpty();
		}
	}
  
  /*destructor*/
  ScmApp::~ScmApp(){
    int i = 0;
    while (courseList_[i] != nullptr){
      delete courseList_[i];
      i++;
    }
  }

	/*setters*/
	void ScmApp::setEmpty() {
		/* Sets all data members to safe empty state */;
		for (int i = 0; i < MAX_NO_RECS; i++) {
			courseList_[i] = nullptr;
		}
		noOfCourses_ = 0;
		filename_ [0] = '\0';
	}

	/*validation funcitons*/
	bool ScmApp::isEmpty() const{
		/* Return true if the data members are in safe empty state*/
		bool courseListEmpty = true;
		bool noOfCoursesEmpty = (noOfCourses_ > 0) ? false : true;

		for (int i = 0; i < MAX_NO_RECS; i++) {
			if (courseList_[i] != nullptr) {
				courseListEmpty = false;
			}
		}
		cout << "courseList empty? " << courseListEmpty << endl;
		cout << "noOfCoursesEmpty? " << noOfCoursesEmpty << endl;
		cout << setw(PRINT_DASH_WIDTH) << setfill('-') << "-" << endl;
		return (courseListEmpty && noOfCoursesEmpty);
	}


	/*interface function*/
	int ScmApp::menu() {
		int input = -1;
		bool numValidate;

		cout << "Seneca Course Management Tool" << endl;
		cout << "1- List Courses" << endl;
		cout << "2- Display the details of a course" << endl;
		cout << "3- Add a course" << endl;
		cout << "4- Change the study load of course" << endl;
		cout << "5- Load courses from a file" << endl;
		cout << "6- Save courses to a file" << endl;
		cout << "0- Exit program" << endl;
		cin >> input;
		numValidate = cin.fail();
		if (numValidate) {
      cout << "Error: invalid menu entry" << endl;
      cout << "Input was " << input <<endl;
      input = -1;
      cin.clear();
		}
		else if (input < SCMAPP_MENU_MIN || input > SCMAPP_MENU_MAX) {
			input = -1;
		}

		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return input;
	}


	/*misc functions*/
	void ScmApp::pause() const{
		int i = 0;
		do {
			if (i != 0) {
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			cout << "Press enter to continue . . ."<< endl;
			i++;
		} while (cin.get() != '\n');
	}

	/*self tests*/
	void ScmApp::pauseTest() {
		cout << endl << "Test: pause() Test!" << endl;
		pause();
	}

	void initSelfTest(const ScmApp& src) {
		cout << "Test: Initaling an empty ScmApp object. Expecting object to be empty." << endl;
		cout << setw(PRINT_DASH_WIDTH) << setfill('-') << "-" << endl;
		if (src.isEmpty()) {
			cout << "Result: Pass!";
		}
		else {
			cout << "Result: Fail!";
		}
		cout << endl;
	}

	void ScmApp::listCourseTest() {
		listCourses();
	}

	void ScmApp::menuTestChar() {
		//Test to see if menu will return -1 to denote error if user enters a character
		int code = 0;
			cout << "Test: Manual Menu Test. Enter a character. Expected output: -1 " << endl;
		cout << setw(PRINT_DASH_WIDTH) << setfill('-') << "-" << endl;
		code = menu();
		cout << "Menu got " << code << endl;
		menuTestResult(code, -1);
	}

	void ScmApp::menuTestNumericMin() {
		//Test to see if menu returns -1 to denote error if user enters -1
		int code = 0;
		cout << "Test: Manual Menu Test. Enter -1. Expected output: -1 " << endl;
		cout << setw(PRINT_DASH_WIDTH) << setfill('-') << "-" << endl;
		code = menu();
		cout << "Menu got " << code << endl;
		menuTestResult(code, -1);
	}

	void ScmApp::menuTestNumericMax() {
		//Test to see if menu returns -1  if user enters a number greater than max selection available
		int code = 0;
		cout << "Test: Manual Menu Test. Enter a number > max selections. Expected output: -1 " << endl;
		cout << setw(PRINT_DASH_WIDTH) << setfill('-') << "-" << endl;
		code = menu();
		cout << "Menu got " << code << endl;
		menuTestResult(code, -1);
	}

	void ScmApp::menuTestNumericOK() {
		//Test to see if menu returns correct selection if user enters valid menu selection
		int code = 0;
		cout << "Test: Manual Menu Test - Entry within range. Select 2 from  the menu. Expected output: 2" << endl;
		cout << setw(PRINT_DASH_WIDTH) << setfill('-') << "-" << endl;
		code = menu();
		cout << "Menu got " << code << endl;
		menuTestResult(code, 2);
	}

	void ScmApp::menuTestNumericZero() {
		//Test to see if menu returns 0 when user wants to exit program
		int code = 0;
		cout << "Test: Manual Menu Test - Exit condition. Enter 0. Expected output: 0" << endl;
		cout << setw(PRINT_DASH_WIDTH) << setfill('-') << "-" << endl;
		code = menu();
		cout << "Menu got " << code << endl;
		menuTestResult(code, 0);

	}

	void ScmApp::menuTestResult(int input, int expected) {
		if (input == expected) {
			cout << "Result: Pass!" << endl;
		}
		else {
			cout << "Result: Fail!" << endl;
		}
	}

	void ScmApp::addCourseTest(int value) {
		for (int i = 0; i < value; i++) {
			courseList_ [i] = new ICTCourse("btp200", "c++", 1, 1, "matrix");
			noOfCourses_++;
		}
		listCourses();
	}

	void ScmApp::listCourses() const {
		cout << " Row |  Code  |     Course Title     | Credit | Load | System | Lang |" << endl;

		//Setting up dash lines under the headings
		cout << setw(5) << setfill('-') << "-" << "|"; //Row#
		cout << setw(8) << "-" << "|"; //Code
		cout << setw(22) << "-" << "|"; //Course Title
		cout << setw(8) << "-" << "|"; //Credit
		cout << setw(6) << "-" << "|"; //Load
		cout << setw(8) << "-" << "|"; // System
		cout << setw(6) << "-" << "|" << endl; // Langs
		cout << setfill(' ');

		for (int i = 1; i <= noOfCourses_; i++) {

			if (i % DISPLAY_LINES == 1 && i > 1) {
				/* Pause display every 10 lines displayed*/
				pause();
			}
			cout << setw(4) << right << i << " | ";
			cout << *courseList_[i - 1];
			cout << endl;
		}
		cout << setfill('-') << setw(70) << "-" << endl;
		cout << setfill(' ');
	}

	/*misc private function*/
	void ScmApp::listCoursesTest() {
		listCourses();
	}

	/*getter private functions*/
	int ScmApp::searchACourse(const char* courseCode) const{
		for (int i = 0; i < noOfCourses_; i++) {
			if (*courseList_[i] == (courseCode)) {
				return i;
			}
		}
		return -1;
	}

	/*setter private functions*/
	void ScmApp::changeStudyLoad(const char* courseCode) {
		//Note to self: it is Ok to have a negative study load number. It is used to decrease study load
		int index = searchACourse(courseCode);
		int studyLoadNum = 0;
		if (index == -1) {
			cout << "Not found!" << endl<< endl;
		}
		else {
			cout << "Please enter the amount of the study load: ";
			cin >> studyLoadNum;
			while (cin.fail()){
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "Please enter the amount of the study load: ";
				cin >> studyLoadNum;
			}
			*courseList_[index] += studyLoadNum;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << endl;
		}
	}
	void ScmApp::addCourse(int courseType) {
			/* Read in user input and store data to the appropriate class */

			if (noOfCourses_ < MAX_NO_RECS) {
				switch (courseType) {
					case 1:
						courseList_[noOfCourses_] = new ICTCourse();
						courseList_[noOfCourses_]->read(cin);
						break;
					case 2:
						courseList_[noOfCourses_] = new GenEdCourse();
						courseList_[noOfCourses_]->read(cin);
						break;
				}
				noOfCourses_++;
			}

			cout << endl;
			//Clear buffer before returning to main menu
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

	/*file private functions*/
	void ScmApp::loadRecs() {
		char courseType = { 0 };
		datafile_.open(filename_, ios::in);
		if (datafile_.fail()) {
			datafile_.clear();
			datafile_.close();
		}
		else {
			for (int j = 0; j < noOfCourses_; j++) {
				delete courseList_[j];
			}

			while (!datafile_.eof() && !datafile_.fail()) {
			datafile_.get(courseType);
				if (courseType == 'G') {
					//Initialize GenEdCourse
					datafile_.ignore();//getting rid of the ","
					courseList_ [noOfCourses_] = new GenEdCourse ();
					courseList_[noOfCourses_]->load(datafile_);
          noOfCourses_++;
				}
				else if (courseType == 'I') {
					//Initialize ICTCourse
					datafile_.ignore(); //getting rid of the ","
					courseList_[noOfCourses_] = new ICTCourse();
					courseList_[noOfCourses_]->load(datafile_);
          noOfCourses_++;
				}
				else if (courseType == ','){
					//Regular course
					courseList_[noOfCourses_] = new Course();
					courseList_[noOfCourses_]->load(datafile_);
          noOfCourses_++;
        }
        else{
          cerr << "Error: Data file is empty or invalid. No courses to read." << endl;
        }
			}
		}
		datafile_.close();
	}

	void ScmApp::saveRecs() {
		datafile_.open(filename_, ios::out | ios::trunc);
		if (datafile_.fail()) {
			datafile_.clear();
			datafile_.close();
		}else{
			for (int i = 0; i < noOfCourses_; i++) {
        if (i < (noOfCourses_ - 1)){
          courseList_[i]->store(datafile_, true);
        }
				else{
					courseList_[i]->store(datafile_, false);
				}
			}
		}
		datafile_.close();
	}

	/*misc function*/
	int ScmApp::run() {
		int selection = -1;
		int counter = 0;
		do{
			if (counter > 0) {
				cout << endl;
			}
			selection = menu();
			switch (selection) {
			case 1:
				//menu: list courses
				listCourses();
				break;
			case 2:
			{
				//menu: search a course
				cout << "Please enter course code: ";
				char theCourse[7];
				cin.getline(theCourse, sizeof(theCourse));
				int result = searchACourse(theCourse);
				if (result == -1) {
					cout << "Not Found!" << endl << endl;
				}
				else {
					cout << *courseList_[result] << endl;;
				}
			}
				break;
			case 3:
			{
				//menu: adding a course
				int courseType = 0;

				cout << "Please enter the course type (1-ICT or 2-GenEd): ";
				cin >> courseType;
				while (cin.fail() || courseType < 0 || courseType > 2) {
					cout << "Error: Course type must be 1-ICT or 2-GenEd" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Please enter the course type (1-ICT or 2-GenEd): ";
					cin >> courseType;
				}
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				addCourse(courseType);
			}
				break;
			case 4:
			{
				//menu: change study load
				cout << "Please enter the course code: ";
				char theCourse[7];
				cin.getline(theCourse, sizeof(theCourse));
				changeStudyLoad(theCourse);
			}
				break;
			case 5:
				//menu: load records
				loadRecs();
				break;
			case 6:
				//menu: save records
          if (courseList_ [0]!= nullptr){
            saveRecs();
          }else{
            cerr << "Error: You have no course(s) at the moment to store. Please insert a course first." << endl;
          }
				break;
			case 0:
				//menu: exit program
				cout << "Goodbye!!";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				return 0;
			}
			counter++;
		} while (selection != 0);
		return 0;
	}
}
