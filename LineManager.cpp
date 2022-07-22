// Name: Aleksandr Valuev
// Date of completion: 12/4/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Workstation.h"
#include "LineManager.h"
#include "Utilities.h"

namespace sdds {
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
		Utilities util;
		m_cntCustomerOrder = pending.size();

		std::ifstream f(file);
		if (!f)
			std::cout << "Unable to open [" + file + "] file." << std::endl;
		else {
			while (f) {
				std::string line{}, workstation{}, workstation2{};
				size_t next_p = 0;
				bool more = true;
				
				std::getline(f, line);
				if (!line.empty()) {
					util.setDelimiter('|');
					workstation = util.extractToken(line, next_p, more);
					if (more) workstation2 = util.extractToken(line, next_p, more);
					//push station to the activeLine
					std::for_each(stations.begin(), stations.end(), [&](Workstation* w) {
						if (w->getItemName() == workstation) activeLine.push_back(w);
						});
					//set next station for the pushed station
					if (!workstation2.empty()) {
						std::for_each(stations.begin(), stations.end(), [&](Workstation* w) {
							if (w->getItemName() == workstation2) activeLine.back()->setNextStation(w);
							});
					}
					
				}
			}
		}
		//set the first station
		m_firstStation = activeLine[0];
	}

	void LineManager::linkStations() {
		//sorted workstations
		std::vector<Workstation*> sorted;
		sorted.push_back(m_firstStation);
		
		while (sorted.size() != activeLine.size()) {
			for (auto it = activeLine.begin(); it != activeLine.end(); it++) {
				if (sorted.back()->getNextStation() == *(it)) {
					sorted.push_back(*it);
					break;
				}
			}
		}
		activeLine.clear();
		activeLine = sorted;
	}

	static size_t iter = 0;
	bool LineManager::run(std::ostream& os) {
		bool allFilled = false;
	
		os << "Line Manager Iteration: " << ++iter << std::endl;

		if (!pending.empty()) {
			*m_firstStation += std::move(pending.front());
			pending.pop_front();
		}

		std::for_each(activeLine.begin(), activeLine.end(), [&os](Workstation* w) {
			w->fill(os);
			});
		std::for_each(activeLine.begin(), activeLine.end(), [](Workstation* w) {
			w->attemptToMoveOrder();
			}); 

		if (completed.size() + incomplete.size() == m_cntCustomerOrder) allFilled = true;
		return allFilled;
	}
	void LineManager::display(std::ostream& os) const {
		std::for_each(activeLine.begin(), activeLine.end(), [&os](Workstation* w) {
			w->display(os);
			});

	}
};