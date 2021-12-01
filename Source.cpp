#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


void SetIcon(sf::Window& wnd);
void Init();
void Draw();

GLfloat move_z = 0;
GLfloat move_x = 0;
GLfloat move_y = 0;

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
				move_x -= 0.05;
				break;
			case sf::Keyboard::Down:
				move_x += 0.05;
				break;
			case sf::Keyboard::Right:
				move_z -= 0.05;
				break;
			case sf::Keyboard::Left:
				move_z += 0.05;
				break;
			case sf::Keyboard::W:
				move_y += 0.05;
				break;
			case sf::Keyboard::S:
				move_y -= 0.05;
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

	// � ��� ���� �� ������ �������� ��� ���������� ������� �

	return 0;
}

// � ������ ������������� ������� ���������� �������� �������, ������� � ������ �����
void Init() {
	// ������� ������ ���� ����� ������
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// ������� ��������������� ��������� �����
void Draw() {

	// ������������� ��������� ������� ��������������
	//glLoadIdentity();
	glEnable(GL_DEPTH_TEST);


	// ������������� ��������� ������� ��������������
	glLoadIdentity();

	glTranslatef(move_x, 0.0, 0.0);
	glTranslatef(0.0, move_y, 0.0);
	glTranslatef(0.0 , 0.0, -move_z);

	glRotated(-90, 1.0, 0.0, 0.0);
	glRotated(-16, 0.0, 1.0, 0.0);

	//front triangle
	glBegin(GL_TRIANGLES);
	// Front
	glColor3f(1.0f, 1.0f, 1.0f); glVertex3f(0.0f, 0.5f, 0.0f);//w
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);//r
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);//b
	glEnd();

	glBegin(GL_TRIANGLES);
	// Right
	glColor3f(1.0f, 1.0f, 1.0f); glVertex3f(0.0f, 0.5f, 0.0f);//w
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);//r
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); glVertex3f(0.0f, -0.5f, -0.5f);//g
	
	glEnd();

	glBegin(GL_TRIANGLES);
	// Back
	glColor3f(1.0f, 1.0f, 1.0f); glVertex3f(0.0f, 0.5f, 0.0f);//w
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);//b
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); glVertex3f(0.0f, -0.5f, -0.5f);//g
	glEnd();

	glBegin(GL_TRIANGLES);
	// Bottom
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);//r
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);//b
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); glVertex3f(0.0f, -0.5f, -0.5f);//g
	glEnd();

	

	// ���������� ����� ������ ��������������
	glFlush();

}


void SetIcon(sf::Window& wnd)
{
	sf::Image image;

	
		image.create(16, 16);
	for (int i = 0; i < 16; ++i)
		for (int j = 0; j < 16; ++j)
			image.setPixel(i, j, {
			(sf::Uint8) (i * 16), (sf::Uint8)(j * 16), 0 });

	wnd.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
}