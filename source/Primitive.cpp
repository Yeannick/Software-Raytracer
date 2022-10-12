#include "Primitive.h"

Primitive::Primitive(Elite::FPoint3 origin, Elite::RGBColor color, Material* m_pMaterial):
	m_Color{color},
	m_Origin{origin},
	m_pMaterial{ std::move(m_pMaterial) }
{
}
