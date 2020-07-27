#include <sennet/sennet.hpp>

#include <glm/glm.hpp>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

glm::mat4 camera(float Translate, glm::vec2 const & Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
} 

class example_layer : public sennet::layer
{
public:
	example_layer()
		: layer("example")
	{
	}

	void on_update() override
	{
		if (sennet::input::is_key_pressed(SN_KEY_TAB))
			SN_TRACE("Tab key is pressed (poll)!");
	}

	void on_event(sennet::event& event) override
	{
		if (event.get_event_type() == sennet::event_type::key_pressed)
		{
			sennet::key_pressed_event& e =
				(sennet::key_pressed_event&)event;
			
			if (e.get_key_code() == SN_KEY_TAB)
			{
				SN_TRACE("Tab key is pressed (event)!");
			}

			SN_TRACE("{0}", (char)e.get_key_code());
		}
	}
};

class sandbox : public sennet::application
{
public:
	sandbox()
	{
		push_layer(new example_layer());
		push_overlay(new sennet::imgui_layer());
	}

	~sandbox()
	{
	}
};

sennet::application* sennet::create_application()
{
	return new sandbox();
}


int sennet::main(int argc, char** argv)
{
	sennet::log::init();

	auto app = sennet::create_application();
	app->run();
	return 0;
}

int main(int argc, char** argv)
{	
	return sennet::main(argc, argv);
}
