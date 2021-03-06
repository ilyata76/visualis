#include "./freeglut_settings.hpp"

Freeglut_settings::Freeglut_settings() {
				this->coloring_sample					= VVIS_USING_COLOR;
				this->shape								= VVIS_SHAPE_CONE;
				this->shape_wstr						= VVIS_SHAPE_CONE_WSTR;
				this->additional_rotation				= Angle2f(0.0, 0.0);
				this->estrangement						= 1.0;
				this->global_translation				= Point3f(0.0, 0.0, 0.0);
				this->scaling_parameters				= Parameters3f(20.0, 20.0, 20.0); //
				this->scaling_translation				= Parameters3f(1.0, 1.0, 1.0);
				this->position_of_camera				= Point3f(0.0, 0.0, 0.0);
				this->position_of_element				= Point3f(0.0, 0.0, -100.0);
				this->scaling_parameters_changes		= Parameters3f(VVIS_SCALING_PARAMETERS_CHANGES_X, VVIS_SCALING_PARAMETERS_CHANGES_Y, VVIS_SCALING_PARAMETERS_CHANGES_Z);
				this->translation_changes				= Parameters3f(VVIS_TRANSLATION_CHANGES_X, VVIS_TRANSLATION_CHANGES_Y, VVIS_TRANSLATION_CHANGES_Z);
				this->camera_changes					= Parameters3f(VVIS_CAMERA_CHANGES_X, VVIS_CAMERA_CHANGES_Y, VVIS_CAMERA_CHANGES_Z);
				this->translation_by_element			= VVIS_TRANSLATION_BY_ELEMENT;
				this->fullscreen						= false;
				this->estrangement_changes				= VVIS_ESTRAGNEMENT_CHANGES;
				this->use_additional_subwindows			= true;
				this->polygonrate						= 10;
				this->spinrate							= 1;
				this->gap								= 7;
				this->beta_light						= false;
};

std::wostream& operator<<(std::wostream& _out, const Freeglut_settings& _settings) {
	_out << L"\t Coloring sample\t\t\t: " << std::boolalpha << _settings.coloring_sample << L"\n";
	_out << L"\t Shape\t\t\t\t\t: " << _settings.shape << "|" << _settings.shape_wstr << L"\n";
	_out << L"\t Additional rotation\t\t\t: " << _settings.additional_rotation.phi << "(phi), " << _settings.additional_rotation.theta << L"(theta)\n";
	_out << L"\t Estrangement\t\t\t\t: " << _settings.estrangement << L"\n";
	_out << L"\t Global translation\t\t\t: (" << _settings.global_translation.x << L", " << _settings.global_translation.y << L", " << _settings.global_translation.z << L")\n";
	_out << L"\t Scaling parameters\t\t\t: (" << _settings.scaling_parameters.x << L", " << _settings.scaling_parameters.y << L", " << _settings.scaling_parameters.z << L")\n";
	_out << L"\t Scaling translation\t\t\t: (" << _settings.scaling_translation.x << L", " << _settings.scaling_translation.y << L", " << _settings.scaling_translation.z << L")\n";
	_out << L"\t Position of camera\t\t\t: (" << _settings.position_of_camera.x << L", " << _settings.position_of_camera.y << L", " << _settings.position_of_camera.z << L")\n";
	_out << L"\t Position of element\t\t\t: (" << _settings.position_of_element.x << L", " << _settings.position_of_element.y << L", " << _settings.position_of_element.z << L")\n";
	_out << L"\t Scaling parameters changes\t\t: (" << _settings.scaling_parameters_changes.x << L", " << _settings.scaling_parameters_changes.y << L", " << _settings.scaling_parameters_changes.z << L")\n";
	_out << L"\t Translation changes\t\t\t: (" << _settings.translation_changes.x << L", " << _settings.translation_changes.y << L", " << _settings.translation_changes.z << L")\n";
	_out << L"\t Camera changes\t\t\t\t: (" << _settings.camera_changes.x << L", " << _settings.camera_changes.y << L", " << _settings.camera_changes.z << L")\n";
	_out << L"\t Translation by element\t\t\t: " << std::boolalpha << (_settings.translation_by_element == -1 ? false : true) << L"\n";
	_out << L"\t Fullscreen\t\t\t\t: " << std::boolalpha << _settings.fullscreen << L"\n";
	_out << L"\t Estrangement changes\t\t\t: " << std::boolalpha << _settings.estrangement_changes << L"\n";
	_out << L"\t Additional subwindows\t\t\t: " << std::boolalpha << _settings.use_additional_subwindows << L"\n";
	_out << L"\t Poligon rate\t\t\t\t: " << _settings.polygonrate << L"\n";
	_out << L"\t Spinrate\t\t\t\t: " << _settings.spinrate << L"\n";
	_out << L"\t Gap\t\t\t\t\t: " << _settings.gap << L"\n";
	_out << L"\t Lighting (beta)\t\t\t: " << std::boolalpha << _settings.beta_light << L"\n";
	return _out;
}
