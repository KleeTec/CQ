#pragma once
#include <stddef.h>
#include <stdbool.h>
#include <wchar.h>

#define freeFunction_cast(F) ((void (*)(void*)) (F))
#define printFunction_cast(F) ((void (*)(void*)) (F))
typedef void (freeFunction)(void*);
typedef void (printFunction)(void*);

typedef struct LinkedList {
	size_t size;
	struct LinkedListItem {
		struct LinkedList* head;
		struct LinkedListItem* previous;
		struct LinkedListItem* next;
		void* content;
	} * first;
	struct LinkedListItem* last;
} * LinkedList;

typedef struct LinkedListItem* LinkedListItem;

LinkedList LinkedList_new();
void LinkedList_append(LinkedList list, void* content);
void LinkedList_free(LinkedList list, freeFunction f);
void LinkedList_print(LinkedList list, printFunction f);

