all:
	@cd src && make clean
	@cd src && make
	@cd boot && make
	@make clean
run:
	@cd ./boot/ && bochs -f bochsrc.txt -q

clean:
	@cd src && make clean
