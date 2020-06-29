#!/bin/bash

# ------------------------------- Useful commands ------------------------------
# ip addr show
# ip addr add [address] dev [device]
# ip addr del [address] dev [device]

# ip link show
# ip link set dev [device] [up/down]

# ip route list
# ip route add [destination] via [gateway] dev [device]
# ip route add default via [gateway]
# ip route del [destination] via [gateway]
# ip route del default

# ---------------------------- Application specific ----------------------------
# To use this script to connect to the UHI, substitute enp4s0 with the interface
# that the UHI is connected to.

# Ensure that the network interface is enabled.
sudo ip link set enp4s0 up

# Add IP address to interface.
sudo ip addr add 192.168.1.100 dev enp4s0

# Add static route.
sudo ip route add 192.168.1.103 via 192.168.1.100 dev enp4s0
