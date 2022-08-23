#pragma once


#ifndef GLOBAL_DEFINES
#define GLOBAL_DEFINES

/// INTERPRETATOR

constexpr char VVIS_PATH_PLUG_WSTR[] = "<nothing>";
constexpr int VVIS_INT_PLUG = -1;

/// FILE NAMES AND FILES

constexpr char VVIS_SETTINGS_FILE_NAME_WSTR[] = "visualis-settings.json";
constexpr char VVIS_VVIS_FILE_START_NAME_WSTR[] = "sconfiguration-";
constexpr char VVIS_VVIS_FILE_FORMAT_WSTR[] = ".vvis";

constexpr char VVIS_VAMPIRE5_BASE_WSTR[] = "00000000";
constexpr char VVIS_VAMPIRE5_ATOMS_NAME_WSTR[] = "atoms-coords";
constexpr char VVIS_VAMPIRE5_SPINS_START_NAME_WSTR[] = "spins-";
constexpr char VVIS_VAMPIRE5_ATOMS_FORMAT_WSTR[] = ".data";
constexpr char VVIS_VAMPIRE5_SPINS_FORMAT_WSTR[] = ".data";

constexpr wchar_t VVIS_VVIS_COMMENT = L'#';
constexpr wchar_t VVIS_VAMPIRE5_DATA_COMMENT = L'#';
constexpr wchar_t VVIS_VVIS_SEPARATOR = L'\t';

/// DRAWER SHAPES

constexpr wchar_t VVIS_SHAPE_CONE = L'c';
constexpr wchar_t VVIS_SHAPE_CONE_WSTR[] = L"cone";
constexpr wchar_t VVIS_SHAPE_NOTHING = L'n';
constexpr wchar_t VVIS_SHAPE_NOTHING_WSTR[] = L"nothing";
constexpr wchar_t VVIS_SHAPE_SPHERE = L's';
constexpr wchar_t VVIS_SHAPE_SPHERE_WSTR[] = L"sphere";
constexpr wchar_t VVIS_SHAPE_ARROW = L'a';
constexpr wchar_t VVIS_SHAPE_ARROW_WSTR[] = L"arrow";

/// DRAWER OPTIONS

constexpr int VVIS_DRAW_ALL = -1;
constexpr bool VVIS_USING_COLOR = false;
constexpr bool VVIS_COUNTERCLOCKWISE = true;

constexpr double VVIS_SCALING_PARAMETERS_CHANGES_X = 0.3;
constexpr double  VVIS_SCALING_PARAMETERS_CHANGES_Y = 0.3;
constexpr double  VVIS_SCALING_PARAMETERS_CHANGES_Z = 0.3;

constexpr double VVIS_TRANSLATION_CHANGES_X = 0.5;
constexpr double VVIS_TRANSLATION_CHANGES_Y = 0.5;
constexpr double VVIS_TRANSLATION_CHANGES_Z = 0.5;

constexpr double VVIS_CAMERA_CHANGES_X = 0.5;
constexpr double VVIS_CAMERA_CHANGES_Y = 0.5;
constexpr double VVIS_CAMERA_CHANGES_Z = 0.5;

constexpr double VVIS_ESTRAGNEMENT_CHANGES = 0.03;

constexpr double VVIS_TRANSLATION_BY_ELEMENT = -1.0; // 1 if left-left; -1 left-right <- translation by head

constexpr double MOVEMENTS_BY_ARROWS_MULTIPLY_SENSIVITY = 0.7; // /= for decrease *= for increase
constexpr double MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY = 0.7;
constexpr double MOVEMENTS_BY_SHIFTSPACE_MULTIPLY_SENSIVITY = 0.9;

constexpr double SCALING_MULTIPLY_SENSIVITY_X = 0.9;
constexpr double SCALING_MULTIPLY_SENSIVITY_Y = 0.9;
constexpr double SCALING_MULTIPLY_SENSIVITY_Z = 0.9;

/// BLOCKS VISUALIS-SETTINGS.JSON

constexpr char VVIS_GLOBAL_SETTINGS[] = "global";
constexpr char VVIS_FREEGLUT_SETTINGS[] = "drawer";
constexpr char VVIS_WINDOWS_SETTINGS[] = "windows";
constexpr char VVIS_OTHER_SETTINGS[] = "other";

/// UNKNOW_MAP_SECOND

constexpr auto VVIS_UNKNOWW_MAP_SECOND = 9911;

#endif