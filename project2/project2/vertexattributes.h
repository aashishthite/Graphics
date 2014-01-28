#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/*	Perry Kivolowitz - UW - Madison - CS 559 Demo
	A  person more  expert in templates whould be able
	to collect these classes into a single templatized
	system. The goal  would be to allow a more generic
	"object" class.

	P = position
	C = color
	N = normal
	T = texture coordinates
*/

class VertexAttributesP
{
public:
	VertexAttributesP();
	VertexAttributesP(const glm::vec3 & p);
	VertexAttributesP(const VertexAttributesP & other);
	glm::vec3 position;
};


class VertexAttributesPC : public VertexAttributesP
{
public:
	VertexAttributesPC();
	VertexAttributesPC(const glm::vec3 & p, const glm::vec3 & c);
	VertexAttributesPC(const VertexAttributesPC & other);
	glm::vec3 color;
};

class VertexAttributesPN : public VertexAttributesP
{
public:
	VertexAttributesPN();
	VertexAttributesPN(const glm::vec3 & p, const glm::vec3 & n);
	VertexAttributesPN(const VertexAttributesPN & other);
	glm::vec3 normal;
};

class VertexAttributesPCN : public VertexAttributesPC
{
public:
	VertexAttributesPCN();
	VertexAttributesPCN(const glm::vec3 & p, const glm::vec3 & c, const glm::vec3 & n);
	VertexAttributesPCN(const VertexAttributesPCN & other);
	glm::vec3 normal;
};

class VertexAttributesPCNT : public VertexAttributesPCN
{
public:
	VertexAttributesPCNT();
	VertexAttributesPCNT(const glm::vec3 & p, const glm::vec3 & c, const glm::vec3 & n, const glm::vec2 & t);
	VertexAttributesPCNT(const VertexAttributesPCNT & other);
	glm::vec2 texture_coordinate;
};