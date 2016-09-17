//Name:Alex Wang
//Student# 118 540 152
//Email: awang63@myseneca.ca

#include <iomanip>
#include <string>
#include "Course.h"

using namespace std;
namespace sict {
	//Empty Constructor
	Course::Course() {
		setEmpty();
	}

	//4 Argument constructor
	Course::Course(const char* courseCode, const char* courseTitle, int credits, int studyLoad) {


		if (courseCode && strlen(courseCode) > 0 && courseTitle && courseTitle[0]
			&& credits > 0 && studyLoad > 0)
		{
			setCourseCode(courseCode);
			courseTitle_ = new char[strlen(courseTitle) + 1];
			setCourseTitle(courseTitle);
			setCredits(credits);
			setStudyLoad(studyLoad);

		}else {
			cout << "Error: Data validation failed. See Course 4 argument constructor for details." << endl << endl;
			setEmpty();
		}
	}

	//Copy Constructor
	Course::Course(const Course& src) {
		*this = src;
	}

	//Destructor
	Course::~Course() {
		delete[] courseTitle_;
	}

	//Validation
	bool Course::isEmpty() const{
		/* Return true to user if the Course object is in safe empty state */
		bool empty = false;

		if (courseCode_[0] == '\0' && courseTitle_ == nullptr
			&& credits_ == 0 && studyLoad_ == 0)
		{
			empty = true;
		}

		return empty;
	}

	// Setter Functions
	void Course::setEmpty() {
		/* Sets everything to safe empty state*/
		courseCode_[0] = '\0';
		courseTitle_ = nullptr;
		credits_ = 0;
		studyLoad_ = 0;
	}

	void Course::setCourseCode(const char* courseCode) {
		if (courseCode && strlen(courseCode) > 0) {
			strncpy(courseCode_, courseCode, MAX_COURSECODE_LEN);
			courseCode_[MAX_COURSECODE_LEN] = '\0';
		}
	}

	void Course::setCourseTitle(const char* courseTitle) {
		/* change the course title */
		if (courseTitle && courseTitle[0]) {
			int len = static_cast<int>(strlen(courseTitle));
			courseTitle_ = new char[len + 1];
			strncpy(courseTitle_, courseTitle, len);
			courseTitle_[len] = '\0';
		}
	}

	void Course::setCredits(int credits) {
		/* Set credits to the desired amount */
		if (credits > 0)
			credits_ = credits;
	}

	void Course::setStudyLoad(int studyLoad) {
		/* Set studyLoad_ to the desired amount */
		if (studyLoad > 0)
			studyLoad_ = studyLoad;
	}

	//Getter Functions
	const char* Course::getCourseCode() const {
		/* get course code and return it to user */
		return courseCode_;
	}

	const char* Course::getCourseTitle() const {
		/* gets course title and return it to user */
		return courseTitle_;
	}

	int Course::getCredits() const {
		/* gets credits and return it to user */
		return credits_;
	}

	int Course::getStudyLoad() const {
		/* gets study load and return it to user */
		return studyLoad_;
	}

	//Operator Overloads
	Course& Course::operator=(const Course& src) {
		if (!src.isEmpty()) {
			setCourseCode(src.courseCode_);
			courseTitle_ = new char[strlen(src.courseTitle_) + 1];
			setCourseTitle(src.courseTitle_);
			setCredits(src.credits_);
			setStudyLoad(src.studyLoad_);
		}
		else {
			setEmpty();
		}
		return *this;
	}

	bool Course::operator==(const char* courseCode) {
		/* overloading == operator to allow comparing of course codes */
		if (strcmp(courseCode_, courseCode) == 0) {
			return true;
		}
		else {
			return false;
		}

	}

	int Course::operator+=(int num) {
		/* overloading += operator to increase study load */
		return studyLoad_ += num;
	}

	//Self Testing
	void Course::initSelfTest(bool expectedFail) const {
		//Check to see if the object has failed to initialize.
		//Paramter default is true
		if (expectedFail) {
			if (isEmpty()) {
				cout << "Result: Pass!";
			}
			else {
				cout << "Result: Fail!";
			}
		}
		else {
			if (isEmpty()) {
				cout << "Result: Fail!";
			}
			else {
				cout << "Result: Pass!";
			}
		}
		cout << endl << endl;
	}


