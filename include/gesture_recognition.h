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

#ifndef __TIZEN_GESTURE_H__
#define __TIZEN_GESTURE_H__

/**
 * @addtogroup	CAPI_CONTEXT_GESTURE_MODULE
 * @{
 */

#include <stdbool.h>
#include <tizen_error.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief	Handle for controlling the gesture recognizer
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 */
typedef struct _gesture_handle_s* gesture_h;

/**
 * @brief	Gesture data handle delivered through gesture_recognition_cb()
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 */
typedef struct _gesture_data_s* gesture_data_h;

/**
 * @brief	Error codes
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 */
typedef enum {
	GESTURE_ERROR_NONE				= TIZEN_ERROR_NONE,					/**< Successful */
	GESTURE_ERROR_INVALID_PARAMETER	= TIZEN_ERROR_INVALID_PARAMETER,	/**< Invalid function parameter */
	GESTURE_ERROR_INVALID_OPERATION	= TIZEN_ERROR_INVALID_OPERATION,	/**< Function not implemented */
	GESTURE_ERROR_OUT_OF_MEMORY		= TIZEN_ERROR_OUT_OF_MEMORY,		/**< Out of memory */
	GESTURE_ERROR_PERMISSION_DENIED	= TIZEN_ERROR_PERMISSION_DENIED,	/**< Permission denied */
	GESTURE_ERROR_NOT_SUPPORTED		= TIZEN_ERROR_NOT_SUPPORTED,		/**< Not supported */
	GESTURE_ERROR_ALREADY_STARTED	= TIZEN_ERROR_CONTEXT | 0x01,		/**< Recognition is already started */
	GESTURE_ERROR_NOT_STARTED		= TIZEN_ERROR_CONTEXT | 0x02,		/**< Recognition is not started */
	GESTURE_ERROR_OPERATION_FAILED	= TIZEN_ERROR_CONTEXT | 0x04,		/**< Operation failed because of a system error */
} gesture_error_e;

/**
 * @brief	Gesture types
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 */
typedef enum {
	GESTURE_DOUBLE_TAP = 1,	/**< The mobile device is tapped twice */
	GESTURE_MOVE_TO_EAR,	/**< The mobile device is moved near to an ear */
	GESTURE_NO_MOVE,		/**< The mobile device is being stopped for a while */
	GESTURE_PICK_UP,		/**< The mobile device is picked up */
	GESTURE_SHAKE,			/**< The mobile device is quickly moved back and forth */
	GESTURE_SNAP,			/**< The mobile device is moved along an axis and back */
	GESTURE_TILT,			/**< The mobile device is tilted */
	GESTURE_TURN_FACE_DOWN,	/**< The mobile device is flipped from face to back */
	GESTURE_WRIST_UP,		/**< The wearable device is moved and faced up */
} gesture_type_e;

/**
 * @brief	Gesture recognition option
 * @details	If the default option is used, the system tries to reduce power consumption.
 *			For example, the recognition engine may stop detecting gestures if the display is turned off.
 *			Using #GESTURE_OPTION_ALWAYS_ON disables such power-saving functionalities.
 *
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 */
typedef enum {
	GESTURE_OPTION_DEFAULT		= 0,	/**< Running in the default setting */
	GESTURE_OPTION_ALWAYS_ON	= 1,	/**< Trying to detect gestures always */
} gesture_option_e;

/**
 * @brief	Regarding the type of the gesture, gesture_get_event() returns one of the followings.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 */
