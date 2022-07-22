// Name: Aleksandr Valuev
// Seneca Student ID: 165445198
// Seneca email: avaluev@myseneca.ca
// Date of completion: 12/4/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include "Station.h"
#include "Workstation.h"

std::deque<sdds::CustomerOrder> pending;
std::deque<sdds::CustomerOrder> completed;
std::deque<sdds::CustomerOrder> incomplete;

namespace sdds {
	Workstation::Workstation(const std::string& str): Station(str) {};
	
	void Workstation::fill(std::ostream& os) {
		if (!m_order.empty()) {
			m_order.front().fillItem(*this, os);
		}
	};

	bool Workstation::attemptToMoveOrder() {
		bool isMoved = false;
		
		if (!m_order.empty()) {
			
			if (m_order.front().isItemFilled(getItemName())) {
				
				if (!m_pNextStation) {
					if (m_order.front().isFilled()) {
						completed.push_back(std::move(m_order.front()));
						m_order.pop_front();
						isMoved = true;
					}
					else {
						incomplete.push_back(std::move(m_order.front()));
						m_order.pop_front();
						isMoved = true;
					}
				}
				else {
					*m_pNextStation += std::move(m_order.front());
					m_order.pop_front();
					isMoved = true;
				}
			}
			else if (getQuantity() <= 0) {
				if (!m_pNextStation) {
					incomplete.push_back(std::move(m_order.front()));
					m_order.pop_front();
					isMoved = true;
				}
				else {
					*m_pNextStation += std::move(m_order.front());
					m_order.pop_front();
					isMoved = true;
				}
			}
		}

		return isMoved;
	};

	void Workstation::setNextStation(Workstation* station) {
		m_pNextStation = station;
	};

	Workstation* Workstation::getNextStation() const {
		return m_pNextStation;
	};

	void Workstation::display(std::ostream& os) const {
		os << this->getItemName() << " --> ";
		if (m_pNextStation) os << m_pNextStation->getItemName();
		else os << "End of Line";
		os << std::endl;
	};

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		m_order.push_back(std::move(newOrder));
		return *this;
	};

}