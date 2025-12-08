## Secure Chatroom App in C++
Tested on: Ubuntu 24.04 and Windows 11. We had some trouble with the 
Windows side of things, but Linux has been thoroughly tested and proven 
to work.

### Running on Linux
Make the client and server side:
```
make
```

Cleanup .o files and executables from previous makes:
```
make clean
```

Make the client only:
```
cd client
make -C client
```

Make the server only:
```
cd server
make -C server
```

### Running on Windows
```
cd scripts
```

Make the client and server side:
```
build_windows.bat
```

Cleanup files:
```
build_windows.bat clean
```

Make the client only:
```
build_windows.bat client
```

Make the server only:
```
build_windows.bat server
```