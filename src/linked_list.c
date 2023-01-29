#include <malloc.h>
#include "include/linked_list.h"

LinkedList LinkedList_new() {
	LinkedList list = calloc(1, sizeof *list);
	return list;
}

/**
 *
 * @param list ==> the list to append to
 * @param content ==> what to append
 */
void LinkedList_append(LinkedList list, void* content) {
	list->size++;
	// create mew item of that type
	LinkedListItem new = calloc(1, sizeof *new);
	new->head = list;
	new->content = content;
	// if the list is empty
	if (list->first == NULL){
		list->first = new;
		list->last = new;
		return;
	}
	// if it is not empty get the last item
	LinkedListItem lastItem = list->last;
	// set the last item's next to the new item
	// and the new's previous item to the last item
	lastItem->next = new;
	new->previous = lastItem;
	// finally, set the list's last item to the new one
	list->last = new;
}


void LinkedList_free(LinkedList list, freeFunction f) {
	LinkedListItem item = list->first;
	for(size_t i = 0; i < list->size; ++i) {
		LinkedListItem next = item->next;
		f(item->content);
		free(item);
		item = next;
	}
}

void LinkedList_print(LinkedList list, printFunction f) {
	wprintf(L"[");
	bool indent = list->size >= 7;
	if (indent) wprintf(L"\n\t");
	LinkedListItem item = list->first;
	size_t index = 0;
	while(item != NULL) {
		f(item->content);
		if (index < list->size - 1){
			wprintf(L",");
			if (indent) wprintf(L"\n\t");
			else wprintf(L" ");
		}
		item = item->next;
		index++;
	}
	wprintf(L"\n]\n");
}

