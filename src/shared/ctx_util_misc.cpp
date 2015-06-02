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

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <glib.h>
#include <system_info.h>
#include <ctx_types_private.h>
#include "ctx_error.h"
#include "ctx_util_misc.h"

int ctx::generate_rid()
{
	static GMutex rid_mutex;
	static int rid = 0;
	int ret = 0;

	g_mutex_lock(&rid_mutex);

	if (++rid < 0)
		rid = 1;

	ret = rid;

	g_mutex_unlock(&rid_mutex);

	return ret;
}

int ctx::is_supported(const char* feature)
{
	bool supported = false;
	int ret = system_info_get_platform_bool(feature, &supported);

	if (ret == CERR_NONE && !supported) {
		SLOGD("Not Supported: %s", feature);
		return CERR_NOT_SUPPORTED;
	} else if (ret != CERR_NONE) {
		SLOGE("Getting system info failed: %#x", ret);
		return CERR_OPERATION_FAILED;
	}

	return CERR_NONE;
}

int64_t ctx::time::get_utc(int64_t* ymd, int64_t* hms)
{
	struct timeval now;
	struct tm tm_now;
	int64_t timestamp;
	int64_t hms_now;

	gettimeofday(&now, NULL);
	timestamp = now.tv_sec * 1000LL + now.tv_usec / 1000;

	if (ymd || hms) {
		time_t now_sec = now.tv_sec;
		gmtime_r(&now_sec, &tm_now);
		hms_now = ((tm_now.tm_hour * 60 + tm_now.tm_min) * 60 + tm_now.tm_sec) * 1000LL + now.tv_usec / 1000;

		if (hms)
			*hms = hms_now;

		if (ymd)
			*ymd = timestamp - hms_now;
	}

	return timestamp;
}
