struct ia32_registers {
    // General Purpose Registers
    long eax, ebx, ecx, edx;
    long esp, ebp, esi, edi;
    long eip;
    
    // segment registers
    long cs, ss, ds, es, fs, gs;
    
    // eflags register
    long eflags;
    
    // control registers
    long cr3;
}

struct task_struct {
  unsigned long pid;
  
  int state;
  
  int exit_code;
  
  struct task_struct parent;
  
  struct tss_struct tss;
}