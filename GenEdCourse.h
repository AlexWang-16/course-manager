//Name:Alex Wang
//Student# 118 540 152
//Email: awang63@myseneca.ca
#ifndef SICT_GENEDCOURSE_H
#define SICT_GENEDCOURSE_H

#include<iostream>
#include "Course.h"
#include "general.h"
namespace sict {
	class GenEdCourse : public Course {
		int langLevel_;
	public:
		GenEdCourse();
		GenEdCourse(const char* courseCode, const char* courseTitle, int credits, int studyLoad, int langlvl);

		//getter functions
		int getLangLevel() const;

		//setter functions
		void setLangLevel(int value);

		//display function
		std::ostream& display(std::ostream& os) const;

		//streamable functions
    std::fstream& store(std::fstream& fileStream, bool addNewLine) const;
		virtual std::fstream& load(std::fstream& fileStream);
		virtual std::istream& read(std::istream& istr);

		//tester functions
		virtual void initSelfTest(bool = true)const;
		void fiveArgConstructorTest()const;
	};

	//helper functions
	std::ostream& operator<< (std::ostream& os, const GenEdCourse& src);
}
#endif