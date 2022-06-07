CUBE3D
===

[Subject](https://cdn.intra.42.fr/pdf/pdf/48490/fr.subject.pdf)

## Resources :
- [Walls textures](https://opengameart.org/art-search-advanced?field_art_tags_tid=wall)
- [Convert to xpm](https://convertio.co/)
- [Debug maps (Outdated?)](https://github.com/nsterk/cub3D/tree/main/maps)
- [Tester & maps](https://github.com/MichelleJiam/cub3D_tester)

## Issues:
- report invalid mapfile:
	- wrong extension,
	- unacessible file (wrong permission, directory, missin name)
	- 
	- invalid color : Ci > 255, Ci < 0, i > 4
	- invalid texture (wrong permission, missing wall orientation texture, missing used block texture (warning + use default unknow texture))
	- empty line in map description,
	- unauthorized character in map description (!isdigt)
	- 

## Memo:
- ToDo: add F1 keycode on linux,
- Add toggle for mouse control,
## Program life cycle :
### Parsing
- [x] read file,
- [x] extract walls textures,
- [x] extract sky and ceil colors
- [x] import map into chained list,
- [x] comvert list to 2D array.
- [x] save player pos,
- [ ] handle errors,
	- [x] not closed map
	- [ ] texture files not exist, not permited or with wrong extension
	- [ ] impossible color used
	- [-] missing map
### Init
### Window
### Render
- [x] display ceil, walls and floor
- [x] display wall's texture
### Control
- [x] enable commands
	- [x] wasd to move
- [o] react to commands :
	- [x] calculate new pos,
	- [x] display new view,
	- [x] avoid colisions
	- [x] M to show minimap
	- [x] SHIFT to run
	- [-] Debugs window with F1
	- [x] Exit with Esc and X 
### Quit 
- [ ] clean and exit
