# Bluetooth Low-Energy (BLE) Communication
This command line utility provides a way to interface with the ESP32-C3 chip through BLE. Text is sent over the low-energy protocol and is useful when serial input is not feasible.

### Building the Application
This application is cross compiled for **x86-64**, **arm32** and **arm64** chips using Docker.
```bash
# Build the compiling container
docker build . -t ble-comm

# Run the container to build the application for each target
docker run --rm -v "$(pwd)/build:/ble_comm/build" ble-comm
```
The resulting executables are found in `/build`. They are named `ble_comm-[arch]`.
