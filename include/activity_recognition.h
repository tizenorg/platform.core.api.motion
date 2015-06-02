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

#ifndef __TIZEN_ACTIVITY_H__
#define __TIZEN_ACTIVITY_H__

/**
 * @addtogroup	CAPI_CONTEXT_ACTIVITY_MODULE
 * @{
 */

#include <stdbool.h>
#include <tizen_error.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief	Handle for controlling the activity recognizer
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 */
typedef struct _activity_handle_s* activity_h;

/**
 * @brief	Activity data handle delivered through activity_recognition_cb()
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 */
typedef struct _activity_data_s* activity_data_h;

/**
 * @brief	Error codes
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 */
typedef enum {
	ACTIVITY_ERROR_NONE					= TIZEN_ERROR_NONE,					/**< Successful */
	ACTIVITY_ERROR_INVALID_PARAMETER	= TIZEN_ERROR_INVALID_PARAMETER,	/**< Invalid function parameter */
	ACTIVITY_ERROR_INVALID_OPERATION	= TIZEN_ERROR_INVALID_OPERATION,	/**< Function not implemented */
	ACTIVITY_ERROR_OUT_OF_MEMORY		= TIZEN_ERROR_OUT_OF_MEMORY,		/**< Out of memory */
	ACTIVITY_ERROR_PERMISSION_DENIED	= TIZEN_ERROR_PERMISSION_DENIED,	/**< Permission denied */
	ACTIVITY_ERROR_NOT_SUPPORTED		= TIZEN_ERROR_NOT_SUPPORTED,		/**< Not supported */
	ACTIVITY_ERROR_ALREADY_STARTED		= TIZEN_ERROR_CONTEXT | 0x01,		/**< Recognition is already started */
	ACTIVITY_ERROR_NOT_STARTED			= TIZEN_ERROR_CONTEXT | 0x02,		/**< Recognition is not started */
	ACTIVITY_ERROR_OPERATION_FAILED		= TIZEN_ERROR_CONTEXT | 0x04,		/**< Operation failed because of a system error */
} activity_error_e;

/**
 * @brief	Activity types
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 */
typedef enum {
	ACTIVITY_STATIONARY = 1,	/**< Stationary */
	ACTIVITY_WALK,			/**< Walking */
	ACTIVITY_RUN,			/**< Running */
	ACTIVITY_IN_VEHICLE,	/**< In a moving vehicle */
} activity_type_e;

/**
 * @brief	Recognition accuracy
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 */
typedef enum {
	ACTIVITY_ACCURACY_LOW = 0,	/**< Not accurate */
	ACTIVITY_ACCURACY_MID,		/**< Moderate */
	ACTIVITY_ACCURACY_HIGH,		/**< Highly accurate */
} activity_accuracy_e;

/**
 * @brief	Called when a activity is recognized.
 *
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]	activity	Activity recognized.
 * @param[in]	data		Detailed information of the recognized activity.
 * @param[in]	timestamp	The time when the activity is recognized. Epoch time in seconds.
 * @param[in]	error		An error value. It can be one of the following error values:@n
 *							#ACTIVITY_ERROR_NONE, if the operation succeeded.@n
 *							#ACTIVITY_ERROR_NOT_SUPPORTED, if the activity is not supported in the current profile.@n
 *							#ACTIVITY_ERROR_OPERATION_FAILED, if the operation failed because of a system error.@n
 *							#ACTIVITY_ERROR_PERMISSION_DENIED, if the application has no permission to use this.
 * @param[in]	user_data	The user data had passed to activity_start_recognition().
 *
 * @pre		activity_start_recognition()
 * @see		activity_get_accuracy()
 */
typedef void(* activity_recognition_cb)(activity_type_e activity, const activity_data_h data, double timestamp, activity_error_e error, void *user_data);

/**
 * @brief	Check whether the activity is supported or not.
 * @details	Check if the given activity type is supported in the current device.
 *
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]	activity	Activity type to be checked.
 * @param[out]	supported	@c true, if the activity is recognizable in the current device.@n
 *							@c false, otherwise.
 *
 * @return	0 if the @c activity is supported, otherwise a negative error value.
 * @retval	#ACTIVITY_ERROR_NONE				Supported.
 * @retval	#ACTIVITY_ERROR_INVALID_PARAMETER	Invalid parameter used.
 * @retval	#ACTIVITY_ERROR_NOT_SUPPORTED		The @c activity is not supported.
 * @retval	#ACTIVITY_ERROR_OPERATION_FAILED	Operation failed because of a system error.
 * @retval	#ACTIVITY_ERROR_PERMISSION_DENIED	Does not have permission to use this.
 */
