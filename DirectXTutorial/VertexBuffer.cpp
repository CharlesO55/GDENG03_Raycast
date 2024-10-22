#include "VertexBuffer.h"
#include "RenderSystem.h"

#include "Debugger.h"

VertexBuffer::VertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list,
	void* shader_byte_code, size_t size_byte_shader,
	RenderSystem* system, ShaderType SHADER_TYPE) : m_system(system), m_layout(0), m_buffer(0)
{
	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_vertex * size_list;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_vertices;

	m_size_vertex = size_vertex;
	m_size_list = size_list;

	if (FAILED(m_system->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
	{
		Debugger::Error("[Vertex Buffer] Failed to create.");
	}


	D3D11_INPUT_ELEMENT_DESC* layout = nullptr;
	UINT size_layout;

	switch (SHADER_TYPE)
	{
		case ShaderType::ANIMATED_COLOR: {
			D3D11_INPUT_ELEMENT_DESC bufferElements[] =
			{
				{"POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D11_INPUT_PER_VERTEX_DATA ,0},
				{"POSITION", 1,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 12,D3D11_INPUT_PER_VERTEX_DATA ,0},
				{ "COLOR", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 24,D3D11_INPUT_PER_VERTEX_DATA ,0 },
				{ "COLOR", 1,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 36,D3D11_INPUT_PER_VERTEX_DATA ,0 }
			};
			layout = bufferElements;
			size_layout = ARRAYSIZE(bufferElements);
			break;
		}
		case ShaderType::BASIC_TEXTURE: {
			D3D11_INPUT_ELEMENT_DESC bufferElements[] =
			{
				{"POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D11_INPUT_PER_VERTEX_DATA ,0},
				{"TEXCOORD", 0,  DXGI_FORMAT_R32G32_FLOAT, 0, 12,D3D11_INPUT_PER_VERTEX_DATA ,0},
			};
			layout = bufferElements;
			size_layout = ARRAYSIZE(bufferElements);
			break;
		}

		default:
			Debugger::Error("[Vertex Buffer] Unhandled layout case.");
	}


	if (FAILED(m_system->m_d3d_device->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &m_layout)))
	{
		Debugger::Error("[Vertex Buffer] Invalid layout parameters.");
	}

}


UINT VertexBuffer::getSizeVertexList()
{
	return this->m_size_list;
}


VertexBuffer::~VertexBuffer()
{
	m_layout->Release();
	m_buffer->Release();
}