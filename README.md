При запуске приложение ищет Input.bmp, с которым впоследствии и рабтает. Полученное фото сохраняется в Output.bmp

Для компиляции:
mkdir build
cd build/
cmake ..
cmake --build . --config Release
./Release/image_rotation.exe #Перед запуском не забудте поместить в данную директорию bmp файл