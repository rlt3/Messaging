all:
	clang++ -c src/sound.cpp -o obj/sound.o -std=c++11 -F/Library/Frameworks
	clang++ -c src/graphics.cpp -o obj/graphics.o -std=c++11 -F/Library/Frameworks
	clang++ -c src/main.cpp -o obj/main.o -std=c++11 -F/Library/Frameworks
	clang++ -o slow obj/main.o obj/graphics.o obj/sound.o -std=c++11 -I/usr/include/ -F/Library/Frameworks -framework Cocoa -framework SDL2 -framework SDL2_image -framework SDL2_Mixer
