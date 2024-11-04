#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Primitive.h"
#include "ConstantBuffer.h"

#include "InputListener.h"

#include "Camera.h"

class Primitive;

#include <vector>

class AppWindow : public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();

	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;


private:
	std::vector<Primitive*> m_shapes = {};
	std::vector<Primitive*> m_rays = {};

	bool m_is_selected = false;
	Primitive* m_selected_prim = nullptr;

	bool TryRacyastObjects(Vector3D* hitPos, Primitive*& hitObj);
	void DoRaycast();


	Vector3D GetRayDirection(int mouseX, int mouseY);


	// TESTING
	TexturePtr m_wood_tex = nullptr;
	void testCreate();
	void testUpdate();
	void testDraw();

	SwapChainPtr m_swap_chain;
	VertexBufferPtr m_vb;
	VertexShaderPtr m_vs;
	PixelShaderPtr m_ps;
	ConstantBufferPtr m_cb;
	IndexBufferPtr m_ib;


private:
	void InstantiateShape(const Vector3D& spawnPos);

	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Point& mouse_pos) override;
	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;
	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;

	virtual void onFocus() override;
	virtual void onKillFocus() override;
};