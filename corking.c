/*
 * netsniff-ng - the packet sniffing beast
 * Copyright 2009, 2010 Daniel Borkmann.
 * Subject to the GPL, version 2.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <linux/udp.h>
#include <linux/tcp.h>
#include <linux/in.h>

#include "corking.h"
#include "die.h"

void set_udp_cork(int fd)
{
	int ret, state = 1;

	ret = setsockopt(fd, IPPROTO_UDP, UDP_CORK, &state, sizeof(state));
	if (unlikely(ret))
		panic("Cannot cork UDP socket!\n");
}

void set_udp_uncork(int fd)
{
	int ret, state = 0;

	ret = setsockopt(fd, IPPROTO_UDP, UDP_CORK, &state, sizeof(state));
	if (unlikely(ret))
		panic("Cannot uncork UDP socket!\n");
}

void set_tcp_cork(int fd)
{
	int ret, state = 1;

	ret = setsockopt(fd, IPPROTO_TCP, TCP_CORK, &state, sizeof(state));
	if (unlikely(ret))
		panic("Cannot cork TCP socket!\n");
}

void set_tcp_uncork(int fd)
{
	int ret, state = 0;

	ret = setsockopt(fd, IPPROTO_TCP, TCP_CORK, &state, sizeof(state));
	if (unlikely(ret))
		panic("Cannot uncork TCP socket!\n");
}

void set_sock_cork(int fd, int udp)
{
	if (!!udp)
		set_udp_cork(fd);
	else
		set_tcp_cork(fd);
}

void set_sock_uncork(int fd, int udp)
{
	if (!!udp)
		set_udp_uncork(fd);
	else
		set_tcp_uncork(fd);
}