name := minesweeper
src := src/*.c

flags := -std=gnu2x -Wall -Wextra -lSDL2
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
	windres res/res.rc -o res/res2.o