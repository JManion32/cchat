## CChat
Tested on Ubuntu 24.04 with X86 64 architecture.

### Cloning the Repository
```
git clone https://github.com/JManion32/cchat.git
```

## Connecting to the Live Server
There are 2 client platforms available:
#### Browser client:
https://cchat.fun/
#### Native GUI Client:
Create a `.env` file in /bin/linux and add:
```
CCHAT_SERVER_HOST=cchat.fun
```

## Configuring Locally
The server runs on port 5000. You can connect locally with either of the clients.
#### Browser client:
Create a `.env` file in /client_site and add:
```
VITE_GATEWAY_URL=ws://localhost:8080
```
#### Native GUI Client:
Create a `.env` file in /bin/linux and add:
```
CCHAT_SERVER_IP=127.0.0.1
```

## Running Locally

### React Website Client
```
cd gateway
npm install
node gateway.js
```
```
cd client_site
npm install
npm run dev
```

### Server and Native GUI on Linux
Make the client GUI and server (root dir):
```
make
```

Cleanup .o files and executables from previous makes (root dir):
```
make clean
```

Make the native client GUI only:
```
make -C client_gui
```

Make the server only:
```
make -C server
```

Executables for the native GUI client and the server are found in `bin/linux`, and run with:
```
./server
./client
```

## Running on Windows
Though you may see conditional code execution that accomodates both Windows and Linux socket and threading libraries, it is incomplete. Only the React website client is currently supported on Windows.
