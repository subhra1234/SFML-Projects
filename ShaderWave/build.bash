%bashrc
set -m
cd ~/Documents/Codes/C++/SfmlPros/ShaderWave &&
g++ -c main.cpp && 
g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app