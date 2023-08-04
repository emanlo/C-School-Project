// Name: Chi Fai Lo
// Seneca Student ID: 164450215
// Seneca email: clo36@myseneca.ca
// Date of completion: 24-March-23
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef _SDDS_CUST_ORDER_H_
#define _SDDS_CUST_ORDER_H_

#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>

#include "Station.h"
#include "Utilities.h"

using namespace std;

//Item Definition
struct Item
{
	std::string m_itemName;
	size_t m_serialNumber{ 0 };
	bool m_isFilled{ false };
	Item(const std::string& src) : m_itemName(src) {};
};

namespace sdds {
	class CustomerOrder
	{
	private:
		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem = 0;
		Item** m_lstItem = nullptr;
		static size_t m_widthField;
	public:

		//default constructor
		CustomerOrder(){};
		CustomerOrder(const string& record);

		//Reject Copy operator
		CustomerOrder(const CustomerOrder& order);
		CustomerOrder& operator=(const CustomerOrder&) = delete;

		//Move constructor
		CustomerOrder(CustomerOrder&& order)noexcept;
		CustomerOrder& operator=(CustomerOrder&& order) noexcept;

		~CustomerOrder();

		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
}

#endif // !_SDDS_CUST_ORDER_H_


