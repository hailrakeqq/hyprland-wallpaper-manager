rm -rf build
mkdir -p build
gtk4-builder-tool simplify --3to4 gui.glade > gui.ui
git clone https://github.com/nlohmann/json/
cd build 
cmake ..
make