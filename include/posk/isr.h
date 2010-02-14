#ifndef ISR_H_
#define ISR_H_ FOO

extern void isrs_install();

struct regs {
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
};

#endif
