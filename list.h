#ifndef  _LIST_H_
#define  _LIST_H_

#include <pthread.h>


typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

typedef struct {
    ListNode *head;
    pthread_mutex_t lock;
} ThreadSafeList;


ThreadSafeList* create_thread_safe_list();
void insert_at_head(ThreadSafeList *list, int value);
void insert_at_tail(ThreadSafeList *list, int value);
void delete_node(ThreadSafeList *list, int value);
ListNode* find_node(ThreadSafeList *list, int value);
void traverse_linked_list(ThreadSafeList *list);
void reverse_linked_list(ThreadSafeList *list);
void free_linked_list(ThreadSafeList *list);

#endif //_LIST_H_