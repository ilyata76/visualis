## Файлы  
* **main**.cpp должен быть зависим от входящих параметров, содержит некоторые TODO
* **defines**.hpp содержит в себе некоторые строковые константы. Здесь же определены названия файлов и их форматы, например, `.vvis`, а также *"заглушки"*, используемые в файлах, сигнализирующие о том, что поле класса не было инициализировано или это было сделано с ошибкой
* **parser-v5**.cpp содержит в себе namespace parser, хранит одну глобальную переменную - путь до папки; просто собирает отформатированную строку `wstring` для последующей работы с ней. Функция `get_string(%path%)` возвращает функцию `get_out(%index%)`, которая уже будет стучаться к конкретному файлу
    * parser-v5.hpp
        * string
        * fstream для чтения файлов
        * algorithm для замены символов
        * defines.hpp
        * assert.hpp <- из Exceptio
* **converter-v5**.cpp содержит в себе конвертор, который просто должен склеить вампировские файлы в один; создаёт новый файл расширения, определённого в defines.hpp
    * converter-v5.hpp
        * string
        * algorithm
        * fstream
        * defines.hpp
        * assert.hpp <- из Exceptio
* **point-spin**.cpp содержит в себе раскрытие классов `Point` и `Spin`, которые будут составной частью класса `Vertex`. Каждый из них содержит 3 координаты. Определены сеттеры и геттеры, работающие обобщённо: например, `Spin.set(L'x', 1.0)`, `Spin.set(L"sx", 1.0)`. Работает уже в namespace vvis :: namespace creator
    * point-spin.hpp
        * string
        * assert.hpp <- из Exceptio
        * defines.hpp
* **creator_of_vertex_arr**.cpp содежрит в себе одну глобальную переменную - путь до папки (отличную от той, что определена в parser-v5). Функция `create_arry(%path%)` работает аналогично функции get_string из parser-v5, возвращает `get_out(%index%)`, которая возвращает вектор из `Vertex`. Класс `Vertex` содежрит в себе классы Point, Spin, а также номер спина, number, материал, material, и слой, layer. Сеттеров нет, только геттеры. При работе с `.vvis` умеет определять комментарии, начало которых определено в defines.hpp, но только тогда, когда строка начинается с #, в противном случае поведение пока что не определено, должна выскакивать ошибка.  Работает в namespace vvis :: namespace creator
    ```vvis
    #	number	count  
        9	9  
    #M	L	X	Y	Z	SX	SY	SZ  
    0	0	0	0	0	-0.968655	0.24516	0.0400459  
            ...
    #  
    # КОММЕНТ  
    #  
            ...
    0	0	10.028	0	0	-0.970037	0.239893	0.0384543 >
    ```
    * creator_of_vertex_arr.hpp
        * point-spin.hpp
        * string
        * fstream
        * vector
        * sstream - используется для обработки строк из getline
* **shape**.cpp содержит в себе класс(-ы) конечных фигур, которые вспоследствии будут отрисованы
    * shape.hpp
        * creator_of_vertex_arr.hpp
        * color_class.hpp
        * glut.h для того, чтобы методы классов уже умели рисовать
        * math.h
* **color_cass**.cpp содержит в себе определение класса цвета
    * color_cass.hpp
        * math.h
        * point-spin.hpp
        * defines.hpp

