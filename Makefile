#-----------------------------------------------------------
# source files
#-----------------------------------------------------------
ALL_SRC = main.c shape.c board.c playtree.c


.PHONY: all 

all: 
	gcc $(ALL_SRC) -o play_shape.exe

clean:
	@rm -rf *.o
	@rm -rf *.exe





