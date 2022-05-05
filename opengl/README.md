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
    - [] CAMERA
- [ ] variable main.cpp
  
## Зависимости
+ **[Exceptio](https://github.com/ilyata76/tia-Exceptio.git)** для исключений и `Assert`. CMake самостоятельно (через инструкцию)
линкует библиотеку
+ **[freeglut](https://github.com/FreeGLUTProject/freeglut.git)** для рисования. Через CMake можно подключить `.lib` библиотеки (см. CmakeLists.txt), а вот с `.dll` - нужно перетаскивать вместе с экзешником или сохранять в PATH
  

## Текущее быстродействие
- [issues/Оптимизация](https://github.com/ilyata76/visualis/issues/12)