## Пространства имён
Основные функции  
При вариациях параметров выбраны лишь одни из.  
```cpp 
// работает с файлами vampire5 (6?)
namespace vampire5 {
    namespace parser {
        int get_count(const std::wstring& path_to_file); // получает количество из первой строки
        std::wstring get_spin_file_name(const int& number); // генерирует строку spins-xxx
        std::wstring get_out(const int& number); // - возвращаемая из get_string - возвращает форматную строку
        special_fun get_string(const std::wstring& path_to_folder); // - возвращает get_out, сохраняет путь до папки
    }
    namespace converter {
        std::wstring get_number_of_file_from_f_str(const std::wstring& f_str, int& index); // получает число из строки
        std::wstring get_count_from_f_str(const std::wstring& f_str, int& index); // получает количество из строки
        std::wstring get_output_str(const std::wstring& f_str, int& index); // обрабатывает конструкцию m;l;x;y;z;sx;sy;sz!
        std::wstring get_file_name(const std::wstring& number); // аналогичен в parser-v5
        bool convert(const std::wstring& formatted_str, const std::wstring& path_to_folder, int& index);
        /*заглавная строка, конвертирует файлы в склеенный формат, определённый в defines.hpp (.vvis) */
    }
}

// vvis работает с конечным склеенным файлом
namespace vvis {
    namespace creator {
        class Point;
        class Spin; /*эти классы содержат в себе сеттеры, геттеры, а также по три protected-координаты*/

        class Vertex; // заглавный класс, содержит геттеры
            Vertex(Point& p, Spin& s, unsigned int number, short int layer, short int material); // его основной конструктор

        std::vector <Vertex> get_out(const int& index); // парсит файл и создаёт вертекс
        special_func create_arry(const std::wstring& p_t_folder); // запоминает путь (как в parse-v5), возвращает get_out

        std::wstring get_file_name(const int& index); // получить имя (аналогично parse-v5) типа spins-xxx
    }
    namespace visualization {

        class VvisColor_3f; // содержит в себе 3 поля RGB
            VvisColor_3f get_color_by_direction(int x, int y, int z); // для определение цвета конечного элемента (WIP)
            VvisColor_3f get_color_by_direction(vvis::creator::Spin& spin);

        class Shape; // содержит в себе Vertex. Это родительский класс для всех фигур

        class Cone : public Shape; // содержит в себе два эейлеровых угла
            bool set_draw_configuration();	// на основании this->vertex построит конфигурацию		
            bool draw(double base, double height, GLint slices, GLint stacks, vvis::visualization::VvisColor_3f color);  // рисует
            wchar_t info_wchar(); // вернёт L'c'

        float get_euler_phi(const double& sx, const double& sy, const double& sz);
        float get_euler_theta(const double& sx, const double& sy, const double& sz);

        ////////////////////////////

        struct vec3; // три точки double
        struct app_freeglut;   // большой набор глобальных изменяемых переменных, связанных с конечным окном


        void draw_sample(app_freeglut& app, int argc, char** argv); // - рисует окно и образец с помощью вспомогательных функций 
            void display();
            void draw_shape(int index);

            void n_keys(unsigned char key, int x, int y);
            void s_keys(int key, int x, int y);

        // Конструктор app_freeglut, где всё определяется через defines.hpp

        vvis::visualization::app_freeglut::app_freeglut(std::vector<vvis::creator::Vertex>& vect_of_vertexes, wchar_t shape, bool use_color, int index_of_line) {
            this->index_of_line = index_of_line;
            this->additional_rotation_phi = 0.0;
            this->additional_rotation_theta = 0.0;

            this->estrangement = 1.0;

            this->use_color = use_color;
            this->shape = shape;

            this->height_of_window = 0;
            this->width_of_window = 0;

            this->global_translation = vec3(0., 0., 0.);
            this->scaling_parameters = vec3(1., 1., 1.);
            this->scaling_translation = vec3(1./32., 1./32., 1./32.);
            this->position_of_camera = vec3(0., 0., 0.);
            this->position_of_element = vec3(0., 0., -100.);

            this->scaling_translation_changes_up = vec3(SCALING_PARAMETERS_CHANGES_UP_X, SCALING_PARAMETERS_CHANGES_UP_Y, SCALING_PARAMETERS_CHANGES_UP_Z);
            this->scaling_translation_changes_down = vec3(SCALING_PARAMETERS_CHANGES_DOWN_X, SCALING_PARAMETERS_CHANGES_DOWN_Y, SCALING_PARAMETERS_CHANGES_DOWN_Z);

            this->translation_changes = vec3(TRANSLATION_CHANGES_X, TRANSLATION_CHANGES_Y, TRANSLATION_CHANGES_Z);

            this->translation_by_element = ELEMENT_TRANSLATION;

            this->camera_changes = vec3(CAMERA_CHANGES_X, CAMERA_CHANGES_Y, CAMERA_CHANGES_Z);

            this->estrangement_changes = ESTRAGNEMENT_CHANGES;

            this->vect_of_vertexes = vect_of_vertexes;
        }


    }
}
```
  
Конструктор `app_freeglut` должен полностью определять параметры окна и образца, изменения его ориентации, поворотов, масштабирования, трансляций и пр.  