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

#ifndef _MOTION_ACTIVITY_PROXY_H_
#define _MOTION_ACTIVITY_PROXY_H_

#include <activity_recognition.h>
#include "SensorProxy.h"

struct _activity_data_s {
	int activity;
	int accuracy;
};

namespace motion {

	class ActivityProxy : public SensorProxy {
	public:
		ActivityProxy();
		~ActivityProxy();

		bool setActivity(activity_type_e type);
		void setCb(activity_recognition_cb cb);

		bool start();

		static bool isSupported(activity_type_e type);

	protected:
		void onEvent(sensor_data_t *eventData);

	private:
		activity_type_e __activityType;
		activity_recognition_cb __callback;
	};

}

#endif	/* _MOTION_ACTIVITY_PROXY_PRIVATE_H_ */
