#include "./useful_functions.hpp"

float get_euler_phi(const double& sx, const double& sy, const double& sz) {
	Assert(!(sx == 0 && sy == 0 && sz == 0), 1, L"NULL-agruments sx,sy,sz were recieved", L"Assert, get_euler_phi");
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
	Assert(!(sx == 0 && sy == 0 && sz == 0), 1, L"NULL-agruments sx,sy,sz were recieved", L"Assert, get_euler_theta");
	int sign = -1;
	if (VVIS_COUNTERCLOCKWISE) sign = 1;

	if (sz == 0) return (sign * 90.0f);

	if (sz > 0) return (sign * (atan(fabs(sqrt(pow(sx, 2) + pow(sy, 2))) / fabs(sz))) * 180.0 / 3.1415);
	else return (sign * (180 - (atan(fabs(sqrt(pow(sx, 2) + pow(sy, 2)) / sz))) * 180.0 / 3.1415));

	return (sign * 0.0f);
}

bool file_exist(const std::string _path) {
	Assert(_path.size() > 0, 1, L"NULL path was recieved", L"Assert, file_exists");
	return std::ifstream(_path).good();
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
	std::transform(_value.begin(), _value.end(), _value.begin(), [](unsigned char c) { return std::tolower(c); });
	return std::wstring(_value);
}

int get_second_from_map(std::map<std::wstring, int>& _map, std::wstring _value) {
	std::map<std::wstring, int>::iterator it = _map.find(_value);

	return it == _map.end() ? VVIS_UNKNOWW_MAP_SECOND : it->second;
}

std::wstring remove_quotations(std::wstring& _str) {
	Assert(_str.size() > 0, 1, L"NULL str value was recieved", L"Assert, remove_quotations");
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

bool contains_substr(const std::string& _str, const std::string& _substr) {
	return _str.find(_substr) != _str.npos;
}

// yes no exit
std::wstring by_synonyms(const std::wstring& _value) {
	std::wstring copy_value = _value; to_lower_wstr(copy_value);

	std::vector<std::wstring> exit = { L"exit", L"(exit)", L"exit.", L"end" };
	std::vector<std::wstring> yes = { L"y", L"yes", L"yes.", L"yep", L"1", L"true" };
	std::vector<std::wstring> no = { L"n", L"no", L"not.", L"nope", L"0", L"false" };


	std::vector<std::wstring>::iterator it = std::find(exit.begin(), exit.end(), copy_value);
	if (it != exit.end()) return L"exit";

	it = std::find(yes.begin(), yes.end(), copy_value);
	if (it != yes.end()) return L"yes";

	it = std::find(no.begin(), no.end(), copy_value);
	if (it != no.end()) return L"no";

	return _value;

}

std::string v5_get_file_number(const std::string& _number) {
	Assert(_number.size() > 0, 1, L"NULL number value was recieved", L"Assert, v5_get_file_number");
	std::string num = _number;
	std::string base = VVIS_VAMPIRE5_BASE_WSTR;

	size_t num_lenght = num.length(); size_t base_lenght = base.length();
	for (int i = 0; num_lenght != 0; ++i, num.pop_back(), num_lenght = num.length()) {
		base[base_lenght - 1 - i] = num[num_lenght - 1];
	};

	return std::string(base);
}

std::string wstr2str(const std::wstring& _wstr) {
	return std::string(_wstr.begin(), _wstr.end());
}

std::wstring str2wstr(const std::string& _wstr) {
	return std::wstring(_wstr.begin(), _wstr.end());
}

const char* c_str(const std::string& _str) {
	return _str.c_str();
}

bool is_double(std::wstring& _value) {
	try {
		std::stod(_value);
		return true;
	}
	catch (std::invalid_argument& e) {
		return false;
	};
}

int int_rand_result(int a, int b) {
	std::random_device rd;
	std::mt19937 mt(rd());
	if (a > b) {
		int temp = a; a = b; b = temp;
	}
	std::uniform_int_distribution <int> dist(a, b);
	return dist(mt);
}

int double_rand_result(double a, double b) {
	std::random_device rd;
	std::mt19937 mt(rd());
	if (a > b) {
		double temp = a; a = b; b = temp;
	}
	std::uniform_real_distribution <double> dist(a, b);
	return dist(mt);
}
