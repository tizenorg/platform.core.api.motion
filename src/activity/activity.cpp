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

#include <ctx_types_private.h>
#include <ctx_error.h>
#include "activity.h"

EXTAPI int activity_is_supported(activity_type_e activity, bool* supported)
{
	if (supported)
		*supported = false;

	return CERR_NOT_SUPPORTED;
}

EXTAPI int activity_create(activity_h *handle)
{
	return CERR_NOT_SUPPORTED;
}

EXTAPI int activity_release(activity_h handle)
{
	return CERR_NOT_SUPPORTED;
}

EXTAPI int activity_start_recognition(activity_h handle, activity_type_e activity, activity_recognition_cb callback, void *user_data)
{
	return CERR_NOT_SUPPORTED;
}

EXTAPI int activity_stop_recognition(activity_h handle)
{
	return CERR_NOT_SUPPORTED;
}

EXTAPI int activity_get_accuracy(const activity_data_h data, activity_accuracy_e *accuracy)
{
	return CERR_NOT_SUPPORTED;
}
