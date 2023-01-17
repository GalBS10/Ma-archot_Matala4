#include "stdlib.h"
#include "stdio.h"
#include "graph.h"
#include "nodes.h"


void delete_all_edges(pnode temp){
    pedge runner = temp->edges; 
    while(runner!=NULL){
        pedge delete = runner;
        runner = runner->next;
        free(delete);
    }
}

void delete_edge(int value, pnode Node){
    if(Node->edges!= NULL){
        pedge N_e = Node->edges;
        while(N_e->next != NULL){
            if (N_e->next->endpoint->node_num == value){
                pedge remove = N_e->next;
                N_e->next = remove->next;
                free(remove);
                return;
            }
            N_e = N_e->next;
        }
    }
}