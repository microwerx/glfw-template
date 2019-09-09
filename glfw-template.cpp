#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "viperfish.hpp"

#ifdef WIN32
#ifndef _DEBUG
#pragma comment(lib, "glfw3.lib")
#else
#pragma comment(lib, "glfw3d.lib")
#endif // NDEBUG
#endif // WIN32

//////////////////////////////////////////////////////////////////////
// G L O B A L   V A R I A B L E S ///////////////////////////////////
//////////////////////////////////////////////////////////////////////

namespace glfwt
{
	std::string windowTitle = "GLFW Template";
	int displayMode = GLUT_DOUBLE | GLUT_STENCIL | GLUT_RGBA | GLUT_DEPTH;
	int screenWidth = 1280;
	int screenHeight = 720;
	double Fps = 0;
	double aspectRatio = (double)glfwt::screenWidth / (double)glfwt::screenHeight;
	int mouseDX = 0;
	int mouseDY = 0;
	int mouseX = 0;
	int mouseY = 0;
	int mouseButtons = 0;
	int joystickButtonMask = 0;
	int joystickX = 0;
	int joystickY = 0;
	int joystickZ = 0;
	int joystickPollInterval = 16;
	int timer1millis = 0;
	int timer2millis = 0;
	int timer3millis = 0;
	int timer4millis = 0;
	int timer1value = 0;
	int timer2value = 0;
	int timer3value = 0;
	int timer4value = 0;
	int frameCount = 0;
	bool willResetErrorCountAfterFrame = false;
	int errorCount = 0;
	double updateInterval = 0.01666667f;
	double renderInterval = 0.01666667f;
	double Fov = 45.0;
	double zNear = 0.01;
	double zFar = 100.0;
	std::map<int, int> keyMap;
	int specialKeyMap[256] = { 0 };
	std::vector<std::string> args;
	Viperfish::Widget::SharedPtr vfWidget = nullptr;
	bool exitMainloop = false;

	GLFWwindow* window = nullptr;
}

//////////////////////////////////////////////////////////////////////
// P R O T O T Y P E S ///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

namespace glfwt
{
	int glfwKeyToVf(int key)
	{
		if (key >= GLFW_KEY_F1 && key <= GLFW_KEY_F12) return VF_KEY_F1 + (key - GLFW_KEY_F1);
		else if (key == GLFW_KEY_LEFT) return VF_KEY_LEFT;
		else if (key == GLFW_KEY_RIGHT) return VF_KEY_RIGHT;
		else if (key == GLFW_KEY_UP) return VF_KEY_UP;
		else if (key == GLFW_KEY_DOWN) return VF_KEY_DOWN;
		else if (key == GLFW_KEY_ESCAPE) return 27;
		else if (key == GLFW_KEY_TAB) return '\t';
		else if (key == GLFW_KEY_ENTER) return '\n';
		else if (key == GLFW_KEY_BACKSPACE) return '\b';
		else if (key == GLFW_KEY_LEFT_ALT) return VF_KEY_ALT_L;
		else if (key == GLFW_KEY_RIGHT_ALT) return VF_KEY_ALT_R;
		else if (key == GLFW_KEY_LEFT_SHIFT) return VF_KEY_SHIFT_L;
		else if (key == GLFW_KEY_RIGHT_SHIFT) return VF_KEY_SHIFT_R;
		else if (key == GLFW_KEY_LEFT_CONTROL) return VF_KEY_CTRL_L;
		else if (key == GLFW_KEY_RIGHT_CONTROL) return VF_KEY_CTRL_R;
		else if (key == GLFW_KEY_MENU) return VF_KEY_MENU;
		else if (key == GLFW_KEY_LEFT_SUPER) return VF_KEY_META_L;
		else if (key == GLFW_KEY_RIGHT_SUPER) return VF_KEY_META_R;
		else if (key >= GLFW_KEY_KP_0 && key <= GLFW_KEY_KP_EQUAL) return VF_KEY_KP_0 + (key - GLFW_KEY_KP_0);
		else if (key == GLFW_KEY_PAGE_UP) return VF_KEY_PAGE_UP;
		else if (key == GLFW_KEY_PAGE_DOWN) return VF_KEY_PAGE_DOWN;
		else if (key == GLFW_KEY_HOME) return VF_KEY_HOME;
		else if (key == GLFW_KEY_END) return VF_KEY_END;
		else if (key == GLFW_KEY_INSERT) return VF_KEY_INSERT;
		else if (key == GLFW_KEY_DELETE) return VF_KEY_DELETE;
		return key;
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		keyMap[key] = action;
		Viperfish::SetKeyboardModifiers(
			mods & GLFW_MOD_SHIFT,
			mods & GLFW_MOD_CONTROL,
			mods & GLFW_MOD_ALT,
			mods & GLFW_MOD_SUPER,
			mods & GLFW_MOD_CAPS_LOCK,
			mods & GLFW_MOD_NUM_LOCK);
		key = glfwKeyToVf(key);
		int keymod = Viperfish::GetKeyboardModifiers();
		std::string keyName = key < 0x100 ? Viperfish::KeyToHTML5Name(key) : Viperfish::SpecialKeyToHTML5Name(key);
		
		if (vfWidget) {
			if (action == GLFW_PRESS)
				vfWidget->OnKeyDown(keyName, keymod);
			else if (action == GLFW_RELEASE) {
				vfWidget->OnKeyUp(keyName, keymod);
			}
			else if (action == GLFW_REPEAT) {
				// ... not doing repeats right now
			}
		}
		else {
			if (key == 27) {
				glfwt::exitMainloop = true;
			}
		}
	}

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		if (!vfWidget) return;
		vfWidget->OnMouseMove((int)xpos, (int)ypos);
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (!vfWidget) return;

