#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;


void SetIcon(sf::Window& wnd);
void Init();
void Draw();

GLfloat rotate_z = 0;
GLfloat rotate_x = 0;
GLfloat rotate_y = 0;
int main() {
	// Создаём окно
	sf::Window window(sf::VideoMode(600, 600), "My OpenGL window", sf::Style::Default, sf::ContextSettings(32));
	// Ставим иконку (окна с дефолтной картинкой это некрасиво)
	SetIcon(window);
	// Включаем вертикальную синхронизацию (синхронизация частоты отрисовки с частотой кадров монитора, что бы картинка не фризила, делать это не обязательно)
	window.setVerticalSyncEnabled(true);

	// Активируем окно
	window.setActive(true);

	// Инициализация
	Init();

	// Главный цикл окна
	while (window.isOpen()) {
		sf::Event event;
		// Цикл обработки событий окна, тут можно ловить нажатия клавиш, движения мышки и всякое такое
		while (window.pollEvent(event)) {
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				rotate_x -= 0.5;
				break;
			case sf::Keyboard::Down:
				rotate_x += 0.5;
				break;
			case sf::Keyboard::Right:
				rotate_z -= 0.5;
				break;
			case sf::Keyboard::Left:
				rotate_z += 0.5;
				break;
			case sf::Keyboard::W:
				rotate_y += 0.5;
				break;
			case sf::Keyboard::S:
				rotate_y -= 0.5;
				break;
			default:
				break;
			}
			if (event.type == sf::Event::Closed) {
				// Окно закрыто, выходим из цикла
				window.close();
			}
			else if (event.type == sf::Event::Resized) {
				// Изменён размер окна, надо поменять и размер области Opengl отрисовки
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}

		// Очистка буферов
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Рисуем сцену
		Draw();

		// Отрисовывает кадр - меняет передний и задний буфер местами
		window.display();
	}

	// -- тут надо не забыть очистить все выделенные ресурсы --

	return 0;
}

// В момент инициализации разумно произвести загрузку текстур, моделей и других вещей
void Init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Функция непосредственно отрисовки сцены
void Draw() {
	glEnable(GL_DEPTH_TEST);
	// Устанавливаем единичную матрицу преобразования
	glLoadIdentity();
	glRotatef(rotate_z, 0.0, 0.0, 1.0);
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);

	glBegin(GL_POLYGON);
	//передняя
	glColor3f(1.0, 1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
	glColor3f(1.0, 0.0, 0.0); glVertex3f(0.5, 0.5, -0.5);
	glColor3f(1.0, 1.0, 0.0); glVertex3f(-0.5, 0.5, -0.5);
	glColor3f(1.0, 1.0, 1.0); glVertex3f(-0.5, -0.5, -0.5);

	glEnd();
	//задняя
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0); glVertex3f(0.5, -0.5, 0.5);//синий
	glColor3f(0.0, 0.0, 0.0); glVertex3f(0.5, 0.5, 0.5);//ч
	glColor3f(0.0, 1.0, 0.0); glVertex3f(-0.5, 0.5, 0.5);//зелен
	glColor3f(0.0, 1.0, 1.0); glVertex3f(-0.5, -0.5, 0.5);//зеленый г
	glEnd();

	//левая
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 1.0); glVertex3f(-0.5, -0.5, 0.5);//зеленый г
	glColor3f(0.0, 1.0, 0.0); glVertex3f(-0.5, 0.5, 0.5);//зелен
	glColor3f(1.0, 1.0, 0.0); glVertex3f(-0.5, 0.5, -0.5);//желтый
	glColor3f(1.0, 1.0, 1.0); glVertex3f(-0.5, -0.5, -0.5);//белый
	glEnd();

	//правая
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);//розовый
	glColor3f(1.0, 0.0, 0.0); glVertex3f(0.5, 0.5, -0.5);//красный
	glColor3f(0.0, 0.0, 0.0); glVertex3f(0.5, 0.5, 0.5);//ч
	glColor3f(0.0, 0.0, 1.0); glVertex3f(0.5, -0.5, 0.5);//синий
	glEnd();


	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0); glVertex3f(0.5, 0.5, 0.5);//ч
	glColor3f(1.0, 0.0, 0.0); glVertex3f(0.5, 0.5, -0.5);//красный
	glColor3f(1.0, 1.0, 0.0); glVertex3f(-0.5, 0.5, -0.5);//желтый
	glColor3f(0.0, 1.0, 0.0); glVertex3f(-0.5, 0.5, 0.5);//зелен
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);//розовый
	glColor3f(0.0, 0.0, 1.0); glVertex3f(0.5, -0.5, 0.5);//синий
	glColor3f(0.0, 1.0, 1.0); glVertex3f(-0.5, -0.5, 0.5);//зеленый г
	glColor3f(1.0, 1.0, 1.0); glVertex3f(-0.5, -0.5, -0.5);//белый
	glEnd();

	// Отправляем набор команд отрисовываться
	glFlush();
}


void SetIcon(sf::Window& wnd)
{
	sf::Image image;

	// Вместо рисования пикселей, можно загрузить иконку из файла (image.loadFromFile("icon.png"))
	image.create(16, 16);
	for (int i = 0; i < 16; ++i)
		for (int j = 0; j < 16; ++j)
			image.setPixel(i, j, {
				(sf::Uint8) (i * 16), (sf::Uint8)(j * 16), 0 });

	wnd.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
}