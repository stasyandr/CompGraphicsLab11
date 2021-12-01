#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <tgmath.h>
void SetIcon(sf::Window& wnd);
void Init();
void DrawCircle();
std::vector<double> RGB_Transformer_From_HSV(double, double, double);
double a = 0.25, b = 0.5;
int main() {
	sf::Window window(sf::VideoMode(1000, 1000), "My OpenGL window", sf::Style::Default, sf::ContextSettings(32));
	SetIcon(window);
	window.setVerticalSyncEnabled(true);

	window.setActive(true);

	Init();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::Resized) {
				glViewport(0, 0, event.size.width, event.size.height);
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Left)
				{
					b *= 0.99;
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					a *= 0.99;
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					b *= 1.01;
				}
				if (event.key.code == sf::Keyboard::Up)
				{
					a *= 1.01;
				}
			}
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		DrawCircle();
		window.display();
	}
	return 0;
}

void Init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void DrawCircle() {
	float twicePi = 2.0 * 3.142;
	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(255, 255, 255);
	glVertex2f(0, 0);
	for (int i = 0; i <= 120; i++) {
		std::vector<double> col = RGB_Transformer_From_HSV(3 * i, 1, 1);
		glColor3ub(col[0] * 255, col[1] * 255, col[2] * 255);
		glVertex2f(
			b * cosf(i * twicePi / 120.0f), a * sinf(i * twicePi / 120.0f)
		);
	}
	glEnd();
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

std::vector<double> RGB_Transformer_From_HSV(double H, double S, double V)
{

	int helper = (int)floor(H / 60.0) % 6;
	double x = H / 60.0 - floor(H / 60.0);
	double y = 1.0 * (1 - S) * V;
	double z = 1.0 * (1 - x * S) * V;
	double t = 1.0 * (1 - (1 - x) * S) * V;
	std::vector<double> l;
	switch (helper)
	{
	case 0:
		l.push_back(V);
		l.push_back(t);
		l.push_back(y);
		return l;
	case 1:
		l.push_back(z);
		l.push_back(V);
		l.push_back(y);
		return l;
	case 2:
		l.push_back(y);
		l.push_back(V);
		l.push_back(t);
		return l;
	case 3:
		l.push_back(y);
		l.push_back(z);
		l.push_back(V);
		return l;
	case 4:
		l.push_back(t);
		l.push_back(y);
		l.push_back(V);
		return l;
	case 5:
		l.push_back(V);
		l.push_back(y);
		l.push_back(z);
		return l;
	default:
		l.push_back(0);
		l.push_back(0);
		l.push_back(0);


		return l;
	}
}