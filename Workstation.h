// Name: Chi Fai Lo
// Seneca Student ID: 164450215
// Seneca email: clo36@myseneca.ca
// Date of completion: 24-March-23
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef _SDDS_WORKSTATION_H_
#define _SDDS_WORKSTATION_H_

#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

using namespace std;

namespace sdds {
	//Global Variable
	extern deque<CustomerOrder> g_pending;
	extern deque<CustomerOrder> g_completed;
	extern deque<CustomerOrder> g_incomplete;

	class Workstation : public Station
	{
	private:
		deque<CustomerOrder> m_order;
		Workstation* m_pNextStation = nullptr;
	public:
		Workstation();
		Workstation(const std::string& line);
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
	};
}

#endif // !_SDDS_WORKSTATION_H_
