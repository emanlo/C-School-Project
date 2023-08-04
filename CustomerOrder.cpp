// Name: Chi Fai Lo
// Seneca Student ID: 164450215
// Seneca email: clo36@myseneca.ca
// Date of completion: 24-March-23
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include "CustomerOrder.h"
#include "Utilities.h"
#include "Station.h"

using namespace std;

namespace sdds {

	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder(const string& record){
		////Uses a Utilities object to extract each token from the record
		Utilities tmpUtil;
		//Variable for the token function
		size_t next_pos = 0;
		size_t org_pos = 0;
		bool remain = true;
		int count = 0;

		//Extracts name and the Order Name
		m_name = tmpUtil.extractToken(record, next_pos, remain);
		m_product = tmpUtil.extractToken(record, next_pos, remain);

		//Calcaute the Number of Item
		org_pos = next_pos; //Save the org position
		while (remain) {
			tmpUtil.extractToken(record, next_pos, remain);
			count++; //Calcaute the Total Number
		}

		//Reset the Boom
		remain = true;
		//Allocate the memorary
		m_lstItem = new Item*[count];

		//Loop all the product
		while (remain)
		{
			m_lstItem[m_cntItem] = new Item(tmpUtil.extractToken(record, org_pos, remain)); //Use the org_pos to capture the word
			m_cntItem++;
		}

		//Updates if the current value is smaller than the value stored in Utilities::m_widthField
		if (CustomerOrder::m_widthField < tmpUtil.getFieldWidth()) CustomerOrder::m_widthField = tmpUtil.getFieldWidth();
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& order){
		//copy constructor should throw an exception
		throw string("Error");
	}

	//Move
	CustomerOrder::CustomerOrder(CustomerOrder&& order) noexcept{
		*this = std::move(order);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& order) noexcept{
		//Self Check
		if (this != &order) {
			//Free the Memeroy 
			if (m_lstItem != nullptr) {
				for (size_t i = 0; i < m_cntItem; i++)
				{
					delete m_lstItem[i];
					m_lstItem[i] = nullptr;
				}
				delete[] m_lstItem;
				m_lstItem = nullptr;
			}

			m_name = order.m_name;
			m_product = order.m_product;
			m_cntItem = order.m_cntItem;
			m_lstItem = order.m_lstItem;
			//Reset the Right side
			order.m_name = "";
			order.m_product = "";
			order.m_cntItem = 0;
			order.m_lstItem = nullptr;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		if (m_lstItem != nullptr) {
			for (size_t i = 0; i < m_cntItem; i++)
			{
				delete m_lstItem[i];
				m_lstItem[i] = nullptr;
			}
			delete[] m_lstItem;
			m_lstItem = nullptr;
		}
	}

	bool CustomerOrder::isOrderFilled() const
	{
		bool result = true;
		for (size_t i = 0; i < m_cntItem && result; i++)
		{
			//If not fill, that end loop and return the result
			if (!(this->m_lstItem[i]->m_isFilled)) {
				result = false;
			}
		}
		return result;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		//Check the item exist or not
		bool exist = false;
		bool filled = true;

		for (size_t i = 0; i < m_cntItem && !exist; i++){
			if (m_lstItem[i]->m_itemName == itemName) exist = true;
		}

		//returns true if the item doesn't exist in the order
		if (!exist) return true;
		else
		{
			//if exist, that check all items specified by itemName have been filled
			for (size_t i = 0; i < m_cntItem && filled; i++) {
				if (m_lstItem[i]->m_itemName == itemName) {
					if (!(m_lstItem[i]->m_isFilled)) filled = false;
				}
			}
		}
		return filled;

	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		//if the order doesn't contain the item handled, this function does nothing
		for (size_t i = 0; i < m_cntItem; i++)
		{
			//the order contains items handled, and the Station's inventory contains and not yet fill
			if (m_lstItem[i]->m_itemName == station.getItemName() && !(m_lstItem[i]->m_isFilled)) {
				//IF still have stock
				if (station.getQuantity() > 0) {
					//subtracts 1 from the inventory
					station.updateQuantity();
					//updates Item::m_serialNumber and Item::m_isFilled
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					//also prints the message
					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
					break;
				}
				else
				{
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
				}
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const{
		os << m_name << " - " << m_product << endl;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			os << "[" << setw(6) << setfill('0') << right << m_lstItem[i]->m_serialNumber << "] ";
			os << setw(m_widthField) << setfill(' ') << left << m_lstItem[i]->m_itemName << " - ";
			(m_lstItem[i]->m_isFilled) ? os << "FILLED" : os << "TO BE FILLED";
			os << endl;
		}
	}

}