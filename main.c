#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "list.h"

void* thread_function(void* arg)
{
    int i = 0;
    ThreadSafeList *list = (ThreadSafeList*)arg;
    for (i = 0; i < 5; i++)
    {
        insert_at_tail(list, i);
    }
    return NULL;
}

int main()
{
    int i = 0;
    ThreadSafeList *list = create_thread_safe_list();
    
    pthread_t threads[2];
    pthread_create(&threads[0], NULL, thread_function, list);
    pthread_create(&threads[1], NULL, thread_function, list);
    
    for (i = 0; i < 2; i++)
    {
        pthread_join(threads[i], NULL);
    }
    
    printf("Final list: ");
    traverse_linked_list(list);
    
    free_linked_list(list);
    return 0;
}
