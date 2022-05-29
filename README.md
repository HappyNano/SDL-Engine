# **SDL-Engine**

Игровой движок, работающий на **SDL-2.0**

# **UI**-элементы движка

## **`Assets`**

Состоит из файлов: `UI/Assets.cpp` и `UI/Assets.hpp`

Работает на принципе Сигнлтона-Майерса.

### Использование: 
- Вызов объекта класса `Assets`
```cpp
SDLEngine::UI::Assets::Instance();
```
- Можно сохранить в поле класса типа `std::map` названия текстур/шрифтов, указывания путь до текстуры/шрифта
  - Одновременно с добавлением происходит проверка на существования данной текстуры/шрифта и на успешную загрузку текстуры/шрифта
```cpp
static bool checkAndSaveTextures(SDL_Renderer*, const std::string&, const std::string&); // Загрузка текстур
static bool checkAndSaveFonts(const std::string&, const std::string&, int); // Загрузка шрифтов
```
```cpp
static SDL_Texture* getTextureByName(SDL_Renderer*, const std::string&); // Получение текстуры по ее имени
static TTF_Font* getFontByName(const std::string&, int); // Получение шрифта по его имени
```
- Можно загрузить шрифт/текстуру сразу по его пути
```cpp
static SDL_Texture* LoadBMP(SDL_Renderer* renderer, const char* filename); // Загрузка BMP изображения
static SDL_Texture* LoadPNG(SDL_Renderer* renderer, const char* filename); // Загрузка PNG изображения
static TTF_Font* LoadFont(const char* filename, int size); // Загрузка шрифта
```

