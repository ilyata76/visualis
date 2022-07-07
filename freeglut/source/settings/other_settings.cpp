#include "./other_settings.hpp"


Other_settings::Other_settings() {
	this->axis_by_cones					 = false;
	this->show_axis_names				 = true;

	this->font_stats					 = ((void*)0x0002); // 9_BY_15
	this->font_log						 = ((void*)0x0002); // 9_BY_15

	this->inverted_black_text_stats		 = false;
	this->inverted_black_text_log		 = false;
	this->inverted_black_text_axis		 = false;

	this->transl_stats					 = { 0.0, 0.0, 0.0 };
	this->transl_log					 = { 0.0, 0.0, 0.0 };
}


std::wostream& operator<<(std::wostream& _out, const Other_settings& _settings) {
	_out << L"\t Axis by cones\t\t\t: " << std::boolalpha << _settings.axis_by_cones << L"\n";
	_out << L"\t Show axis names\t\t\t: " << std::boolalpha << _settings.show_axis_names << L"\n";
	_out << L"\t Inverted black text in stats\t\t\t: " << std::boolalpha << _settings.inverted_black_text_stats << L"\n";
	_out << L"\t Inverted black text in logs\t\t\t: " << std::boolalpha << _settings.inverted_black_text_log << L"\n";
	_out << L"\t Inverted black text in axis\t\t\t: " << std::boolalpha << _settings.inverted_black_text_axis << L"\n";
	_out << L"\t Translation stats\t\t\t: (" << _settings.transl_stats.x << L", " << _settings.transl_stats.y << L", " << _settings.transl_stats.z << L"\n";
	_out << L"\t Translation log\t\t\t: (" << _settings.transl_log.x << L", " << _settings.transl_log.y << L", " << _settings.transl_log.z << L"\n";
	return _out;
}
