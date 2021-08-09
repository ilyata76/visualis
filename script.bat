@chcp 65001
@echo.
@title OPENGL
@echo [BAT] OPENGL
@echo.
@mkdir build
@cd build
@echo.
@echo [BAT] Сборка проекта
@echo.
@cmake ..

@echo.
@echo [BAT] Линковка и создание исполняемого файла
@echo.
@cmake --build .
@echo.


@cd ..
@rem [BAT] 
@copy %CD%\build\Debug\PROJECT_OPENGL.exe %CD%
@powershell "$x=(New-Object -ComObject WScript.Shell).CreateShortcut('%CD%\OPENGL.lnk'); $x.TargetPath='%CD%\PROJECT_OPENGL.exe'; $x.HotKey='CTRL+ALT+F'; $x.IconLocation = '%CD%\vamp.ico'; $x.Save()"                    								
@echo.

@pause
@echo.