// Name: Chi Fai Lo
// Seneca Student ID: 164450215
// Seneca email: clo36@myseneca.ca
// Date of completion: 24-March-23
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.#pragma once

#ifndef _SDDS_LINEM_H_
#define _SDDS_LINEM_H_

#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <deque>
#include <vector>
#include "Station.h"
#include "CustomerOrder.h"
#include "Workstation.h"
#include "Utilities.h"

using namespace std;

namespace sdds {

	class LineManager
	{
	private:
		std::vector<Workstation*> m_activeLine;
		size_t m_cntCustomerOrder = 0;
		Workstation* m_firstStation = nullptr;
	public:
		LineManager();
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void reorderStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;
	};

}

#endif // !_SDDS_LINEM_H_