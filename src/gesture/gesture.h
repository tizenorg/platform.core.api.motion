/*
 * motion
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
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

#ifndef _CONTEXT_GESTURE_H_
#define _CONTEXT_GESTURE_H_

#include <gesture_recognition.h>

#define FEATURE_KEY_GESTURE "tizen.org/feature/sensor.gesture_recognition"
#define FEATURE_KEY_WRISTUP "tizen.org/feature/sensor.wrist_up"

typedef struct _gesture_data_s {
	int gesture;
	int event;
	int tilt_x;
	int tilt_y;
} _cx_gesture_data;

typedef struct _gesture_handle_s {
	int req_id;
	int gesture;
	gesture_recognition_cb callback;
	void *user_data;

	int me_handle;	// Handle for motion-engine in sensor-fw
	int me_event;	// Event enum for motion-engine in sensor-fw

} _cx_gesture_h;

void cx_gesture_deliver_data(int req_id, _cx_gesture_data data, double timestamp, int error);

#endif	/* End of _CONTEXT_GESTURE_PRIVATE_H_ */
