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

#ifndef __CONTEXT_TYPES_PRIVATE_H__
#define __CONTEXT_TYPES_PRIVATE_H__

#include <dlog.h>
#include <ctx_error.h>

#define EXTAPI __attribute__ ((visibility("default")))

#define ASSERT_SUPPORTED(feature) \
	do { \
		int __result = ctx::is_supported(feature); \
		if (__result != CERR_NONE) return __result; \
	} while (0)

#define try_return_result_tag(cond, ret, tag, fmt, arg...) \
	do { if (!(cond)) { tag(fmt, ##arg); return ret; } } while (0)

#define try_return_void_tag(cond, tag, fmt, arg...) \
	do { if (!(cond)) { tag(fmt, ##arg); return; } } while (0)

#define try_catch_tag(cond, tag, fmt, arg...) \
	do { if (!(cond)) { tag(fmt, ##arg); goto CATCH; } } while (0)

#define try_return_result(cond, ret) \
	do { if (!(cond)) { return ret; } } while (0)

#define try_return_void(cond) \
	do { if (!(cond)) { return; } } while (0)

#define try_catch(cond) \
	do { if (!(cond)) { goto CATCH; } } while (0)

#define assert_invalid_param(cond) \
	do { if (!(cond)) { return CERR_INVALID_PARAMETER; } } while (0)

#define IS_FAILED(X) ((X) != CERR_NONE)

#define CTX_VALUE_UNDEFINED -1

#define ASSERT_HANDLE		try_return_result_tag(handle, CERR_INVALID_PARAMETER, LOGE, "handle cannot be null")
#define ASSERT_ALLOC(X)		try_return_result_tag(X, CERR_OPERATION_FAILED, LOGE, "Memory allocation failed")
#define ASSERT_NULL(X)		try_return_result_tag(X, CERR_INVALID_PARAMETER, LOGE, "Parameter null")

#define CTX_DBUS_DEST		"org.tizen.context"
#define CTX_DBUS_PATH		"/org/tizen/context"
#define CTX_DBUS_IFACE		"org.tizen.context"
#define CTX_DBUS_SIGNAL_LAUNCHED		"Launched"
#define CTX_DBUS_LIB_PATH	"/org/tizen/context/lib"
#define CTX_DBUS_LIB_IFACE	"org.tizen.context.lib"
#define CTX_DBUS_LIB_METHOD_REQUEST		"Request"
#define CTX_DBUS_LIB_METHOD_RESPONSE	"Response"
#define CTX_DBUS_LIB_METHOD_SUPPORT		"Support"

#define DBUS_NAME_OWNER_IFACE	"org.freedesktop.DBus"
#define DBUS_NAME_OWNER_SIGNAL	"NameOwnerChanged"
#define DBUS_NAME_OWNER_MATCH	"type='signal',sender='org.freedesktop.DBus',path='/org/freedesktop/DBus',interface='"DBUS_NAME_OWNER_IFACE"',member='"DBUS_NAME_OWNER_SIGNAL"',arg0='%s'"
#define MATCH_RULE_LENGTH	256

enum context_method_e {
	CONTEXT_METHOD_REGISTER_SCOPE	= 1,
	CONTEXT_METHOD_UNREGISTER_SCOPE,
	CONTEXT_METHOD_GET_CONTEXT,
	CONTEXT_METHOD_SET_CALLBACK,
	CONTEXT_METHOD_UNSET_CALLBACK,
	CONTEXT_METHOD_SET_OPTION,
	CONTEXT_SYSTEM_METHOD_ENABLE,
	CONTEXT_SYSTEM_METHOD_DISABLE,
};

//TODO: re-define method values as strings
#define CTX_METHOD_GET_CURRENT_INFO	CONTEXT_METHOD_GET_CONTEXT
#define CTX_METHOD_SET_CALLBACK		CONTEXT_METHOD_SET_CALLBACK
#define CTX_METHOD_UNSET_CALLBACK	CONTEXT_METHOD_UNSET_CALLBACK
#define CTX_METHOD_SET_PARAM		CONTEXT_METHOD_SET_OPTION

#endif /* __CONTEXT_TYPES_PRIVATE_H__ */
