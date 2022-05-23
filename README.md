CUBE3D
===

[Subject](https://cdn.intra.42.fr/pdf/pdf/48490/fr.subject.pdf)

## Resources :
- [Walls textures](https://opengameart.org/art-search-advanced?field_art_tags_tid=wall)
- [Convert to xpm](https://convertio.co/)

## Program life cycle :
- map parsing :
	- [ ] read file,
	- [ ] extract walls textures,
	- [ ] extract sky and ceil colors
	- [ ] import map into array,
	- [ ] save player pos,
	- [ ] handle errors,
- initialize env
- generate window
- display view
- enable commands
- react to commands :
	- calculate new pos,
	- display new view,
- clean and exit

## thoughts :

## verify map validity :
The map must be closed with the player inside the walls.
- calloc a 2D array as X size is the size of the longer
	line and y is the numbers of map lines.
- set the array cells to 1 for floor, 2 for walls
- outside cells will be zeros.
- read line by line until you encounter first wall then turn around
the map following the walls and never going on an already visited
wall until you come back to starting pos.


## initialize env :
- required datas : initial player pov angle, 
- walls height
- eyes positions from screen ( -> field of view)
- calculate fov rays unit vectors,


## display view :
- calculate distance between player and intersection between rays and walls
- calculate viewed height of walls for each verticle
- draw walls, floor and sky
