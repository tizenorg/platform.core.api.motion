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

#ifndef _CONTEXT_HANDLE_LIST_H_
#define _CONTEXT_HANDLE_LIST_H_

#include <map>
#include <glib.h>
#include "ctx_types_private.h"

namespace ctx {

template <typename _handle_t>
class handle_map_t
{
private:
	std::map<int, _handle_t*> _map;
	GMutex _mutex;

public:
	handle_map_t() {}
	~handle_map_t() {}

	void insert(int rid, _handle_t *h);
	void remove(int rid);

	_handle_t* find(int rid);
	_handle_t* get_copy(int rid);

};	/* class handle_map_t */

}	/* namesapce ctx */

template <typename _handle_t>
void ctx::handle_map_t<_handle_t>::insert(int rid, _handle_t *h)
{
	g_mutex_lock(&_mutex);

	_map[rid] = h;

	g_mutex_unlock(&_mutex);
}

template <typename _handle_t>
void ctx::handle_map_t<_handle_t>::remove(int rid)
{
	g_mutex_lock(&_mutex);

	_map.erase(rid);

	g_mutex_unlock(&_mutex);
}

template <typename _handle_t>
_handle_t* ctx::handle_map_t<_handle_t>::find(int rid)
{
	_handle_t *h = NULL;

	g_mutex_lock(&_mutex);

	typename std::map<int, _handle_t*>::iterator it = _map.find(rid);
	if (it != _map.end())
		h = it->second;

	g_mutex_unlock(&_mutex);

	return h;
}

template <typename _handle_t>
_handle_t* ctx::handle_map_t<_handle_t>::get_copy(int rid)
{
	_handle_t *copy = static_cast<_handle_t*>(malloc(sizeof(_handle_t)));
	try_return_result_tag(copy, NULL, LOGE, "Memory allocation failed");

	g_mutex_lock(&_mutex);

	typename std::map<int, _handle_t*>::iterator it = _map.find(rid);
	if (it != _map.end()) {
		*copy = *(it->second);
	} else {
		free(copy);
		copy = NULL;
	}

	g_mutex_unlock(&_mutex);

	return copy;
}

#endif	/* _CONTEXT_HANDLE_LIST_H_ */
