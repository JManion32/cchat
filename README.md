## CChat
Tested on Ubuntu 24.04

### Cloning the Repository
```
git clone https://github.com/JManion32/cchat.git
```

## Running Locally

### React Website Client
```
cd client_site
npm run dev
```

### Server and Native on Linux
Make the client GUI and server:
```
make
```

Cleanup .o files and executables from previous makes:
```
make clean
```

Make the client GUI only:
```
make -C client_gui
```

Make the server only:
```
make -C server
```

### Running on Windows
Only the React website client can be ran on Windows. The server and native GUI use Linux-specific socket and threading libraries.
