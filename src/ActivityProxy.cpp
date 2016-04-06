/*
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

#include "ActivityProxy.h"

#define ACTIVITY_BIT(X) (0x1 << (int)(X))

using namespace motion;

ActivityProxy::ActivityProxy()
	: __activityType(static_cast<activity_type_e>(UNDEFINED))
	, __callback(NULL)
{
}

ActivityProxy::~ActivityProxy()
{
}

bool ActivityProxy::setActivity(activity_type_e type)
{
	__activityType = type;
	setSensor(ACTIVITY_TRACKER_SENSOR);
	return true;
}

void ActivityProxy::setCb(activity_recognition_cb cb)
{
	__callback = cb;
}

bool ActivityProxy::start()
{
	IF_FAIL_RETURN(SensorProxy::start(), false);
	sensord_set_attribute_int(sensorHandle, SENSOR_ATTR_ACTIVITY, ACTIVITY_BIT(__activityType));
	return true;
}

bool ActivityProxy::isSupported(activity_type_e type)
{
	return SensorProxy::isSupported(ACTIVITY_TRACKER_SENSOR);
}

void ActivityProxy::onEvent(sensor_data_t *eventData)
{
	_activity_data_s data;
	data.activity = __activityType;
	data.accuracy = eventData->accuracy;

	__callback(__activityType, &data, getTime(eventData->timestamp),
			static_cast<activity_error_e>(ERR_NONE), userData);
}
