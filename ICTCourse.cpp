//Name:Alex Wang
//Student# 118 540 152
//Email: awang63@myseneca.ca

#include <iostream>
#include <iomanip>
#include <string>
#include <cerrno>
#include "ICTCourse.h"

using namespace std;
using std::strerror;
namespace sict {
	//empty constructor
	ICTCourse::ICTCourse() {
		strncpy(computerSystem_, "matrix",6);
		computerSystem_[6] = '\0';
	}

	//One Argument constructor
	ICTCourse::ICTCourse(const char* courseCode, const char* courseTitle, int credits, int studyLoad, const char* compSystem) : Course (courseCode, courseTitle, credits, studyLoad) {
		strncpy(computerSystem_, compSystem, MAX_COMPUTERSYSTEM_LEN);
		computerSystem_[6] = '\0';
	}

	ostream& ICTCourse::display(ostream& os) const {
		char courseTitle[21];
		int courseTitleLen = static_cast<int>(strlen(getCourseTitle()));
		if (courseTitleLen > 20) {
			strncpy(courseTitle, getCourseTitle(), 20);
			courseTitle[20] = '\0';
		}
		 
		os << setfill(' ') << left << setw(MAX_COURSECODE_LEN) << getCourseCode() << " | ";
		os << setw(20) << left << ((courseTitleLen > 20)? courseTitle:getCourseTitle()) << " | ";
		os << setw(6) << right << getCredits() << " | ";
		os << setw(4) << right << getStudyLoad() << " | ";
		os << setw(6) << left << getComputersystem() << " | ";
		os << setw(5) << setfill(' ') << " " << "|"; // finishing touches to the display menu
		return os;
	}

	//getter functions
	const char* ICTCourse::getComputersystem() const {
		return computerSystem_;
	}
	
	
	//setter functions
	void ICTCourse::setComputerSystem(const char* value) {
		strncpy(computerSystem_, value, MAX_COMPUTERSYSTEM_LEN);
		computerSystem_ [MAX_COMPUTERSYSTEM_LEN] = 0;
	}

	//streamable functions
	fstream& ICTCourse::store(fstream& fileStream, bool addNewLine) const {

		if (fileStream) {
			fileStream << TYPE_ICT << "," << getCourseCode() << "," << getCourseTitle() << "," << getCredits() << "," << getStudyLoad() << "," << getComputersystem();

			if (addNewLine) {
				fileStream << endl;
			}
		}else{
			cerr << "Error: Cannot open file for writing." << endl;
		}
		return fileStream;
	}
	
	fstream& ICTCourse::load(fstream& fileStream) {
		/*Reads 1 record from the file and sets the current object's data members*/
		if (!fileStream.fail()) {
			char courseCode[7] = "\0";
			string cTitle_str = "\0";
			char* courseTitle = nullptr;
			int credits = 0;
			int studyLoad = 0;
			char compSys[7] = "\0";
			fileStream.getline(courseCode, sizeof(courseCode), ',');
			getline(fileStream, cTitle_str, ',');
			fileStream >> credits;
			fileStream.ignore();
			fileStream >> studyLoad;
			fileStream.ignore();
			fileStream.getline(compSys, sizeof(compSys));
		

			if (cTitle_str.length() > 1) {
				courseTitle = new char[cTitle_str.length()+1];
				strncpy(courseTitle, cTitle_str.c_str(), cTitle_str.length());
				courseTitle[cTitle_str.length()] = '\0';
      }else {
				courseTitle = new char[5];
				strcpy(courseTitle, "none");
				courseTitle[4] = '\0';
			}

			setCourseCode(courseCode);
			setCourseTitle(courseTitle);
			setCredits(credits);
			setStudyLoad(studyLoad);
			setComputerSystem(compSys);
		}
		return	fileStream;
	}

