#include <iostream>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
// forward declarations 
class InputHandler;
class ICommand;
class JumpCommand;
class FireCommand;

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
class ICommand
{
public:
	virtual ~ICommand() {}
	virtual void execute() = 0;
};

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
class JumpCommand : ICommand
{
public:
	virtual void execute() override { jump(); }
private:
	void jump() { std::cout << "jump()" << std::endl; }
};

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
class FireCommand : ICommand
{
public:
	virtual void execute() override { fireGun(); }
private:
	void fireGun() { std::cout << "fireGun()" << std::endl; }
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

	void handleInput(uint8_t input) 
	{
		switch(input)
		{
			case button_cross: tryExecute(m_PSbuttonCross); break;
			case button_rect: tryExecute(m_PSbuttonRect); break;
			case button_circle: tryExecute(m_PSbuttonCircle); break;
			case button_triangle: tryExecute(m_PSbuttonTriangle); break;
		}
	}
private:
	void tryExecute(ICommand* command)
	{
		if(command != nullptr) command->execute();
	}

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

	InputHandler handler{
		reinterpret_cast<ICommand*>(&fireCommand), 
		reinterpret_cast<ICommand*>(&jumpCommand), 
		nullptr, 
		nullptr};

	handler.handleInput(InputHandler::button_cross);
	handler.handleInput(InputHandler::button_rect);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//