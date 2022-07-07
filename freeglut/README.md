# visualis freeglut
  alpha 0.4.0  
  
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
    + `get` - восстанавливает текущие настройки из файла по тем же путям, в том числе вид на образец
    + `reset` - сбрасывает в текущей консоли все настройки (не в файле)
+ `set` - позволяет устанавливать конкретную доступную для изменения (указано [C]) настройку 
    + `folderpath` - позволяет установить путь до папки, в которой находятся файлы либо нуждающиеся в конвертировании, либо уже конвертированные. Используется в связке с *filenumber*
    + `filenumber` - позволяет установить номер файла. Используется в связке с *folderpath*
    + `filepath` - позволяет установить путь до файла sconfiguration-xxxxxxxx.vvis
    + `spinindex` - устанавливает номер отрисовываемого спина (по умолчанию: все)
    + `settingsfolder` - устанавливает путь до папки, в которой лежит файл visualis-settings.json. При визуализации может быть восстановлен через *folderpath*, *filepath*
    + `settingsfolder` - устанавливает путь до файла visualis-settings.json
    + `coloring` - устанавливает нужно ли использовать цветовую окраску образца (по умолчанию: нет)
    + `backgroundcolor` - устанавливает цвет фона RGB (по умолчанию: белый фон) в случае, если указано лишь 3 int-значения. Если 4, то для подокна по первому параметру
    + `fullscreen` - устанавливает инструкцию: нужен ли полный экран (по умолчанию: нет)
    + `shape` - устанавливает фигуру, которой будет отрисовываться каждый спин (по умолчанию: конус)
    + `translationbyelement` - устанавливает, нужно ли инвертировать нажатие клавиш
    + `estrangementchanges` - устанавливает чувствительность изменения увеличения или уменьшения образца
    + `scalingchanges` - устанавливает чувствительность изменения увеличения или уменьшения размеров каждого *shape*
    + `translationchanges` - устанавливает чувствительность перемещения образца вдоль плоскости XY
    + `camerachanges` - устанавливает чувствительность перемещения камеры
    + `spinrate`- устанавливает количество отрисовываемых конусов (каждый *spinrate* конус будет отрисован)
    + `gap`- устанавливает расстояние между подокнами
    + `subwindowing` - устанавливает, используются ли дополнительные подокна в приложении (лог, статистика, оси)
    + `polygonrate` - устанавливает параметр качества отображаемых объектов
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
  
### Кнопки мыши главного окна
При нажатии ПКМ открывается меню, где можно: 
+ выбрать цвет фона из ряда существующих (в т.ч. указанных для каждой из областей в консоли)
+ изменить параметр *gap*, отвечающий за расстояние между подокнами
+ убрать или отрисовать дополнительные подокна
  
### Клавиши подокна отрисовки
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
+ Увеличить или уменьшить отрисовываемые фигуры `PAGE UP`/`PAGE DOWN`
+ Выйти: `ESC`
  
### Кнопки и движения мыши подокна отрисовки
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
+ изменить количество отрисовываемых фигур *spinrate*
+ инвертировать управление
+ изменить качество отрисовываемых фигур *polygonrate*
+ выбрать фигуру
+ восстановить *gap*, если тот был указан 0
+ выбрать цвет фона из ряда существующих (в т.ч. указанных для каждой из областей в консоли)
+ включить цветное отражение света (beta)

### Подокна логов и статистика
+ С помощью клавиш `arrow UP`/`arrow DOWN` можно прокручивать текст
+ -- или с помощью прокручивания колеса мыши
+ При нажатии ПКМ - меню:
    + позволяет изменить цвет фона
    + изменить шрифт
    + инвертировать чёрный текст в белый и наоборот
    + (для логов) очистить лог
  
### Подокно осей
  Оси вращаются вместе с образцом, повторяя *camera position* и *additional rotation*  
  При нажатии ПКМ - меню:  
+ использовать линии или конусы
+ скрыть/показать названия осей
+ изменить цвет фона
+ инвертировать чёрный текст в белый и наоборот
  
## Другое
+ Позволяет пропускать комментарии в .data файлах (v6), даже если те написаны не в начале строки
+ То же - в файлах .vvis
+ Переход к визуализации всегда инициализирует папку настроек, даже если тот не был указан, но это не значит, что будет создан файл (будет создан только при нажатии *save*)
+ Для цвета подокон есть несколько стандартных + те, что указал пользователь (все 5)
+ При определённых параметрах окна (если оно слишком вытянуто в высоту или сжато) дополнительные подокна не показываются
+ Оси - в перспективной проекции, образец - в ортогональной

