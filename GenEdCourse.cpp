#include "GenEdCourse.h"
//Name:Alex Wang
//Student# 118 540 152
//Email: awang63@myseneca.ca

#include <iomanip>
#include <string>
#include <fstream>
#include "GenEdCourse.h"

using namespace std;
namespace sict {
	GenEdCourse::GenEdCourse() {
		langLevel_ = 0;
	}

	GenEdCourse::GenEdCourse(const char * courseCode, const char * courseTitle, int credits, int studyLoad, int langlvl) : Course(courseCode, courseTitle, credits, studyLoad)
	{
		if (langlvl > 0) {
			langLevel_ = langlvl;
		}
		else {
			cout << "Error: Lang level less than 1 detected. Check GenEdCourse five argument constructor for specification" << endl;
			cout << "langLevel_ set to 0" << endl << endl;

			langLevel_ = 0;
		}
	}

	//getter functions
	int GenEdCourse::getLangLevel() const {
		return langLevel_;
	}

	//setter functions
	void GenEdCourse::setLangLevel(int value) {
		if (value > 0) {
			langLevel_ = value;
		}
		else {
			cout << "error: language level must be a positive integer" << endl;
		}
	}

	//display functions
	ostream& GenEdCourse::display(ostream& os) const {
		char courseTitle[21];
		int courseTitleLen = static_cast<int> (strlen(getCourseTitle()));
		if (courseTitleLen > 20) {
			strncpy(courseTitle, getCourseTitle(), 20);
			courseTitle[20] = '\0';
		}
		os << setfill(' ') << left << setw(MAX_COURSECODE_LEN) << getCourseCode() << " | ";
		os << setw(20) << left << ((courseTitleLen > 20) ? courseTitle : getCourseTitle()) << " | ";
		os << setw(6) << right << getCredits() << " | ";
		os << setw(4) << right << getStudyLoad() << " | ";
		os << setw(6) << left << " " << " | ";
		os << setw(4) << right << getLangLevel() << " |";
		return os;
	}

	//streamable functions
	fstream& GenEdCourse::store(fstream& fileStream, bool addNewLine) const
	{
		if (fileStream) {
			fileStream << TYPE_GEN << "," << getCourseCode() << "," << getCourseTitle() << "," << getCredits() << "," << getStudyLoad() << "," << getLangLevel();

			if (addNewLine) {
				fileStream << endl;
			}
		}else{
			cerr << "error: cannot open file for writing" << endl;
		}
		
		return fileStream;
	}

	fstream& GenEdCourse::load(fstream& fileStream) {
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
      fileStream.ignore();

			if (cTitle_str.length() > 1) {
				courseTitle = new char[cTitle_str.length() + 1];
				strncpy(courseTitle, cTitle_str.c_str(), cTitle_str.length());
				courseTitle[cTitle_str.length()] = '\0';
			}
			else {
				courseTitle = new char[5];
				strcpy(courseTitle, "none");
				courseTitle[4] = '\0';
        cout << "GenEdCourse Error: load() cannot read from file." << endl;
        cout << strerror(errno) << endl;
        
			}

			setCourseCode(courseCode);
			setCourseTitle(courseTitle);
			setCredits(credits);
			setStudyLoad(studyLoad);
			setLangLevel(langLevel);
		}
		return fileStream;
	}

	istream& GenEdCourse::read(istream& istr) {
		char courseCode[MAX_COURSECODE_LEN + 1] = "\0";
		char* courseTitle = nullptr;
		string courseTitleInput;
		int credits = 0, studyLoad = 0, langLvl = 0;

		cout << "Course Code: ";
		istr.getline(courseCode, sizeof(courseCode));
		while (istr.fail()||strlen(courseCode) != 6) {
			cout << "Error: Course code must be 6 characters long" << endl << endl;
			if (istr.fail()) {
				istr.clear();
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
			getline(istr, courseTitleInput);
		}

		courseTitle = new char[courseTitleInput.length() + 1];
		strncpy(courseTitle, courseTitleInput.c_str(), courseTitleInput.length());
		courseTitle[courseTitleInput.length()] = '\0';

		cout << "Credits: ";
		istr >> credits;
		while (cin.fail() || credits < 1) {
			cout << "Error: Credits must be a positive integer" << endl;
			cin.clear();
			istr.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Credits: ";
			istr >> credits;
		}

		istr.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Study Load: ";
		istr >> studyLoad;
		while (cin.fail() || studyLoad < 1) {
			cout << "Error: study load must be a positive integer" << endl;
			istr.clear();
			istr.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Study Load: ";
			istr >> studyLoad;
		}

		//Clear buffer before reading the next requirement depending on course type
		istr.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Language Requirement: ";
		istr >> langLvl;
		while (istr.fail() || langLvl < 1) {
			cout << "Error: Language requirement must be a positive integer" << endl;
			istr.clear();
			istr.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Language Requirement: ";
			istr >> langLvl;
		}
		setCourseCode(courseCode);
		setCourseTitle(courseTitle);
		setCredits(credits);
		setStudyLoad(studyLoad);
		setLangLevel(langLvl);
		return istr;
	}


	//helper functions
	ostream& operator<<(ostream& os, const GenEdCourse& src) {
		src.display(os);
		return os;
	}

	//tester functions

	/*Test: see if empty constructor sets safe empty state properly*/
	void GenEdCourse::initSelfTest(bool expectedFail) const{
		cout << "Test: Empty constructor. Expecting langLevel: 0" << endl;
		cout << setw(PRINT_DASH_WIDTH) << setfill('-') << "-" << endl;
		if (getLangLevel() == 0) {
			cout << "Result: Pass" << endl;
		}
		else {
			cout << "Result: Fail" << endl;
		}
		cout << setw(PRINT_DASH_WIDTH) << setfill('-') << "-" << endl;
		cout << setw(' ');
	}

	/*Test: see if five argument constructor initalizes properly*/
	void GenEdCourse::fiveArgConstructorTest() const {
		char courseCode[7] = "btc140";
		char courseTitle[8] = "english";

		cout << "Test: Five argument constructor." << endl;
		cout << "Expecting langLevel : 2, credits : 1, study load : 1" << endl;
		cout << "course code: btc140, course title: english." << endl;
		cout << setw(PRINT_DASH_WIDTH) << setfill('-') << "-" << endl;

		if (getLangLevel() == 2 && getCredits() == 1 && getStudyLoad() == 1 && (strcmp(getCourseCode(), courseCode) == 0) && (strcmp(getCourseTitle(), courseTitle) == 0)) {
			cout << "Result: Pass" << endl;
		}
		else {
			cout << "Result: Fail" << endl;
			cout << "--Diagnostic data--" << endl;
			display(cout) << endl;
			cout << setw(PRINT_DASH_WIDTH) << setfill('-') << "-" << endl;
			cout << setfill(' ');
		}
	}
}
