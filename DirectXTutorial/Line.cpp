#include "Line.h"

#include "GraphicsEngine.h"
#include "DeviceContext.h"

Line::Line(const Vector3D startPos, const Vector3D endPos) : Primitive()
{
	m_verts =
	{
		{startPos, startPos,  Vector3D(1),  Vector3D(1)},
		{endPos, endPos,	Vector3D(1), Vector3D(1) },
	};

	//NOTE THERE'S NO INDEX BUFFER NEEDED SINCE IT'S ONLY 2 POINTS
}

void Line::draw()
{
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	//GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	// USING LINELIST INSTEAD OF INDEXLIST
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawLineList(m_verts.size());

	//// Recursive call to draw children
	if (m_child != nullptr) {
		((Primitive*)m_child)->draw();
	}
}