typedef enum {
	GESTURE_EVENT_NONE		= 0,	/**< The gesture is not detected */
	GESTURE_EVENT_DETECTED	= 1,	/**< The gesture is detected */

	GESTURE_SHAKE_DETECTED	= 1,	/**< Shake gesture is detected */
	GESTURE_SHAKE_FINISHED	= 2,	/**< Shake gesture finished */

	GESTURE_SNAP_X_NEGATIVE = 1,	/**< -X snap is detected */
	GESTURE_SNAP_X_POSITIVE = 2,	/**< +X snap is detected */
	GESTURE_SNAP_Y_NEGATIVE = 3,	/**< -Y snap is detected */
	GESTURE_SNAP_Y_POSITIVE = 4,	/**< +Y snap is detected */
	GESTURE_SNAP_Z_NEGATIVE = 5,	/**< -Z snap is detected */
	GESTURE_SNAP_Z_POSITIVE = 6,	/**< +Z snap is detected */
} gesture_event_e;

/**
 * @brief	Called when a gesture is detected.
 *
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]	gesture		Gesture type detected.
 * @param[in]	data		Detailed information of the detected gesture.@n
 *							gesture_get_event() or gesture_get_tilt()
 *							can be used to extract the information from @c data.
 * @param[in]	timestamp	The time when the gesture is detected. Epoch time in seconds.
 * @param[in]	error		An error value. It can be one of the following error values:@n
 *							#GESTURE_ERROR_NONE, if the operation succeeded.@n
 *							#GESTURE_ERROR_NOT_SUPPORTED, if the gesture is not supported in the current profile.@n
 *							#GESTURE_ERROR_OPERATION_FAILED, if the operation failed because of a system error.@n
 *							#GESTURE_ERROR_PERMISSION_DENIED, if the application has no permission to use this.
 * @param[in]	user_data	The user data had passed to gesture_start_recognition().
 *
 * @pre		gesture_start_recognition()
 */
typedef void(* gesture_recognition_cb)(gesture_type_e gesture, const gesture_data_h data, double timestamp, gesture_error_e error, void *user_data);

/**
 * @brief	Check whether the gesture is supported or not.
 * @details	Check if the given gesture type is supported in the current device.
 *
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]	gesture		Gesture type to be checked.
 * @param[out]	supported	@c true, if the gesture is recognizable in the current device.@n
 *							@c false, otherwise.
 *
 * @return	0 if the @c gesture is supported, otherwise a negative error value.
 * @retval	#GESTURE_ERROR_NONE					Supported.
 * @retval	#GESTURE_ERROR_INVALID_PARAMETER	Invalid parameter used.
 * @retval	#GESTURE_ERROR_NOT_SUPPORTED		The @c gesture is not supported.
 * @retval	#GESTURE_ERROR_OPERATION_FAILED		Operation failed because of a system error.
 * @retval	#GESTURE_ERROR_PERMISSION_DENIED	Does not have permission to use this.
 */
int gesture_is_supported(gesture_type_e gesture, bool* supported);

/**
 * @brief	Initializes a gesture handle.
 *
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[out]	handle		Gesture handle to be initialized.
 *
 * @return	0 on success, otherwise a negative error value.
 * @retval	#GESTURE_ERROR_NONE					Successful.
 * @retval	#GESTURE_ERROR_INVALID_PARAMETER	Invalid parameter used.
 * @retval	#GESTURE_ERROR_NOT_SUPPORTED		Gesture recognition is not supported.
 * @retval	#GESTURE_ERROR_OPERATION_FAILED		Operation failed because of a system error, e.g., out of memory.
 *
 * @see		gesture_release()
 */
int gesture_create(gesture_h *handle);

/**
 * @brief	Releases the resources occupied by the gesture handle.
 *
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]	handle		Gesture handle to be released.
 *
 * @return	0 on success, otherwise a negative error value.
 * @retval	#GESTURE_ERROR_NONE					Successful.
 * @retval	#GESTURE_ERROR_INVALID_PARAMETER	Invalid parameter used.
 * @retval	#GESTURE_ERROR_NOT_SUPPORTED		Gesture recognition is not supported.
 * @retval	#GESTURE_ERROR_OPERATION_FAILED		Operation failed because of a system error.
 *
 * @pre		gesture_create()
 */
