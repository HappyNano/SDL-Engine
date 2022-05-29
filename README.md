# **SDL-Engine**

Игровой движок

Написан на **SDL-2.0**, **SDL-ttf**, **SDL-Image**

Выполнен на **GNU++14**

# Установка

Для установки `SDL-2.0`, `SDL-ttf`, `SDL-Image`
- Для пользователей Linux
```bash
sudo apt-get update
sudo apt-get install libsdl2-2.0 libsdl2-ttf-dev libsdl2-image-dev -y
```
- Для сборки необходимо дополнительно установить `make`, `g++` и `valgrind` (необязательно)
```bash
sudo apt-get update
sudo apt-get install make g++ valgrind -y
```

# Основные файлы движка

## **`Logs`**

Состоит из файлов: `Logs.cpp` и `Logs.hpp`

Работает на принципе Синглтона-Майерса.

Выводит все логи красиво

### Использование

```cpp
static void print(const std::string&, const std::string&, LogLevel);
```

- Основной метод `print`
  - Принимает `tag`, `text` и `level`
- `LogLevel`
  - 3 уровня вывода логов:
  1. `ERROR`
  2. `INFO`
  3. `DEBUG`
- Пример использования
```cpp
SDLEngine::Logs::print("Textures", "Loaded texture: " + test_texture, SDLEngine::LogLevel::INFO);
```
Вывод:
```
INFO   [Textures  ] Loaded texture: assets/cloud.png
```

## **`Timer`**

Состоит из файлов: `Timer.cpp` и `Timer.hpp`

Служит для удобного контроля над FPS игры

### Методы

- `setFps`
  - Устанавливает максимальный FPS
- `startTimer`
  - Запускает таймер. Необходимо выполнять данный метод перед запуском основного цикла программы
- `updateTimer`
  - Обновляет таймер. Необходимо выпонлять данный метод на каждой итерации цикла
- `getCurrentFPS`
  - Получение текущего FPS. Возвращает значение в int
- `getDT`
  - Получение временного интервала одного кадра

# **UI**-файлы движка

## **`Assets`**

Состоит из файлов: `UI/Assets.cpp` и `UI/Assets.hpp`

Работает на принципе Синглтона-Майерса.

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

## **`Surface`**

Состоит из файлов: `UI/Surface.cpp` и `UI/Surface.hpp`

Упрощает работу с поверхностями из `SDL2/SDL.h`: автоматическое уничтожение поверхности

Запрещено копирование

### Использование
- Конструктор из `SDL_Surface`
```cpp
Surface(SDL_Surface*);
```
- Создание текстуры из поверхности
```cpp
SDL_Texture* createTexture(SDL_Renderer*);
```
- Получение размера поверхности
```cpp
SDL_Rect getRect() const;
```

## **`Texture`**

Состоит из файлов: `UI/Texture.cpp` и `UI/Texture.hpp`

Упрощает работу с текстурами из `SDL2/SDL.h`: автоматическое уничтожение текстуры

Запрещено копирование

> ВАЖНО! Следите за тем, чтобы деструктор Texture выполнялся раньше, чем произойдет уничтожение **SDL_Renderer**

