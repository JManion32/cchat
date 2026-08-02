## CChat
A real-time client-server chat application. Supports a Qt GUI and React web clients. This project was created for a school assignment, and has since been polished and expanded.

## Building

### Prerequisites
```bash
sudo apt install cmake g++ qt6-base-dev nlohmann-json3-dev
```
Node 18+ is needed for the web client and gateway.

Qt is only required for the desktop GUI. To work on the server or web client
without installing it, see [Building without Qt](#building-without-qt).

### Build
```bash
cmake --preset dev
cmake --build --preset dev
```
Binaries land in `bin/`. The preset handles the Qt lookup, so no environment
variables or `-D` flags are needed.

#### If Qt is installed somewhere non-standard
The preset looks for the Qt online installer's default location,
`~/Qt/6.10.1/gcc_64`, and otherwise falls back to the system Qt from
`qt6-base-dev`. If yours is elsewhere, or is a different version, create
`CMakeUserPresets.json` in the repo root (it is gitignored, so it stays local):
```json
{
    "version": 3,
    "configurePresets": [
        {
            "name": "local",
            "inherits": "dev",
            "cacheVariables": {
                "CMAKE_PREFIX_PATH": "$env{HOME}/Qt/6.11.0/gcc_64"
            }
        }
    ]
}
```
Then build with `cmake --preset local` and `cmake --build --preset local`.

#### Building without Qt
```bash
cmake --preset dev -D BUILD_CLIENT_GUI=OFF
cmake --build --preset dev
```

## Running Locally

The server listens on port 5000. Start it first:
```bash
./bin/server 5000
```

### Native GUI client
```bash
./bin/client 127.0.0.1 5000
```

### Browser client
The gateway bridges the browser's WebSocket to the server's TCP socket. It takes
the server host, the server port, and the port to serve WebSockets on:
```bash
cd gateway
npm install
node gateway.js 127.0.0.1 5000 8080
```
Then, in another terminal, create `client_site/.env` with:
```
VITE_GATEWAY_URL=ws://localhost:8080
```
and start the dev server:
```bash
cd client_site
npm install
npm run dev
```

## Connecting to the Live Server with the GUI
The live server listens on port `5000`.
```bash
./client cchat.fun 5000
```
You can also connect from a local browser environment with:
```
VITE_GATEWAY_URL=ws://cchat.fun:8080
```