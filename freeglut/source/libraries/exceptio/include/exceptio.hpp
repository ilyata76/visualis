#pragma once



#ifndef EXCEPTIO_HPP
#define EXCEPTIO_HPP

#define INT_PLUG INT16_MIN
#define STR_PLUG L"\0"

	#include <stdint.h>
	#include <string>

	// MAIN CLASS
	class Exceptio {
		protected:
			int16_t index; // -32k +32k
			std::wstring description;
			std::wstring comment;

		public:
		//
			// INDEX - number of 16-bit integer for your enumeration and lists (if you see INT_PLUG you made a mistake)
			Exceptio(int16_t index);

			// INDEX - number of 16-bit integer for your enumeration and lists (if you see INT_PLUG you made a mistake)
			// DESCRIPTION - wstring which should describe the problem
			Exceptio(int16_t index, const wchar_t* description);

			// INDEX - number of 16-bit integer for your enumeration and lists (if you see INT_PLUG you made a mistake)
			// DESCRIPTION - wstring which should describe the problem
			Exceptio(int16_t index, const std::wstring& description);

			// DESCRIPTION - wstring which should describe the problem
			Exceptio(const wchar_t* description);
			
			// DESCRIPTION - wstring which should describe the problem
			Exceptio(const std::wstring& description);

			// DESCRIPTION - wstring which should describe the problem
			// COMMENT - optional wstr
			Exceptio(const wchar_t* description, const wchar_t* comment);

			// DESCRIPTION - wstring which should describe the problem
			// COMMENT - optional wstr
			Exceptio(const std::wstring& description, const std::wstring& comment);

			// INDEX - number of 16-bit integer for your enumeration and lists (if you see INT_PLUG you made a mistake)
			// DESCRIPTION - wstring which should describe the problem
			// COMMENT - optional wstr
			Exceptio(int16_t index, const wchar_t* description, const wchar_t* comment);

			// INDEX - number of 16-bit integer for your enumeration and lists (if you see INT_PLUG you made a mistake)
			// DESCRIPTION - wstring which should describe the problem
			// COMMENT - optional wstr
			Exceptio(int16_t index, const std::wstring& description, const std::wstring& comment);

		//
			bool operator == (Exceptio& a);
		//
		protected:
			int16_t get_raw_index();
			const std::wstring get_raw_description();
			const std::wstring get_raw_comment();

			// Checks whether the index was entered or entered correctly (if yes returns not 0)
			friend bool checking_index_for_out(Exceptio&);
			// Checks whether the description string was entered (if yes returns not 0)
			friend bool checking_description_for_out(Exceptio&);
			// Checks whether the comment string was entered (if yes returns not 0)
			friend bool checking_comment_for_out(Exceptio&);
		//
		public:
			int16_t get_index();
			const std::wstring get_description();
			const std::wstring get_comment();

	};

// childs by exceptio?
#endif