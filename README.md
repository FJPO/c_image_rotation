При запуске приложение ищет Input.bmp, с которым впоследствии и рабтает. Полученное фото сохраняется в Output.bmp

Для компиляции:
mkdir build<br>
cd build/<br>
cmake ..<br>
cmake --build . --config Release<br>
./Release/image_rotation.exe #Перед запуском не забудте поместить в данную директорию bmp файл<br>