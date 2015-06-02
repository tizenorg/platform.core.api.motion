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

/**
 * @ingroup		CAPI_CONTEXT_FRAMEWORK
 * @defgroup	CAPI_CONTEXT_ACTIVITY_MODULE Activity Recognition
 *
 * @brief		The activity recognition API allows applications to be notified and
 *				react when a user activity is recognized.
 *
 * @section		CAPI_CONTEXT_ACTIVITY_MODULE_HEADER Required Header
 *				\#include <activity_recognition.h>
 *
 * @section		CAPI_CONTEXT_ACTIVITY_MODULE_OVERVIEW Overview
 *
 * The activity recognition API allows to register callback functions to be called
 * when a user activity is recognized, for example, the user starts to run.
 *
 * Available activity types are listed in #activity_type_e.
 * Applications can check whether each activity type is recognizable in the current
 * device using activity_is_supported().

 \code
	bool supported = false;
	activity_is_supported(ACTIVITY_RUN, &supported);

	if (!supported) {
		// Not supported in the current device.
	}
 \endcode

 * Regarding a recognizable activity,
 * an application can set and unset a callback function as follows.
 *
 * First, an activity handle needs to be initialized.
 * With the @c handle, a callback function can be registered by activity_start_recognition().

 \code
	activity_h handle;

	result = activity_create(&handle);

	if (result != ACTIVITY_ERROR_NONE) {
		// An error occurred.
	}

	result = activity_start_recognition(handle, ACTIVITY_RUN, activity_cb, NULL);

	if (result != ACTIVITY_ERROR_NONE) {
		// An error occurred. Do necessary error handling here.
	}
 \endcode

 * Note that, calling activity_start_recognition() twice on the same handle returns #ACTIVITY_ERROR_ALREADY_STARTED.
 * If the application needs to recognize multiple activities,
 * it needs to created multiple handles, one handle for each activity type.
 *
 * Once the activity recognition is started, the callback function is called
 * if the registered activity is detected.
 * Here is an example of the callback function.

 \code
	void activity_cb(activity_type_e type, const activity_data_h data, double timestamp, activity_error_e error, void *user_data)
	{
		int result;
		activity_accuracy_e accuracy;

		if (error != ACTIVITY_ERROR_NONE) {
			// An error occurred. Do necessary error handling here.
			return;
		}

		if (type == ACTIVITY_RUN) {
			// More than one activities can be started using the same callback function.

			result = activity_get_accuracy(data, &accuracy);

			if (result != GESTURE_ERROR_NONE) {
				// An error occurred. Do necessary error handling here.
				return;
			}

			// ...
		}
	}
 \endcode

 * Finally, if the application does not need to be notified the activity event,
 * it can be stopped as follows.

 \code
	activity_stop_recognition(handle);

	// If the handle will not be used anymore, its resources needs be released explicitly.
	activity_release(handle);
 \endcode

 * @section		CAPI_CONTEXT_ACTIVITY_MODULE_FEATURE Related Features
 * This API is related with the following features:\n
 * - http://tizen.org/feature/sensor.activity_recognition
 *
 * It is recommended to design feature related code in your application for reliability.\n
 *
 * You can check if a device supports the related features for this API by using @ref CAPI_SYSTEM_SYSTEM_INFO_MODULE, thereby controlling the procedure of your application.\n
 *
 * To ensure your application is only running on the device with specific features, please define the features in your manifest file using the manifest editor in the SDK.\n
 *
 * More details on featuring your application can be found from <a href="../org.tizen.mobile.native.appprogramming/html/ide_sdk_tools/feature_element.htm"><b>Feature Element</b>.</a>
 *
 */
