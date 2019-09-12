#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <viperfish_dear_imgui.hpp>
#include "GraphicsTestApp.hpp"

GraphicsTestApp::GraphicsTestApp()
	: Widget("Graphics Test App")
{

}


GraphicsTestApp::~GraphicsTestApp()
{

}

void GraphicsTestApp::OnUpdate(double timestamp)
{
	Vf::Widget::OnUpdate(timestamp);
}

void GraphicsTestApp::OnKeyDown(const std::string& key, int keymod)
{
	Vf::Widget::OnKeyDown(key, keymod);
	if (key == "Escape") LeaveMainLoop();
}

void GraphicsTestApp::OnKeyUp(const std::string& key, int keymod)
{
	Vf::Widget::OnKeyUp(key, keymod);
}

void GraphicsTestApp::OnReshape(int width, int height)
{
	HFLOGDEBUGFIRSTRUN();
	Vf::Widget::OnReshape(width, height);

	glViewport(windowRect().x, windowRect().y, windowRect().w, windowRect().h);
}

void GraphicsTestApp::OnPreRender()
{
	HFLOGDEBUGFIRSTRUN();
	Vf::Widget::OnPreRender();

	glClearColor(0.5f * (1.0f + cosf(getT1())), 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsTestApp::OnRender3D()
{
	HFLOGDEBUGFIRSTRUN();
}

void GraphicsTestApp::OnRender2D()
{
	HFLOGDEBUGFIRSTRUN();
}

void GraphicsTestApp::OnRenderDearImGui()
{
	return;
	HFLOGDEBUGFIRSTRUN();
	//ImGui::SetNextWindowContentWidth(512.0f);
	//ImGui::SetNextWindowPos(ImVec2(32, 64));
	//ImGui::Begin("Graphics Test");
	//if (ImGui::Button("Test")) {
	//	if (ImGui::Button("Shows")) {

	//	}
	//}
	//ImGui::End();
}

void GraphicsTestApp::OnPostRender()
{
	HFLOGDEBUGFIRSTRUN();
	Vf::Widget::OnPostRender();
}
