#include "path.hpp"
#ifndef WIN32
#	include <unistd.h>
#else
#	include <Libloaderapi.h>
#endif
#include <limits.h>

namespace Path {
	static inline std::string get_exec_path(void) {
	#ifdef WIN32
		char buf[PATH_MAX];
		const auto len = GetModuleFileNameA(nullptr, buf, sizeof(buf) - 1);
	#else
		char buf[PATH_MAX];
		ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
	#endif
		if (len != -1) {
			buf[len] = '\0';
			return std::string(buf);
		}
		exit(EXIT_FAILURE);
	}

	std::string get(const char * str) {
		if(str[0] == '/' || str[0] == 'C')
			return str;
		
		std::string rsult = get_exec_path();
		size_t found = rsult.find_last_of("/\\");
		rsult = rsult.substr(0, found);
		found = rsult.find_last_of("/\\");
		rsult = rsult.substr(0, found);
		rsult += "/data/";
		rsult += str;
		return rsult;
	}
};