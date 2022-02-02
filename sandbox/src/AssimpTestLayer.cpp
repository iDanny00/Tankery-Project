#include "AssimpTestLayer.h"
#include "assimpLoader.h"


AssimpLayer::AssimpLayer(const char* name) : Layer(name)
{
	clearColorAndDepthCommand.reset(RenderCommandFactory::createCommand(RendererCommands::Commands::clearColorAndDepthBuffer));
	std::shared_ptr<RendererCommands> setclearCommand;
	setclearCommand.reset(RenderCommandFactory::createCommand(RendererCommands::Commands::setClearColor, 1.0f, 1.0f, 1.0f, 1.0f));
	RendererShared::actionCommand(setclearCommand);

	m_camera.setCameraPos(glm::vec3(-1.0f, 1.0f, 6.0f));
	m_view3D = m_camera.getCameraViewMatrix();
	m_projection3D =
		glm::perspective(glm::radians(m_camera.getFOV()), (float)RendererShared::SCR_WIDTH / (float)RendererShared::SCR_HEIGHT, 0.1f, 100.f);

	m_swu3D["u_view"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(m_view3D)));
	m_swu3D["u_projection"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(m_projection3D)));

	//1st model
	Loader::ASSIMPLoad("./assets/models/Tank.obj", aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_Triangulate);

	//2nd model
	Loader::ASSIMPLoad("./assets/models/lettercube/lettercube.obj", aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_Triangulate);

#pragma region [History] VAO stuff
	//cubeVAO2.reset(VertexArray::create());
	//VertexBufferLayout cubeBufferLayout2 = { ShaderDataType::Float3,ShaderDataType::Float3 ,ShaderDataType::Float2 };
	//cubeVBO2.reset(VertexBuffer::create(Loader::output.vertices.data(), sizeof(Renderer3DVertex) * Loader::output.vertices.size(), cubeBufferLayout2));
	//cubeIBO2.reset(IndexBuffer::create(Loader::output.indicies.data(), Loader::output.indicies.size()));
	//cubeVAO2->addVertexBuffer(cubeVBO2);
	//cubeVAO2->setIndexBuffer(cubeIBO2);
	//material1.reset(new Material(shader, Loader::output.diffusTex, glm::vec4(1.0f)));
#pragma endregion
}

void AssimpLayer::OnUpdate(float timestep)
{
	glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), m_rotation.x, { 1.f, 1.f, 1.f });
	glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), m_rotation.y, { 0.f, 1.f, 0.f });
	glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), m_rotation.z, { 0.f, 1.f, 1.f });
	
	glm::mat4 rotation = rotX * rotY * rotZ;

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), { m_scale, m_scale, m_scale });
	
	m_model1 = rotation * scale;
	m_model2 = rotation * scale;
	m_model2 = glm::translate(glm::mat4(1.0f), glm::vec3(-5.f, 0.f, 0.f));
	m_camera.update(timestep);
}

void AssimpLayer::OnRender()
{
	RendererShared::actionCommand(clearColorAndDepthCommand);
	m_view3D = m_camera.getCameraViewMatrix();

	m_swu3D["u_view"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(m_view3D)));
	m_swu3D["u_projection"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(m_projection3D)));

	Renderer3D::begin(m_swu3D);

	auto count = Loader::s_VAO.size();
	for (int i = 0; i < count; i++)
	{
		m_VAO = Loader::s_VAO[i];
		mat = Loader::s_material[i];
		Renderer3D::submit(m_VAO, mat, m_model1);
		m_model1 = glm::translate(glm::mat4(1.0f), glm::vec3(-5.f, 0.f, 0.f));
	}

	//Renderer3D::submit(cubeVAO1, material, m_model1);
	//Renderer3D::submit(cubeVAO2, material1, m_model2);

	Renderer3D::end();
}

void AssimpLayer::onMouseMoved(MouseMovedEvent& e)
{
	m_camera.mouseMovement(e.getMousePos().x, e.getMousePos().y);
}

void AssimpLayer::onKeyPressed(KeyPressedEvent& e)
{
	float rot = 0.25;
	float scale = 0.01;
	if (e.getKeyCode() == NG_KEY_KP_ADD)
	{
		if (InputPoller::isKeyPressed(NG_KEY_X)) { m_rotation.x += rot; }
		else if (InputPoller::isKeyPressed(NG_KEY_Y)) { m_rotation.y += rot; }
		else if (InputPoller::isKeyPressed(NG_KEY_Z)) { m_rotation.z += rot; }
		else { m_scale += scale; }
	}

	if (e.getKeyCode() == NG_KEY_KP_SUBTRACT)
	{
		if (InputPoller::isKeyPressed(NG_KEY_X)) { m_rotation.x -= rot; }
		else if (InputPoller::isKeyPressed(NG_KEY_Y)) { m_rotation.y -= rot; }
		else if (InputPoller::isKeyPressed(NG_KEY_Z)) { m_rotation.z -= rot; }
		else if (m_scale >scale) { m_scale -= scale; }
	}
}