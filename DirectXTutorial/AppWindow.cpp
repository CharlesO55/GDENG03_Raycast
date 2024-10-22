#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"
#include "EngineTime.h"

#include "Cube.h"
#include "Quad.h"
#include "Circle.h"
#include "Plane.h"

#include "Debugger.h"
#include <iostream>


AppWindow::AppWindow(){}
AppWindow::~AppWindow(){}

void AppWindow::onCreate()
{
	Window::onCreate();

	// INPUT SYSTEM
	InputSystem::get()->addListener(this);
	InputSystem::get()->showCursor(false);

	// GRAPHICS ENGINE
	m_swap_chain = GraphicsEngine::get()->getRenderSystem()->createSwapChain(this->m_hwnd, m_windowWidth, m_windowHeight);

	
	// SCENE CAMERA
	m_Camera = new Camera(&m_windowWidth, &m_windowHeight);

	//testCreate();
	
	// CREATE A PLANE
	Primitive* plane = new Plane(Vector3D(96/256.f, 125 / 256.f, 141 / 256.f));
	plane->initialize();
	plane->getTransform()->scale(Vector3D(20));

	m_shapes.push_back(plane);


	Vector3D spawnPositions[] = {
		Vector3D(-1, 1, 0),
		Vector3D(0, 1, 0),
		Vector3D(1, 1, 0),
		Vector3D(-0.5f, 3, 0),
		Vector3D(0.5f, 3, 0),
		Vector3D(0, 5, 0),
	};


	Vector3D offset = Vector3D(0.5f,0,0);
	float angle = 76 * 0.0174533;

	//TRIANGLES
	for (int i = 0; i < sizeof(spawnPositions)/sizeof(Vector3D); i++) {
		Primitive* leftplane = new Plane();
		leftplane->initialize();

		leftplane->getTransform()->move(spawnPositions[i]);
		leftplane->getTransform()->scale(Vector3D(0,0, -0.5f));
		leftplane->getTransform()->rotate(Vector3D(0,0, angle));

		m_shapes.push_back(leftplane);

		Primitive* rightPlane = new Plane();
		rightPlane->initialize();

		rightPlane->getTransform()->move(spawnPositions[i] + offset);
		rightPlane->getTransform()->scale(Vector3D(0, 0,- 0.5f));
		rightPlane->getTransform()->rotate(Vector3D(0, 0, -angle));

		m_shapes.push_back(rightPlane);
	}
	
	Vector3D basePositions[] = {
		Vector3D(-0.5f, 2.01f, 0),
		Vector3D(1, 2, 0),
		Vector3D(0.25f, 4, 0)
	};

	for (int i = 0; i < sizeof(basePositions)/sizeof(Vector3D); i++)
	{
		Primitive* baseplane = new Plane();
		baseplane->initialize();
		baseplane->getTransform()->move(basePositions[i]);
		baseplane->getTransform()->scale(Vector3D(0, 0, -0.5f));

		m_shapes.push_back(baseplane);
	}




	for (int i = 1; i < m_shapes.size(); i++) {
		std::cout << i << std::endl;
		std::cout << "Pos  :"; Debugger::PrintVector(m_shapes[i]->getTransform()->m_pos);
		std::cout << "Scale:"; Debugger::PrintVector(m_shapes[i]->getTransform()->m_scale);
		std::cout << "Rot:"; Debugger::PrintVector(m_shapes[i]->getTransform()->m_rot);
	}


	//CONSTANT BUFFER
	constant cc;
	cc.m_time = 0;
	
	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
}


void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::get()->update();

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0.2, 0.2, 0.2, 1); //BLACK
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(m_windowWidth, m_windowHeight);

	// Update the camera
	m_Camera->update();

	for (int i = 0; i < m_shapes.size(); i++) {
		// Calc the circle's matrices
		m_shapes[i]->updateMatrix(m_Camera->getView(), m_Camera->getProj());

		// Move the cube based on its position on screen space
		m_shapes[i]->update();
		m_shapes[i]->draw();
	}

	//testUpdate();
	//testDraw();

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	
	while (m_shapes.size() > 0) {
		delete m_shapes.back();
		m_shapes.pop_back();
	}
}




