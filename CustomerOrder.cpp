// Name: Aleksandr Valuev
// Date of completion: 11/18/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <iomanip>
#include "Utilities.h"
#include "Station.h"
#include "CustomerOrder.h"

namespace sdds {
	size_t CustomerOrder::m_widthField{ 0 };

	CustomerOrder::CustomerOrder() {};
	
	CustomerOrder::CustomerOrder(const std::string& str) {
		Utilities util;
		bool more{ true };
		size_t next_pos{ 0 };
		m_name = util.extractToken(str, next_pos, more);
		m_product = util.extractToken(str, next_pos, more);
		
		while (more) {
			Item* item = new Item(util.extractToken(str, next_pos, more));
			
			if(!m_listItem) m_listItem = new Item * [++m_cntItem];
			else {
				Item** oldList = m_listItem;
				m_listItem = new Item * [++m_cntItem];
				for (size_t i = 0; i < m_cntItem - 1; i++)
					m_listItem[i] = oldList[i];
				delete[] oldList;
			}
			m_listItem[m_cntItem - 1] = item;
			item = nullptr;
		}

		if (m_widthField < util.getFieldWidth()) m_widthField = util.getFieldWidth();
	};
	
	CustomerOrder::CustomerOrder(const CustomerOrder& order) {
		throw "";
	};

	CustomerOrder::CustomerOrder(CustomerOrder&& order) noexcept {
		*this = std::move(order);
	};
	
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& order) noexcept {
		if (this != &order) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_listItem[i];
			};
			delete[] m_listItem;
			m_name = order.m_name;
			m_product = order.m_product;
			m_cntItem = order.m_cntItem;
			m_listItem = order.m_listItem;

			order.m_name = "";
			order.m_product = "";
			order.m_cntItem = 0u;
			order.m_listItem = nullptr;
		}
		return *this; 
	};
	
	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_listItem[i];
		};
		delete[] m_listItem;
	};

	bool CustomerOrder::isFilled() const {
		bool isFilled = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_listItem[i]->m_isFilled == false) {
				isFilled = false;
				break;
			}
		}
		return isFilled;
	};
	
	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool isFilled = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_listItem[i]->m_itemName == itemName && m_listItem[i]->m_isFilled == false) {
				isFilled = false;
				break;
			}
		}
		return isFilled;
	};
	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_listItem[i]->m_itemName == station.getItemName() ){
				if (station.getQuantity() > 0) {
					m_listItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_listItem[i]->m_isFilled = true;
					station.updateQuantity();
					os << "    Filled " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << std::endl;
				}
				else {
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << std::endl;
				}
			}
		}
	};

	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;

		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << std::setw(6) << std::right << std::setfill('0') << m_listItem[i]->m_serialNumber << "] " << std::setfill(' ') << std::left
				<< std::setw(m_widthField) << m_listItem[i]->m_itemName << " - ";
			if (m_listItem[i]->m_isFilled) os << "FILLED";
			else os << "TO BE FILLED";
			os << std::endl;
		};
	};
}