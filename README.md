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
* MemoryWorker - manager of continous memory, based on bare parser
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
	* Audio addon, Audiocodec addon


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
##### Any Linux
````
cd ~; git clone git://github.com/liballeg/allegro5cd allegro5;git checkout 5.2; mkdir build; cd build
sudo ccmake -DCMAKE_INSTALL_PREFIX=/usr ..
````
Here press 'c', 'c', 'g', unpack will begin.
If an error connected to OPUS occurs, change WANT_OPUS to 'OFF' in list of packages in white box on the right side
````
sudo make;sudo make install
````
##### On Ubuntu
````
sudo add-apt-repository ppa:allegro/5.2
sudo apt-get update
sudo apt-get install liballegro5-dev
````
### Testing
#### Installing
Tests in project are based on [Unity Test Framework](http://www.throwtheswitch.org/unity). To get it, just type:
````
git clone https://github.com/ThrowTheSwitch/Unity.git
````
#### Building and running tests
Do the following:
````
make tests D_UNITY=<UNITY PATH>
````
where <UNITY_PATH> is absolute path to your directory which contains Unity. After building everything, run **test-sokoban**.
All tests will gone, if not - please, let us know
## Authors
* **Arseniy Prosvirin** - arseniy.p@d7ss.com
* **Ryabota Igor** - x@x.ru
## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

