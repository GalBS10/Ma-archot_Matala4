
typedef struct priority_queue {
	int priority;
	struct priority_queue* next;
	pnode node;
} priority_queue,*ppq;

pnode pop(ppq* head);
void push(ppq* head, pnode d, int p);
