#include <pthread.h>
typedef pthread_t ThreadType;

typedef void* (*ThreadFunc)(void*);

ThreadType thread_create(ThreadFunc func, void* arg);
void thread_detach(ThreadType t);
