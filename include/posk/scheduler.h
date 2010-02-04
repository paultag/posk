struct tss_struct {
    long link; // 16-31 0
    long esp0;
    long ss0; // 16-31 0
    long esp1;
    long ss1; // 16-31 0
    long esp2;
    long ss2; // 16-31 0
    
    long cr3;
    
    long eip;
    
    long eflags;
    
    long eax;
    long ecx;
    long edx;
    long ebx;
    long esp;
    long ebp;
    long esi;
    long edi;
    
    long es; // 16-31 0
    long cs; // 16-31 0
    long ss; // 16-31 0
    long ds; // 16-31 0
    long fs; // 16-31 0
    long gs; // 16-31 0
    
    long ldtr; // 16-31 0
    long iopb_offset // 0-15 0
}

struct task_struct {
  unsigned long pid;
  
  int state;
  
  int exit_code;
  
  struct task_struct parent;
  
  struct tss_struct tss;
}
