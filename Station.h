// Name: Aleksandr Valuev
// Date of completion: 11/18/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef STATION_H
#define STATION_H
#include <string>

namespace sdds {
	class Station {
		int m_id;
		std::string m_name{};
		std::string m_description{};
		size_t m_nextSerialNum{ 0u };
		size_t m_quantity{ 0u };

		static size_t m_widthField;
		static int id_generator;

	public:
		Station(const std::string&);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}
#endif // !STATION_H