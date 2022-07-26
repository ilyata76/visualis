# Exceptio  
  
## Exceptio
Implements a simple exception for a block `try-catch`  
   
Class fields:
```cpp
int index; // error code
std::wstring description; // main description
std::wstring comment; // anything that can help
```

Constructors:
```cpp
Exceptio(int index);
Exceptio(int index, const wchar_t* description);
Exceptio(int index, const std::wstring& description);
Exceptio(const wchar_t* description);
Exceptio(const std::wstring& description);
Exceptio(const wchar_t* description, const wchar_t* comment);
Exceptio(const std::wstring& description, const std::wstring& comment);
Exceptio(int index, const wchar_t* description, const wchar_t* comment);
Exceptio(int index, const std::wstring& description, const std::wstring& comment);

Exceptio(std::exception _exc); // std::exception

virtual ~Exceptio();
```

Methods:
```cpp
virtual bool operator == (Exceptio& a);
virtual Exceptio operator = (std::exception& exc); // std::exception

virtual int get_index();
virtual std::wstring get_description();
virtual std::wstring get_comment();
virtual std::wstring what();
```


Allows you to create heir classes by overloading virtual functions. For example:
```cpp
using tia::Exceptio;
class Logic_Error : public tia::Exceptio {
public:
    Logic_Error(int _index) : Exceptio(_index) {};
    Logic_Error(int _index, const wchar_t* _discr) : Exceptio(_index, _discr) {};
    
    std::wstring what() override {
        return std::wstring(L"Logic Error!");
    };
    
    ~Logic_Error() {
        std::wcout << "LE object was Destroyed\n";
    }
};
```
  File `exceptio.hpp`  


## Assert
Implements the simplest version of the assert version, based on calling the `operator()` current class.  
As a result of which the exception `Exceptio` is called.

Macro
```cpp
#define ASSERT(condition) { tia::Assert a; a(condition, L"by ASSERT"); }
```
  
  File `assert.hpp`  

## Assert_t
Assert implementation via `template`:
```cpp
template<typename EXC>
void operator()(bool condition, EXC exc);
```
Macro
```cpp
#define ASSERTT(condition, index) {tia::Assert_t{}(condition, tia::Exceptio{100, L"by ASSERTT"});}
```
Example
```cpp
tia::Assert_t{}(0, std::exception{});
```

  File `assert_3rd.hpp`

# Compiling with CMake  
  
## Separately  
```console
cd .\build\
cmake -DBUILD_TEST=ON ..
cmake --build .
```
  
## In project  
```cmake
add_subdirectory(path_to_folder)
  target_link_libraries( ${PROJECT} exceptio )
```