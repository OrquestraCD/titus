#include "util.hpp"
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/ip.h>

void set_nonblocking (int fd, bool nonblocking)
{
	int		old_flags = fcntl(fd, F_GETFL);
	if (old_flags == -1) {
		throw System_error("fcntl(F_GETFL)", "", errno);
	}
	int		new_flags = old_flags;
	if (nonblocking) {
		new_flags |= O_NONBLOCK;
	} else {
		new_flags &= ~O_NONBLOCK;
	}
	if (new_flags != old_flags && fcntl(fd, F_SETFL, new_flags) == -1) {
		throw System_error("fcntl(F_SETFL)", "", errno);
	}
}

void set_transparent (int sock_fd)
{
	int transparent = 1;
	if (setsockopt(sock_fd, IPPROTO_IP, IP_TRANSPARENT, &transparent, sizeof(transparent)) == -1) {
		throw System_error("setsockopt(IP_TRANSPARENT)", "", errno);
	}
}

void set_not_v6only (int sock_fd)
{
	int v6only = 0;
	if (setsockopt(sock_fd, IPPROTO_IPV6, IPV6_V6ONLY, &v6only, sizeof(v6only)) == -1) {
		throw System_error("setsockopt(IPV6_V6ONLY)", "", errno);
	}
}

