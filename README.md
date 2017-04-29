# Sokoban-project
Sokoban (倉庫番 sōkoban, warehouse keeper) is a type of transport puzzle, in which the player pushes boxes or crates around in a warehouse, trying to get them to storage locations. The puzzle is usually implemented as a video game.

## Getting Started
This game is build using c-language and based on [Allegro](http://liballeg.org/) Library
### Directory structure
The source code is organized as follows:

Subdirectory | Description
-------------|-------------------
src/         | source files 
src/tests    | unit tests 
doc/         | documentation 
res/     | static resources
### Structure
* Main - menu module 
* Level - level drawer, game-play handler
* Generator - level generator, which returns 2-dimensional array (will be changed to LevelEditor)
* MemoryWorker - manager of continous memory, based on JSON
* Managers:
	* SpriteManager - manager for rendering sprites from bitmaps
	* Button - button manager for handling clicks, writing text and placing sprites
	* Label - manager for labels
### Dependencies 
* [Allegro](http://liballeg.org/) framework <br />
	Addons using:
	* Font addon
	* Image addon
	* TTF font addon
	* Dialog addon
	* Color addon
	* Primitives addon
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
#### Building Allegro
````
cd ~; git clone git://github.com/liballeg/allegro5cd allegro5;git checkout 5.2; mkdir build; cd build
sudo ccmake -DCMAKE_INSTALL_PREFIX=/usr ..
````
Here press 'c', 'c', 'g', unpack will begin.
If an error connected to OPUS occurs, change WANT_OPUS to 'OFF' in list of packages in white box on the right side
````
sudo make;sudo make install
````
## Authors
* **Arseniy Prosvirin** - arseniy.p@d7ss.com
* **Ryabota Igor** - x@x.ru
## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

