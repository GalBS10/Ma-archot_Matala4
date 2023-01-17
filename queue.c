#include <stdio.h>
#include "graph.h"
#include "nodes.h"
#include <stdlib.h>
#include "queue.h"


pnode pop(ppq* Pqueue){
	ppq popped = *Pqueue;
	pnode node = (*Pqueue)->node;
	(*Pqueue) = (*Pqueue)->next;
	free(popped);
	return node;
}


void push(ppq* Pqueue, pnode node, int priority){
	ppq head_of_q = (*Pqueue);
	ppq new_node = (priority_queue*)malloc(sizeof(priority_queue));
	new_node->node = node;
	new_node->priority = priority;
	new_node->next = NULL;
	if (*Pqueue==NULL){
		(*Pqueue) = new_node;
		return;
	}
	if ((*Pqueue)->priority < priority) {
		new_node->next = *Pqueue;
		(*Pqueue) = new_node;
	}
	else {

		while (head_of_q->next != NULL){
			
			if(head_of_q->next->priority < priority){break;}

			head_of_q = head_of_q->next;

			}

		new_node->next = head_of_q->next;
		head_of_q->next = new_node;
	}
}