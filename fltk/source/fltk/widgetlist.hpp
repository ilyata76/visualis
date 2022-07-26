#pragma once

#ifndef MY_WIDGETLIST_HPP
#define MY_WIDGETLIST_HPP

	#include <FL/Fl.H>

	#include <map>
	#include <iostream>

	class WidgetList {
		private:
			std::map<int, Fl_Widget*> map;
		public:
			WidgetList() : map() {};
			WidgetList(std::map<int, Fl_Widget*> _map) : map(_map) {};

			bool exist(int _index);
			bool add(int _index, Fl_Widget* _widget);
			bool remove(int _index);

			Fl_Widget* operator[] (int _index);

			~WidgetList();
	};

#endif // !MY_WIDGETLIST_HPP
