/**
 * @brief some useful utils
 * @file thread_utils.h
 * @author Vladimir Ermakov <vooon341@gmail.com>
 *
 * @addtogroup mavutils
 * @{
 *  @brief Some useful utils
 */
/*
 * libmavconn
 * Copyright 2014,2015 Vladimir Ermakov, All rights reserved.
 *
 * This file is part of the mavros package and subject to the license terms
 * in the top-level LICENSE file of the mavros repository.
 * https://github.com/mavlink/mavros/tree/master/LICENSE.md
 */

#pragma once

#include <thread>
#include <cstdio>
#include <sstream>
#include <cstdarg>
#include <pthread.h>

namespace mavutils {

/**
 * @brief Set std::thread name with printf-like mode
 * @param[in] thd std::thread
 * @param[in] name name for thread
 * @return true if success
 *
 * @note Only for Linux target
 * @todo add for other posix system
 */
inline bool set_thread_name(std::thread &thd, const char *name, ...)
{
   // On OSX a threads name can only be set from within the thread.
   // Disable thread names on osx as they are not essential.
   // See: http://stackoverflow.com/a/7989973
#ifdef __APPLE__
       return true;
#else

	pthread_t pth = thd.native_handle();
	va_list arg_list;
	va_start(arg_list, name);

	char new_name[256];
	vsnprintf(new_name, sizeof(new_name), name, arg_list);
	va_end(arg_list);
	return pthread_setname_np(pth, new_name) == 0;
#endif
}

/**
 * @brief Set thread name (std::string variation)
 */
template <typename Thread>
inline bool set_thread_name(Thread &thd, std::string &name)
{
	return set_thread_name(thd, name.c_str());
};

/**
 * @brief Convert to string objects with operator <<
 */
template <typename T>
inline const std::string to_string_ss(T &obj)
{
	std::ostringstream ss;
	ss << obj;
	return ss.str();
}

}; // namespace mavutils
