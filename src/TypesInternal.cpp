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

#include <system_info.h>
#include "TypesInternal.h"

int motion::isSupported(const char *feature)
{
	bool supported = false;
	int ret = system_info_get_platform_bool(feature, &supported);

	if (ret == ERR_NONE && !supported) {
		_W("Not Supported: %s", feature);
		return ERR_NOT_SUPPORTED;
	} else if (ret != ERR_NONE) {
		_E("Getting system info failed: %#x", ret);
		return ERR_OPERATION_FAILED;
	}

	return ERR_NONE;
}
