#pragma once

#ifndef MY_ASSERT_HPP
#define MY_ASSERT_HPP

#include "exceptio.hpp"

// based on EXCEPTIO_HPP
class Assert {
	public:
		// COMMENT: "It was caused by using Assert"
		Assert(bool condition) {
			if (!condition) throw Exceptio(INT_PLUG, STR_PLUG, "It was caused by using Assert");
		}

		// Your DECRIPTION when calling an Exceptio
		// COMMENT: "It was caused by using Assert"
		Assert(bool condition, const char* description) {
			if (!condition) throw Exceptio(INT_PLUG, description, "It was caused by using Assert");
		}

		// Your DESCRIPTION and COMMENT when calling an Exception
		Assert(bool condition, const char* description, const char* comment) {
			if (!condition) throw Exceptio(INT_PLUG, description, comment);
		}

		// Your INDEX, DESCRIPTION when calling and Exception
		// COMMENT: "It was caused by using Assert"
		Assert(bool condition, int16_t index, const char* description) {
			if (!condition) throw Exceptio(index, description, "It was caused by using Assert");
		}

		// Your INDEX, DESCRIPTION and COMMENT when calling and Exception
		Assert(bool condition, int16_t index, const char* description, const char* comment) {
			if (!condition) throw Exceptio(index, description, comment);
		}
};

#endif // !MY_ASSERT_HPP
