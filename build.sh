
cd build
g++ -c ../src/main.cpp
g++ main.o -o VisuStock ../src/date.cpp ../src/datapoint.cpp ../src/IO.cpp ../src/stockdata_manipulation.cpp -lsfml-graphics -lsfml-window -lsfml-system
cd ..
