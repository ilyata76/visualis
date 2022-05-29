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
- [ ] запоминание настроек (json)
- [ ] выборка отрисовки не всех конусов
- [ ] флаги для запуска .\visualis_freeglut
- [ ] разделение окна на подокна
- [ ] новые фигуры для рисования (стрелки, например)
- [ ] FLTK или что-то другое?
- [ ] ????
  
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
При стандартных настройках и наличия их в требуемых директориях, проект соберётся самостоятельно. Динамическую же библиотеку придётся искать
  
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
         Using color?                            (c): false
         Number of file                          (c): 0
         Shape for drawing                       (u): c - cone
         Index of spin                           (u): DRAW ALL
         Background color (RGB)                  (c): 255/255 255/255 255/255

vis > set folp ../../temp/b

        Path to folder : ../../temp/b : has been set up

vis > set filepath "../../temp/b/sconfiguration-00000010.vvis"

        Path to sconfiguration file : ../../temp/b/sconfiguration-00000010.vvis : has been set up

vis > set filenumber 1

        Number of file : 1 : has been set up

vis > set backgroundcolor 200 140 200

        Coloring background : 0.784314*255 0.54902*255 0.784314*255 : has been set up

vis > set coloring yes

        Coloring mode : true : has been set up

vis > show

         Path to folder with files               (c): ../../temp/b
         Path to sconfiguration file             (c): ../../temp/b/sconfiguration-00000010.vvis
         Using color?                            (c): true
         Number of file                          (c): 1
         Shape for drawing                       (u): c - cone
         Index of spin                           (u): DRAW ALL
         Background color (RGB)                  (c): 200/255 140/255 200/255

vis >
```
Приглашение для ввода `vis > `. Ожидается введение некоторых управляющих команд:
+ `help` выводит в консоль список команд и их краткое описание
+ `show` показывает влияющие на работу программы переменные (изменяемые (c) и неизменяемые (u))
+ `set` позволяет устанавливать значение для некоторых переменных
    + `folderpath <path-to-folder>` позволяет устанавливать путь до папки с файлами, подлежащими конвертации и/или формата .vvis
    + `filenumber <integer>` позволяет устанавливать, какой файл будет подлежать конвертации и/или визуализации .vvis 
    + `filepath <path-to-file>` позволяет устанавливать пусть до файла sconfiguration-xxx.vvis
    + `coloring <y/n>` позволяет устанавливать, будет ли использоваться цвет
    + `backgroundcolor <red> <green> <blue>` в числах от 0 до 255 устанавливает цвет фона картинки
+ `unset` позволяет сбросить переменную до стандартного значения, принимает всё то же, что и `set`
+ `convert` конвертирует файлы в формат `.vvis`
    + `vampire6` конвертирует файлы [Vampire6](https://github.com/richard-evans/vampire), Vampire5
+ `visualize` рисует спиновую систему
    + ``folder`` позволяет рисовать спиновую систему, используя путь до папки (`folderpath`) и номер файла (`filenumber`)
    + `file` позволяет рисовать спиную систему, используя путь до файла sconfiguration-xxx.vvis (`filepath`)
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

  
## Текущее быстродействие
- [issues/Оптимизация](https://github.com/ilyata76/visualis/issues/12)

## Examples
![colorful_vertex](https://github.com/ilyata76/visualis/blob/master/freeglut/guide/colorful_vertex.png)
![colorful_vertex](https://github.com/ilyata76/visualis/blob/master/freeglut/guide/Curie_Ni_colorful.png)
