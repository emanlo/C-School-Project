// Name: Chi Fai Lo
// Seneca Student ID: 164450215
// Seneca email: clo36@myseneca.ca
// Date of completion: 24-March-23
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Workstation.h"
#include "CustomerOrder.h"

using namespace std;

namespace sdds {

	std::deque<CustomerOrder> g_pending;
	std::deque<CustomerOrder> g_completed;
	std::deque<CustomerOrder> g_incomplete;

	Workstation::Workstation(){
		m_pNextStation = nullptr;
	}

	Workstation::Workstation(const std::string& line) : Station(line) {
		//passes it to the Station base class
		m_pNextStation = nullptr;
	}

	void Workstation::fill(std::ostream& os){
		//if there are CustomerOrders in the queue
		if (!m_order.empty()) {
			//Fills the order at the front of the queue 
			m_order.front().fillItem(*this,os);
		}
	}

	bool Workstation::attemptToMoveOrder(){
		//If order requires no more service at this station, then return false
		if (m_order.empty())
			return false;

		if (m_order.front().isItemFilled(getItemName())) {
			//if there is no next station in the assembly line
			if (!m_pNextStation) {
				//then the order is moved into g_completed or g_incomplete queue
				(m_order.front().isOrderFilled()) ? 
					g_completed.push_back(std::move(m_order.front())) : g_incomplete.push_back(std::move(m_order.front()));
			} else {
				//move it to the next station
				*m_pNextStation += std::move(m_order.front());
			}
			m_order.pop_front();
		}
		//Not enough inventory
		else if (!getQuantity()) {
			if (!m_pNextStation) g_incomplete.push_back(std::move(m_order.front()));
			else {
				//move it to the next station
				*m_pNextStation += std::move(m_order.front());
			}
			m_order.pop_front();
		}
		return true;
	}

	void Workstation::setNextStation(Workstation* station){
		//Prevent mermory leak
		if (m_pNextStation != nullptr) delete m_pNextStation;
		//stores the address of the referenced Workstation object in the pointer to the m_pNextStation
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const{
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const{
		os << this->getItemName() << " --> ";

		if (m_pNextStation != nullptr) {
			os << m_pNextStation->getItemName() << endl;
		}
		else {
			os << "End of Line" << endl;
		}
		//if the current object is the last 
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		//Moves the CustomerOrder referenced in parameter newOrder to the back of the queue.
		m_order.push_back(std::move(newOrder));
		return *this;
	}

}