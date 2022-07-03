#include "../include/exceptio.hpp"

bool checking_index(int i) {
	return (i < INT16_MIN || i > INT16_MAX) ? false : true;
}

// index - number of 16-bit integer for your enumeration and lists (if you see INT_PLUG you made a mistake)
Exceptio::Exceptio(int16_t index) {
	this->comment = std::wstring(STR_PLUG);
	this->description = std::wstring(STR_PLUG);
	this->index = checking_index(index) ? index : INT_PLUG;
}

// description - string which should describe the problem
Exceptio::Exceptio(const wchar_t* description) {
	this->comment = std::wstring(STR_PLUG);
	this->description = std::wstring(description);
	this->index = INT_PLUG;
}

// description - string which should describe the problem
Exceptio::Exceptio(const std::wstring& description) {
	this->comment = std::wstring(STR_PLUG);
	this->description = std::wstring(description);
	this->index = INT_PLUG;
}

// description - string which should describe the problem
// comment - optional str
Exceptio::Exceptio(const wchar_t* description, const wchar_t* comment) {
	this->comment = std::wstring(comment);
	this->description = std::wstring(description);
	this->index = INT_PLUG;
}

// description - string which should describe the problem
// comment - optional str
Exceptio::Exceptio(const std::wstring& description, const std::wstring& comment) {
	this->comment = std::wstring(comment);
	this->description = std::wstring(description);
	this->index = INT_PLUG;
}

// index - number of 16-bit integer for your enumeration and lists (if you see INT_PLUG you made a mistake)
// description - string which should describe the problem
Exceptio::Exceptio(int16_t index, const wchar_t* description) {
	this->comment = std::wstring(STR_PLUG);
	this->description = std::wstring(description);
	this->index = checking_index(index) ? index : INT_PLUG;
}

// index - number of 16-bit integer for your enumeration and lists (if you see INT_PLUG you made a mistake)
// description - string which should describe the problem
Exceptio::Exceptio(int16_t index, const std::wstring& description) {
	this->comment = std::wstring(STR_PLUG);
	this->description = std::wstring(description);
	this->index = checking_index(index) ? index : INT_PLUG;
}

// index - number of 16-bit integer for your enumeration and lists (if you see INT_PLUG you made a mistake)
// description - string which should describe the problem
// comment - optional str
Exceptio::Exceptio(int16_t index, const wchar_t* description, const wchar_t* comment) {
	this->comment = std::wstring(comment);
	this->description = std::wstring(description);
	this->index = checking_index(index) ? index : INT_PLUG;
}

// index - number of 16-bit integer for your enumeration and lists (if you see INT_PLUG you made a mistake)
// description - string which should describe the problem
// comment - optional str
Exceptio::Exceptio(int16_t index, const std::wstring& description, const std::wstring& comment) {
	this->comment = std::wstring(comment);
	this->description = std::wstring(description);
	this->index = checking_index(index) ? index : INT_PLUG;
}

// compares by index
bool Exceptio::operator == (Exceptio& a) {
	return bool(this->index == a.index);
}

int16_t Exceptio::get_raw_index() {
	return int16_t(this->index);
}

bool checking_index_for_out(Exceptio& a) {
	return a.get_raw_index() != INT_PLUG;
}

const std::wstring Exceptio::get_raw_description() {
	return this->description;
}

bool checking_description_for_out(Exceptio& a) {
	return a.get_raw_description() != STR_PLUG;
	// returns 0 if strs are equal
}

const std::wstring Exceptio::get_raw_comment() {
	return this->comment;
}

bool checking_comment_for_out(Exceptio& a) {
	return a.get_raw_comment() != STR_PLUG;
	// returns 0 if strs are equal
}

//////////////////////////////////////////////////////////////////////////// GETTERS

int16_t Exceptio::get_index() {
	return int16_t(this->index);
}

const std::wstring Exceptio::get_description() {
	return checking_description_for_out(*this) ? this->get_raw_description() : L"Your exceptio was created without description.";
}

const std::wstring Exceptio::get_comment() {
	return checking_comment_for_out(*this) ? this->get_raw_comment() : L"Your exceptio was created without comment.";
}

////////////////////////////////////////////////////////////////////////////