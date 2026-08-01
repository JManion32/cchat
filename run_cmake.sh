if [ -f client_gui/.env ]; then
    set -a
    source client_gui/.env
    set +a
else
    export CMAKE_PREFIX_PATH="/home/$USER/Qt/6.10.1/gcc_64"
fi

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