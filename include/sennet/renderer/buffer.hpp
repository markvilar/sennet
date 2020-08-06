#pragma once

namespace sennet
{

enum class shader_data_type
{
	None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3,
	Int4, Bool
};

static uint32_t shader_data_type_size(shader_data_type type)
{
	switch (type)
	{
		case shader_data_type::Float: 	return 4;
		case shader_data_type::Float2: 	return 4 * 2;
		case shader_data_type::Float3: 	return 4 * 3;
		case shader_data_type::Float4: 	return 4 * 4;
		case shader_data_type::Mat3: 	return 4 * 3 * 3;
		case shader_data_type::Mat4: 	return 4 * 4 * 4;
		case shader_data_type::Int: 	return 4;
		case shader_data_type::Int2: 	return 4 * 2;
		case shader_data_type::Int3: 	return 4 * 3;
		case shader_data_type::Int4: 	return 4 * 4;
		case shader_data_type::Bool: 	return 1;
		case shader_data_type::None:	return 0;
	}

	SN_CORE_ASSERT(false, "Unknown shader_data_type!");
	return 0;
}

static std::string to_string(shader_data_type type)
{
	switch (type)
	{
		case shader_data_type::Float: 	return "Float";
		case shader_data_type::Float2: 	return "Float2";
		case shader_data_type::Float3: 	return "Float3";
		case shader_data_type::Float4: 	return "Float4";
		case shader_data_type::Mat3: 	return "Mat3";
		case shader_data_type::Mat4: 	return "Mat4";
		case shader_data_type::Int: 	return "Int";
		case shader_data_type::Int2: 	return "Int2";
		case shader_data_type::Int3: 	return "Int3";
		case shader_data_type::Int4: 	return "Int4";
		case shader_data_type::Bool: 	return "Bool";
		case shader_data_type::None:	return "None";
	}

	SN_CORE_ASSERT(false, "Unknown shader_data_type!");
	return "";
}

struct buffer_element
{
	std::string name;	
	shader_data_type type;
	uint32_t offset;
	uint32_t size;
	bool normalized;

	buffer_element() {}
	buffer_element(const shader_data_type type, const std::string& name,
		const bool normalized = false)
		: type(type), name(name), size(shader_data_type_size(type)), 
		offset(0), normalized(normalized)
	{
	}

	uint32_t get_component_count() const
	{
		switch (type)
		{
			case shader_data_type::Float: 	return 1;
			case shader_data_type::Float2: 	return 2;
			case shader_data_type::Float3: 	return 3;
			case shader_data_type::Float4: 	return 4;
			case shader_data_type::Mat3: 	return 3 * 3;
			case shader_data_type::Mat4: 	return 4 * 4;
			case shader_data_type::Int: 	return 1;
			case shader_data_type::Int2: 	return 2;
			case shader_data_type::Int3: 	return 3;
			case shader_data_type::Int4: 	return 4;
			case shader_data_type::Bool: 	return 1;
			case shader_data_type::None:	return 0;
		}

		SN_CORE_ASSERT(false, "Unknown shader_data_type!");
		return 0;
	}
};

class buffer_layout
{
public:
	buffer_layout() {}
	buffer_layout(const std::initializer_list<buffer_element>& elements) 
		: m_elements(elements) 
	{
		calculate_offset_and_stride();
	}

	inline uint32_t get_stride() const { return m_stride; }
	inline const std::vector<buffer_element>& get_elements() const 
	{ 
		return m_elements; 
	}

	std::vector<buffer_element>::iterator begin() { return m_elements.begin(); }
	std::vector<buffer_element>::iterator end() { return m_elements.end(); }
	std::vector<buffer_element>::const_iterator begin() const 
	{ 
		return m_elements.begin(); 
	}
	std::vector<buffer_element>::const_iterator end() const 
	{ 
		return m_elements.end(); 
	}

	std::string to_string() const;

private:
	void calculate_offset_and_stride();

private:
	std::vector<buffer_element> m_elements;
	uint32_t m_stride = 0;
};

class vertex_buffer
{
public:
	virtual ~vertex_buffer() {}

	virtual void bind() const = 0;
	virtual void unbind() const = 0;

	virtual const buffer_layout& get_layout() const = 0;
	virtual void set_layout(const buffer_layout& layout) = 0;

	static vertex_buffer* create(float* vertices, uint32_t size);
};

class index_buffer
{
public:
	virtual ~index_buffer() {}

	virtual void bind() const = 0;
	virtual void unbind() const = 0;

	virtual uint32_t get_count() const = 0;

	static index_buffer* create(uint32_t* indices, uint32_t count);
};

}
