#include <iostream>

class Subject;
class IObserver;

class Entity {};
enum class Event { pseudoState };
class IObserver
{
	friend class Subject;
public:
	explicit IObserver() : m_next(nullptr) {}
	virtual ~IObserver() = default;
	virtual void onNotify(Entity entity, Event event) = 0;
private:
	IObserver* m_next;
};

class OneObserver : IObserver
{
	virtual void onNotify(Entity entity, Event event) override
	{
		std::cout << "notify()" << std::endl;
	}
};

class Subject
{
public:
	Subject()
		: m_head(nullptr)
	{}

	void addObserver(IObserver* observer)
	{
		observer->m_next = m_head;
		m_head = observer;
	}

	void removeObserver(IObserver* observer)
	{
		if (m_head == observer)
		{
			m_head = observer->m_next;
			observer->m_next = nullptr;
			return;
		}

		IObserver* current = m_head;
		while (current != nullptr)
		{
			if (current->m_next == observer)
			{
				current->m_next = observer->m_next;
				observer->m_next = nullptr;
				return;
			}

			current = current->m_next;
		}
	}

	void notify(const Entity& entity, Event event)
	{
		IObserver* observer = m_head;
		while (observer != nullptr)
		{
			observer->onNotify(entity, event);
			observer = observer->m_next;
		}
	}
private:
	IObserver* m_head;
};

auto main() -> int
{
	OneObserver obs{};
	OneObserver obs2{};
	OneObserver obs3{};

	Entity entity{};

	Subject sub{};
	sub.addObserver(reinterpret_cast<IObserver*>(& obs));
	sub.addObserver(reinterpret_cast<IObserver*>(&obs2));
	sub.addObserver(reinterpret_cast<IObserver*>(&obs3));
	sub.notify(entity, Event::pseudoState);

	std::cout << std::endl;

	sub.removeObserver(reinterpret_cast<IObserver*>(&obs2));
	sub.notify(entity, Event::pseudoState);
}