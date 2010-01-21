int frob() {
	printf( "Frobing\n" );
}

void test() {
	int (*func)() = &frob;
	(*func)();
}
