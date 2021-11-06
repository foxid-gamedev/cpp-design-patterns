#include <iostream>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
// forward declarations 
class InputHandler;
class ICommand;
class MoveCommand;
class GameActor; // new class 

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
class GameActor
{
public:
	explicit GameActor(std::string name) : m_name(std::move(name)) {}
	
	void jump() { }
	void fireGun() { }

	void move(int32_t x, int32_t y) 
	{ 
		m_x += x;
		m_y += y;

		std::cout	<< "actor: "	<< m_name 
					<< " move("		<< x << ", " << y 
					<< ") -> pos: " << m_x << ", " << m_y  << std::endl;
	}
private:
	std::string m_name;
	int32_t m_x{0}, m_y{0};
};

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
class ICommand
{
public:
	virtual ~ICommand() {}
	virtual void execute() = 0;
	virtual void undo() = 0;
};

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//

class MoveCommand : ICommand
{
public:
	explicit MoveCommand(GameActor* actor, int32_t x, int32_t y) : m_actor(actor), m_x(x), m_y(y) {}

	virtual void execute() override
	{
		std::cout << "execute(): " << std::endl;
		m_xBefore = m_x;
		m_yBefore = m_y;
		m_actor->move(m_x, m_y);
	}

	virtual void undo() override
	{
		std::cout << "undo(): " << std::endl;
		m_actor->move(-m_xBefore, -m_yBefore);
	}
private:
	GameActor* m_actor;
	int32_t m_x;
	int32_t m_y;
	int32_t m_xBefore{ 0 };
	int32_t m_yBefore{ 0 };
};

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//

class InputHandler
{
public:
	explicit InputHandler(
		ICommand* buttonCross,
		ICommand* buttonRect,
		ICommand* buttonCircle,
		ICommand* buttonTriangle)

		: m_PSbuttonCross(buttonCross),
		m_PSbuttonRect(buttonRect),
		m_PSbuttonCircle(buttonCircle),
		m_PSbuttonTriangle(buttonTriangle)
	{}

	static constexpr uint8_t button_cross = 0b0000001;
	static constexpr uint8_t button_rect = 0b0000010;
	static constexpr uint8_t button_circle = 0b0000100;
	static constexpr uint8_t button_triangle = 0b0001000;

	ICommand* handleInput(uint8_t input) // changed return value from void to ICommand*
	{
		switch (input)
		{
		case button_cross: return m_PSbuttonCross; break;
		case button_rect: return m_PSbuttonRect; break;
		case button_circle: return m_PSbuttonCircle; break;
		case button_triangle: return m_PSbuttonTriangle; break;
		}
		return nullptr;
	}
private:
	ICommand* m_PSbuttonCross{ nullptr };
	ICommand* m_PSbuttonRect{ nullptr };
	ICommand* m_PSbuttonCircle{ nullptr };
	ICommand* m_PSbuttonTriangle{ nullptr };
};


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
auto main() -> int32_t
{


	GameActor actor{ "Player" };
	MoveCommand moveCommand{&actor, 2, 1 };

	InputHandler handler
	{
		reinterpret_cast<ICommand*>(&moveCommand),
		nullptr, 
		nullptr, 
		nullptr 
	};

	if (auto command = handler.handleInput(InputHandler::button_cross); command != nullptr)
	{
		command->execute();
		command->execute();
		command->undo();
	}
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//