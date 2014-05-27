#ifndef __brain_vm_h
#define __brain_vm_h

struct bfVM {
    int ip;
    char *program;

    int cp;
    char *cells;
    unsigned int num_cells;
};

struct bfVM *createVM(char *program, unsigned int num_cells);
void destroyVM(struct bfVM *vm);

#endif
