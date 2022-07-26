#include "./widgetlist.hpp"

bool WidgetList::exist(int _index) {
	auto it = this->map.find(_index);

	return (it != map.end());
}

bool WidgetList::tied(int _index) {
	try {

		if (this->exist(_index)) return this->map[_index].second;
		else return false;

	} catch (...) {
		return false;
	}
}

bool WidgetList::add(int _index, Fl_Widget* _widget) {
	try {

		if (!this->exist(_index)) {
			this->map[_index] = std::pair<Fl_Widget*, bool>{_widget, false};
			return true;
		} else return false;

	} catch (...) {
		return false;
	}
}

bool WidgetList::add(int _index, Fl_Widget* _widget, bool tied) {
	try {

		if (!this->exist(_index)) {
			this->map[_index] = std::pair<Fl_Widget*, bool>{_widget, tied};
			return true;
		} else return false;

	} catch (...) {
		return false;
	}
}

bool WidgetList::remove(int _index) {
	try {

		if (this->exist(_index)) {
			
			if (!this->tied(_index)) delete this->map[_index].first;
			
			this->map.erase(_index);
			
			return true;
		} else return false;

	} catch (std::exception& E) {
		return false;
	}
}

bool WidgetList::set_tied(int _index) {
	try {

		if (this->exist(_index)) { this->map[_index].second = true; return (this->map[_index].second == true); }
		else return false;

	} catch (std::exception& E) {
		return nullptr;
	}
}

bool WidgetList::set_untied(int _index) {
	try {

		if (this->exist(_index)) { this->map[_index].second = false; return (this->map[_index].second == false); }
		else return false;

	} catch (std::exception& E) {
		return nullptr;
	}
}

Fl_Widget* WidgetList::operator[](int _index) {
	try {

		if (this->exist(_index)) return this->map[_index].first;
		else return nullptr;

	} catch (std::exception& E) {
		return nullptr;
	}
}

WidgetList::~WidgetList() {

	for (auto& iterator : this->map) {
		if (this->tied(iterator.first) == false) delete iterator.second.first;
	}
	// DELETE MAIN_WINDOW юбрнлюрхвеяйх нвхыюер бяе бхдферш, й мелс опхбъгюммше
}
