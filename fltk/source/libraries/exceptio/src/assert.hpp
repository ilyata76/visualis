#pragma once

#ifndef TIA_ASSERT_HPP
#define TIA_ASSERT_HPP

	#include "./exceptio.hpp"

	namespace tia {

		// based on EXCEPTIO_HPP
		class Assert {
			public:
				// COMMENT: "It was caused by using Assert"

				Assert() {};

				virtual void operator()(bool condition) {
					if (!condition) throw Exceptio(TIA_EXCEPTIO_INT_PLUG, TIA_EXCEPTIO_STR_PLUG, L"It was caused by using Assert");
				}

				// Your INDEX
				// COMMENT: "It was caused by using Assert"
				virtual void operator()(bool condition, int index) {
					if (!condition) throw Exceptio(index, TIA_EXCEPTIO_STR_PLUG, L"It was caused by using Assert");
				}

				// Your DECRIPTION when calling an Exceptio
				// COMMENT: "It was caused by using Assert"
				virtual void operator()(bool condition, const wchar_t* description) {
					if (!condition) throw Exceptio(TIA_EXCEPTIO_INT_PLUG, description, L"It was caused by using Assert");
				}

				// Your DECRIPTION when calling an Exceptio
				// COMMENT: "It was caused by using Assert"
				virtual void operator()(bool condition, const std::wstring& description) {
					if (!condition) throw Exceptio(TIA_EXCEPTIO_INT_PLUG, description, L"It was caused by using Assert");
				}

				// Your DESCRIPTION and COMMENT when calling an Exception
				virtual void operator()(bool condition, const wchar_t* description, const wchar_t* comment) {
					if (!condition) throw Exceptio(TIA_EXCEPTIO_INT_PLUG, description, comment);
				}

				// Your DESCRIPTION and COMMENT when calling an Exception
				virtual void operator()(bool condition, const std::wstring& description, const std::wstring& comment) {
					if (!condition) throw Exceptio(TIA_EXCEPTIO_INT_PLUG, description, comment);
				}

				// Your INDEX, DESCRIPTION when calling and Exception
				// COMMENT: "It was caused by using Assert"
				virtual void operator()(bool condition, int index, const wchar_t* description) {
					if (!condition) throw Exceptio(index, description, L"It was caused by using Assert");
				}

				// Your INDEX, DESCRIPTION when calling and Exception
				// COMMENT: "It was caused by using Assert"
				virtual void operator()(bool condition, int index, const std::wstring& description) {
					if (!condition) throw Exceptio(index, description, L"It was caused by using Assert");
				}

				// Your INDEX, DESCRIPTION and COMMENT when calling and Exception
				virtual void operator()(bool condition, int index, const wchar_t* description, const wchar_t* comment) {
					if (!condition) throw Exceptio(index, description, comment);
				}

				// Your INDEX, DESCRIPTION and COMMENT when calling and Exception
				virtual void operator()(bool condition, int index, const std::wstring& description, const std::wstring& comment) {
					if (!condition) throw Exceptio(index, description, comment);
				}

				virtual ~Assert();

		};
	
	#define ASSERT(condition) { tia::Assert a; a(condition, L"by ASSERT"); }
	//#define ASSERT(condition, description) { tia::Assert a; a(condition, description); }

	}

	

#endif // !MY_ASSERT_HPP
