//Name:Alex Wang
//Student# 118 540 152
//Email: awang63@myseneca.ca

#ifndef SICT_COURSE_H
#define SICT_COURSE_H

#include <iostream>
#include <cstring>
#include <limits>
#include "general.h"
#include "Streamable.h"

namespace sict{
	class Course : public Streamable{
		char courseCode_[MAX_COURSECODE_LEN + 1];
		char* courseTitle_;
		int credits_; //Num of credits this course provides
		int studyLoad_; //Num of assignments
	public:
		//constructors
		Course();
		Course(const char* courseCode, const char* courseTitle, int credits, int studyLoad);
		Course(const Course& src);
		
		//destructor
		virtual ~Course();

		//display functions
		void displayStatus(const char*) const;
		virtual std::ostream& display(std::ostream& os) const;

		//validation functions
		bool isEmpty() const;
		virtual void initSelfTest(bool = true) const;

		//getters
		const char* getCourseCode() const;
		const char* getCourseTitle() const;
		int getCredits() const;
		int getStudyLoad() const;

		//setters
		void setEmpty();
		void setCourseCode(const char*);
		void setCourseTitle(const char*);
		void setCredits(int);
		void setStudyLoad(int);

		//operator overloads
		Course& operator=(const Course& src);
		bool operator==(const char* courseCode);
		int operator+=(int num);

		//streamable functions
		virtual std::fstream& load(std::fstream& fileStream);
		virtual std::fstream& store(std::fstream& fileStream, bool addNewLine) const;
		virtual std::istream& read(std::istream& is);
	};
	
	//helper functions
	std::ostream& operator<<(std::ostream& os, Course& src);

	//tester helper functions
	void testSetter(const Course& src, char* course_code, char* course_title, int credits, int study_load);
}

#endif