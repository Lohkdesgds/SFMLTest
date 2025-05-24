cmake -S . -B build
cmake --build build --config Release --parallel 4
if not exist "__release" mkdir "__release"
copy build\main\MainApp.exe __release\