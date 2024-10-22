#include "GraphicsEngine.h"
#include "RenderSystem.h"

#include "Debugger.h"

GraphicsEngine* GraphicsEngine::m_engine = nullptr;

GraphicsEngine::GraphicsEngine()
{
	try
	{
		m_render_system = new RenderSystem();
	}
	catch (...) { Debugger::Error("[CREATE ERROR] Graphics Engine>Render System"); }
	try
	{
		m_tex_manager = new TextureManager();
	}
	catch (...) { Debugger::Error("[CREATE ERROR] Graphics Engine>Texture Manager"); }
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return m_render_system;
}

TextureManager* GraphicsEngine::getTextureManager()
{
	return m_tex_manager;
}

GraphicsEngine::~GraphicsEngine()
{
	GraphicsEngine::m_engine = nullptr;
	delete m_tex_manager;
	delete m_render_system;

	Debugger::Warning("[Graphics Engine] Destroyed");
}

void GraphicsEngine::create()
{
	if (GraphicsEngine::m_engine) 
		Debugger::Error("[DUPLICATE ERROR] Graphics Engine");
	
	GraphicsEngine::m_engine = new GraphicsEngine();
	Debugger::Success("[Graphics Engine] Created");
}

void GraphicsEngine::release()
{
	if (!GraphicsEngine::m_engine) 
		return;
	delete GraphicsEngine::m_engine;
}

GraphicsEngine* GraphicsEngine::get()
{
	return m_engine;
}