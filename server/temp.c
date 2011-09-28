#include <pthread.h>
#include <stdio.h>

int main() {
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    size_t size;
    pthread_attr_getstacksize(&attr, &size);
    size /= 1024 * 1024;
    printf("Stack size is %d\n", size);
}
