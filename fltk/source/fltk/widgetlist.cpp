#include "./widgetlist.hpp"

bool WidgetList::exist(int _index) {
	auto it = this->map.find(_index);

	return (it != map.end());
}

bool WidgetList::add(int _index, Fl_Widget* _widget) {
	try {

		if (!this->exist(_index)) {
			this->map[_index] = _widget;
			return true;
		} else return false;

	} catch (std::exception& E) {
		return false;
	}
}

bool WidgetList::remove(int _index) {
	try {

		if (this->exist(_index)) {
			delete this->map[_index];
			this->map.erase(_index);
			return true;
		} else return false;

	} catch (std::exception& E) {
		return false;
	}
}

Fl_Widget* WidgetList::operator[](int _index) {
	try {

		if (this->exist(_index)) return this->map[_index];
		else return nullptr;

	} catch (std::exception& E) {
		return nullptr;
	}

	
}

WidgetList::~WidgetList() {

	for (const auto& iterator : this->map) {
		delete iterator.second;
	}

}
