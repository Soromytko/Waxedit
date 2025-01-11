#pragma once
#include <memory>
#include <glm/glm.hpp>

class Viewport;

typedef std::shared_ptr<Viewport> ViewportSharedPtr;

class Viewport final
{
public:
	Viewport() = default;
	~Viewport() = default;

	static void setCurrent(const ViewportSharedPtr viewport);
	static ViewportSharedPtr getCurrent();

	void setProjectMat(const glm::mat4& value);
	void setViewMat(const glm::mat4& value);

	const glm::mat4& getProjectMat() const;
	const glm::mat4& getViewMat() const;

private:
	glm::mat4 _projectMat = glm::mat4(1.0f);
	glm::mat4 _viewMat = glm::mat4(1.0f);

};