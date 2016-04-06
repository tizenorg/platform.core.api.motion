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

#ifndef _MOTION_GESTURE_PROXY_H_
#define _MOTION_GESTURE_PROXY_H_

#include <gesture_recognition.h>
#include "SensorProxy.h"

struct _gesture_data_s {
	int gesture;
	int event;
	int tilt_x;
	int tilt_y;
};

namespace motion {

	class GestureProxy : public SensorProxy {
	public:
		GestureProxy();
		~GestureProxy();

		bool setGesture(gesture_type_e type);
		void setCb(gesture_recognition_cb cb);

		static bool isSupported(gesture_type_e type);

	protected:
		void onEvent(sensor_data_t *eventData);

	private:
		gesture_type_e __gestureType;
		gesture_recognition_cb __callback;

		static sensor_type_t __toSensor(gesture_type_e type);
	};

}

#endif /* _MOTION_GESTURE_PROXY_H_ */

