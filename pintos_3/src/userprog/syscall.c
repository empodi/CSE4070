#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
#include "filesys/filesys.h"
#include "filesys/file.h"
#include "filesys/off_t.h"
// is_user_vaddr (const void* vaddr);
// is_kernel_vaddr (const void* vaddr);

struct file {
	struct inode* inode;
	off_t pos;
	bool deny_write;
};

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{	
    intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
	lock_init(&mutex);
	lock_init(&wrt);
	read_count = 0;
}

static void
syscall_handler (struct intr_frame *f) 
{

	uint32_t* sysEsp = f->esp;
	uint32_t esp4, esp8, esp12, esp16;
	
	int fdIdx;
	char* file;
	struct file* fp;
	struct thread* cur_t = thread_current ();

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
		case SYS_CREATE:
			if (is_kernel_vaddr(esp4) || is_kernel_vaddr(esp8))
				sysExit(-1);
			
			file = (char*)esp4;
			ASSERT_FILE (file);
			
			f->eax = sysCreate(file, (unsigned)esp8);
			break;
		case SYS_REMOVE:
			if (is_kernel_vaddr(esp4)) 
				sysExit(-1);
			
			file = (char*)esp4;
			ASSERT_FILE (file);
			
			f->eax = sysRemove((char*)esp4);
			
			break;
		case SYS_OPEN:
			if (is_kernel_vaddr(esp4)) 
				sysExit(-1);
			
			file = (char*)esp4;
			ASSERT_FILE (file);
			
			f->eax = sysOpen((char*)esp4);
			
			break;
		case SYS_FILESIZE:
		
			if (is_kernel_vaddr(esp4)) 
				sysExit(-1);
			
			fp = cur_t->FD[(int)esp4];
			ASSERT_FILE (fp);
			
			f->eax = sysFilesize((int)esp4);
			break;
		case SYS_SEEK:
			if (is_kernel_vaddr(esp4) || is_kernel_vaddr(esp8))
				sysExit(-1);
			
			fp = cur_t->FD[(int)esp4];
			ASSERT_FILE (fp);
			
			sysSeek ((int)esp4, (unsigned)esp8);
			break;
		case SYS_TELL:
			if (is_kernel_vaddr(esp4))
				sysExit(-1);
			
			fp = cur_t->FD[(int)esp4];
			ASSERT_FILE (fp);
		
			f->eax = sysTell ((int)esp4);
			break;
		case SYS_CLOSE:
			if (is_kernel_vaddr(esp4))
				sysExit(-1);
			
			fp = cur_t->FD[(int)esp4];
			ASSERT_FILE (fp);
			
			sysClose ((int)esp4);
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
			break;
			
  }
	
}

int sysFibo (int n) {
	
	if (n < 2) return n;
	else return sysFibo(n - 1) + sysFibo(n - 2);
}

int sysMax (int a, int b, int c, int d) {
	
	a = (a > b) ? a : b;
	c = (c > d) ? c : d;

	return (a > c) ? a : c;
}

void sysHalt () {

	shutdown_power_off();
}

pid_t sysExec (const char* cmd_line) {
	
	return process_execute(cmd_line);
}

int sysWait (pid_t pid) {

	return process_wait(pid);
}

void sysExit (int status) {

	struct thread* t = thread_current ();
	t->exit_status = status;
	
	close_all_files ();
	
	printf("%s: exit(%d)\n", thread_name(), status);
	thread_exit();
}

int sysWrite (int fd, const void *buffer, unsigned size){

	if (is_kernel_vaddr(buffer)) sysExit(-1);

	lock_acquire (&wrt);

	if (fd == 1){
		putbuf(buffer, size);

		lock_release (&wrt);
		return size;
	}

	if (fd >= FD_RESERVED_NO && fd < MAX_FILENO) {
		
		struct file* fp = thread_current()->FD[fd];

		ASSERT_FILE (fp);

		if (fp->deny_write)
			file_deny_write (fp);
		
		int ret_write;
		
		ret_write =  file_write (fp, buffer, size);
		lock_release (&wrt);
		return ret_write;
	} 
	else {
		sysExit(-1);
	}
	
	lock_release (&wrt);
	return -1;
}

int sysRead (int fd, void* buffer, unsigned size) {

	ASSERT(buffer);

	if (is_kernel_vaddr(buffer)) sysExit(-1);
	
	int ret_read = -1;

	lock_acquire (&mutex);
	read_count++;
	if (read_count == 1) lock_acquire (&wrt);
	
	if (fd == 0) {
		
		int i = 0, len = size;

		while (i < len && input_getc() != '\0') i++;

		ret_read = i;
	}
	else {
		
		if (fd >= FD_RESERVED_NO && fd < MAX_FILENO) {
			
			struct file* fp = thread_current()->FD[fd];
			
			ret_read = file_read (fp, buffer, size);
		} 
		else sysExit(-1);
	}
	
	read_count--;

	if (read_count == 0)
		lock_release(&wrt);

	lock_release(&mutex);

	return ret_read;
}

bool sysCreate (const char *file, unsigned initial_size) {
	
	ASSERT_FILE (file);
	
	return filesys_create (file, initial_size);
}

bool sysRemove (const char* file) {
	
	ASSERT_FILE (file);
	
	return filesys_remove(file);
}

int sysOpen (const char* file) {
	
	ASSERT_FILE (file);
	
	lock_acquire (&wrt);

	struct file* fp = filesys_open (file);
	
	if (fp) {

		int fdIdx = get_empty_file_descriptor();

		if (fdIdx < 0) sysExit(-1);

		struct thread* cur_t = thread_current();
		char* t_name = cur_t->name;
		cur_t->FD[fdIdx] = fp;

		if (strcmp(file, t_name) == 0)
			file_deny_write(fp);

		lock_release (&wrt);
		return fdIdx;
	}
	else {
		lock_release (&wrt);
		return -1;
	}
}

int sysFilesize (int fd) {
	
	struct file* fp = thread_current()->FD[fd];
	
	ASSERT_FILE (fp);
	
	return file_length(fp);
}

void sysSeek (int fd, unsigned position) {
	
	struct file* fp = thread_current()->FD[fd];
	
	ASSERT_FILE (fp);

	file_seek (fp, position);
}

unsigned sysTell (int fd) {
	
	struct file* fp = thread_current()->FD[fd];
	
	ASSERT_FILE (fp);
	
	return file_tell (fp);
}

void sysClose (int fd) {
	
	struct thread* t = thread_current ();
	struct file* fp = t->FD[fd];
	
	ASSERT_FILE (fp);
	
	file_close (fp);
	t->FD[fd] = NULL;
}


// syscall.c
