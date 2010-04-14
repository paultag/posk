all:
	@cd src && make clean
	@cd src && make
	@cd boot && make

docs:
	@doxygen doc/DocumentCode
