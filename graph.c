#include <stdio.h>
#include "graph.h"
#include "nodes.h"
#include <stdlib.h>

////////side_functions//////////
void add_node_V(pnode node, pnode add){
    pnode tmp1 = node;
    while(tmp1->next!=NULL){
        tmp1 = tmp1->next;
    }
    tmp1->next = add;
}

pnode search_node( pnode Node,int value){
while (Node!=NULL){
    if (Node->node_num == value){
        return Node;
    }
    Node = Node->next;
}
return NULL;
}

////////////////////////////////////

void build_graph_cmd(pnode *head){
    int what_node;
    pedge prev = NULL;
    pnode dest = NULL;

    scanf("%d", &what_node);
    pnode here = *head;
    while((here!=NULL))
    {
        if(here->node_num == what_node){
            break;
        }
        here = here->next;
    }
    while(scanf("%d", &what_node)==1){
        dest = *head;
    while(dest!=NULL)
    {
        if(dest->node_num == what_node){
            break;
        }
        dest = dest->next;
    }
        int weight;
        scanf("%d", &weight);
        pedge tmp_node = (pedge)malloc(sizeof(edge));
        tmp_node->weight = weight;
        tmp_node->endpoint = dest;
        tmp_node->next = prev;
        prev = tmp_node;
    }
    here->edges = prev;
}


void insert_node_cmd(pnode *head){
    int what_node;
    scanf("%d", &what_node);
    pnode add_node = search_node(*head, what_node);
    if (*head == NULL){
        pnode node_t = (pnode)malloc(sizeof(node));
        node_t->edges = NULL;
        node_t->node_num = what_node;
        node_t->next = NULL;
        *head = node_t;
        add_node = *head;
    }
    else if(add_node != NULL){
        delete_all_edges(add_node);
    }
    else{
        pnode *temp = head;
        while ((*temp)->next!=NULL)
        {
            if((*temp)->node_num< what_node && (*temp)->next->node_num> what_node){
                pnode temp2 = (pnode) malloc(sizeof(node));
                temp2->edges = NULL;
                temp2->next=(*temp)->next;
                temp2->node_num = what_node;
                (*temp)->next = temp2;
                return ;
            }
            temp=&((*temp)->next);
        }
        pnode ans = (pnode) malloc(sizeof(node));
        ans->edges = NULL;
        ans->next = (*temp)->next;
        ans->node_num = what_node;
        (*temp)->next = ans;
        add_node = ans;
    }
    pedge prev = NULL;
    int where_to=0;
    int weight =0;
    while(scanf("%d", &where_to)==1){
        pnode dest = search_node(*head,where_to);
        pedge tmp_node = (pedge)malloc(sizeof(edge));
        scanf("%d", &weight);
        tmp_node->weight = weight;
        tmp_node->endpoint = dest;
        tmp_node->next = prev;
        prev = tmp_node;
    }
    add_node->edges = prev;
}


void delete_node_cmd(pnode *head){
    int what_node;
    scanf("%d", &what_node);
    pnode before_delete = search_node(*head,what_node-1);
    pnode delete =search_node(*head,what_node);
    before_delete->next = delete->next;
    pnode runnig_node = *head;
    while(runnig_node!=NULL){
        delete_edge(what_node, runnig_node);
        runnig_node = runnig_node->next;
    }
    delete_all_edges(delete);
    free(delete);
}
