#ifndef INPUT_EVENT_H
#define INPUT_EVENT_H

enum class InputID
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	JUMP,
	FALLING,
	HIT_GROUND,
	EXIT
};

enum class InputType
{
	NONE,
	PRESSED,
	RELEASED
};

struct InputEvent
{
	InputID ID;
	InputType type;

	/// <summary>
	/// @brief Overloaded c'tor
	/// </summary>
	/// <param name="t_type">Type of event</param>
	InputEvent(InputID t_ID = InputID::NONE, InputType t_type = InputType::NONE) :
		ID{ t_ID },
		type{ t_type }
	{};

	/// <summary>
	/// Default d'tor
	/// </summary>
	~InputEvent() = default;
};

#endif // !INPUT_EVENT_H