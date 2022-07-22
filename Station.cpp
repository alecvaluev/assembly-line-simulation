// Name: Aleksandr Valuev
// Date of completion: 11/18/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace sdds {
	size_t Station::m_widthField{ 0u };
	int Station::id_generator{ 0 };

	Station::Station(const std::string& str) {
		Utilities util;
		size_t next_pos = 0;
		bool more = true;

		m_id = ++id_generator;
		m_name = util.extractToken(str, next_pos, more);
		m_nextSerialNum = std::stoi(util.extractToken(str, next_pos, more));
		m_quantity = std::stoi(util.extractToken(str, next_pos, more));

		m_widthField = (m_widthField > util.getFieldWidth())? m_widthField: util.getFieldWidth();
		m_description = util.extractToken(str, next_pos, more);
	};
	const std::string& Station::getItemName() const{
		return m_name;
	};
	size_t Station::getNextSerialNumber() {
		return m_nextSerialNum++;
	};
	size_t Station::getQuantity() const {
		return m_quantity;
	};
	void Station::updateQuantity() {
		if(m_quantity != 0 ) m_quantity--;
	};
	void Station::display(std::ostream& os, bool full) const {
		os << "[" << std::setfill('0') << std::right 
			<< std::setw(3) << m_id << std::setfill(' ') << std::left 
			<< "] Item: " 
			<< std::left << std::setw(m_widthField) << m_name 
			<< " [" 
			<< std::setfill('0') <<std::right << std::setw(6) << m_nextSerialNum 
			<< ']' 
			<< std::setfill(' ') << std::left;

		if (full) {
			os << " Quantity: " << std::setw(m_widthField) << m_quantity 
				<< " Description: " <<  m_description;
		}
		os << std::endl;
	};
}