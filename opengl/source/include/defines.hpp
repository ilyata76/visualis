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

#define SHAPE_CONE 'c'
#define SHAPE_CONE_STR L"cone"

#define ROTATE_Z_FO_SECOND_REPRESENTATION 0 // 0 for not
#define COUNTERCLOCKWISE 1 // use 0 for not
#define INVERT_Y_FOR_THIRD_REPRESENTATION 0 // use 0 for not

#define DRAW_ALL -1



#define TRANSLATION_CONST 0.1
#define TRANSLATION_BY_HEAD -1.0 // use 1 for not or -1 for yes

#define SCALING_SHAPE_UPPER_LIMIT 3
#define SCALING_SHAPE_LOWER_LIMIT 0.1

#define SCALING_TRANSLATION_UPPER_LIMIT 1.5
#define SCALING_TRANSLATION_LOWER_LIMIT 0.5

#endif 