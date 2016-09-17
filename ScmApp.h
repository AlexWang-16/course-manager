//Name:Alex Wang
//Student# 118 540 152
//Email: awang63@myseneca.ca

#ifndef SICT_SCMAPP_H
#define SICT_SCMAPP_H

#include "Course.h"
namespace sict {
	class ScmApp {
		Course* courseList_[MAX_NO_RECS];
		int noOfCourses_;
		char filename_[256];
		std::fstream datafile_;

	private:
		//misc private functions
		void pause() const;
		int menu();
		void listCourses() const;
		
		//getter private functions
		int searchACourse(const char* courseCode) const;
		
		//setter private functions
		void changeStudyLoad(const char* courseCode);
		void addCourse(int courseType);
		void setEmpty();

		//file functions
		void loadRecs();
		void saveRecs();

	public:
		//constructors
		ScmApp();
		ScmApp(const char* filename);
		ScmApp(const ScmApp& src) = delete;
    
    //destructor
    ~ScmApp();

		//disabled member operator
		ScmApp& operator=(const ScmApp& src) = delete;
		
		//validation functions
		bool isEmpty() const;
		void pauseTest();
		void listCourseTest();
		void menuTestChar();
		void menuTestNumericMin();
		void menuTestNumericMax();
		void menuTestNumericOK();
		void menuTestNumericZero();
		void listCoursesTest();
		void menuTestResult(int input, int expected);
		void addCourseTest(int value);

		//misc functions
		int run();
		
		
	};

	void initSelfTest(const ScmApp& src);
	
}

#endif