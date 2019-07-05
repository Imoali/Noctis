#pragma once
namespace Noctis {
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		GraphicsContext();
		~GraphicsContext();
	};
}