## Зависимости
+ **[Exceptio](https://github.com/ilyata76/tia-Exceptio.git)** для обработки исключений и ошибок
+ **[freeglut](https://github.com/FreeGLUTProject/freeglut.git)** для рисования
+ **[json](https://github.com/nlohmann/json.git)** для хранения настроек  

## Текущие ограничения
+ C++17
+ Windows 10 / Ubuntu 22.04LTS verified the project build

## Компиляция CMake
  Можно склонировать репозиторий, например, так
```s
    git clone git@github.com:ilyata76/visualis.git
```
  Далее для компиляции `freeglut`-версии:
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
  **Для компиляции проекта в LINUX нужно лишь единственное условие, чтобы компилировалась библиотека freeGLUT.**

## Текущее быстродействие
- [issues/Оптимизация](https://github.com/ilyata76/visualis/issues/12)

## Порядок действий V6
```

    ____   ____.___  _____________ ___  _____  .____    .___  _________
    \   \ /   /|   |/   _____/    |   \/  _  \ |    |   |   |/  _____/
     \   Y   / |   |\_____  \|    |   /  /_\  \|    |   |   |\_____ \
      \     /  |   |/        \    |  /    |    \    |___|   |/       \
       \___/   |___/_______  /______/\____|__  /_______ \___/_______ /
                           \/                \/        \/          \/

vvis > set folp ../temp/b

        Path to folder "../temp/b" has been set up

vvis > set fn 25

        File number "25" has been set up

vvis > convert v6

        atoms file exists? : true
        spins file exists? : true
        Parsing and converting... : Successful!

vvis > visualize

        sconfiguration file exists? : true
        loading... : 6912 vertexes has been loaded
        visualizing...

```


## PICTURES AND EXAMPLES
### Актуально с alpha 0.3.0
Основные направления и возможности отрисовки:  
![directions](https://github.com/ilyata76/visualis/blob/master/freeglut/pics/alpha-0.3.0/Directions_alpha_0_3_0.png)  
Фигуры для отрисовки:  
![shapes](https://github.com/ilyata76/visualis/blob/master/freeglut/pics/alpha-0.3.0/Shapes_alpha_0_3_0.png)  
![cube_shapes](https://github.com/ilyata76/visualis/blob/master/freeglut/pics/alpha-0.3.0/Co_cube_alpha_0_3_0.png)  
Влияние *spinrate* (отрисовано в конусах)  
![cube_spinrating](https://github.com/ilyata76/visualis/blob/master/freeglut/pics/alpha-0.3.0/Co_cube_spinrating_alpha_0_3_0.png)  
Стандартный интерфейс (отрисовано в сферах)  
![vertex_interface](https://github.com/ilyata76/visualis/blob/master/freeglut/pics/alpha-0.3.0/Co_vertex_spheres_interface_alpha_0_3_0.png)  
Выпадающие меню на ПКМ (стрелки указывают только на область, не обязательно в конкретной точке, отрисовано в гиперболизированных стрелках):  
![popup_menus](https://github.com/ilyata76/visualis/blob/master/freeglut/pics/alpha-0.3.0/Popup_menus_alpha_0_3_0.png)  
Примеры других интерфейсов (отрисовано: в сферах(1) и в стрелках (2)):  
![co_dw_spheres](https://github.com/ilyata76/visualis/blob/master/freeglut/pics/alpha-0.3.0/Co_DW_spheres_alpha_0_3_0.png)  
![co_dw_spheres](https://github.com/ilyata76/visualis/blob/master/freeglut/pics/alpha-0.3.0/Co_DW_arrows_alpha_0_3_0.png)  
### 0.4.0 сборка доступна для Linux
Проверено для `Ubuntu 22.04 LTS, X11`  
![co_cube_ubuntu](https://github.com/ilyata76/visualis/blob/master/freeglut/pics/alpha-0.4.0/Co_cube_alpha_0_4_0_ubuntu_22.04_LTS.png)  
![co_vertex_ubuntu](https://github.com/ilyata76/visualis/blob/master/freeglut/pics/alpha-0.4.0/Co_vertex_alpha_0_4_0_ubuntu_22.04LTS_lighting.png)  