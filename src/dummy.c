
void doNothing() {
  asm volatile("xchg %bx,%bx"); 
  int i; 
   for(i = 0; i<100; i++);
    // do nothing, a lot
}