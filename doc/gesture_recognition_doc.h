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
 * @defgroup	CAPI_CONTEXT_GESTURE_MODULE Gesture Recognition
 *
 * @brief		The gesture recognition API allows applications to be notified and
 *				react when the user performs a gesture.
 *
 * @section		CAPI_CONTEXT_GESTURE_MODULE_HEADER Required Header
 *				\#include <gesture_recognition.h>
 *
 * @section		CAPI_CONTEXT_GESTURE_MODULE_OVERVIEW Overview
 *
 *
 * The gesture recognition API allows to register callback functions to be called
 * when the user performs meaningful gestures listed in #gesture_type_e, for example,
 * shaking the device.
 *
 * Regardless of the gesture types,
 * the overall process of using the gesture recognition API is as follows.
 *
 * If necessary, applications can check whether a gesture type is supported in the current device in advance.
 * Note that, some gestures may not be supported in some devices, if the devices do not have necessary sensors.

 \code
	bool supported = false;
	gesture_is_supported(GESTURE_SHAKE, &supported);

	if (!supported) {
		// Not supported in the current device.
	}
 \endcode

 * If the gesture type is supported, to use the recognition engine,
 * an @c handle for the gesture recognition needs to be initialized first.

 \code
	gesture_h handle;

	result = gesture_create(&handle);

	if (result != GESTURE_ERROR_NONE) {
		// An error occurred.
	}
 \endcode

 * With the @c handle initialized, a callback function,
 * which will be called when a specified gesture is detected,
 * is registered by using gesture_start_recognition().

 \code
	result = gesture_start_recognition(handle, GESTURE_SHAKE, GESTURE_OPTION_DEFAULT, gesture_cb, NULL);

	if (result != GESTURE_ERROR_NONE) {
		// An error occurred. Do necessary error handling here.
	}
 \endcode

 * Then the callback function @c gesture_cb will be called whenever the shake gesture is detected.
 *
 * Note that, calling gesture_start_recognition() twice on the same handle returns #GESTURE_ERROR_ALREADY_STARTED.
 * If it needs to recognize another gesture using the same handle,
 * the started recognition session should be stopped and restarted with the new gesture type.
 * Otherwise, the application needs to created multiple handles, one handle for each gesture needed.
 *
 * An example callback function is as follows.

 \code
	void gesture_cb(gesture_type_e type, const gesture_data_h data, double timestamp, gesture_error_e error, void *user_data)
	{
		int result;
		gesture_event_e event;

		if (error != GESTURE_ERROR_NONE) {
			// An error occurred. Do necessary error handling here.
			return;
		}

		if (type == GESTURE_SHAKE) {
			// More than one gestures can be started using the same callback function.

			result = gesture_get_event(data, &event);

			if (result != GESTURE_ERROR_NONE) {
				// An error occurred. Do necessary error handling here.
				return;
			}

			if (event == GESTURE_SHAKE_DETECTED) {
				// Shake gesture is started

			} else if (event == GESTURE_SHAKE_FINISHED) {
				// Shake gesture is stopped
			}
		}
	}
 \endcode

 * As we started gesture recognition with #GESTURE_SHAKE,
 * gesture_get_event() returns either #GESTURE_SHAKE_DETECTED or #GESTURE_SHAKE_FINISHED
 * as it has two different states, the gesture is started, or finished.
 * Most of the gesture types, however, simply provide #GESTURE_EVENT_DETECTED.
 * In such cases, #GESTURE_EVENT_NONE may not be delivered at all.
 *
 * If #GESTURE_TILT is started, within the callback function,
 * gesture_get_tilt() can be used to extract the tilting degrees.
 *
 * Finally, if the application does not need to be notified the gesture event,
 * it can be stopped as follows.

 \code
	gesture_stop_recognition(handle);

	// If the handle will not be used anymore, its resources needs be released explicitly.
	gesture_release(handle);
 \endcode

 * @section		CAPI_CONTEXT_GESTURE_MODULE_FEATURE Related Features
 * This API is related with the following features:\n
 * - http://tizen.org/feature/sensor.gesture_recognition\n
 * - http://tizen.org/feature/sensor.wrist_up
 *
 * It is recommended to design feature related code in your application for reliability.\n
 *
 * You can check if a device supports the related features for this API by using @ref CAPI_SYSTEM_SYSTEM_INFO_MODULE, thereby controlling the procedure of your application.\n
 *
 * To ensure your application is only running on the device with specific features, please define the features in your manifest file using the manifest editor in the SDK.\n
 *
 * More details on featuring your application can be found from <a href="https://developer.tizen.org/development/tools/native-tools/manifest-text-editor#feature"><b>Feature Element</b>.</a>
 *
 */
