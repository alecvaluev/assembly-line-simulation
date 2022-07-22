// Name: Aleksandr Valuev
// Date of completion: 11/18/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include "Utilities.h"

namespace sdds {
	char Utilities::m_delimiter{ ',' };

	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	};

	size_t Utilities::getFieldWidth() const{
		return m_widthField;
	};
	
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		std::string copy{};
		size_t found = str.find(getDelimiter(), next_pos);
		if (found != std::string::npos) {
			if (found == next_pos) {
				more = false;
				throw "Error delimiter";
			}
			copy = str.substr(next_pos, found - next_pos);
			next_pos = found + 1;
			more = true;
		}
		else {
			copy = str.substr(next_pos);
			more = false;
		}
		if (getFieldWidth() < copy.length()) setFieldWidth(copy.length());
		return copy;
	};

	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	};

	char Utilities::getDelimiter() {
		return m_delimiter;
	};
}