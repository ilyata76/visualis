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

//#define SCALING_PARAMETERS_CHANGES_UP_X 1.1 // >= 1
//#define SCALING_PARAMETERS_CHANGES_UP_Y 1.1
//#define SCALING_PARAMETERS_CHANGES_UP_Z 1.1
//
//#define SCALING_PARAMETERS_CHANGES_DOWN_X 0.9 // <= 1
//#define SCALING_PARAMETERS_CHANGES_DOWN_Y 0.9
//#define SCALING_PARAMETERS_CHANGES_DOWN_Z 0.9

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

#define ESTRAGNEMENT_CHANGES 0.05

//

#endif 