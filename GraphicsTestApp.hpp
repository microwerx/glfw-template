#ifndef GRAPHICS_TEST_APP_HPP
#define GRAPHICS_TEST_APP_HPP

#include <viperfish_dear_imgui.hpp>

class GraphicsTestApp :
	public Vf::DearImGuiWidget
{
public:
	GraphicsTestApp();
	~GraphicsTestApp() override;

	void OnUpdate(double timeStamp) override;

	void OnKeyDown(const std::string& key, int keymod) override;
	void OnKeyUp(const std::string& key, int keymod) override;

	void OnReshape(int width, int height) override;

	void OnPreRender() override;
	void OnRender3D() override;
	void OnRender2D() override;
	void OnRenderDearImGui() override;
	void OnPostRender() override;
private:
	float windowSize = 512.0f;
	ImVec2 windowPosition = ImVec2(32.0f, 32.0f);
};

#endif