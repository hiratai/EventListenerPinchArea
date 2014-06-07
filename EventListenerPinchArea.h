#ifndef _EVENT_LISTENER_PINCH_AREA_H_
#define _EVENT_LISTENER_PINCH_AREA_H_

#include "cocos2d.h"

class EventListenerPinchArea : public cocos2d::Node
{
public:
	EventListenerPinchArea();
	~EventListenerPinchArea();

	std::function<void()> onPinchBegan;
	std::function<void(const float)> onPinchMoved;
	std::function<void(const float)> onPinchEnded;

	cocos2d::EventListenerTouchAllAtOnce* getEventListenerTouch();

	//Macro : add "create()" and reference counting
	virtual bool init();
	CREATE_FUNC(EventListenerPinchArea);

private:
	cocos2d::EventListenerTouchAllAtOnce* listener;
	cocos2d::Point lastTouchPos;
	int touchNumber;
	float startDistance;
	float result;
	

};

#endif
