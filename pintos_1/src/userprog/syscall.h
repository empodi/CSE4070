#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H
#include "process.h"
#include "../lib/user/syscall.h"

void syscall_init (void);

void sysHalt();
pid_t sysExec(const char* cmd_line);
int sysWait(pid_t pid);
int sysExit(int status);

int sysRead(int fd, void* buffer, unsigned size);
int sysWrite (int fd, const void* buffer, unsigned size);

int sysFibo(int n);
int sysMax(int a, int b, int c, int d);

#endif /* userprog/syscall.h */