int activity_is_supported(activity_type_e activity, bool* supported);

/**
 * @brief	Initializes an activity handle.
 *
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[out]	handle		Activity handle to be initialized.
 *
 * @return	0 on success, otherwise a negative error value.
 * @retval	#ACTIVITY_ERROR_NONE				Successful.
 * @retval	#ACTIVITY_ERROR_INVALID_PARAMETER	Invalid parameter used.
 * @retval	#ACTIVITY_ERROR_NOT_SUPPORTED		Activity recognition is not supported.
 * @retval	#ACTIVITY_ERROR_OPERATION_FAILED	Operation failed because of a system error, e.g., out of memory.
 *
 * @see		activity_release()
 */
int activity_create(activity_h *handle);

/**
 * @brief	Releases the resources occupied by the activity handle.
 *
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]	handle		Activity handle to be released.
 *
 * @return	0 on success, otherwise a negative error value.
 * @retval	#ACTIVITY_ERROR_NONE				Successful.
 * @retval	#ACTIVITY_ERROR_INVALID_PARAMETER	Invalid parameter used.
 * @retval	#ACTIVITY_ERROR_NOT_SUPPORTED		Activity recognition is not supported.
 * @retval	#ACTIVITY_ERROR_OPERATION_FAILED	Operation failed because of a system error.
 *
 * @pre		activity_create()
 */
int activity_release(activity_h handle);

/**
 * @brief	Starts to recognize an activity.
 * @details	Sets a callback function to be invoked when the activity is detected,
 *			and starts to monitor occurrences of the activity.
 *
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]	handle		Activity handle to be used to control the activity event.
 * @param[in]	activity	Activity type to be monitored.
 * @param[in]	callback	Callback function to receive activity events.
 * @param[in]	user_data	User data to be passed to the callback function.
 *
 * @return	0 on success, otherwise a negative error value.
 * @retval	#ACTIVITY_ERROR_NONE				Successful.
 * @retval	#ACTIVITY_ERROR_INVALID_PARAMETER	Invalid parameter used.
 * @retval	#ACTIVITY_ERROR_NOT_SUPPORTED		Activity recognition is not supported.
 * @retval	#ACTIVITY_ERROR_ALREADY_STARTED		The @c handle is being used already.
 * @retval	#ACTIVITY_ERROR_OPERATION_FAILED	Operation failed because of a system error.
 * @retval	#ACTIVITY_ERROR_PERMISSION_DENIED	Does not have permission to use this.
 *
 * @pre		activity_create()
 * @post	activity_recognition_cb()
 * @see		activity_stop_recognition()
 */
int activity_start_recognition(activity_h handle, activity_type_e activity, activity_recognition_cb callback, void *user_data);

/**
 * @brief	Stops recognizing the activity registered to the activity handle.
 *
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]	handle		Activity handle to release its callback function registered.
 *
 * @return	0 on success, otherwise a negative error value.
 * @retval	#ACTIVITY_ERROR_NONE				Successful.
 * @retval	#ACTIVITY_ERROR_INVALID_PARAMETER	Invalid parameter used.
 * @retval	#ACTIVITY_ERROR_NOT_SUPPORTED		Activity recognition is not supported.
 * @retval	#ACTIVITY_ERROR_NOT_STARTED			Nothing is started using the @c handle.
 * @retval	#ACTIVITY_ERROR_OPERATION_FAILED	Operation failed because of a system error.
 */
int activity_stop_recognition(activity_h handle);

/**
 * @brief	Gets the recognition accuracy.
 *
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]	data		Activity data received through activity_cb().
 * @param[out]	accuracy	Accuracy.
 *
 * @return	0 on success, otherwise a negative error value.
 * @retval	#ACTIVITY_ERROR_NONE				Successful.
 * @retval	#ACTIVITY_ERROR_INVALID_PARAMETER	Invalid parameter used.
 * @retval	#ACTIVITY_ERROR_NOT_SUPPORTED		Activity recognition is not supported.
 * @retval	#ACTIVITY_ERROR_OPERATION_FAILED	Operation failed because of a system error.
 */
int activity_get_accuracy(const activity_data_h data, activity_accuracy_e *accuracy);

#ifdef __cplusplus
}
#endif // __cplusplus

/**
* @}
*/

#endif // __TIZEN_ACTIVITY_H__
