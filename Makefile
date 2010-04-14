all:
	@cd src && make

docs:
	@doxygen doc/DocumentCode
