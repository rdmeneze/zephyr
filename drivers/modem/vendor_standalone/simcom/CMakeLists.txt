# Copyright (c) 2025 Metratec GmbH.
# SPDX-License-Identifier: Apache-2.0

# zephyr-keep-sorted-start
add_subdirectory_ifdef(CONFIG_MODEM_SIM7000 sim7000)
add_subdirectory_ifdef(CONFIG_MODEM_SIM7080 sim7080)
# zephyr-keep-sorted-stop
