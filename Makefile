# Generated Makefile, Just a template. You can modify me

Var0 = clang++

run:
	
src/main.cc.o:
	ccache ${Var0} -c src/main.cc -o build/main.cc.o --std=gnu++23 -Wall -I includes 
	@echo "[[1;32m Compiling file src/main.cc 0.0%...[0m]"
src/aux.cc.o:
	ccache ${Var0} -c src/aux.cc -o build/aux.cc.o --std=gnu++23 -Wall -I includes 
	@echo "[[1;32m Compiling file src/aux.cc 33.3%...[0m]"
src/display.cc.o:
	ccache ${Var0} -c src/display.cc -o build/display.cc.o --std=gnu++23 -Wall -I includes 
	@echo "[[1;32m Compiling file src/display.cc 66.7%...[0m]"
Link:
	clang++ build/main.cc.o build/aux.cc.o build/display.cc.o -o build/Setwal -lncurses
	@echo "[[1;32m Linking 100%...[0m]"

all:	run	src/main.cc.o	src/aux.cc.o	src/display.cc.o	Link
install:
	sudo mv build/Setwal /usr/bin