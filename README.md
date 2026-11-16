# C-Based Network Packet Sniffer

A lightweight, foundational network packet sniffer built from scratch in C using Linux raw sockets. This tool operates directly at the Data Link layer to intercept and analyze live network traffic.

## Features
- Captures live network traffic using raw sockets (`AF_PACKET`).
- Parses and decodes standard network headers using C structs:
  - **Layer 2:** Ethernet frames
  - **Layer 3:** IPv4 packets
  - **Layer 4:** TCP, UDP, and ICMP headers
- Manages memory buffers efficiently to analyze traffic without packet loss under moderate loads.

## Prerequisites
- A Linux environment (built and tested on Kali Linux).
- Root/Sudo privileges (required for raw socket access).
- GCC compiler.

## How to Compile and Run
1. Clone the repository:
   ```bash
   git clone [https://github.com/CHIBISASUKE1245/c-packet-sniffer.git](https://github.com/CHIBISASUKE1245/c-packet-sniffer.git)
   cd c-packet-sniffer