	//Display Functions
	void Course::displayStatus(const char* type) const {
		cout << "Test: " << type << endl;
		cout << setfill('-') << setw(30) << "-" << endl;
		if (isEmpty()) {
			cout << "Course is empty" << endl;
			cout << setw(PRINT_DASH_WIDTH) << setfill('-')  << "-" << endl;
		}
		else {
			cout << "Course Code: " << getCourseCode() << endl;
			cout << "Course Title: " << getCourseTitle() << endl;
			cout << "Credits: " << getCredits() << endl;
			cout << "studyLoad: " << getStudyLoad() << endl;
			cout << setw(PRINT_DASH_WIDTH) << setfill('-') << "-" << endl;
		}
	}

	ostream& Course::display(ostream& os) const {
		os <<  setfill(' ') << left << setw(MAX_COURSECODE_LEN) << getCourseCode() << " | ";
		os << setw(20) << left << getCourseTitle() << " | ";
		os << setw(6) << right << getCredits() << " | ";
		os << setw(4) << right << getStudyLoad() << " | ";
    os << setw(6) << setfill(' ') << " " << " | ";
    os << setw(4) << " " << " |";
		return os;
	}

	//file functions
	fstream& Course::load(fstream& fileStream) {
		/*Reads 1 record from the file and sets the current object's data members*/
		if (fileStream) {
			char courseCode[7] = "\0";
			string cTitle_str = "\0";
			char* courseTitle = nullptr;
			int credits = 0;
			int studyLoad = 0;
			int langLevel = 0;
			fileStream.getline(courseCode, sizeof(courseCode), ',');
			getline(fileStream, cTitle_str, ',');
			fileStream >> credits;
			fileStream.ignore();
			fileStream >> studyLoad;
			fileStream.ignore();
			fileStream >> langLevel;

			if (cTitle_str.length() > 1) {
				courseTitle = new char[cTitle_str.length() + 1];
				strncpy(courseTitle, cTitle_str.c_str(), cTitle_str.length());
				courseTitle[cTitle_str.length()] = '\0';
			}
			else {
				courseTitle = new char[5];
				strcpy(courseTitle, "none");
				courseTitle[4] = '\0';
			}

			setCourseCode(courseCode);
			setCourseTitle(courseTitle);
			setCredits(credits);
			setStudyLoad(studyLoad);
		}
		return fileStream;
	}

	fstream& Course::store(fstream& fileStream, bool addNewLine) const {
		if (fileStream) {
			fileStream << "," << getCourseCode() << "," << getCourseTitle() << "," << getCredits() << "," << getStudyLoad();

			if (addNewLine) {
				fileStream << endl;
			}
			else {
				cerr << "error: cannot open file for writing" << endl;
			}
		}
		return fileStream;
	}

	istream& Course::read(istream& is) {
		return is;
	}

	//Helper Functions
	ostream& operator<<(ostream& os, Course& src) {
		src.display(os);
		return os;
	}

	//Tester Helper functions
	void testSetter(const Course& src, char* course_code, char* course_title, int credits, int study_load) {
		cout << setfill('-') << setw(30) << "-" << endl;
		cout << "setCourseCode(): ";
		if (strcmp(src.getCourseCode(), course_code) == 0) {
			cout << "Pass" << endl;
		}
		else {
			cout << "Fail. Course code shows: " << src.getCourseCode() << " instead of " << course_code << endl;
		}

		cout << "setCourseTitle(): ";
		if (strcmp(src.getCourseTitle(), course_title) == 0)
		{
			cout << "Pass" << endl;
		}
		else {
			cout << "Fail. Course Title shows: " << src.getCourseTitle() << " instead of " << course_title<< endl;
		}

		cout << "setCredits(): ";
		if (src.getCredits() == credits) {
			cout << "Pass" << endl;
		}
		else {
			cout << "Fail. Credits shows " << src.getCredits() << " instead of " << credits << endl;
		}

		cout << "setStudyLoad(): ";
		if (src.getStudyLoad() == study_load) {
			cout << "Pass" << endl;
		}
		else {
			cout << "Fail. Study Load shows " << src.getStudyLoad() << "instead of " << study_load << endl;
		}
		cout << setfill('-') << setw(30) << "-" << endl;
		cout << setfill(' ');
		cout << endl;
	}
}
