# visualis openGL

## Roadmap
- [x] .data parser
    - [x] .data -> string -> convertor to .vvis
- [x] .vvis -> creator of vertex array
- [x] adding the freeglut in project structure
    - [ ] отмучаться с dll - решения нет?
    - [x] preparation for drawing
- [x] vertex -> creating a shape
    - [x] shape -> cone
        - [ ] vertex array -> shape array
    - [x] cone -> printing simple cone
    - [x] shape -> printing sample
    - [x] printing sample -> keys, etc
    - [x] CAMERA
        - [x] повороты образца, а не камеры
- [ ] variable main.cpp
  
## Зависимости
+ **[Exceptio](https://github.com/ilyata76/tia-Exceptio.git)** для исключений и `Assert`. CMake самостоятельно (через инструкцию)
линкует библиотеку
+ **[freeglut](https://github.com/FreeGLUTProject/freeglut.git)** для рисования. Через CMake можно подключить `.lib` библиотеки (см. CmakeLists.txt), а вот с `.dll` - нужно перетаскивать вместе с экзешником или сохранять в PATH
  
## Манипуляции с образцом
  При настройке by_head в левую-правую сторону будет как бы поворачиваться голова, сама камера:
+ Поднять/опустить камеру: `W`/`S`
+ Повернуть влево/вправо камеру: `A`/`D`
  Следующие операции меняют местоположение всего образца на полотне (by_head):
+ Вверх/вниз: `KEY_ARROW_UP`/`KEY_ARROW_DOWN`
+ Влево/вправо: `KEY_ARROW_LEF`/`KEY_ARROW_RIGHT`
  Следующие операции меняют ориентацию объекта в пространстве, поворачивая его вместе с локальными осями:
+ Повернуть вокруг оси `X` : `I`/`K`
+ Повернуть вокруг оси `Y` : `J`/`L`
  

## Текущее быстродействие
- [issues/Оптимизация](https://github.com/ilyata76/visualis/issues/12)