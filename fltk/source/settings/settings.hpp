#pragma once

#ifndef MY_SETTINGS_HPP
#define MY_SETTINGS_HPP

	#include <string>

	constexpr char PATH_PLUG[] = "none";

	class Settings {
		protected:
			int argc;
			char** argv;

			int width;			// ширина окна
			int height;			// высотка окна
			int gap;			// gap, который будет отделять glut окно от границ обычного

			bool ready_to_visualization;

			std::string path_to_folder;

			std::string path_to_sconfiguration_file;

			std::string path_to_spins_file;

			std::string path_to_atoms_file;

		public:
			Settings() {
				this->argc = 0;
				this->argv = {};

				this->width = 300;
				this->height = 300;
				this->gap = 5;

				this->path_to_folder = PATH_PLUG;
				this->path_to_sconfiguration_file = PATH_PLUG;
				this->path_to_spins_file = PATH_PLUG;
				this->path_to_atoms_file = PATH_PLUG;

				this->ready_to_visualization = false;
			};

			Settings(int argc, char** argv) {
				this->argc = argc;
				this->argv = argv;

				this->width = 300;
				this->height = 300;
				this->gap = 5;

				this->path_to_folder = PATH_PLUG;
				this->path_to_sconfiguration_file = PATH_PLUG;
				this->path_to_spins_file = PATH_PLUG;
				this->path_to_atoms_file = PATH_PLUG;

				this->ready_to_visualization = false;
			};

			~Settings() {};

			friend class MainWindow;
			friend class VampireConfigWindow;
			friend bool windowing(Settings* settings);
	};

#endif // !MY_SETTINGS_HPP