void AppWindow::InstantiateShape()
{
	Primitive* newShape = new Cube();
	newShape->initialize();
	newShape->getTransform()->move(Vector3D(
		std::rand() % 10 + -5,
		std::rand() % 10 + -5,
		std::rand() % 10 + -5
	));

	m_shapes.push_back(newShape);
}


void AppWindow::testCreate()
{
	m_wood_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"..\\Assets\\Textures\\wood.jpg");

	Vector3D position_list[] =
	{
		{ Vector3D(-0.5f,-0.5f,-0.5f)},
		{ Vector3D(-0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,-0.5f,-0.5f)},

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f) },
		{ Vector3D(0.5f,0.5f,0.5f) },
		{ Vector3D(-0.5f,0.5f,0.5f)},
		{ Vector3D(-0.5f,-0.5f,0.5f) }
	};

	Vector2D texcoord_list[] =
	{
		{ Vector2D(0.0f,0.0f) },
		{ Vector2D(0.0f,1.0f) },
		{ Vector2D(1.0f,0.0f) },
		{ Vector2D(1.0f,1.0f) }
	};



	vertexTex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{ position_list[0],texcoord_list[1] },
		{ position_list[1],texcoord_list[0] },
		{ position_list[2],texcoord_list[2] },
		{ position_list[3],texcoord_list[3] },


		{ position_list[4],texcoord_list[1] },
		{ position_list[5],texcoord_list[0] },
		{ position_list[6],texcoord_list[2] },
		{ position_list[7],texcoord_list[3] },


		{ position_list[1],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[2],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[0],texcoord_list[0] },
		{ position_list[3],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[3],texcoord_list[1] },
		{ position_list[2],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[1],texcoord_list[2] },
		{ position_list[0],texcoord_list[3] }


	};


	UINT size_list = ARRAYSIZE(vertex_list);


	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		8,9,10,
		10,11,8,
		//BOTTOM SIDE
		12,13,14,
		14,15,12,
		//RIGHT SIDE
		16,17,18,
		18,19,16,
		//LEFT SIDE
		20,21,22,
		22,23,20
	};

	UINT size_index_list = ARRAYSIZE(index_list);
	m_ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(index_list, size_index_list);


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);
	//CHANGE.........................
	m_vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(vertex_list, sizeof(vertexTex), size_list, shader_byte_code, (UINT)size_shader, ShaderType::BASIC_TEXTURE);

	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();


	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();
}

void AppWindow::testUpdate()
{
	constant cc;
	cc.m_world.setIdentity();

	Matrix4x4 temp;
	Matrix4x4 world_cam;
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(0);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(0);
	world_cam *= temp;

	cc.m_view = m_Camera->getView();
	cc.m_proj = m_Camera->getProj();
	m_cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);
}

void AppWindow::testDraw()
{
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setTexture(m_ps, m_wood_tex);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}



void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}


void AppWindow::onKeyDown(int key)
{
	switch (key) {
		//ESCAPE
	case 27:
		this->onDestroy();
		break;
		//SPACE
	case 32:
		InstantiateShape();
		break;
		//BACKSPACE
	case 8:
		if (m_shapes.size() > 0) {
			delete m_shapes.back();
			m_shapes.pop_back();
		}
		break;
		//DELETE
	case 46:
		while (m_shapes.size() > 0) {
			delete m_shapes.back();
			m_shapes.pop_back();
		}
		break;
	}
}

void AppWindow::onKeyUp(int key){}

void AppWindow::onMouseMove(const Point& mouse_pos)
{
	InputSystem::get()->setCursorPosition(Point((m_windowWidth / 2), (m_windowHeight / 2)));
}

void AppWindow::onLeftMouseDown(const Point& mouse_pos){}
void AppWindow::onLeftMouseUp(const Point& mouse_pos){}
void AppWindow::onRightMouseDown(const Point& mouse_pos){}
void AppWindow::onRightMouseUp(const Point& mouse_pos){}