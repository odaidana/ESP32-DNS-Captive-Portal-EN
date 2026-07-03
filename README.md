# ESP32 DNS Server & Captive Portal Guide

This repository provides a production-ready, open-source educational implementation of a local DNS Server and Captive Portal using the ESP32 microcontroller. It demonstrates how to intercept DNS queries and redirect all connected clients to a locally hosted web server.

## Key Mechanisms
- **SoftAP Configuration:** Setting up a secure, independent local Wi-Fi Access Point.
- **DNS Interception:** Running a lightweight DNS server on Port 53 to resolve all domain queries (`*`) to the ESP32's local IP address.
- **Asynchronous Web Server:** Serving custom HTML pages dynamically to connected network clients.

## Repository Structure
- `src/dns_portal.cpp` — Main firmware running the Access Point, DNS stack, and HTTP server.

## Contact & Support
For questions or hardware discussions, feel free to reach out via Discord: `odai.7`
