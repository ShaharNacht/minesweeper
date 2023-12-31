name := minesweeper
src := src/*.c

flags := -std=c2x -Wall -Wextra -Wconversion -lSDL2 -lSDL2_image
debug_flags := -ggdb3 -Og -D_FORTIFY_SOURCE=3 -fanalyzer
release_flags := -flto -O3 -mwindows

.PHONY: debug
debug:
	gcc $(src) -o $(name)_dbg $(flags) $(debug_flags)

.PHONY: release
release:
	gcc $(src) -o $(name) $(flags) $(release_flags)

.PHONY: analyze
analyze:
	gcc $(src) -o _analysis $(flags) $(release_flags) -fanalyzer
	@del _analysis.exe

.PHONY: res
res:
	windres res/res.rc -o res/res.o