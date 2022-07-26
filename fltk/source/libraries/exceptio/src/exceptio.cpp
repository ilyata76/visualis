#include "./exceptio.hpp"

namespace tia {

	bool checking_index(int i) {
		return (i < INT16_MIN || i > INT16_MAX) ? false : true;
	}

	Exceptio::Exceptio(int index) {
		this->comment = std::wstring(TIA_EXCEPTIO_STR_PLUG);
		this->description = std::wstring(TIA_EXCEPTIO_STR_PLUG);
		this->index = checking_index(index) ? index : TIA_EXCEPTIO_INT_PLUG;
	}

	Exceptio::Exceptio(const wchar_t* description) {
		this->comment = std::wstring(TIA_EXCEPTIO_STR_PLUG);
		this->description = std::wstring(description);
		this->index = TIA_EXCEPTIO_INT_PLUG;
	}

	Exceptio::Exceptio(const std::wstring& description) {
		this->comment = std::wstring(TIA_EXCEPTIO_STR_PLUG);
		this->description = std::wstring(description);
		this->index = TIA_EXCEPTIO_INT_PLUG;
	}

	Exceptio::Exceptio(const wchar_t* description, const wchar_t* comment) {
		this->comment = std::wstring(comment);
		this->description = std::wstring(description);
		this->index = TIA_EXCEPTIO_INT_PLUG;
	}

	Exceptio::Exceptio(const std::wstring& description, const std::wstring& comment) {
		this->comment = std::wstring(comment);
		this->description = std::wstring(description);
		this->index = TIA_EXCEPTIO_INT_PLUG;
	}

	Exceptio::Exceptio(int index, const wchar_t* description) {
		this->comment = std::wstring(TIA_EXCEPTIO_STR_PLUG);
		this->description = std::wstring(description);
		this->index = checking_index(index) ? index : TIA_EXCEPTIO_INT_PLUG;
	}

	Exceptio::Exceptio(int index, const std::wstring& description) {
		this->comment = std::wstring(TIA_EXCEPTIO_STR_PLUG);
		this->description = std::wstring(description);
		this->index = checking_index(index) ? index : TIA_EXCEPTIO_INT_PLUG;
	}

	Exceptio::Exceptio(int index, const wchar_t* description, const wchar_t* comment) {
		this->comment = std::wstring(comment);
		this->description = std::wstring(description);
		this->index = checking_index(index) ? index : TIA_EXCEPTIO_INT_PLUG;
	}

	Exceptio::Exceptio(int index, const std::wstring& description, const std::wstring& comment) {
		this->comment = std::wstring(comment);
		this->description = std::wstring(description);
		this->index = checking_index(index) ? index : TIA_EXCEPTIO_INT_PLUG;
	}

	Exceptio::Exceptio(std::exception _exc) {
		std::string a{ _exc.what() };

		this->index = 100;
		this->description = std::wstring{ a.begin(), a.end() };
		this->comment = L"by std::exception";
	}

	Exceptio::~Exceptio() {
		return;
	}

	bool Exceptio::operator == (Exceptio& a) {
		return bool(this->index == a.index && this->description == a.description && this->comment == a.comment);
	}

	Exceptio Exceptio::operator = (std::exception& exc) {

		std::string a{ exc.what() };

		this->description = std::wstring{ a.begin(), a.end() };
		return *this;
	}

	int Exceptio::get_raw_index() {
		return int(this->index);
	}

	bool checking_index_for_out(Exceptio& a) {
		return a.get_raw_index() != TIA_EXCEPTIO_INT_PLUG;
	}

	const std::wstring Exceptio::get_raw_description() {
		return this->description;
	}

	bool checking_description_for_out(Exceptio& a) {
		return a.get_raw_description() != TIA_EXCEPTIO_STR_PLUG; // returns 0 if strs are equal
	}

	const std::wstring Exceptio::get_raw_comment() {
		return this->comment;
	}

	bool checking_comment_for_out(Exceptio& a) {
		return a.get_raw_comment() != TIA_EXCEPTIO_STR_PLUG; // returns 0 if strs are equal
	}

	//////////////////////////////////////////////////////////////////////////// GETTERS

	int Exceptio::get_index() {
		return int(this->index);
	}

	std::wstring Exceptio::get_description() {
		return checking_description_for_out(*this) ? this->get_raw_description() : L"Your exceptio was created without description.";
	}

	std::wstring Exceptio::get_comment() {
		return checking_comment_for_out(*this) ? this->get_raw_comment() : L"Your exceptio was created without comment.";
	}

	std::wstring Exceptio::what() {
		return (L"[" + std::to_wstring(this->get_index()) + L"]" + this->get_description());
	}

	////////////////////////////////////////////////////////////////////////////

}
