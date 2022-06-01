CUBE3D
===

[Subject](https://cdn.intra.42.fr/pdf/pdf/48490/fr.subject.pdf)

## Resources :
- [Walls textures](https://opengameart.org/art-search-advanced?field_art_tags_tid=wall)
- [Convert to xpm](https://convertio.co/)
- [Debug maps (Outdated?)](https://github.com/nsterk/cub3D/tree/main/maps)
- [Tester & maps](https://github.com/MichelleJiam/cub3D_tester)

## Issues:
- Distances increase while time pass.

## Program life cycle :
### Parsing
- [x] read file,
- [x] extract walls textures,
- [x] extract sky and ceil colors
- [x] import map into chained list,
- [x] comvert list to 2D array.
- [x] save player pos,
- [ ] handle errors,
	- [-] not closed map
	- [ ] texture files not exist, not permited or with wrong extension
	- [ ] impossible color used
	- [-] missing map
### Init
### Window
### Render
- [x] display ceil, walls and floor
- [ ] display wall's texture
### Control
- [x] enable commands
	- [x] wasd to move
- [ ] react to commands :
	- [x] calculate new pos,
	- [x] display new view,
	- [x] avoid colisions
	- [x] M to show minimap
	- [x] SHIFT to run
### Quit 
- [ ] clean and exit
