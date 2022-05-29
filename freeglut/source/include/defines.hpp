#pragma once

#ifndef DEFINES_HPP
#define DEFINES_HPP


#define BASE_NUMBER_OF_FILE_V5 L"00000000"
#define NAME_OF_ATOMS_FILE_V5 L"atoms-coords"
#define FORMAT_OF_ATOMS_FILE_V5 L".data"
#define FORMAT_OF_SPINS_FILE_V5 L".data"
#define START_OF_SPINS_NAME_FILE_V5 L"spins-"

#define START_OF_OUR_FILE L"sconfiguration-"
#define FORMAT_OF_OUR_FILE L".vvis"
#define COMMENT_OF_OUR_FILE L"#"

#define PLUG_1 L';'
#define PLUG_2 L'!'
#define PLUG_3 L'?'

#define DOUBLE_PLUG_VVIS 0.0
#define INT_PLUG_VVIS 0



#define ROTATE_Z_FOR_SECOND_REPRESENTATION 0 // 0 for not
#define COUNTERCLOCKWISE 1 // use 0 for not
#define INVERT_Y_FOR_THIRD_REPRESENTATION 0 // use 0 for not



// рисование

#define SHAPE_CONE L'c'
#define SHAPE_CONE_STR L"cone"
#define SHAPE_NOTHING L'n'

#define DRAW_ALL -1

#define SCALING_PARAMETERS_CHANGES_X 0.3 // +-
#define SCALING_PARAMETERS_CHANGES_Y 0.3
#define SCALING_PARAMETERS_CHANGES_Z 0.3

#define TRANSLATION_CHANGES_X 0.5
#define TRANSLATION_CHANGES_Y 0.5
#define TRANSLATION_CHANGES_Z 0.5

#define ELEMENT_TRANSLATION -1.0 // 1 if left-left; -1 left-right <- translation by head

#define CAMERA_CHANGES_X 0.5
#define CAMERA_CHANGES_Y 0.5
#define CAMERA_CHANGES_Z 0.5

#define ESTRAGNEMENT_CHANGES 0.03

#define MOVEMENTS_BY_ARROWS_MULTIPLY_SENSIVITY 0.7 // /= for decrease *= for increase
#define MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY 0.7
#define MOVEMENTS_BY_SHIFTSPACE_MULTIPLY_SENSIVITY 0.9

#define SCALING_MULTIPLY_SENSIVITY_X 0.9
#define SCALING_MULTIPLY_SENSIVITY_Y 0.9
#define SCALING_MULTIPLY_SENSIVITY_Z 0.9

// TODO: increase, decrease by 0.9, 0.8, 0.7 etc.


#define INTERPETATOR_PATH_PLUG_WSTR L"<nothing>"
#define INTERPETATOR_NUMBER_PLUG_INT 0

#define VISUALIS_SETTINGS_JSON L"visualis-settings.json"


//

#endif 