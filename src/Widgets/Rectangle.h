#pragma once
#include "Widget.h"

class Rectangle : public Widget
{
public:
	Rectangle();
	~Rectangle();

	void draw() const override;

private:
	rendell::VertexArraySharedPtr _vertexArray;

};
