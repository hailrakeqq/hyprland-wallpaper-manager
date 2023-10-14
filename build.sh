rm -rf build
mkdir -p build
git clone https://github.com/nlohmann/json/
cd build 
cmake ..
make