// Name: Chi Fai Lo
// Seneca Student ID: 164450215
// Seneca email: clo36@myseneca.ca
// Date of completion: 24-March-23
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef _SDDS_UTILITIES_H_
#define _SDDS_UTILITIES_H_

#include <iostream>
#include <string>

using namespace std;

namespace sdds {
	class Utilities
	{
	private:
		size_t m_widthField = 1;
		static char m_delimiter;
	public:
		Utilities();
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};
}


#endif // !_SDDS_UTILITIES_H_
