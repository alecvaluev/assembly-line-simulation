// Name: Aleksandr Valuev
// Seneca Student ID: 165445198
// Seneca email: avaluev@myseneca.ca
// Date of completion: 12/4/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef WORKSTATION_H
#define WORKSTATION_H
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

extern std::deque<sdds::CustomerOrder> pending;
extern std::deque<sdds::CustomerOrder> completed;
extern std::deque<sdds::CustomerOrder> incomplete;

namespace sdds {
	

	class Workstation: public Station {
		std::deque<CustomerOrder> m_order;
		Workstation* m_pNextStation{ nullptr };

	public:
		Workstation(const std::string&);
		Workstation(const Workstation&) = delete;
		Workstation& operator=(const Workstation&) = delete;
		Workstation(Workstation&&) = delete;
		Workstation&& operator=(Workstation&&) = delete; 
		
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
	};
}
#endif //!WORKSTATION_H