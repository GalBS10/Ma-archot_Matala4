
typedef struct priority_queue {
	int priority;
	struct priority_queue* next;
	pnode node;
} priority_queue,*ppq;

pnode pop(ppq* head);
void push(ppq* head, pnode d, int p);


/*void tsp_branch_and_bound(int* cities, int visited, int n, int current_length, int current_city, int ans, pnode head) {
    int current_bound=0;
    if (visited == (1 << n) - 1) {
        int last_city = current_city;
        pnode last = search_node(head, cities[last_city]);
        pedge edge = last->edges;
        while (edge) {
            if (edge->endpoint->node_num == cities[0]) {
                if (current_length + edge->weight < ans) {
                    ans = current_length + edge->weight;
                }
                break;
            }
            edge = edge->next;
        }
        return;
    }
    for (int i = 0; i < n; i++) {
        if (!(visited & (1 << i))) {
            pnode here = search_node(head, cities[i]);
            pedge edge = here->edges;
            while (edge) {
                if (edge->endpoint->node_num == cities[current_city]) {
                    int new_length = current_length + edge->weight;
                    if (new_length + current_bound < ans) {
                        tsp_branch_and_bound(cities, visited | (1 << i), n, new_length, i, ans, head);
                    }
                    break;
                }
                edge = edge->next;
            }
        }
    }
}
void TSP_cmd(pnode head) {
    int j;
    scanf("%d", &j);
    int *cities = (int*)malloc(sizeof(int)*j);
    if (!cities) {
        return;
    }
    for (int i = 0; i < j; i++) {
        scanf("%d", &cities[i]);
    }
    numbering(head);
    int ans = INT_MAX;
    tsp_branch_and_bound(cities, 0, j, 0, 0, ans, head);
    if (ans != INT_MAX) {
        printf("TSP shortest path: %d\n", ans);
    } else {
        printf("TSP shortest path: -1\n");
    }
    free(cities);
}*/