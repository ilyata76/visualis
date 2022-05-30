# visualis freeglut
  
## Roadmap
- [x] .data vampire parser
- [x] convertor to .vvis
- [x] .vvis -> vertex(point, spin) array
- [x] adding the freeglut library in project
- [x] vertex -> shape::cone
    - [x] printing simple cone
    - [x] printing full sample
- [x] picture -> camera and sample movements
    - [x] colorful
- [x] -> menu with settings
- [x] interactive main-function with cmds interpetator
- [x] запоминание настроек (json)
- [ ] выборка отрисовки не всех конусов
- [ ] движение мыши - поворот образца с контролом, а без ктрл - по плоскости движение
- [ ] комбинации клавиш для разных задач (редисплей, закрытие окна и пр.)
- [ ] флаги для запуска .\visualis_freeglut
- [ ] новые фигуры для рисования (стрелки, например)
- [ ] FLTK или что-то другое?
- [ ] ИЛИ разделение окна на подокна
- [ ] LINUX
  
## Compiling with CMake
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


## Зависимости
+ **[Exceptio](https://github.com/ilyata76/tia-Exceptio.git)** для обработки исключений и ошибок
+ **[freeglut](https://github.com/FreeGLUTProject/freeglut.git)** для рисования
+ **[json](https://github.com/nlohmann/json.git)** для хранения настроек  
  
  При стандартных настройках и наличия их в требуемых директориях проект соберётся самостоятельно. Динамическую же библиотеку придётся искать
  
## Консольное приложение
```

    ____   ____.___  _____________ ___  _____  .____    .___  _________
    \   \ /   /|   |/   _____/    |   \/  _  \ |    |   |   |/  _____/
     \   Y   / |   |\_____  \|    |   /  /_\  \|    |   |   |\_____ \
      \     /  |   |/        \    |  /    |    \    |___|   |/       \
       \___/   |___/_______  /______/\____|__  /_______ \___/_______ /
                           \/                \/        \/          \/

vis > show

         Path to folder with files               (c): <nothing>
         Path to sconfiguration file             (c): <nothing>
         Path to folder with .json settings      (c): <nothing>
         Using color?                            (c): false
         Number of file                          (c): 0
         Shape for drawing                       (u): c - cone
         Index of spin                           (u): DRAW ALL
         Background color (RGB)                  (c): 255/255 255/255 255/255

vis > set sp ../temp/b

        Path to settings file folder : ../temp/b : has been set up

vis > settings get

        Succsesful

vis > show

         Path to folder with files               (c): .
         Path to sconfiguration file             (c): <nothing>
         Path to folder with .json settings      (c): ../temp/b
         Using color?                            (c): false
         Number of file                          (c): 30
         Shape for drawing                       (u): c - cone
         Index of spin                           (u): DRAW ALL
         Background color (RGB)                  (c): 255/255 200/255 150/255

vis >
```
Приглашение для ввода `vis > `. Ожидается введение некоторых управляющих команд (синонимы к ним прописаны в `help`):
+ `help` выводит в консоль список команд и их краткое описание
+ `show` показывает влияющие на работу программы переменные (изменяемые (c) и неизменяемые (u))
+ `set` позволяет устанавливать значение для некоторых переменных
    + `folderpath <path-to-folder>` позволяет устанавливать путь до папки с файлами, подлежащими конвертации и/или формата .vvis
    + `filenumber <integer>` позволяет устанавливать, какой файл будет подлежать конвертации и/или визуализации .vvis 
    + `filepath <path-to-file>` позволяет устанавливать пусть до файла sconfiguration-xxx.vvis
    + `coloring <y/n>` позволяет устанавливать, будет ли использоваться цвет
    + `backgroundcolor <red> <green> <blue>` в числах от 0 до 255 устанавливает цвет фона картинки
    + `settingspath <path-to-folder>` указывает на директорию, в которой должен(или есть) находиться файл visualis-settings.json
+ `unset` позволяет сбросить переменную до стандартного значения, принимает всё то же, что и `set`
+ `convert` конвертирует файлы в формат `.vvis`
    + `vampire6` конвертирует файлы [Vampire6](https://github.com/richard-evans/vampire), Vampire5
+ `visualize` рисует спиновую систему
    + `folder` позволяет рисовать спиновую систему, используя путь до папки (`folderpath`) и номер файла (`filenumber`)
    + `file` позволяет рисовать спиную систему, используя путь до файла sconfiguration-xxx.vvis (`filepath`)
+ `settings`
    + `save` позволяет сохранить переменные в файле формата .json по пути settingspath/visualis-settings.json. Если файла не существует, то он создастся
    + `get` позволяет получить переменные из файла формата .json, который был сохранён предыдущей подкомандой, по пути settingspath/visualis-settings.json
+ `reset` обнуляет все переменные, но не перезапускает программу
+ `restart` полностью обнуляет все переменные и перезапускает программу
+ `exit` выход из приложения

## Манипуляции с образцом
  
### Клавиши
  
При настройке by_head в левую-правую сторону будет как бы поворачиваться голова, сама камера:  
+ Поднять/опустить камеру: `W`/`S`  
+ Повернуть влево/вправо камеру: `A`/`D`  
  
Следующие операции меняют местоположение всего образца на полотне (by_head):  
+ Вверх/вниз: `KEY_ARROW_UP`/`KEY_ARROW_DOWN`  
+ Влево/вправо: `KEY_ARROW_LEF`/`KEY_ARROW_RIGHT`  
  
Следующие операции меняют ориентацию объекта в пространстве, поворачивая его вместе с локальными осями:  
+ Повернуть вокруг оси X : `I`/`K`  
+ Повернуть вокруг оси Y : `J`/`L`  
  
### Клавиши мыши
  
При нажатии ПКМ открывается выпадающее меню, в котором можно:
+ включить/выключить цвет
+ изменить чувствительность
+ сохранить, восстановить, сбросить и сбросить в файле visualis-settings.json настройки, касающиеся поведения клавиш

  
## Текущее быстродействие
- [issues/Оптимизация](https://github.com/ilyata76/visualis/issues/12)

## Examples
![colorful_vertex](https://github.com/ilyata76/visualis/blob/master/freeglut/guide/colorful_vertex.png)
![colorful_vertex](https://github.com/ilyata76/visualis/blob/master/freeglut/guide/Curie_Ni_colorful.png)
