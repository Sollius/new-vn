#pragma once

#include "MainHeader.h"
#include "BaseAction.h"

////template <typename T>
class Chapter
{
private:
	std::vector<BaseAction> m_actions = std::vector<BaseAction>();
public:
	Chapter();

	Chapter(BaseAction actions[]);
};

