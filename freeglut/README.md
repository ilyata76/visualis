# visualis freeglut
  alpha 0.2.0  
  
# Консольное приложение

## Консольное начало
```

    ____   ____.___  _____________ ___  _____  .____    .___  _________
    \   \ /   /|   |/   _____/    |   \/  _  \ |    |   |   |/  _____/
     \   Y   / |   |\_____  \|    |   /  /_\  \|    |   |   |\_____ \
      \     /  |   |/        \    |  /    |    \    |___|   |/       \
       \___/   |___/_______  /______/\____|__  /_______ \___/_______ /
                           \/                \/        \/          \/

vvis > help

        Usage : help <subcommand: {settings, set, unset, convert, visualize, reset, restart}>
        Exit  : exit

vvis > help settings

        settings show
          -- <nothing> : shows CONSOLE settings (paths, filenumber etc.)
          -- all       : shows ALL settings (including spinrate, main_window, console_settings, window(freeglut)_settings)
          -- console   : shows only CONSOLE settings (paths, filenumber etc.)
          -- window    : shows only WINDOW(freeglut)_settings (coloring, positions etc.)

        settings save
          -- <nothing> : saves ALL settings in visualis-settings.json file by path (in order of importance):
                       : path to settings file, path to settings folder, path to folder

        settings get
          -- <nothing> : restores ALL settings from visualis-settings.json file by path (in order of importance):
                       : path to settings file, path to settings folder, path to folder

        settings reset
          -- <nothing> : resets ALL settings in console (not file)
                       : also command "reset" does the same

        Aliases: settings, setting, setgs, setg, sgs

vvis >
```
  Ожидается, что после приглашения ввода, `vvis >`, пользователем будут введены доступные команды (синонимичные им указаны в help)
+ `help` - позволяет получить справку по каждой из последующих комманд, а также пример их применения и синонимы
+ `settings` - позволяет работать с настройками как консольного приложения, так и отрисовки в окне. Позволяет их сохранять или восстанавливать из файла
    + `show` - показывает текущие настройки (по умолчанию через *console*)
        + `all` - показывает ВСЕ текущие настройки (не обязательно *console + window*)
        + `console` - показывает настройки консольного начала, например, пути до папок и файлов
        + `window` - показывает настройки, которые будут применятся при рисовании
    + `save` - сохраняет текущие настройки по пути *settingsfile* или *settingsfolder*, или *folderpath* (в порядке уменьшения важности)
    + `get` - восстанавливает текущие настройки из файла по тем же путям
    + `reset` - сбрасывает в текущей консоли все настройки (не в файле)
+ `set` - позволяет устанавливать конкретную доступную для изменения (указано [C]) настройку 
    + `folderpath` - позволяет установить путь до папки, в которой находятся файлы либо нуждающиеся в конвертировании, либо уже конвертированные. Используется в связке с *filenumber*
    + `filenumber` - позволяет установить номер файла. Используется в связке с *folderpath*
    + `filepath` - позволяет установить путь до файла sconfiguration-xxxxxxxx.vvis
    + `spinindex` - устанавливает номер отрисовываемого спина (по умолчанию: все)
    + `settingsfolder` - устанавливает путь до папки, в которой лежит файл visualis-settings.json. При визуализации может быть восстановлен через *folderpath*, *filepath*
    + `settingsfolder` - устанавливает путь до файла visualis-settings.json
    + `coloring` - устанавливает нужно ли использовать цветовую окраску образца (по умолчанию: нет)
    + `backgroundcolor` - устанавливает цвет фона RGB (по умолчанию: белый фон)
    + `fullscreen` - устанавливает инструкцию: нужен ли полный экран (по умолчанию: нет)
    + `shape` - устанавливает фигуру, которой будет отрисовываться каждый спин (по умолчанию: конус)
    + `translationbyelement` - устанавливает, нужно ли инвертировать нажатие клавиш
    + `estrangementchanges` - устанавливает чувствительность изменения увеличения или уменьшения образца
    + `scalingchanges` - устанавливает чувствительность изменения увеличения или уменьшения размеров каждого *shape*
    + `translationchanges` - устанавливает чувствительность перемещения образца вдоль плоскости XY
    + `camerachanges` - устанавливает чувствительность перемещения камеры
    + `spinrate`- устанавливает количество отрисовываемых конусов (каждый *spinrate* конус будет отрисован)
