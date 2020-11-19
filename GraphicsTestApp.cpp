#include <fluxions_opengl.hpp>
#include <GLFW/glfw3.h>
#include <viperfish_dear_imgui.hpp>
#include "GraphicsTestApp.hpp"

GraphicsTestApp::GraphicsTestApp()
	: DearImGuiWidget("Graphics Test App") {

}


GraphicsTestApp::~GraphicsTestApp() {

}

void GraphicsTestApp::OnUpdate(double timestamp) {
	Vf::DearImGuiWidget::OnUpdate(timestamp);
}

void GraphicsTestApp::OnKeyDown(const std::string& key, int keymod) {
	Vf::DearImGuiWidget::OnKeyDown(key, keymod);
	if (key == "Escape") LeaveMainLoop();
}

void GraphicsTestApp::OnKeyUp(const std::string& key, int keymod) {
	Vf::DearImGuiWidget::OnKeyUp(key, keymod);
}

void GraphicsTestApp::OnReshape(int width, int height) {
	HFLOGDEBUGFIRSTRUN();
	Vf::DearImGuiWidget::OnReshape(width, height);

	glViewport(windowRect().x, windowRect().y, windowRect().w, windowRect().h);
}

void GraphicsTestApp::OnPreRender() {
	HFLOGDEBUGFIRSTRUN();
	Vf::DearImGuiWidget::OnPreRender();

	glClearColor(0.5f * (1.0f + cosf(getT1())), 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsTestApp::OnRender3D() {
	HFLOGDEBUGFIRSTRUN();
	Vf::DearImGuiWidget::OnRender3D();

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(45.0f, aspectRatio(), 0.1f, 100.0f);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//glTranslatef(0.0f, 0.0f, -10.0f);
	//glBegin(GL_TRIANGLE_STRIP);
	//glColor3f(0.1f, 0.5f, 1.0f);
	//glNormal3f(0.0f, 0.0f, 1.0f);
	//glVertex3f(-1.0f,  1.0f, 0.0f);
	//glVertex3f(-1.0f, -1.0f, 0.0f);
	//glVertex3f( 1.0f,  1.0f, 0.0f);
	//glVertex3f( 1.0f, -1.0f, 0.0f);
	//glEnd();
}

void GraphicsTestApp::OnRender2D() {
	HFLOGDEBUGFIRSTRUN();
	Vf::DearImGuiWidget::OnRender2D();
}

void GraphicsTestApp::OnRenderDearImGui() {
	HFLOGDEBUGFIRSTRUN();
	Vf::DearImGuiWidget::OnRenderDearImGui();
	ImGui::SetNextWindowSize(ImVec2(512.0f, 128.0f), ImGuiCond_Appearing);
	ImGui::SetNextWindowPos(ImVec2(32.0f, 32.0f), ImGuiCond_Appearing);
	ImGui::Begin("Graphics Test");
	ImGui::SetWindowFontScale(2.0f);
	if (ImGui::Button("Test")) {
	}
	if (ImGui::Button("Shows")) {

	}
	ImGui::End();
}

void GraphicsTestApp::OnPostRender() {
	HFLOGDEBUGFIRSTRUN();
	Vf::DearImGuiWidget::OnPostRender();
}
