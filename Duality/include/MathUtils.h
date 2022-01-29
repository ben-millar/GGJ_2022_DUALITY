#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <SFML/Graphics.hpp>

class MathUtils
{
public:
	/// <summary>
	/// Converts a heading (in DEGREES) to a unit vector in that direction.
	/// </summary>
	/// <param name="t_heading">Heading in degrees to convert</param>
	/// <returns>Unit vector in the direction of the passed heading</returns>
	static sf::Vector2f heading2vector(float t_heading) { return sf::Vector2f(cosf(t_heading * deg2rad), sinf(t_heading * deg2rad)); }

	/// <summary>
	/// Converts a vector to a heading (in DEGREES).
	/// </summary>
	/// <param name="t_vector">Vector, of any length, to convert to a heading</param>
	/// <returns>Angle of passed vector in degrees</returns>
	static float vector2heading(sf::Vector2f t_vector) { return atan2f(t_vector.y, t_vector.x) * rad2deg; }

	/// <summary>
	/// Returns the squared length/magnitude of a vector (avoids expensive sqrt)
	/// </summary>
	/// <param name="t_vector">Const reference to vector to calculate length of</param>
	/// <returns>Squared length of vector as a float</returns>
	static float squaredLength(sf::Vector2f const& t_vector) { return powf((t_vector.x), 2) + powf((t_vector.y), 2); }

	/// <summary>
	/// Returns the length/magnitude of a vector
	/// </summary>
	/// <param name="t_vector">Const reference to vector to calculate length of</param>
	/// <returns>Length of vector as a float</returns>
	static float length(sf::Vector2f const& t_vector) { return sqrt(squaredLength(t_vector)); }

	/// <summary>
	/// Normalises a vector in place
	/// </summary>
	/// <param name="t_vector">Reference to vector to be normalised</param>
	static void normalise(sf::Vector2f& t_vector) {
		float len = length(t_vector);
		0 != len ?
			t_vector /= length(t_vector) :
			t_vector = sf::Vector2f();
	}

	/// <summary>
	/// Returns a normalised (unit) vector for a given vector
	/// </summary>
	/// <param name="t_vector">Vector to calculate unit vector for</param>
	/// <returns></returns>
	static sf::Vector2f unit(sf::Vector2f const& t_vector) {
		float len = length(t_vector);
		return 0 != len ?
			t_vector / length(t_vector) :
			sf::Vector2f();
	}

	/// <summary>
	/// Returns the center point of a texture.
	/// </summary>
	/// <param name="t_texture">A reference to the texture</param>
	/// <returns>sf::Vector2f representing the center of the passed texture</returns>
	static sf::Vector2f getTextureCenterPoint(sf::Texture& t_texture) { return sf::Vector2f(t_texture.getSize() / 2u); }

	/// <summary>
	/// Given a float rect and a point, determine the point on the surface
	/// of the rect which is nearest to the passed point
	/// </summary>
	/// <param name="t_rect"></param>
	/// <param name="t_point"></param>
	/// <returns></returns>
	static sf::Vector2f nearestPointOnRect(sf::FloatRect t_rect, sf::Vector2f t_point)
	{
		float halfWidth = t_rect.width / 2.f;
		float halfHeight = t_rect.height / 2.f;
		
		sf::Vector2f nearestPoint = {
			std::clamp(t_point.x, t_rect.left, t_rect.left + t_rect.width),
			std::clamp(t_point.y, t_rect.top, t_rect.top + t_rect.height)
		};


		return nearestPoint;
	}

	static const float PI;
	static const float deg2rad;
	static const float rad2deg;
};

#endif