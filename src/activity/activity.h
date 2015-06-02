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

#ifndef _CONTEXT_ACTIVITY_H_
#define _CONTEXT_ACTIVITY_H_

#include <activity_recognition.h>

#define FEATURE_KEY_ACTIVITY "tizen.org/feature/sensor.activity_recognition"

typedef struct _activity_data_s {
	int activity;
	int accuracy;
} _cx_activity_data;

typedef struct _activity_handle_s {
	int req_id;
	activity_recognition_cb callback;
	void *user_data;
} _cx_activity_h;

#endif	/* End of _CONTEXT_ACTIVITY_PRIVATE_H_ */
