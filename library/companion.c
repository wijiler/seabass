
/*
    SEABASS STANDARD LIBRARY IMPLEMENTATION FOR C PROGRAMMING.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <errno.h>
#ifndef __APPLE__

#include "lockstepthread.h"

#endif

#define uc unsigned char



size_t openfile(uc* fname, uc* mode){
    return (size_t)fopen((char*)fname, (char*)mode);
}

int closefile(size_t p){
    return fclose((FILE*)p);
}

size_t get_stdout_handle(){
    return (size_t)stdout;
}

size_t get_stdin_handle(){
    return (size_t)stdin;
}

size_t get_stderr_handle(){
    return (size_t)stderr;
}

size_t write_bytes(size_t fhandle, uc* buf, size_t nbytes){
    return fwrite(buf, 1, nbytes,(FILE*)fhandle);
}

size_t read_bytes(size_t fhandle, uc* buf, size_t nbytes){
    return fread(buf, 1, nbytes,(FILE*)fhandle);
}

size_t get_utime(){
    return time(0);
}

uc* get_real_path(uc* path){
    return (uc*)realpath((char*)path,NULL);
}

void set_errno(int new_errno){
    errno = new_errno;
}

int get_errno(){
    return errno;
}

//this is included in case we are not able to optimize...

void mcpy(unsigned char* dst, unsigned char* src, size_t sz){
    memcpy(dst, src, sz);
}
void mmove(unsigned char* dst, unsigned char* src, size_t sz){
    memmove(dst, src, sz);
}

//these are provided for similar reasons...
unsigned char* mem_alloc(size_t amt){
    return malloc(amt);
}

void mem_free(unsigned char* p){
    free(p);
}

unsigned char* mem_realloc(unsigned char* b, size_t amt){
    return realloc(b, amt);
}

void println(char* s){
    puts(s);
}

void sys_exit(int a){
    exit(a);
}


//MULTITHREADING LIBRARY
#ifndef __APPLE__


unsigned char* thread_new(){
    lsthread* p = malloc(sizeof(lsthread));
    init_lsthread(p);
    return (unsigned char*)p;
}
void thread_delete(unsigned char* tr){
    lsthread* p = (lsthread*)tr;
    destroy_lsthread(p);
    free(p);
    return;
}

void thread_assign_fn(unsigned char* tr, unsigned char* funk){
    lsthread* p = (lsthread*)tr;
    void* fnk = funk;
    p->execute = fnk;
}

void thread_assign_arg(unsigned char* tr, unsigned char* arg){
    lsthread* p = (lsthread*)tr;
    p->argument = arg;
}

void thread_start(unsigned char* tr){
    lsthread* p = (lsthread*)tr;
    start_lsthread(p);
}
void thread_kill(unsigned char* tr){
    lsthread* p = (lsthread*)tr;
    kill_lsthread(p);
}

void thread_step(unsigned char* tr){
    lsthread* p = (lsthread*)tr;
    step(p);
}

void thread_lock(unsigned char* tr){
    lsthread* p = (lsthread*)tr;
    lock(p);
}

unsigned char* mutex_new(){
    pthread_mutex_t* m = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(m, NULL);
    return (unsigned char*)m;
}

void mutex_delete(unsigned char* mtx){
    pthread_mutex_t* m = (pthread_mutex_t*)mtx;
	pthread_mutex_destroy(m);
	free(m);
}

void mutex_lock(unsigned char* mtx){
    pthread_mutex_t* m = (pthread_mutex_t*)mtx;
	pthread_mutex_lock(m);
}
void mutex_unlock(unsigned char* mtx){
    pthread_mutex_t* m = (pthread_mutex_t*)mtx;
	pthread_mutex_unlock(m);
}
#else
unsigned char* thread_new(){
    return NULL;
}
void thread_delete(unsigned char* tr){
    free(tr);
    return;
}

void thread_assign_fn(unsigned char* tr, unsigned char* funk){
    return;
}

void thread_assign_arg(unsigned char* tr, unsigned char* arg){
    return;
}

void thread_start(unsigned char* tr){
    return;
}
void thread_kill(unsigned char* tr){
    return
}

void thread_step(unsigned char* tr){
    return;
}

void thread_lock(unsigned char* tr){
    return;
}

unsigned char* mutex_new(){
    return NULL;
}

void mutex_delete(unsigned char* mtx){
	free(mtx);
}

void mutex_lock(unsigned char* mtx){
    return;
}
void mutex_unlock(unsigned char* mtx){
    return;
}

#endif
