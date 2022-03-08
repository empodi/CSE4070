#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H
#include "process.h"
#include "../lib/user/syscall.h"
#include "threads/synch.h"

struct lock wrt;
struct lock mutex;
int read_count;

void syscall_init (void);

void sysHalt();
pid_t sysExec(const char* cmd_line);
int sysWait(pid_t pid);
void sysExit(int status);

int sysRead(int fd, void* buffer, unsigned size);
int sysWrite (int fd, const void* buffer, unsigned size);

bool sysCreate(const char *file, unsigned initial_size);
bool sysRemove(const char* file);
int sysOpen(const char* file);
int sysFilesize(int fd);
void sysSeek (int fd, unsigned position);
unsigned sysTell (int fd);
void sysClose (int fd);

int sysFibo(int n);
int sysMax(int a, int b, int c, int d);


#define ASSERT_FILE(CONDITION)			\
		if (CONDITION) { } else {		\
				sysExit (-1);			\
		}

#endif /* userprog/syscall.h */
