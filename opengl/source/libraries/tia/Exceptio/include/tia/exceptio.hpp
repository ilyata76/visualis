#pragma once

#include <stdint.h>
#include <cstring>

#ifndef EXCEPTIO_HPP
#define EXCEPTIO_HPP

#define INT_PLUG INT16_MIN
#define STR_PLUG "\0"

// MAIN CLASS
class Exceptio {
	protected:
		int16_t index; // -32k +32k
		const char* description;
		const char* comment;

	public:
	//
		// INDEX - number of 16-bit integer for your enumeration and lists (if you see INT_PLUG you made a mistake)
		Exceptio(int16_t index);

		// INDEX - number of 16-bit integer for your enumeration and lists (if you see INT_PLUG you made a mistake)
		// DESCRIPTION - string which should describe the problem
		Exceptio(int16_t index, const char* description);

		// DESCRIPTION - string which should describe the problem
		Exceptio(const char* description);

		// DESCRIPTION - string which should describe the problem
		// COMMENT - optional str
		Exceptio(const char* description, const char* comment);

		// INDEX - number of 16-bit integer for your enumeration and lists (if you see INT_PLUG you made a mistake)
		// DESCRIPTION - string which should describe the problem
		// COMMENT - optional str
		Exceptio(int16_t index, const char* description, const char* comment);
	//
		bool operator == (Exceptio& a);
	//
	protected:
		int16_t get_raw_index();
		const char* get_raw_description();
		const char* get_raw_comment();

		// Checks whether the index was entered or entered correctly (if yes returns not 0)
		friend bool checking_index_for_out(Exceptio&);
		// Checks whether the description string was entered (if yes returns not 0)
		friend bool checking_description_for_out(Exceptio&);
		// Checks whether the comment string was entered (if yes returns not 0)
		friend bool checking_comment_for_out(Exceptio&);
	//
	public:
		int16_t get_index();
		const char* get_description();
		const char* get_comment();

};

// childs by exceptio?
#endif