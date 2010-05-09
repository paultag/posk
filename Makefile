all:
	@cd cherrytree && make
	@cd src && make clean
	@cd src && make
	@cd boot && make
	@make clean
docs:
	@doxygen doc/DocumentCode

run:
	@cd ./boot/ && bochs -f bochsrc.txt -q

clean:
	@cd src && make clean
	@cd cherrytree && make clean