int gesture_release(gesture_h handle);

/**
 * @brief	Starts to recognize a gesture.
 * @details	Sets a callback function to be invoked when the gesture is detected,
 *			and starts to monitor occurrences of the gesture.
 *
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]	handle		Gesture handle to be used to control the gesture event.
 * @param[in]	gesture		Gesture type to be monitored. It should be one of #gesture_type_e.
 * @param[in]	option		Detection option. It should be one of #gesture_option_e.
 * @param[in]	callback	Callback function to receive gesture events.
 * @param[in]	user_data	User data to be passed to the callback function.
 *
 * @return	0 on success, otherwise a negative error value.
 * @retval	#GESTURE_ERROR_NONE					Successful.
 * @retval	#GESTURE_ERROR_INVALID_PARAMETER	Invalid parameter used.
 * @retval	#GESTURE_ERROR_NOT_SUPPORTED		Gesture recognition is not supported.
 * @retval	#GESTURE_ERROR_ALREADY_STARTED		The @c handle is being used already.
 * @retval	#GESTURE_ERROR_OPERATION_FAILED		Operation failed because of a system error.
 * @retval	#GESTURE_ERROR_PERMISSION_DENIED	Does not have permission to use this.
 *
 * @pre		gesture_create()
 * @post	gesture_recognition_cb()
 * @see		gesture_stop_recognition()
 */
int gesture_start_recognition(gesture_h handle, gesture_type_e gesture, gesture_option_e option, gesture_recognition_cb callback, void *user_data);

/**
 * @brief	Stops recognizing the gesture registered to the gesture handle.
 *
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]	handle		Gesture handle to release its callback function registered.
 *
 * @return	0 on success, otherwise a negative error value.
 * @retval	#GESTURE_ERROR_NONE					Successful.
 * @retval	#GESTURE_ERROR_INVALID_PARAMETER	Invalid parameter used.
 * @retval	#GESTURE_ERROR_NOT_SUPPORTED		Gesture recognition is not supported.
 * @retval	#GESTURE_ERROR_NOT_STARTED			Nothing is started using the @c handle.
 * @retval	#GESTURE_ERROR_OPERATION_FAILED		Operation failed because of a system error.
 */
int gesture_stop_recognition(gesture_h handle);

/**
 * @brief	Gets the gesture event from the gesture data received.
 *
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]	data		Gesture data received through a callback function.
 * @param[out]	event		Gesture event data.
 *
 * @return	0 on success, otherwise a negative error value.
 * @retval	#GESTURE_ERROR_NONE					Successful.
 * @retval	#GESTURE_ERROR_INVALID_PARAMETER	Invalid parameter used.
 * @retval	#GESTURE_ERROR_NOT_SUPPORTED		Gesture recognition is not supported.
 * @retval	#GESTURE_ERROR_OPERATION_FAILED		Operation failed because of a system error.
 */
int gesture_get_event(const gesture_data_h data, gesture_event_e *event);

/**
 * @brief	Gets the tilting degrees from #GESTURE_TILT data received.
 *
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in]	data		Tilt gesture data received through a callback function.
 * @param[out]	x			Tilting degree on X-axis.
 * @param[out]	y			Tilting degree on Y-axis.
 *
 * @return	0 on success, otherwise a negative error value.
 * @retval	#GESTURE_ERROR_NONE					Successful.
 * @retval	#GESTURE_ERROR_INVALID_PARAMETER	Invalid parameter used.
 * @retval	#GESTURE_ERROR_NOT_SUPPORTED		Gesture recognition is not supported.
 * @retval	#GESTURE_ERROR_OPERATION_FAILED		Operation failed because of a system error.
 */
int gesture_get_tilt(const gesture_data_h data, int *x, int *y);

#ifdef __cplusplus
}
#endif // __cplusplus

/**
* @}
*/

#endif // __TIZEN_GESTURE_H__
