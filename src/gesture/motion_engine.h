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

#ifndef _CX_GESTURE_MOTION_ENGINE_H_
#define _CX_GESTURE_MOTION_ENGINE_H_

#include <stdbool.h>
#include "gesture.h"

namespace ctx { namespace gesture{

	bool me_check_coverage(int gesture);
	int me_is_supported(int gesture);
	int me_start(_cx_gesture_h *handle, int gesture, int mode);
	int me_stop(_cx_gesture_h *handle);

} }	/* namespace ctx::gesture */

#endif	/* End of _CX_GESTURE_MOTION_ENGINE_H_ */