		bool pressed = (action == GLFW_PRESS);

		int mbutton = 0;

		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			mbutton = VF_MOUSE_BUTTON_LEFT;
		}
		
		if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
			mbutton = VF_MOUSE_BUTTON_RIGHT;
		}
		
		if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			mbutton = VF_MOUSE_BUTTON_MIDDLE;
		}

		if (pressed) {
			vfWidget->OnMouseButtonDown(mbutton);
		}
		else {
			vfWidget->OnMouseButtonUp(mbutton);
		}
	}

	void window_size_callback(GLFWwindow* window, int width, int height)
	{
		aspectRatio = (double)width / (double)height;
		screenWidth = width;
		screenHeight = height;

		if (vfWidget) {
			vfWidget->OnReshape(width, height);
		}
		else {
			glViewport(0, 0, width, height);
		}
	}

	// timeStamp is seconds
	void OnUpdate(double deltaTime)
	{
		if (!vfWidget) return;
		vfWidget->OnUpdate(deltaTime);
	}

	void OnRender()
	{
		if (!vfWidget) return;
		vfWidget->OnPreRender();
		vfWidget->OnRender3D();
		vfWidget->OnRender2D();
		vfWidget->OnRenderDearImGui();
		vfWidget->OnPostRender();
	}
}

//////////////////////////////////////////////////////////////////////
// M A I N   E N T R Y   P O I N T  //////////////////////////////////
//////////////////////////////////////////////////////////////////////


void GlfwTemplateSetParameters(const std::string &windowTitle, int width, int height, int displayMode)
{
	glfwt::windowTitle = windowTitle;
	glfwt::screenWidth = width;
	glfwt::screenHeight = height;
	glfwt::aspectRatio = (float)width / (float)height;
	if (displayMode >= 0) {
		glfwt::displayMode = displayMode;
	}
}

bool GlfwTemplateInit(int argc, char **argv)
{
	// Initialize GLFW
	if (!glfwInit()) {
		HFLOGERROR("GLFW cannot be initialized");
		return false;
	}

	// monitor is set to NULL
	// share is set to NULL
	glfwt::window = glfwCreateWindow(glfwt::screenWidth, glfwt::screenHeight, glfwt::windowTitle.c_str(), NULL, NULL);

	glfwMakeContextCurrent(glfwt::window);

	glfwSetKeyCallback(glfwt::window, glfwt::key_callback);
	glfwSetMouseButtonCallback(glfwt::window, glfwt::mouse_button_callback);
	glfwSetCursorPosCallback(glfwt::window, glfwt::cursor_position_callback);
	glfwSetWindowSizeCallback(glfwt::window, glfwt::window_size_callback);

	glfwt::exitMainloop = false;

	return true;
}

void GlfwTemplateWidget(Viperfish::Widget::SharedPtr widget)
{
	glfwt::vfWidget = widget;
}

void GlfwTemplateMainLoop()
{
	// Initialize Viperfish widgets
	if (glfwt::vfWidget) {
		glfwt::vfWidget->Init(glfwt::args);
		glfwt::vfWidget->OnReshape(glfwt::screenWidth, glfwt::screenHeight);
	}

	// Loop until the user closes the window
	double t0 = glfwGetTime();
	while (!glfwWindowShouldClose(glfwt::window) && !glfwt::exitMainloop) {
		double t1 = glfwGetTime();
		double dt = t1 - t0;
		t0 = t1;

		// Update widgets
		glfwt::OnUpdate(dt);

		// Render widgets (3D, 2D, and then DearImGUI)
		glfwt::OnRender();

		// Double buffering
		glfwSwapBuffers(glfwt::window);

		// Poll/process events
		glfwPollEvents();

		if (glfwt::vfWidget) {
			glfwt::exitMainloop = glfwt::vfWidget->leaveMainLoop();
		}
	}

	// Kill viperfish widgets
	if (glfwt::vfWidget) {
		glfwt::vfWidget->Kill();
	}

	// Uninitialize GLFW
	glfwTerminate();
}