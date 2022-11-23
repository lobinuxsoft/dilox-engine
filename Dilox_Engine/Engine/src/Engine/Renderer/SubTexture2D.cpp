#include "dgepch.h"
#include "SubTexture2D.h"

namespace DiloxGE
{
	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
		: m_Texture(texture)
	{
		m_TextCoords[0] = { min.x, min.y }; //Abajo izquierda
		m_TextCoords[1] = { max.x, min.y }; //Abajo derecha
		m_TextCoords[2] = { max.x, max.y }; //Arriba derecha
		m_TextCoords[3] = { min.x, max.y }; //Arriba izquierda
	}

	///<summary>
	/// <para>Texture: es la textura que se usa para dibujar.</para>
	/// <para>Coords: coordenada de la textura (X,Y).</para>
	/// <para>Cell Size: es el tamaño que ocupa un sprite por pixel.</para>
	/// <para>Sprite Size: es el tamaño del sprite en en el engine.</para>
	///</summary>
	Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize)
	{
		glm::vec2 min = { (coords.x * cellSize.x) / texture->GetWidth(), (coords.y * cellSize.y) / texture->GetHeight() };
		glm::vec2 max = { ((coords.x + spriteSize.x) * cellSize.x) / texture->GetWidth(), ((coords.y + spriteSize.y) * cellSize.y) / texture->GetHeight() };

		return CreateRef<SubTexture2D>(texture, min, max);
	};
}
