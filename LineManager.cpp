// Name: Chi Fai Lo
// Seneca Student ID: 164450215
// Seneca email: clo36@myseneca.ca
// Date of completion: 24-March-23
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#include "LineManager.h"
#include <unordered_map>

using namespace std;

namespace sdds {

	LineManager::LineManager(){
		m_cntCustomerOrder = 0;
		m_firstStation = nullptr;
	}

	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations){

        Utilities tmpUtil;
        size_t next_pos = 0;
        bool remain = true;

        string line,thisWS,nextWS;

        //receives the name of the file
		std::ifstream fileGet(file);
		//If something goes wrong, this constructor reports an error.
		if (!fileGet) {
            std::string err = "Error: Fail to open the " + file;
            throw err;
		}

		tmpUtil.setDelimiter('|');

		Workstation* wsCurrent = nullptr;
		Workstation* wsSecond = nullptr;

        while (getline(fileGet, line)) {
			next_pos = 0; //reset the pos
			thisWS = tmpUtil.extractToken(line, next_pos, remain);
			//stores the workstations in the order received from the file in the m_activeLine
			//Find the firststation match 
			wsCurrent = *std::find_if(stations.begin(), stations.end(),[&](const Workstation* ws) {
				return ws->getItemName() == thisWS; 
				});
			m_activeLine.push_back(wsCurrent);
			//Find the secondstation match
			if (remain) {
				nextWS = tmpUtil.extractToken(line, next_pos, remain);
				wsSecond = *std::find_if(stations.begin(), stations.end(), [&](const Workstation* ws) {
					return ws->getItemName() == nextWS;
					});
				wsCurrent->setNextStation(wsSecond);
			}
        }
		fileGet.close();

		//Find First Station
		for_each(stations.begin(), stations.end(), [&](Workstation* wsTmp) {
			auto firstStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
					return wsTmp == ws->getNextStation();
				});

			if (firstStation == stations.end())
				m_firstStation = wsTmp;
			});

		//Updates the attribute that holds the total number of orders in the g_pending queue
		m_cntCustomerOrder = g_pending.size();
	}

	void LineManager::reorderStations() {
		std::vector<Workstation*> orderedLine;

		// Set the FirstStation
		orderedLine.push_back(m_firstStation);

		for (size_t i = 0; i < orderedLine.size(); i++)
		{
			for (size_t j = 0; j < m_activeLine.size(); j++)
			{
				if (orderedLine[i]->getNextStation() == m_activeLine[j]) {
					orderedLine.push_back(m_activeLine[j]);
					break;
				}
			}
		}
		//Replace the new to the old one
		m_activeLine = orderedLine;
	}

	bool LineManager::run(std::ostream& os){
		//keeps track of the current iteration number (use a local variable)
		static int currIterNum = 1;
		os << "Line Manager Iteration: " << currIterNum++ << std::endl;

		//moves the order at the front of the g_pending queue to the m_firstStation
		if (!g_pending.empty()) {
			*m_firstStation += std::move(g_pending.front());
			//Removes the first element of a deque
			g_pending.pop_front();
		}
		//For each station on the line, executes one fill operation
		for (auto& station : m_activeLine) {
			station->fill(os);
		}

		//for each station on the line, attempts to move an order down the line
		for (auto& station : m_activeLine) {
			station->attemptToMoveOrder();
		}

		//return true if all customer orders have been filled or cannot be filled,
		return(m_cntCustomerOrder == (g_completed.size() + g_incomplete.size())) ? true : false;
	}

	void LineManager::display(std::ostream& os) const{
		for (size_t i = 0u; i < m_activeLine.size(); i++) {
			m_activeLine[i]->display(os);
		}
	}

}
