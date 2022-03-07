#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
// is_user_vaddr (const void* vaddr);
// is_kernel_vaddr (const void(* vaddr);

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f) 
{

	uint32_t* sysEsp = f->esp;
	uint32_t esp4, esp8, esp12, esp16;

	esp4 = *(uint32_t*)(f->esp + 4);
	esp8 = *(uint32_t*)(f->esp + 8);
	esp12 = *(uint32_t*)(f->esp + 12);
	esp16 = *(uint32_t*)(f->esp + 16);
	
	switch (*sysEsp){
		case SYS_HALT:
			sysHalt();
			break;
		case SYS_EXIT:
			if (is_kernel_vaddr(esp4)) 
				sysExit(-1);
			
			sysExit(esp4);
			break;
		case SYS_EXEC:
			if (is_kernel_vaddr(esp4)) 
				sysExit(-1);
			
			f->eax = sysExec((char*)esp4);
			break;
		case SYS_WAIT:
			if (is_kernel_vaddr(esp4)) 
				sysExit(-1);
		
			f->eax = sysWait(esp4);
			break;
		case SYS_READ:
			if (is_kernel_vaddr(esp4) || is_kernel_vaddr(esp8) || is_kernel_vaddr(esp12)) 
				sysExit(-1);
			
			f->eax = sysRead ((int)esp4, (void*)esp8, (unsigned)esp12);
			break;
		case SYS_WRITE:
			if (is_kernel_vaddr(esp4) || is_kernel_vaddr(esp8) || is_kernel_vaddr(esp12)) 
				sysExit(-1);
		
			f->eax = sysWrite((int)esp4, (void*)esp8, (unsigned)esp12);
			break;
		case SYS_FIBO:
			if (is_kernel_vaddr(esp4)) 
				sysExit(-1);
			f->eax = sysFibo ((int)esp4);
			break;
		case SYS_MAX:
			if (is_kernel_vaddr(esp4) || is_kernel_vaddr(esp8) || is_kernel_vaddr(esp12) || is_kernel_vaddr(esp16)) 
				sysExit(-1);
			f->eax = sysMax ((int)esp4, (int)esp8, (int)esp12, (int)esp16);
			
  }
	
	return -1;
}

int sysFibo(int n) {
	
	if (n < 2) return n;
	else return sysFibo(n - 1) + sysFibo(n - 2);
}

int sysMax(int a, int b, int c, int d) {
	
	a = (a > b) ? a : b;
	c = (c > d) ? c : d;

	return (a > c) ? a : c;
}

void sysHalt() {

	shutdown_power_off();
}

pid_t sysExec (const char* cmd_line) {
	
	return process_execute(cmd_line);
}

int sysWait (pid_t pid) {

	return process_wait(pid);
}

int sysExit(int status) {

	thread_current()->exit_status = status;

	printf("%s: exit(%d)\n", thread_name(), status);
	thread_exit();
}

int sysWrite(int fd, const void *buffer, unsigned size){

	if (fd == 1){
		//printf("SYSCALL_ size: %d", size);
		//printf("SYSCALL_ buffer: %s", buffer);
		putbuf(buffer, size);
		return size;
	}

	return -1;
}

int sysRead(int fd, void* buffer, unsigned size) {

	if (fd == 0) {
		
		int i = 0, len = size;

		while (i < len && input_getc() != '\0') i++;
		
		return i;
	}

	return -1;
}






// syscall.c
