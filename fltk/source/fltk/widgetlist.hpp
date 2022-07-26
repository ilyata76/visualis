#pragma once

#ifndef MY_WIDGETLIST_HPP
#define MY_WIDGETLIST_HPP

	#include <FL/Fl.H>

	#include <map>
	#include <iostream>

	class WidgetList {
		private:
			std::map<int, std::pair<Fl_Widget*, bool>> map;
		public:
			WidgetList() : map() {};
			WidgetList(std::map<int, std::pair<Fl_Widget*, bool>> _map) : map(_map) {};

			bool exist(int _index);
			bool tied(int _index);
			bool add(int _index, Fl_Widget* _widget);
			bool add(int _index, Fl_Widget* _widget, bool tied);
			bool remove(int _index);
			bool set_tied(int _index);
			bool set_untied(int _index);

			Fl_Widget* operator[] (int _index);

			~WidgetList();
	};

#endif // !MY_WIDGETLIST_HPP
