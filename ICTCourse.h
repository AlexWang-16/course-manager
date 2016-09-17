//Name:Alex Wang
//Student# 118 540 152
//Email: awang63@myseneca.ca
#ifndef SICT_ICTCOURSE_H
#define SICT_ICTCOURSE_H
#include "Course.h"

namespace sict {

	class ICTCourse : public Course {
		char computerSystem_[6 + 1];
	public:
		ICTCourse();
		ICTCourse(const char* courseCode, const char* courseTitle, int credits, int studyLoad, const char* compSystem);

		//getter functions
		const char* getComputersystem() const;
		
		//display functions
		virtual std::ostream& display(std::ostream& os) const;

		//setter functions
		void setComputerSystem(const char* value);
		
		//streamable functions
		 std::fstream& store(std::fstream& fileStream, bool addNewLine) const;
		 virtual std::fstream& load(std::fstream& fileStream);
		 virtual std::istream& read(std::istream& istr);

		//self-testing
		void noArgConstructorTest();
		void fiveArgConstructorTest(const char* compSystem, const char* courseCode, const char* courseTitle, int credits, int studyLoad);
		void fiveArgConstructorTLTest(const char* compSystem, const char* courseCode, const char* courseTitle, int credits, int studyLoad);
	};

	//helper functions
	ICTCourse& operator<< (std::ostream& os,  ICTCourse& src);
}
#endif