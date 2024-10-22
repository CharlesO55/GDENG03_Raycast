#include "Primitive.h"

#include "GraphicsEngine.h"
#include "DeviceContext.h"

#include "CameraSystem.h"

Primitive::Primitive() : SceneObject() {}

Primitive::~Primitive()
{
	release();
}

void Primitive::initialize()
{
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// VERTEX SHADER & BUFFER
	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShaderColor.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);
	m_vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(std::data(m_verts), sizeof(vertexColor), m_verts.size(), shader_byte_code, size_shader, ShaderType::ANIMATED_COLOR);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	// INDEX BUFFER
	m_ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(std::data(m_indices), m_indices.size());

	// PIXEL SHADER
	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShaderColor.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	// CONSTANT & CONSTANT BUFFER
	m_cc.m_time = 0;

	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&m_cc, sizeof(constant));
}

void Primitive::update()
{
	for (int i = 0; i < m_Components.size(); i++) {
		m_Components[i]->update();
	}
}

void Primitive::updateMVP(Matrix4x4* worldOverride)
{
	m_cc.m_world = getTransform()->getWorldMatrix();

	// Apply parent transform
	if (worldOverride != nullptr) {
		m_cc.m_world *= *worldOverride;
	}

	// UPDATES FROM CAMERA MATRICES
	m_cc.m_view = CameraSystem::getCamera()->getView();
	m_cc.m_proj = CameraSystem::getCamera()->getProj();

	m_cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &m_cc);

	// Recursive call for child to apply my transform as its parent.
	if (this->m_child != nullptr)
		((Primitive*)m_child)->updateMVP(&m_cc.m_world);
}

void Primitive::draw()
{
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);

	// Recursive call to draw children
	if (m_child != nullptr) {
		((Primitive*)m_child)->draw();
	}
}


void Primitive::release()
{
	/*delete m_vb;
	delete m_ib;
	delete m_cb;
	delete m_vs;
	delete m_ps;*/
	m_verts.clear();
}
