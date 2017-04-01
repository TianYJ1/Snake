<<<<<<< HEAD
# sokoban
=======
# Sokoban-project
Sokoban (倉庫番 sōkoban, warehouse keeper) is a type of transport puzzle, in which the player pushes boxes or crates around in a warehouse, trying to get them to storage locations. The puzzle is usually implemented as a video game.

## Getting Started
This game is build using c-language and based on Allegro Library
### Directory structure
The source code is organized as follows:
Subdirectory | Description
-------------|-------------------
src/         | source files 
src/tests    | unit tests 
doc/         | documentation 
res/         | static resources
### Structure
* Main - menu module 
* Level - level drawer, game-play handler
* Generator - level generator, which returns 2-dimensional 
* MemoryWorker - manager of continous memory, based on JSON
### Dependencies 
* Allegro Framework [Refer to allegro ](http://liballeg.org/)
* JSON-library

### Build
To build the project, do the following:
````
make
````
To rebuild everything from scratch, do the following:
````
make clean
````

## Authors
* **Arseniy Prosvirin** - arseniy.p@d7ss.com
* **Ryabota Igor** - x@x.ru
## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
>>>>>>> 2be62ffa3e91d1ee3f371b4836219e4043499c9f
