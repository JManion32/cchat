rm -rf build

cd bin
rm server
rm client
rm shared
cd ..

mkdir build
cd build

cmake ..
cmake --build .