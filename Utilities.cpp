// Name: Chi Fai Lo
// Seneca Student ID: 164450215
// Seneca email: clo36@myseneca.ca
// Date of completion: 24-March-23
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include "Utilities.h"

using namespace std;

namespace sdds {

	char Utilities::m_delimiter;

	Utilities::Utilities(){
		m_widthField = 1;
	}

	void Utilities::setFieldWidth(size_t newWidth)	{
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const	{
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more){
		string word;
		size_t pos_find = str.find(m_delimiter, next_pos);

		//If the string is empty / is the end, then throw a error
		if (pos_find == next_pos) {
			more = false;
			throw "error";
		}

		//If successful
		if (pos_find != string::npos) {
			word = str.substr(next_pos, pos_find - next_pos);
			//update next_pos with the position of the next token
			next_pos = pos_find + 1;
			more = true;
		}
		else{
			//Last Word
			word = str.substr(next_pos);
			more = false;
		}
		//updates the current object's m_widthField data member if its value is less than the size of the token.
		if (m_widthField < word.size()) setFieldWidth(word.size());

		//Clean the Space begin and end
		word.erase(0, word.find_first_not_of(' '));
		word.erase(word.find_last_not_of(' ') + 1);

		return word;
	}

	void Utilities::setDelimiter(char newDelimiter){
		Utilities::m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter(){
		return Utilities::m_delimiter;
	}



}