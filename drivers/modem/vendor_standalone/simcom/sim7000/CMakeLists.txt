# Copyright (C) 2026 Rafael Dias Menezes <rdmeneze@gmail.com>
# SPDX-License-Identifier: Apache-2.0

zephyr_library()

zephyr_library_include_directories(${ZEPHYR_BASE}/drivers/modem)
zephyr_library_include_directories(${ZEPHYR_BASE}/subsys/net/ip)
zephyr_library_include_directories(${ZEPHYR_BASE}/subsys/net/lib/sockets)
zephyr_library_sources(
    sim7000.c
    sim7000_pdp.c
    sim7000_dns.c
    sim7000_sock.c)
