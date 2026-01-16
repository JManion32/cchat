## CChat
Tested on Ubuntu 24.04

### Cloning the Repository
```
git clone https://github.com/JManion32/cchat.git
```

### Running on Linux
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
cd client
make -C client_gui
```

Make the server only:
```
cd server
make -C server
```

### Running on Windows
Does not currently work, will revisit in the future.
