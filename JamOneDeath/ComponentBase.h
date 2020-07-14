#pragma once

class Entity;

class ComponentBase
{
public:
	virtual ~ComponentBase()
	{
	}
	Entity* parent();
	bool active() const
	{
		return m_active;
	}
	void setActive(bool value)
	{
		m_active = value;
	}
protected:
	ComponentBase(Entity* parent);
private:
	bool m_active;
	Entity* m_parent;
};