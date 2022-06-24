#include "./useful_functions.hpp"


float get_euler_phi(const double& sx, const double& sy, const double& sz) {
	int sign = -1;
	if (VVIS_COUNTERCLOCKWISE) sign = 1;
	if (sx > 0 && sy > 0) {
		return (sign * atan(fabs(sy / sx)) * 180.0 / 3.1415);
	} else if (sx < 0 && sy > 0) {
		return (sign * (180 - (atan(fabs(sy / sx))) * 180.0 / 3.1415));
	} else if (sx < 0 && sy < 0) {
		return (sign * (270 - (atan(fabs(sx / sy))) * 180.0 / 3.1415));
	} else if (sx > 0 && sy < 0) {
		return (sign * (360 - (atan(fabs(sy / sx))) * 180.0 / 3.1415));
	} else {
		if (sy == 0) if (sx < 0) return (sign * 180.0); else return (sign * 0.0);
		if (sx == 0) if (sy > 0) return (sign * 90.0); else return (sign * (-90.0));
	} return (sign * 0.0f);
}

float get_euler_theta(const double& sx, const double& sy, const double& sz) {
	int sign = -1;
	if (VVIS_COUNTERCLOCKWISE) sign = 1;

	if (sz == 0) return (sign * 90.0f);

	if (sz > 0) return (sign * (atan(fabs(sqrt(pow(sx, 2) + pow(sy, 2))) / fabs(sz))) * 180.0 / 3.1415);
	else return (sign * (180 - (atan(fabs(sqrt(pow(sx, 2) + pow(sy, 2)) / sz))) * 180.0 / 3.1415));

	return (sign * 0.0f);
}

bool file_exist(const std::wstring& _path) {
	struct _stat buf;
	return (_wstat(_path.c_str(), &buf) != -1);
}

std::wostream& print_logo(std::wostream& _out) {

	_out << L"\n    ____   ____.___  _____________ ___  _____  .____    .___  _________ " << L"\n";
	_out << L"    \\   \\ /   /|   |/   _____/    |   \\/  _  \\ |    |   |   |/  _____/  " << L"\n";
	_out << L"     \\   Y   / |   |\\_____  \\|    |   /  /_\\  \\|    |   |   |\\_____ \\   " << L"\n";
	_out << L"      \\     /  |   |/        \\    |  /    |    \\    |___|   |/       \\  " << L"\n";
	_out << L"       \\___/   |___/_______  /______/\\____|__  /_______ \\___/_______ /  " << L"\n";
	_out << L"                           \\/                \\/        \\/          \\/   " << L"\n" << std::endl;

	return _out;
}

std::vector<std::wstring> line_to_vector(const std::wstring& _str) {
	std::wstringstream wss; wss.str(_str); std::vector<std::wstring> result; std::wstring str;
	
	while (wss.good()) {
		wss >> str;
		if (str != L"") result.push_back(str);
		str = L"\0";
	}

	return result;
}

std::wstring to_lower_wstr(std::wstring& _value) {
	std::transform(_value.begin(), _value.end(), _value.begin(), std::tolower);
	return std::wstring(_value);
}

int get_second_from_map(std::map<std::wstring, int>& _map, std::wstring& _value) {
	std::map<std::wstring, int>::iterator it = _map.find(_value);

	return it == _map.end() ? VVIS_UNKNOWW_MAP_SECOND : it->second;
}

std::wstring remove_quotations(std::wstring& _str) {
	if (_str.size() > 1) {
		if ((_str[0] == L'\"' && _str[_str.size() - 1] == L'\"') ||
			(_str[0] == L'\'' && _str[_str.size() - 1] == L'\'')) {
			_str.pop_back(); _str = _str.substr(1);
		}
	}; return _str;
}

std::wostream& print_vector(std::wostream& _out, std::vector<std::wstring>& _vector, std::wstring separator) {
	
	for (const std::vector<std::wstring>::iterator::value_type& a : _vector) {
		_out << a << separator;
	}
	
	return _out;
}

bool is_number(const std::wstring& _str) {
	return !_str.empty() && std::find_if(_str.begin(),
		_str.end(), [](wchar_t c) { return !(std::isdigit(c) || c == L'0'); }) == _str.end();
}