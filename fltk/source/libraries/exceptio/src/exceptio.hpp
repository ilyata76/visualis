#pragma once



#ifndef TIA_EXCEPTIO_HPP
#define TIA_EXCEPTIO_HPP

	constexpr auto TIA_EXCEPTIO_INT_PLUG = -17341;
	constexpr auto TIA_EXCEPTIO_STR_PLUG = L"\0";

	#include <string>

	namespace tia {

		// (int)index, (std::wstring)description, (std::wstring)comment
		class Exceptio {

			protected:
				int index;
				std::wstring description;
				std::wstring comment;

			public:
				// INDEX - number of 16-bit integer for your enumeration and lists (if you see INT_PLUG you made a mistake)
				Exceptio(int index);

				// INDEX - number of 16-bit integer for your enumeration and lists (if you see INT_PLUG you made a mistake)
				// DESCRIPTION - wstring which should describe the problem
				Exceptio(int index, const wchar_t* description);

				// INDEX - number of 16-bit integer for your enumeration and lists (if you see INT_PLUG you made a mistake)
				// DESCRIPTION - wstring which should describe the problem
				Exceptio(int index, const std::wstring& description);

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
				Exceptio(int index, const wchar_t* description, const wchar_t* comment);

				// INDEX - number of 16-bit integer for your enumeration and lists (if you see INT_PLUG you made a mistake)
				// DESCRIPTION - wstring which should describe the problem
				// COMMENT - optional wstr
				Exceptio(int index, const std::wstring& description, const std::wstring& comment);

				Exceptio(std::exception _exc);

				virtual ~Exceptio();

			//
				virtual bool operator == (Exceptio& a);
				virtual Exceptio operator = (std::exception& exc);
			//
			protected:
				int get_raw_index();
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
				virtual int get_index();
				virtual std::wstring get_description();
				virtual std::wstring get_comment();
				virtual std::wstring what();

		};
		
	}
// childs by exceptio?
#endif