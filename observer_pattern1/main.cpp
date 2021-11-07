#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <cassert>

enum class Event
{
	entityFall
};

struct Entity
{
	std::string name;
};

class IObserver
{
public:
	virtual ~IObserver() {}
	virtual void onNotify(const Entity& entity, Event event) = 0;
};

class Achievement : public IObserver
{
public:
	virtual void onNotify(const Entity& entity, Event event) override
	{
		switch (event)
		{
		case Event::entityFall:
			// if(entity.isHero() && heroIsOnBridge)
			// {
			//		unlock(ACHIEEVEMENT_FELL_OFF_BRIDGE);
			// }
			break;

			// ... handle other events ...


		}

		std::cout << "onNotify(): " << entity.name << std::endl;
	}
private:
	void unlock(Achievement achievment)
	{
		// unlock if not already happpened before
	}
};

class Subject
{
public:
	void addObserver(IObserver* observer)
	{ 
		assert(observer && "Observer does not exis, parameter points to null!");
		m_observers.emplace(observer);
	}

	void removeObserver(IObserver* observer)
	{
		assert(m_observers.contains(observer) && "observer does not listen to subject! Nothing to remove here..");
		m_observers.extract(observer);
	}

	void notify(const Entity& entity, Event event)
	{
		std::for_each(m_observers.begin(), m_observers.end(), [&](auto& observer) {
			observer->onNotify(entity, event);
		});
	}

	void print()
	{
		std::for_each(m_observers.begin(), m_observers.end(), [&](auto observer) {
			std::cout << "adr: " << observer << std::endl;
		});
	}
private:
	std::unordered_set<IObserver*> m_observers;
};

auto main() -> int
{
	Achievement a{};
	Achievement b{};

	Subject sub{};

	sub.print();

	sub.addObserver(&a);
	sub.addObserver(&b);

	sub.notify({ "William" }, Event::entityFall);
}