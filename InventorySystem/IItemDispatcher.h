#pragma once

class IItem;
class HealPotion;
class DamagePotion;
class Sword;

template<typename GameObjTy>
class IItemDispatcher
{
public:
	IItemDispatcher(GameObjTy* target);
	~IItemDispatcher();

	virtual void dispatch(IItem& item) = 0;
	virtual void dispatch(HealPotion& item) = 0;
	virtual void dispatch(DamagePotion& item) = 0;
	virtual void dispatch(Sword& item) = 0;

	void setTarget(GameObjTy* target);

protected:
	GameObjTy* target();

private:
	GameObjTy* m_target;
};

template<typename GameObjTy>
IItemDispatcher<GameObjTy>::IItemDispatcher(GameObjTy* target) : m_target { target }
{
}

template<typename GameObjTy>
IItemDispatcher<GameObjTy>::~IItemDispatcher() = default;

template<typename GameObjTy>
GameObjTy* IItemDispatcher<GameObjTy>::target()
{
	return m_target;
}

template<typename GameObjTy>
void IItemDispatcher<GameObjTy>::setTarget(GameObjTy* target)
{
	m_target = target;
}