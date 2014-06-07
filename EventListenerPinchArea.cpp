#include "EventListenerPinchArea.h"

#include <vector>

USING_NS_CC;

EventListenerPinchArea::EventListenerPinchArea()
{
}

EventListenerPinchArea::~EventListenerPinchArea()
{
}

bool EventListenerPinchArea::init()
{
	touchNumber = 0;
	startDistance = 0.0f;
	onPinchBegan = nullptr;
	onPinchMoved = nullptr;
	onPinchEnded = nullptr;

	listener = EventListenerTouchAllAtOnce::create();

	listener->onTouchesBegan = [&](const std::vector<Touch*>& touches, Event* event)
	{
		for(auto it = touches.begin();it != touches.end();it++)
		{
			touchNumber += 1;
			if(touchNumber == 1)
			{
				lastTouchPos = (*it)->getLocation();
			}
			else if(touchNumber == 2)
			{
				startDistance = (*it)->getLocation().distance(lastTouchPos);

				if (onPinchBegan != nullptr)
				{
					onPinchBegan();
				}
			}
		}
		
	};

	listener->onTouchesMoved = [&](const std::vector<Touch*>& touches, Event* event)
	{
		if(touches.size() < 2)
			return;

		Point pos1 = touches.at(0)->getLocation();		//touches[0]->getLocation()
		Point pos2 = touches.at(1)->getLocation();		//touches[1]->getLocation()

		float movedDistance = pos1.distance(pos2);
		result = movedDistance / startDistance;

		if (onPinchMoved != nullptr)
		{
			onPinchMoved(result);
		}
		
	};

	listener->onTouchesEnded = [&](const std::vector<Touch*>& touches, Event* event)
	{
		if (touchNumber == 2)
		{
			if (onPinchEnded != nullptr)
			{
				onPinchEnded(result);
			}
		}

		touchNumber -= touches.size();
	};
}

EventListenerTouchAllAtOnce* EventListenerPinchArea::getEventListenerTouch()
{
	return listener;
}
