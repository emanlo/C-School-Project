// Name: Chi Fai Lo
// Seneca Student ID: 164450215
// Seneca email: clo36@myseneca.ca
// Date of completion: 24-March-23
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef _SDDS_STATION_H_
#define _SDDS_STATION_H_

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

namespace sdds {
	class Station
	{
	private:
		int m_stat_id = 0;
		string m_stat_name{};
		string m_stat_desc{};
		unsigned int m_stat_serialNum = 0;
		unsigned int m_stat_numItem = 0;
		static size_t m_widthField;
		static int id_generator;
	public:
		Station();
		~Station();
		Station(const string& record);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}

#endif // !_SDDS_STATION_H_
