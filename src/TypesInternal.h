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

#ifndef _MOTION_TYPES_INTERNAL_H_
#define _MOTION_TYPES_INTERNAL_H_

#include <tizen_error.h>
#include <dlog.h>

#define EXTAPI __attribute__ ((visibility("default")))

#define UNDEFINED -1

#define ERR_NONE				TIZEN_ERROR_NONE
#define ERR_INVALID_PARAMETER	TIZEN_ERROR_INVALID_PARAMETER
#define ERR_INVALID_OPERATION	TIZEN_ERROR_INVALID_OPERATION
#define ERR_OUT_OF_MEMORY		TIZEN_ERROR_OUT_OF_MEMORY
#define ERR_PERMISSION_DENIED	TIZEN_ERROR_PERMISSION_DENIED
#define ERR_NOT_SUPPORTED		TIZEN_ERROR_NOT_SUPPORTED
#define ERR_NO_DATA				TIZEN_ERROR_NO_DATA
#define ERR_ALREADY_STARTED		(TIZEN_ERROR_CONTEXT | 0x01)
#define ERR_NOT_STARTED			(TIZEN_ERROR_CONTEXT | 0x02)
#define ERR_OUT_OF_RANGE		(TIZEN_ERROR_CONTEXT | 0x03)
#define ERR_OPERATION_FAILED	(TIZEN_ERROR_CONTEXT | 0x04)
#define ERR_RULE_ENABLED		(TIZEN_ERROR_CONTEXT | 0x05)
#define ERR_RULE_NOT_ENABLED	(TIZEN_ERROR_CONTEXT | 0x06)
#define ERR_INVALID_RULE		(TIZEN_ERROR_CONTEXT | 0x07)
#define ERR_RULE_NOT_EXIST		(TIZEN_ERROR_CONTEXT | 0x08)
#define ERR_INVALID_DATA		ERR_INVALID_RULE
#define ERR_DATA_EXIST			(TIZEN_ERROR_CONTEXT | 0X09)

/* Logging and Error Handling */
#define _I SLOGI
#define _D SLOGD
#define _W SLOGW
#define _E SLOGE
#define _SI SECURE_SLOGI
#define _SD SECURE_SLOGD
#define _SW SECURE_LOGW
#define _SE SECURE_SLOGE

#define IF_FAIL_RETURN_TAG(cond, ret, tag, fmt, arg...) \
	do { if (!(cond)) { tag(fmt, ##arg); return ret; } } while (0)

#define IF_FAIL_RETURN(cond, ret) \
	do { if (!(cond)) { return ret; } } while (0)

#define IF_FAIL_VOID_TAG(cond, tag, fmt, arg...) \
	do { if (!(cond)) { tag(fmt, ##arg); return; } } while (0)

#define IF_FAIL_VOID(cond) \
	do { if (!(cond)) { return; } } while (0)

#define IF_FAIL_CATCH_TAG(cond, tag, fmt, arg...) \
	do { if (!(cond)) { tag(fmt, ##arg); goto CATCH; } } while (0)

#define IF_FAIL_CATCH(cond) \
	do { if (!(cond)) { goto CATCH; } } while (0)

#define IS_FAILED(X) ((X) != ERR_NONE)

#define ASSERT_ALLOC(X)		IF_FAIL_RETURN_TAG(X, ERR_OUT_OF_MEMORY, _E, "Memory allocation failed")
#define ASSERT_NOT_NULL(X)	IF_FAIL_RETURN_TAG(X, ERR_INVALID_PARAMETER, _E, "Parameter null")

#define ASSERT_SUPPORTED(feature) \
	do { \
		int __result = motion::isSupported(feature); \
		if (__result != ERR_NONE) return __result; \
	} while (0)

namespace motion {
	int isSupported(const char *feature);
}

#endif /* _MOTION_TYPES_INTERNAL_H_ */
