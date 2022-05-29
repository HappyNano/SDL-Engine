# **SDL-Engine**

Игровой движок, работающий на **SDL-2.0**

# **UI**-файлы движка

## **`Assets`**

Состоит из файлов: `UI/Assets.cpp` и `UI/Assets.hpp`

Работает на принципе Сигнлтона-Майерса.

### Использование
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

## **`Font`**

Состоит из файлов: `UI/Font.cpp` и `UI/Font.hpp`

Упрощает работу со шрифтами из `SDL2/SDL_ttf.h`: автоматическое удаление указателя на `TTF_Font`.

Запрещено копирование

### Использование
- Конструкторы
1. Из `TTF_Font` и цвета 
2. Из названия шрифта, записанный в `Assets`, размера шрифта и цвета
3. Из `TTF_Font` *(цвет по умолчанию черный)*
4. Из названия шрифта, записанный в `Assets`, размера шрифта *(цвет по умолчанию черный)*
```cpp
Font(TTF_Font*, SDL_Color);
Font(const std::string&, int, SDL_Color);
Font(TTF_Font*);
Font(const std::string&, int);
```
- Рендер **SOLID** обычного текста и utf-16 текста
```cpp
SDL_Surface* renderSolidText(const std::string&) const; // Рендер SOLID текста из std::string
SDL_Surface* renderSolidText(const std::u16string&) const; // Рендер SOLID текста из UTF-16 текста
```
- Получение размеров **SOLID** обычного текста и utf-16 текста
```cpp
int getTextWidth(const std::string&) const;
int getTextHeight(const std::string&) const;
SDL_Rect getTextRect(const std::string&) const;

int getTextWidth(const std::u16string&) const;
int getTextHeight(const std::u16string&) const;
SDL_Rect getTextRect(const std::u16string&) const;
```

## **`Geometry`**

Состоит из файлов: `UI/Geometry.cpp` и `UI/Geometry.hpp`

Упрощает работу с поверхностями `SDL_Surface`

Функции принимают цвет в виде `Uint32`

### Функции
```cpp
void set_pixel(SDL_Surface*, int, int, Uint32);
void DrawCircle(SDL_Surface*, int32_t, int32_t, int32_t, Uint32);
void DrawRectangle(SDL_Surface*, int32_t, int32_t, int32_t, int32_t, Uint32);
void draw_FillRoundedRectangle(SDL_Surface*, int, int, int, int, int, Uint32);
void draw_GradientRectangle(SDL_Surface*, int, int, int, int, Uint32, Uint32);
```
- `set_pixel` - устанавливает пиксель цвета color в координатах x, y
- `DrawCircle` - рисует круг в координатах x, y радиуса r цвета color
- `DrawRectangle` - рисует заполненный прямоугольник в координатах x, y с параметрами width, heigth цвета color
- `draw_FillRoundedRectangle` - рисует заполненный прямоугольник в координатах x, y с параметрами width, heigth радиуса загругления r цвета color
- `draw_GradientRectangle` - рисует прямоугольник с координатами x, y и размерами width, height, заполненный градиентом от begin_color до end_color

# **UI**-элементы движка

Все **UI**-элементы движка наследуются от абстрактного класса `UIElements` 

## **`UIElements.hpp`**

Абстрактный класс **UI**-элементов

### Обязательные виртуальные методы

```cpp
virtual void setWidth(int) = 0; // Установить ширину элемента
virtual void setHeight(int) = 0; // Установить высоту элемента
virtual void setX(int) = 0; // Установить X-координату элемента
virtual void setY(int) = 0;// Установить Y-координату элемента
virtual void move(int, int) = 0; // Переместить элемент на x, y
virtual void setRect(const SDL_Rect&) = 0; // Установить размеры элемента при помощи SDL_Rect

virtual int getWidth() const = 0; // Получить ширину элемента
virtual int getHeight() const = 0; // Получить высоту элемента
virtual int getX() const = 0; // Получить X-координату элемента
virtual int getY() const = 0; // Получить Y-координату элемента
virtual const SDL_Rect& getRect() const = 0; // Получить размеры элемента в SDL_Rect

virtual void handleEvent(const SDL_Event&) = 0; // Обработчик событий

virtual void render(SDL_Renderer*) = 0; // Рендерниг элемента
```