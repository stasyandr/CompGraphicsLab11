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
	// ������ ����
	sf::Window window(sf::VideoMode(600, 600), "My OpenGL window", sf::Style::Default, sf::ContextSettings(32));
	// ������ ������ (���� � ��������� ��������� ��� ���������)
	SetIcon(window);
	// �������� ������������ ������������� (������������� ������� ��������� � �������� ������ ��������, ��� �� �������� �� �������, ������ ��� �� �����������)
	window.setVerticalSyncEnabled(true);

	// ���������� ����
	window.setActive(true);

	// �������������
	Init();

	// ������� ���� ����
	while (window.isOpen()) {
		sf::Event event;
		// ���� ��������� ������� ����, ��� ����� ������ ������� ������, �������� ����� � ������ �����
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
				// ���� �������, ������� �� �����
				window.close();
			}
			else if (event.type == sf::Event::Resized) {
				// ������ ������ ����, ���� �������� � ������ ������� Opengl ���������
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}

		// ������� �������
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// ������ �����
		Draw();

		// ������������ ���� - ������ �������� � ������ ����� �������
		window.display();
	}

	// -- ��� ���� �� ������ �������� ��� ���������� ������� --

	return 0;
}

// � ������ ������������� ������� ���������� �������� �������, ������� � ������ �����
void Init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// ������� ��������������� ��������� �����
void Draw() {
	glEnable(GL_DEPTH_TEST);
	// ������������� ��������� ������� ��������������
	glLoadIdentity();
	glRotatef(rotate_z, 0.0, 0.0, 1.0);
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);

	glBegin(GL_POLYGON);
	//��������
	glColor3f(1.0, 1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
	glColor3f(1.0, 0.0, 0.0); glVertex3f(0.5, 0.5, -0.5);
	glColor3f(1.0, 1.0, 0.0); glVertex3f(-0.5, 0.5, -0.5);
	glColor3f(1.0, 1.0, 1.0); glVertex3f(-0.5, -0.5, -0.5);

	glEnd();
	//������
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0); glVertex3f(0.5, -0.5, 0.5);//�����
	glColor3f(0.0, 0.0, 0.0); glVertex3f(0.5, 0.5, 0.5);//�
	glColor3f(0.0, 1.0, 0.0); glVertex3f(-0.5, 0.5, 0.5);//�����
	glColor3f(0.0, 1.0, 1.0); glVertex3f(-0.5, -0.5, 0.5);//������� �
	glEnd();

	//�����
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 1.0); glVertex3f(-0.5, -0.5, 0.5);//������� �
	glColor3f(0.0, 1.0, 0.0); glVertex3f(-0.5, 0.5, 0.5);//�����
	glColor3f(1.0, 1.0, 0.0); glVertex3f(-0.5, 0.5, -0.5);//������
	glColor3f(1.0, 1.0, 1.0); glVertex3f(-0.5, -0.5, -0.5);//�����
	glEnd();

	//������
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);//�������
	glColor3f(1.0, 0.0, 0.0); glVertex3f(0.5, 0.5, -0.5);//�������
	glColor3f(0.0, 0.0, 0.0); glVertex3f(0.5, 0.5, 0.5);//�
	glColor3f(0.0, 0.0, 1.0); glVertex3f(0.5, -0.5, 0.5);//�����
	glEnd();


	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0); glVertex3f(0.5, 0.5, 0.5);//�
	glColor3f(1.0, 0.0, 0.0); glVertex3f(0.5, 0.5, -0.5);//�������
	glColor3f(1.0, 1.0, 0.0); glVertex3f(-0.5, 0.5, -0.5);//������
	glColor3f(0.0, 1.0, 0.0); glVertex3f(-0.5, 0.5, 0.5);//�����
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);//�������
	glColor3f(0.0, 0.0, 1.0); glVertex3f(0.5, -0.5, 0.5);//�����
	glColor3f(0.0, 1.0, 1.0); glVertex3f(-0.5, -0.5, 0.5);//������� �
	glColor3f(1.0, 1.0, 1.0); glVertex3f(-0.5, -0.5, -0.5);//�����
	glEnd();

	// ���������� ����� ������ ��������������
	glFlush();
}


void SetIcon(sf::Window& wnd)
{
	sf::Image image;

	// ������ ��������� ��������, ����� ��������� ������ �� ����� (image.loadFromFile("icon.png"))
	image.create(16, 16);
	for (int i = 0; i < 16; ++i)
		for (int j = 0; j < 16; ++j)
			image.setPixel(i, j, {
				(sf::Uint8) (i * 16), (sf::Uint8)(j * 16), 0 });

	wnd.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
}