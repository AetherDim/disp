#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

class GraphicsHandler {
public:
	using RenderCallback_t = std::function<void()>;

	GraphicsHandler(std::string name, RenderCallback_t const& f);
	GraphicsHandler(std::string name);
	~GraphicsHandler();

	bool add_render_callback(RenderCallback_t const& f);

	void run();
    void step();
    bool shouldExit();

private:
	bool init();
	void destroy();

	GraphicsHandler(const GraphicsHandler&) = delete;

	std::string const m_window_name;
	std::vector<RenderCallback_t> m_render_callbacks;
	bool m_init_success;
	void* m_window_handle;

};
