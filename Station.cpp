// Name: Chi Fai Lo
// Seneca Student ID: 164450215
// Seneca email: clo36@myseneca.ca
// Date of completion: 24-March-23
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include "Station.h"
#include "Utilities.h"

using namespace std;

//The maximum number of characters required to print to the screen the item name for any object of type Station
//a variable used to generate IDs for new instances of type Station

namespace sdds {
	size_t Station::m_widthField = 0;
	int Station::id_generator = 0;

	Station::Station(){}

	Station::~Station(){}

	Station::Station(const string& record) {
		////Uses a Utilities object to extract each token from the record
		Utilities tmpUtil;
		//Variable for the token function
		size_t next_pos = 0;
		bool remain = true;

		//Extracts name, starting serial number, and quantity
		m_stat_name = tmpUtil.extractToken(record, next_pos, remain);
		if (remain) m_stat_serialNum = stoi(tmpUtil.extractToken(record, next_pos, remain));
		if (remain) m_stat_numItem = stoi(tmpUtil.extractToken(record, next_pos, remain));

		//before extracting description
		//Updates Station::m_widthField to the maximum value of Station::m_widthField and Utilities::m_widthField
		if (Station::m_widthField < tmpUtil.getFieldWidth()) Station::m_widthField = tmpUtil.getFieldWidth();
		if (remain) m_stat_desc = tmpUtil.extractToken(record, next_pos, remain);
		//Add the ID into the order
		m_stat_id = ++Station::id_generator;
	}

	const std::string& Station::getItemName() const{
		return m_stat_name;
	}

	size_t Station::getNextSerialNumber(){
		//returns the next serial number to be used on the assembly line and increments m_serialNumber
		return m_stat_serialNum++;
	}

	size_t Station::getQuantity() const{
		//returns the remaining quantity of items in the Station
		return m_stat_numItem;
	}

	void Station::updateQuantity(){
		//subtracts 1 from the available quantity; should not drop below 0.
		if (m_stat_numItem > 0) m_stat_numItem--;
	}

	void Station::display(std::ostream& os, bool full) const {
		//If False
		//inserts only the ID, name, and serial number in the format: ID | NAME | SERIAL |
		os << setw(3) << right << setfill('0') << m_stat_id << " | ";
		os.fill(' '); //Reset the setfill
		os << setw(m_widthField) << left << m_stat_name << " | ";
		os << setw(6) << setfill('0') << right << m_stat_serialNum << " | ";

		//If true Inserts the information in the following format: ID | NAME | SERIAL | QUANTITY | DESCRIPTION
		if (full) {
			os.fill(' ');
			os << setw(4) << right << m_stat_numItem << " | " << m_stat_desc;
		}

		os << endl;
	}
}