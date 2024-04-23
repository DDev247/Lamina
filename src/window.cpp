#include "../include/window.hpp"

bool lm::Window::CreateWindow(lm::vec2<int> windowSize, std::string windowName, int windowHints)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (windowHints == NULL) glfwDefaultWindowHints();
	else
	{
		switch (windowHints)
		{
		case LM_RESIZABLE_WINDOW:
		{
			glfwDefaultWindowHints();
			glfwWindowHint(GLFW_RESIZABLE, true);
			glfwWindowHint(GLFW_DOUBLEBUFFER, true);
		}
		break;
		case LM_NON_RESIZABLE_WINDOW:
		{
			glfwDefaultWindowHints();
			glfwWindowHint(GLFW_RESIZABLE, false);
			glfwWindowHint(GLFW_DOUBLEBUFFER, true);

		}
		break;
		case LM_FULL_SCREEN_WINDOW:
		{
			glfwDefaultWindowHints();
			glfwWindowHint(GLFW_RESIZABLE, false);
			glfwWindowHint(GLFW_DOUBLEBUFFER, true);
		}
		break;
		case LM_BORDERLESS_WINDOW:
		{
			glfwDefaultWindowHints();
			glfwWindowHint(GLFW_RESIZABLE, false);
			glfwWindowHint(GLFW_DECORATED, false);
			glfwWindowHint(GLFW_MAXIMIZED, true);
			glfwWindowHint(GLFW_SCALE_TO_MONITOR, true);
			glfwWindowHint(GLFW_DOUBLEBUFFER, true);
		}
		break;
		default:
			std::cout << "Failed to create window - invalid hints" << std::endl;
			return false;
			break;
		}
	}

	if(windowHints != LM_FULL_SCREEN_WINDOW) window = glfwCreateWindow(windowSize.x, windowSize.y, windowName.c_str(), NULL, NULL);
	else window = glfwCreateWindow(windowSize.x, windowSize.y, windowName.c_str(), glfwGetPrimaryMonitor(), NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window - window is NULL" << std::endl;
		return false;
	}
	else return true;
}

void lm::Window::Clear(lm::Color color)
{
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) std::cout << "Failed to load GLAD" << std::endl;

	lm::ColorF floatColor = lm::GetFloatColor(color);
	glClearColor(floatColor.r, floatColor.g, floatColor.b, floatColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

template<typename T>
void lm::Window::Draw(T target)
{
	if (std::is_same(T, lm::Rectangle))
	{

	}
	else if (std::is_same(T, lm::Triangle))
	{

	}
	else std::cout << "Undefined drawing type" << std::endl;
}