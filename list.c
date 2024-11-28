#include <stdio.h>
#include <stdlib.h>
#include "list.h"

ThreadSafeList* create_thread_safe_list()
{
    ThreadSafeList *list = (ThreadSafeList*)malloc(sizeof(ThreadSafeList));
    list->head = NULL;
    pthread_mutex_init(&list->lock, NULL);
    return list;
}

void insert_at_head(ThreadSafeList *list, int value)
{
    pthread_mutex_lock(&list->lock);
    
    ListNode *new_node = (ListNode*)malloc(sizeof(ListNode));
    new_node->value = value;
    new_node->next = list->head;
    list->head = new_node;
    
    pthread_mutex_unlock(&list->lock);
}

void insert_at_tail(ThreadSafeList *list, int value)
{
    pthread_mutex_lock(&list->lock);
    
    ListNode *new_node = (ListNode*)malloc(sizeof(ListNode));
    new_node->value = value;
    new_node->next = NULL;

    if (!list->head)
    {
        list->head = new_node;
    }
    else
    {
        ListNode *current = list->head;
        while (current->next) 
        {
            current = current->next;
        }
        current->next = new_node;
    }
    
    pthread_mutex_unlock(&list->lock);
}

void delete_node(ThreadSafeList *list, int value)
{
    pthread_mutex_lock(&list->lock);
    
    if (!list->head)
    {
        pthread_mutex_unlock(&list->lock);
        return;
    }

    if (list->head->value == value)
    {
        ListNode *temp = list->head;
        list->head = list->head->next;
        free(temp);
        pthread_mutex_unlock(&list->lock);
        return;
    }

    ListNode *current = list->head;
    while (current->next)
    {
        if (current->next->value == value)
        {
            ListNode *temp = current->next;
            current->next = current->next->next;
            free(temp);
            pthread_mutex_unlock(&list->lock);
            return;
        }
        current = current->next;
    }
    
    pthread_mutex_unlock(&list->lock);
}

ListNode* find_node(ThreadSafeList *list, int value)
{
    pthread_mutex_lock(&list->lock);
    
    ListNode *current = list->head;
    while (current)
    {
        if (current->value == value)
        {
            pthread_mutex_unlock(&list->lock);
            return current;
        }
        current = current->next;
    }
    
    pthread_mutex_unlock(&list->lock);
    return NULL;
}


void traverse_linked_list(ThreadSafeList *list)
{
    pthread_mutex_lock(&list->lock);
    
    ListNode *current = list->head;
    while (current)
    {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
    
    pthread_mutex_unlock(&list->lock);
}

void reverse_linked_list(ThreadSafeList *list)
{
    pthread_mutex_lock(&list->lock);
    
    ListNode *prev = NULL;
    ListNode *current = list->head;
    while (current)
    {
        ListNode *next_node = current->next;
        current->next = prev;
        prev = current;
        current = next_node;
    }
    list->head = prev;
    
    pthread_mutex_unlock(&list->lock);
}

void free_linked_list(ThreadSafeList *list)
{
    pthread_mutex_lock(&list->lock);
    
    ListNode *current = list->head;
    while (current)
    {
        ListNode *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
    
    pthread_mutex_unlock(&list->lock);
}