	istream& ICTCourse::read(std::istream& istr) {
		char courseCode[MAX_COURSECODE_LEN + 1] = "\0";
		char compSystem[MAX_COURSECODE_LEN + 1] = "\0";
		char* courseTitle = nullptr;
		string courseTitleInput;
		int credits = 0, studyLoad = 0;

		cout << "Course Code: ";
		istr.getline(courseCode, sizeof(courseCode));
		while (istr.fail() || strlen(courseCode) != 6) {
			cout << "Error: Course code must be 6 characters long" << endl << endl;
			if (istr.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			
			cout << "Course Code: ";
			istr.getline(courseCode, sizeof(courseCode));
		}

		cout << "Course title: ";
		getline(istr, courseTitleInput);
		while (courseTitleInput.length() < 1) {
			cout << "Error: Course title cannot be empty" << endl;
			cout << "Course title: ";
			getline(cin, courseTitleInput);
		}

		courseTitle = new char[courseTitleInput.length() + 1];
		strncpy(courseTitle, courseTitleInput.c_str(), courseTitleInput.length());
		courseTitle[courseTitleInput.length()] = '\0';

		cout << "Credits: ";
		cin >> credits;
		while (istr.fail() || credits < 1) {
			cout << "Error: Credits must be a positive integer" << endl;
			istr.clear();
			istr.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Credits: ";
			istr >> credits;
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Study Load: ";
		cin >> studyLoad;
		while (istr.fail() || studyLoad < 1) {
			cout << "Error: study load must be a positive integer" << endl;
			istr.clear();
			istr.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Study Load: ";
			istr >> studyLoad;
		}

		//Clear buffer before reading the next requirement depending on course type
		istr.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Computer System: ";
		istr.get(compSystem, 7, '\n');
		while (cin.fail() || strlen(compSystem) < 1) {
			istr.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error: Computer System cannot be empty" << endl << endl;
			cout << "Computer System: ";
			istr.get(compSystem, 7, '\n');
		}

		setCourseCode(courseCode);
		setCourseTitle(courseTitle);
		setCredits(credits);
		setStudyLoad(studyLoad);
		setComputerSystem(compSystem);
		return istr;
	}

	//self-testing functions
	void ICTCourse::noArgConstructorTest() {
		cout << "Test: No argument constructor test. Expecting: matrix." << endl;
		cout << setw(PRINT_DASH_WIDTH) << setfill('-') << "-" << endl;
		cout << "computerSystem_: " << computerSystem_ << endl;
		if (strcmp(computerSystem_, "matrix") == 0) {
			cout << "Result: Pass" << endl;
		}else{
			cout << "Result: Fail" << endl;
		}
	}
	
	void ICTCourse::fiveArgConstructorTest(const char* compSystem, const char* courseCode, const char* courseTitle, int credits, int studyLoad) {
		cout << "Test: Five argument constructor test." << endl;
		cout << "Expecting: computerSystem_ : matrip, courseCode_ : btp200, courseTitle_: C++, credit_: 1, studyLoad_ : 1." << endl;
		cout << setw(PRINT_DASH_WIDTH) << setfill('-') << "-" << endl;
		
		ICTCourse fiveArgs(courseCode, courseTitle, credits, studyLoad, compSystem);
		strncpy(computerSystem_, compSystem, sizeof(computerSystem_));
		if (strcmp(computerSystem_, "matrip") != 0) {
			cout << "Result: Fail. computerSystem_ was " << computerSystem_ << endl <<endl;
		}
		else if (strcmp(fiveArgs.getCourseCode(), "btp200") != 0) {
			cout << "Result: Fail. courseCode_ was " << fiveArgs.getCourseCode() << endl;
		}
		else if (strcmp(fiveArgs.getCourseTitle(), "C++") != 0) {
			cout << "Result: Fail. courseTitle_ was " << fiveArgs.getCourseTitle() << endl;
		}
		else if (fiveArgs.getCredits() != 1) {
			cout << "Result: Fail. credit_ was " << fiveArgs.getCredits();
		}
		else if (fiveArgs.getStudyLoad() != 1) {
			cout << "Result: Fail. studyLoad_ was " << fiveArgs.getStudyLoad();
		}
		else{
			cout << "Result: Pass" << endl;
		}
		cout << endl;
	}

	void ICTCourse::fiveArgConstructorTLTest(const char* compSystem, const char* courseCode, const char* courseTitle, int credits, int studyLoad) {
		cout << "Test: Five argument constructor test." << endl;
		cout << "Expecting: computerSystem_: zenit, courseCode_: btc240" << endl;
		cout << "courseTitle_: communication credit_: 2, studyLoad_: 1" <<endl;
		cout << setw(PRINT_DASH_WIDTH) << setfill('-') << "-" << endl;

		ICTCourse fiveArgs(courseCode, courseTitle, credits, studyLoad, compSystem);
		strncpy(computerSystem_, compSystem, sizeof(computerSystem_));
		if (strcmp(computerSystem_, "zenit") != 0) {
			cout << "Result: Fail. computerSystem_ was " << computerSystem_ << endl << endl;
		}
		else if (strcmp(fiveArgs.getCourseCode(), "btc240") != 0) {
			cout << "Result: Fail. courseCode_ was " << fiveArgs.getCourseCode() << endl;
		}
		else if (strcmp(fiveArgs.getCourseTitle(), "communication") != 0) {
			cout << "Result: Fail. courseTitle_ was " << fiveArgs.getCourseCode() << endl;
		}
		else if (fiveArgs.getCredits() != 2) {
			cout << "Result: Fail. credit_ was " << fiveArgs.getCredits();
		}
		else if (fiveArgs.getStudyLoad() != 1) {
			cout << "Result: Fail. studyLoad_ was " << fiveArgs.getStudyLoad();
		}
		else {
			cout << "Result: Pass" << endl;
		}
		cout << endl;
	}
	
	//helper functions
	ICTCourse& operator<<(ostream& os, ICTCourse& src) {
		src.display(os);
		return src;
	}
	
}