+ `unset` - позволяет восстановить стандартную настройку
+ `convert` - конвертирует исходные файлы (по доступу через *filepath*) в sconfiguration-xxxxxxxx.vvis
    + `v6` конвертирует файлы [Vampire6](https://github.com/richard-evans/vampire), Vampire5
+ `visualize` - визуализирует систему, находя sconfiguration-xxxxxxxx.vvis (по умолчанию через *folder*)
    + `folder` - ищет sconfiguration-xxxxxxxx.vvis с номером *filenumber* по пути *folderpath*. Путь до папки настроек принимается за *folderpath*, если таковой не был указан
    + `file` - ищет sconfiguration-xxxxxxxx.vvis по пути *filepath*. Путь до папки настроек принимается за папку, в которой этот файл находится, если таковой не был указан
+ `reset` сбрасывает текущие настройки до начальных (синонимичен к *settings reset*)
+ `restart` полностью перезагружает программу
+ `exit` выход из приложения

## Оконное продолжение
  Слева от образца находится подокно с осями координат, изменяющимися вместе с главным окном, при нажатии ПКМ и выпадении меню:  
+ позволяет скрыть или показать названия осей
+ позволяет заменить линии на конусы
  
### Клавиши главного окна
  При настройке by_head в левую-правую сторону будет как бы поворачиваться голова, сама камера:  
+ Поднять/опустить камеру: `W`/`S`  
+ Повернуть влево/вправо камеру: `A`/`D`  
  Следующие операции меняют местоположение всего образца на полотне (by_head):  
+ Вверх/вниз: `KEY_ARROW_UP`/`KEY_ARROW_DOWN`  
+ Влево/вправо: `KEY_ARROW_LEF`/`KEY_ARROW_RIGHT`  
  Следующие операции меняют ориентацию объекта в пространстве, поворачивая его вместе с локальными осями:  
+ Повернуть вокруг оси X : `I`/`K`  
+ Повернуть вокруг оси Y : `J`/`L`  
  Приблизить или отдалить (а также при сверхбольшом приближении можно посмотреть "за спину"):
+ Приблизить: `L_CTRL` или `L_SHIFT`
+ Отдалить: `SPACEBAR`
  Выйти: `esc`
  
### Кнопки и движения мыши главного окна
  Мышь чувствительнее клавиш при скролле в два раза. В два раза менее - при перемещении и повороте образца. При увеличении размеров фигур - такой же чувствительности.
  При зажатой клавише мыши можно:  
+ перемещать образец вдоль плоскости XY
При зажатой клавише мыши и кнопки `ALT_LEFT` можно:
+ вращать образец вдоль осей X или Y
При прокручивании колеса можно:
+ приближать или отдалять образец, а также смотреть ему за спину
При нажатии ПКМ открывается выпадающее меню, в котором можно:
+ включить/выключить цвет
+ изменить чувствительность всех клавиш и движения мыши (неразделимо)
+ как бы нажать на каждую клавишу
+ сохранить, восстановить, сбросить и сбросить в файле visualis-settings.json настройки, касающиеся поведения клавиш. Восстанавливаемые настройки более полны, что позволяет восстановить и вид на образец (положение камеры и т.д.)
+ изменить количество отрисовываемых конусов *spinrate*
+ инвертировать управление

## Другое
+ Позволяет пропускать комментарии в .data файлах (v6), даже если те написаны не в начале строки
+ То же - в файлах .vvis
+ Переход к визуализации всегда инициализирует папку настроек, даже если тот не был указан, но это не значит, что будет создан файл (будет создан только при нажатии *save*)

## Зависимости
+ **[Exceptio](https://github.com/ilyata76/tia-Exceptio.git)** для обработки исключений и ошибок
+ **[freeglut](https://github.com/FreeGLUTProject/freeglut.git)** для рисования
+ **[json](https://github.com/nlohmann/json.git)** для хранения настроек  

## Текущие ограничения
+ C++17
+ only Windows
+ console only

## Компиляция CMake
  Можно склонировать репозиторий со всеми подмодулями  
```s
    git clone --recursive-submodules git@github.com:ilyata76/visualis.git
```
  Или же без них, но в папки, находящиеся по пути `source/libraries/`, требуется разместить соответствующие библиотеки (см. зависимости)  
```
    cd ./freeglut/
    mkdir build 
    cd build
    cmake ..
    cmake --build .
```
  Существующие опции
```s
    USE_STATIC "Use static freeglut library" ON
    COMPILE_FREEGLUT_EXAMPLES "Compile freeglut examples?" OFF
```
  Чтобы собрать проект с динамической freeglut библиотекой, достаточно:
```
    cmake -DUSE_STATIC=OFF ..
    cmake --build .
```

## Текущее быстродействие
- [issues/Оптимизация](https://github.com/ilyata76/visualis/issues/12)

## Examples
### alpha 0.1.0
  Зависимость цвета от направления:
![colorful_vertex](https://github.com/ilyata76/visualis/blob/master/freeglut/pics/colorful_vertex_alpha_0_1_0.png)
  Кубик через конусы и выпадающее меню:
![curie_ni](https://github.com/ilyata76/visualis/blob/master/freeglut/pics/Curie_Ni_colorful_alpha_0_1_0.png)
  Увеличенные конусы для кубика:
![huge_cones](https://github.com/ilyata76/visualis/blob/master/freeglut/pics/cube_with_huge_cones_alpha_0_1_0.png)
### alpha 0.2.0
  Тот же кубик, но новый
![curie_ni_a_0_2_0](https://github.com/ilyata76/visualis/blob/master/freeglut/pics/Curie_Ni_colorful_alpha_0_2_0.png)
  Движение доменной стенки:
![dw_many_a_0_2_0](https://github.com/ilyata76/visualis/blob/master/freeglut/pics/DW_alpha_0_2_0_fully_count.png)
  Движение доменной стенки, если бы рисовался каждый десятый конус:
![dw_a_0_2_0](https://github.com/ilyata76/visualis/blob/master/freeglut/pics/DW_alpha_0_2_0.png)