### Использование
- Конструкторы
1. Из `SDL_Texture*` и размеров `SDL_Rect`
2. Из `SDL_Texture*`. Размер получается на месте, с помощью метода SDL_QueryTexture. Тогда x, y будут равны 0
3. Из `SDL_Surface*`
4. Из `UI::Surface&&`
```cpp
Texture(SDL_Texture*, const SDL_Rect&);
Texture(SDL_Texture*);
Texture(SDL_Renderer*, SDL_Surface*);
Texture(SDL_Renderer*, Surface&&);
```
- Метод `move` для перемещения текстуры на координаты x, y
```cpp
void move(int, int);
```
- Метод `render` для рендера текстуры
```cpp
void render(SDL_Renderer*);
```
- Методы получения показателя "валидности" текстуры и ее очищение
```cpp
bool valid() const;
void erase();
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

### Дополнительно

- У следующих **UI**-элементов нет поля, которое хранит `SDL_Renderer*`, поэтому первая отрисовка и сохранение текстур для последующего быстрого их рендера происходит в первый вызов метода `render`
- > ВАЖНО! Следите за тем, чтобы деструктор элементо выполнялся раньше, чем произойдет уничтожение **SDL_Renderer**, если таковой был использован при вызове в методах класса

## **`Rectangle`**

Состоит из файлов: `UI/Rectangle.cpp` и `UI/Rectangle.hpp`

UI-элемент - прямоугольник. Может быть с загкругленным радиусом.

### Методы
- Все методы из родительского класса переопределены
- Конструктор принимает размеры, цвет, радиус закругления углов прямоугольника
```cpp
Rectangle(SDL_Rect, SDL_Color, int);
```
- Установка цвета
```cpp
void setColor(SDL_Color);
```
- Установка радиуса закругления углов прямоугольника
```cpp
void setRadius(int);
```
- Не используется обработчик событий
- *private*-метод перерисовки элемента
```cpp
void reRender();
```

### Использование
- При изменении ширины или высоты вызвается функция перерисовки элемента
```cpp
SDLEngline::UI::Rectangle test_rectangle({0, 0, 50, 50}, {255, 0, 0, 255}, 0); // Создание test_rectangle с координатами 0 0 и размерами 50 на 50. Цвет - красный. Радиус загругления - 0
test_rectangle.render(renderer); // Рендер прямоугольника на экран
test_rectangle.setColor({0, 255, 0, 255}); // Изменение цвета прямоугольника
// Очищение памяти автоматическое
```

## **`Wrapping`**

Состоит из файлов: `UI/Wrapping.cpp` и `UI/Wrapping.hpp`

Методы для выравнивания массива текстур

> Это дополнительные методы для `UI::TextBox`

### Варианты выравнивания
```cpp
enum class Wrapping
{
  leftTop,       // Левый верхний угол
  centerTop,     // Сверху по центру
  rightTop,      // Правый верхний угол
  leftEquator,   // Слева посередине
  centerEquator, // По центру
  rightEquator,  // Справа посередине
  leftBottom,    // Левый нижний угол
  centerBottom,  // Снизу по центру
  rightBottom,   // Правый нижний угол
  none           // Нет центровки никакой (Текст будет слева сверху и не будет подгоняться по размерам)
};
```

### Методы
- Все методы принимают:
  1. Размеры прямоугольника в котором нужно выравнивать массив элементов
  2. Массив (`std::vector< UI::Texture >`)
  3. Отступ между элементами (вертикальный) в пикселях
- Методы:
1. `wrapLeftTop`
2. `wrapCenterTop` 
3. `wrapRightTop`
4. `wrapLeftEquator`
5. `wrapCenterEquator`
6. `wrapRightEquator`
7. `wrapLeftBottom`
8. `wrapCenterBottom`
9. `wrapRightBottom`

## **`TextBox`**

Состоит из файлов: `UI/TextBox.cpp` и `UI/TextBox.hpp`

Дополнительные файлы: `UI/Wrapping.cpp` и `UI/Wrapping.hpp` (их описание выше)

UI-элемент - поле для текста.

> `TextBoxBase` отдельный класс (деталь реализации), содержащий основную логику выравнивания текста и т.п. (Работает на `SDL_Surface`)

### Необходимые поля
- `UI::TextBoxBase`
  - `SDL_Rect` Общий размер всего элемента
  - `UI::Font` Шрифт
  - `std::vector< UI::Surface >` Массив поверхностей текста
  - `std::u16string` Текст элемента в UTF-16 *(по умолчанию `""`)*
- `UI::TextBox`
  - `int[4] padding` Отступы от края *(по умолчанию {0, 0, 0, 0})*
  - `int indent` Отступ между поверхностями текста *(по умолчанию 3 пикселя)*
  - `UI::Wrapping` Тип выравнивания текста *(по умолчанию `Wrapping::LeftTop`)*
  - `std::vector< UI::Texture >` Массив текстур текста

### Методы
- Все методы из родительского класса переопределены
- Конструктор принимает текст в UTF-16, размеры элемента, шрифт
```cpp
TextBox(const std::u16string&, const SDL_Rect&, Font&&);
```
- Поменять текст
```cpp
void setText(const std::u16string&);
```
- Не используется обработчик событий
- *private*-метод `clearTextSurfaces` - очищает массив поверхностей текста
- *private*-метод `reCreateTextSurfaces` - пересоздает массив поверхностей текста
  - Вызывает `clearTextSurfaces`
  - Разделяет текст на слова
  - Выраванивает текст по ширине и типу выравнивания
- виртуальный *private*-метод `doReCreateTextTextures` - служит для перерисовки всех поерхностей текста, а так же их текстур в `UI::TextBox`
- *private*-метод `addText` - дополнительный метод для легкого добавления поверхности текста в массив


### Использование
- При изменении ширины или высоты вызвается функция перерисовки элемента
```cpp
SDLEngine::Assets::Instance().checkAndSaveFonts("default_font", "assets/default_font.ttf", 1); // Сохраняем шрифт assets/default_font.ttf в UI::Assets под названием default_font
SDLEngine::UI::TextBox test_textbox(u"This is test text!", {0, 0, 100, 100}, {"default", 20, {255, 0, 0, 255}}); // Создаем поле для текста с коорд. 0 0 и размерами 100 на 100. Шрифт - default размера 20 красного цвета
test_textbox.render(renderer); // Рендер элемента
```


# Дополнительно

## Ошибки
- Ошибка `SDL_main`. Убедитесь в том, что ваш `main` принимает 2 параметра: `int argc, char** argv`

