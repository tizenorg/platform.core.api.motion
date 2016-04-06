/*
 * motion
 *
 * Copyright (c) 2016 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "GestureProxy.h"

using namespace motion;

GestureProxy::GestureProxy()
	: __gestureType(static_cast<gesture_type_e>(UNDEFINED))
	, __callback(NULL)
{
}

GestureProxy::~GestureProxy()
{
}

bool GestureProxy::setGesture(gesture_type_e type)
{
	sensor_type_t sensor;

	switch (type) {
	case GESTURE_PICK_UP:
		sensor = GESTURE_MOVEMENT_SENSOR;
		break;
	case GESTURE_WRIST_UP:
		sensor = GESTURE_WRIST_UP_SENSOR;
		break;
	default:
		return false;
	}

	__gestureType = type;
	setSensor(sensor);
	return true;
}

void GestureProxy::setCb(gesture_recognition_cb cb)
{
	__callback = cb;
}

void GestureProxy::onEvent(sensor_data_t *eventData)
{
	_gesture_data_s data;
	data.gesture = __gestureType;

	/* TODO: This is the default form.
	   For each sensor, this part needs to be accordingly */
	data.event = static_cast<int>(eventData->values[0]);

	__callback(__gestureType, &data, getTime(eventData->timestamp),
			static_cast<gesture_error_e>(ERR_NONE), userData);
}
