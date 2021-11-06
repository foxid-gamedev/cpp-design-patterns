#include <iostream>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
// forward declarations 
class InputHandler;
class ICommand;
class JumpCommand;
class FireCommand;

class GameActor; // new class 

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
class GameActor
{
public:
	explicit GameActor(std::string name) : m_name(std::move(name)) {}
	void jump() { std::cout << "actor: " << m_name << " jump()" << std::endl; }
	void fireGun() { std::cout << "actor: " << m_name << " fireGun()" << std::endl; }
private:
	std::string m_name;
};

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
class ICommand
{
public:
	virtual ~ICommand() {}
	virtual void execute(GameActor& actor) = 0;
};

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
class JumpCommand : ICommand
{
public:
	virtual void execute(GameActor& actor) override { actor.jump(); }
};

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
class FireCommand : ICommand
{
public:
	virtual void execute(GameActor& actor) override { actor.fireGun(); }
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

		:	m_PSbuttonCross(buttonCross), 
			m_PSbuttonRect(buttonRect), 
			m_PSbuttonCircle(buttonCircle), 
			m_PSbuttonTriangle(buttonTriangle)
	{}

	static constexpr uint8_t button_cross	 = 0b0000001;
	static constexpr uint8_t button_rect	 = 0b0000010;
	static constexpr uint8_t button_circle	 = 0b0000100;
	static constexpr uint8_t button_triangle = 0b0001000;

	ICommand* handleInput(uint8_t input) // changed return value from void to ICommand*
	{
		switch(input)
		{
			case button_cross: return m_PSbuttonCross; break;
			case button_rect: return m_PSbuttonRect; break;
			case button_circle: return m_PSbuttonCircle; break;
			case button_triangle: return m_PSbuttonTriangle; break;
		}
		return nullptr;
	}
private:
	ICommand* m_PSbuttonCross{nullptr};
	ICommand* m_PSbuttonRect{nullptr};
	ICommand* m_PSbuttonCircle{nullptr};
	ICommand* m_PSbuttonTriangle{nullptr};
};


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
auto main() -> int
{
	FireCommand fireCommand{};
	JumpCommand jumpCommand{};

	GameActor actor{"Player"};

	InputHandler handler{
		reinterpret_cast<ICommand*>(&fireCommand), 
		reinterpret_cast<ICommand*>(&jumpCommand), 
		nullptr, 
		nullptr};

	if(auto command = handler.handleInput(InputHandler::button_cross); command != nullptr)
	{
		command->execute(actor);
	}

	if(auto command = handler.handleInput(InputHandler::button_rect); command != nullptr)
	{
		command->execute(actor);
	}

}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//