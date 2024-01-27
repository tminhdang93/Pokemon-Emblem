makeWin: main.cpp Attack.cpp Attack.h Game.cpp Game.h Map.cpp Map.h Menu.cpp Menu.h Player.cpp Player.h PokemonBase.cpp PokemonBase.h Tile.cpp Tile.h
	g++ Attack.cpp PokemonBase.cpp Tile.cpp Player.cpp Map.cpp Menu.cpp Game.cpp main.cpp -o out -lsfml-graphics -lsfml-window -lsfml-system
	./out

makeMac: Attack.cpp Attack.h PokemonBase.cpp PokemonBase.h Tile.cpp Tile.h Player.cpp Player.h Map.cpp Map.h Menu.h Menu.cpp Game.cpp Game.h main.cpp g++ Attack.cpp PokemonBase.cpp Tile.cpp Player.cpp Map.cpp Menu.cpp Game.cpp main.cpp -I/usr/local/Cellar/sfml/2.5.1_2/include/ -L//usr/local/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system ./a.out
