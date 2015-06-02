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

#ifndef __TIZEN_CONTEXT_ERROR_H__
#define __TIZEN_CONTEXT_ERROR_H__

#include <tizen_error.h>

#define CERR_NONE				TIZEN_ERROR_NONE				/* Successful */
#define CERR_INVALID_PARAMETER	TIZEN_ERROR_INVALID_PARAMETER	/* Invalid function parameter */
#define CERR_INVALID_OPERATION	TIZEN_ERROR_INVALID_OPERATION	/* Function not implemented */
#define CERR_OUT_OF_MEMORY		TIZEN_ERROR_OUT_OF_MEMORY		/* Out of memory */
#define CERR_PERMISSION_DENIED	TIZEN_ERROR_PERMISSION_DENIED	/* Permission denied */
#define CERR_NOT_SUPPORTED		TIZEN_ERROR_NOT_SUPPORTED		/* Not supported */
#define CERR_ALREADY_STARTED	(TIZEN_ERROR_CONTEXT | 0x01)	/* Already started */
#define CERR_NOT_STARTED		(TIZEN_ERROR_CONTEXT | 0x02)	/* Not started */
#define CERR_OPERATION_FAILED	(TIZEN_ERROR_CONTEXT | 0x04)	/* Operation failed because of a system error */

#endif // __TIZEN_CONTEXT_ERROR_H__
