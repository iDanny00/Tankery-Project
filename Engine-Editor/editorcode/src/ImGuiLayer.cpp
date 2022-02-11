#include "../include/ImGuiLayer.h"

#include "imgui.h"
#include "..\OpenGL\ImGuiOpenGL.h"
<<<<<<< Updated upstream
=======
#include "..\OpenGL\ImGuiGLFW.h"
>>>>>>> Stashed changes
#include "GLFW/glfw3.h"

namespace Engine {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
		
	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
<<<<<<< Updated upstream
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
=======

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls

>>>>>>> Stashed changes
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		//Temp - Use Engine KeyCodes?
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDettach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnUpdate(float timestep)
	{
		Log::info("UPDATE GUI");
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::getInstance();
		io.DisplaySize = ImVec2(app.getAppWindow()->getWidth(), app.getAppWindow()->getHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60);
		m_Time = time;
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

#pragma region -- [ GUIInputManager ] --
	void ImGuiLayer::onMouseMoved(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.getX(), e.getY());

	}
	void ImGuiLayer::onKeyPressed(KeyPressedEvent& e)
	{
#pragma region Controls
		if (e.getKeyCode() == GLFW_KEY_C)
		{
			glfwSetInputMode(reinterpret_cast<GLFWwindow*>(app.getAppWindow()->getNativewindow()), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else if (e.getKeyCode() == NG_KEY_LEFT_ALT )
		{
			glfwSetInputMode(reinterpret_cast<GLFWwindow*>(app.getAppWindow()->getNativewindow()), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
#pragma endregion

		//Log::info("Key Pressed GUI");
	}

<<<<<<< Updated upstream
	void ImGuiLayer::OnUpdate(float timestep)
=======
	void ImGuiLayer::onKeyReleased(KeyReleasedEvent& e)
>>>>>>> Stashed changes
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::getInstance();
		io.DisplaySize = ImVec2(app.getAppWindow()->getWidth(), app.getAppWindow()->getHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();


		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

<<<<<<< Updated upstream
	void ImGuiLayer::onMouseMoved(MouseMovedEvent& e)
	{
		Log::info("Mouse MOVED GUI");
	}
	void ImGuiLayer::onKeyPressed(KeyPressedEvent& e)
	{
		Log::info("Key Pressed GUI");
=======
	/*void ImGuiLayer::onKeyTypedEvent(KeyTypedEvent& e)
	{

	}*/

	void ImGuiLayer::onMouseBtnPressed(MouseButtonPressedEvent & e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.getButton()] = true;

		//Log::info("Mouse Button Pressed GUI");
	}

	void ImGuiLayer::onMouseBtnReleased(MouseButtonReleasedEvent&e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.getButton()] = false;
	}

	void ImGuiLayer::onMouseScrolled(MouseScrollEvent & e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.getXScroll();
		io.MouseWheel += e.getYScroll();
		//Log::info("Mouse Scrolled GUI");
>>>>>>> Stashed changes
	}
#pragma endregion

}



