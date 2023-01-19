#include <stdio.h>
#include "graph.h"
#include "nodes.h"
#include <stdlib.h>
#include "queue.h"
#include <limits.h>
#define infinity INT_MAX

////////side_functions//////////
void add_node_V(pnode node, pnode add){
    pnode tmp1 = node;
    while(tmp1->next!=NULL){
        tmp1 = tmp1->next;
    }
    tmp1->next = add;
}

pnode search_node( pnode Node,int value){
    pnode runner = Node;
    while (runner!=NULL){
        if (runner->node_num == value){
            return runner;
        }
        runner = runner->next;
    }
    return NULL;
}



void dijkstra_algo(int *arr,pnode from){
    ppq Pqueue = (priority_queue*)malloc(sizeof(priority_queue));
    if(!Pqueue){return ;}
	Pqueue->node = from;
	Pqueue->priority = 0;//lowest priority
	Pqueue->next = NULL;
    while (Pqueue!=NULL){
        from = pop(&Pqueue);
        pedge this = from->edges;
        while(this!=NULL){
            if (arr[from->new_numbering] + this->weight < arr[this->endpoint->new_numbering]){
                arr[this->endpoint->new_numbering] = arr[from->new_numbering] + this->weight;
                push(&Pqueue,this->endpoint,arr[this->endpoint->new_numbering]);
            }
            this= this->next;
        }
    }
}

////////////////////////////////////

/// @brief - This function gets input from the user and builds a graph by that definition.
/// @param head - The head of the vertex list 
void build_graph_cmd(pnode *head){
    int what_node;
    pedge prev = NULL;
    pnode dest = NULL;

    scanf("%d", &what_node);
    pnode here = *head;
    while((here!=NULL))//searching the node we want to add edges into.(main node)
    {
        if(here->node_num == what_node){
            break;
        }
        here = here->next;
    }
    while(scanf("%d", &what_node)==1){
        dest = *head;
    while(dest!=NULL)//searching the node we want to add an edge from.
    {
        if(dest->node_num == what_node){
            break;
        }
        dest = dest->next;
    }
        int weight;
        scanf("%d", &weight);
        pedge tmp_node = (pedge)malloc(sizeof(edge));
        if(!tmp_node){return ;}
        tmp_node->weight = weight;//initializing the node
        tmp_node->endpoint = dest;
        tmp_node->next = prev;
        prev = tmp_node;
    }
    here->edges = prev;//setting main_node->edges to the linkedlist we created.
}

/// @brief - This function create a new vertex if it's dont already exist with the node_num the user give.
///If the vertex is already exist, the function removes all of his edges.
/// @param head - The head of the vertex list
void insert_node_cmd(pnode *head){
    int what_node;
    scanf("%d", &what_node);
    pnode add_node = search_node(*head, what_node);
    if (*head == NULL){//checking if the head is not already exist.
        pnode node_t = (pnode)malloc(sizeof(node));
        if(!node_t){return ;}
        node_t->edges = NULL;
        node_t->node_num = what_node;
        node_t->next = NULL;
        *head = node_t;//now the head is the node we have just initialize
        add_node = *head;
    }
    else if(add_node != NULL){//if the node is already exist we delete all of his edges.
        delete_all_edges(add_node);
    }
    else{
        pnode *temp = head;
        while ((*temp)->next!=NULL)//ruuning on the vertex list.
        {
            if((*temp)->node_num< what_node && (*temp)->next->node_num> what_node){//we want to add the node in the right place.
                pnode temp2 = (pnode) malloc(sizeof(node));
                if(!temp2){return ;}
                temp2->edges = NULL;
                temp2->next=(*temp)->next;//initializing the node.
                temp2->node_num = what_node;
                (*temp)->next = temp2;
                return ;
            }
            temp=&((*temp)->next);
        }
        pnode ans = (pnode) malloc(sizeof(node));//if the node->node_num doesn't fit we will add him to the end of the list.
        if(!ans){return ;}
        ans->edges = NULL;
        ans->next = (*temp)->next;
        ans->node_num = what_node;//initializing the node.
        (*temp)->next = ans;
        add_node = ans;
    }
    pedge prev = NULL;
    int where_to=0;
    int weight =0;
    while(scanf("%d", &where_to)==1){//while we are getting int (this is what will make the function stop when we will get a 'n' etc.)
        pnode dest = search_node(*head,where_to);//the node we strech an edge to
        pedge tmp_node = (pedge)malloc(sizeof(edge));
        if(!tmp_node){return ;}
        scanf("%d", &weight);//the weight
        tmp_node->weight = weight;
        tmp_node->endpoint = dest;
        tmp_node->next = prev;
        prev = tmp_node;
    }
    add_node->edges = prev;
}

/// @brief  - This function removes a specific node from the vertex list.
/// @param head - The head of the list
void delete_node_cmd(pnode *head){
    int what_node;
    scanf("%d", &what_node);
    pnode before_delete = search_node(*head,what_node-1);//The node before the node we are looking for(because the vertex list is generated by connecting the node i to i+1)
    pnode delete =search_node(*head,what_node);//The node we want to delete
    before_delete->next = delete->next;//Connecting the vertex list without the node we wnat to delete.
    pnode runnig_node = *head;
    while(runnig_node!=NULL){//runnig on the vertex list and deleting all the edges that goes into "delete".
        delete_edge(what_node, runnig_node);
        runnig_node = runnig_node->next;
    }
    delete_all_edges(delete);
    free(delete);
}


/// @brief - While going through all of the vertex in the vertex linkedlist we deletes all of
///          it's edges and freeing their spaces in the memory.
/// @param head - The pointer to the vertex linkedlist.
void deleteGraph_cmd(pnode* head){
    pnode node = *head;//pointer to the head of the vertex linkedlist.
    pnode tmp = node;
    while(tmp!=NULL){
        node = tmp;
        delete_all_edges(tmp);
        tmp = tmp->next;
        free(node);
    }
}

/// @brief - Finding the shortest path from vertex a to b and then printing the weight of the path
/// @param head - The head of the vertex linkedlist.
void shortsPath_cmd(pnode head){
    int from;
    int where_to;
    scanf("%d", &from);//getting the vertex that we want to streach an edge from.
    scanf("%d", &where_to);//getting the vertex that we want to streach an edge to.
    pnode node_from;
    int numbering_where_to;
    node_from = search_node(head,from);
    numbering_where_to = search_node(head,where_to)->new_numbering;
    int j= numbering(head);//tha size of the vertex linkedlist.
    int *arr=(int*)malloc(sizeof(int)*j);//An array to keep the d[v] of each vertex by i = node->new_numbering.
    if(!arr){return ;}
    for (int i=0;i<j;i++){//by dijkstra algo first we need initialize d[v]=infinity to all of the vertexes.
        arr[i] = infinity;
    }
    arr[node_from->new_numbering] = 0;
    dijkstra_algo(arr, node_from);//Running the algorithm
    if (arr[numbering_where_to]!=infinity){//if there is a path
        printf("Dijsktra shortest path: %d \n", arr[numbering_where_to]);
    }
    else{
        printf("Dijsktra shortest path: -1 \n");
    }
    free(arr);
}

void TSP_cmd(pnode head){
    // Initialize the starting point
    int size_of_nodes = numbering(head);
    int ans = 100000;
    int cities[size_of_nodes];
    for (int i=0;i<size_of_nodes;i++){
        cities[i] = i;
    }
    permutation(cities,0,size_of_nodes-1,size_of_nodes,&ans,head);
    printf("the shortest path is: %d\n",ans);
}

void permutation(int* cities,int start,int end,int size_of_nodes, int* ans, pnode head){
    if (start == end){
        int sum = 0;
        for (int i=0;i<size_of_nodes-1;i++){
            pnode temp = head;
            while (temp!=NULL){
                if (temp->new_numbering == cities[i]){
                    pedge runner = temp->edges;
                    while(runner!=NULL){
                        if (runner->endpoint->new_numbering == cities[i+1]){
                            sum += runner->weight;
                            break;
                        }
                        runner = runner->next;
                    }
                }
                temp = temp->next;
            }
        }
        if (sum<*ans){
            *ans = sum;
        }
    }
    else {
        for (int i=start;i<=end;i++){
            swap(&cities[start],&cities[i]);
            permutation(cities,start+1,end,size_of_nodes,ans,head);
            swap(&cities[start],&cities[i]);
        }
    }
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(){
    char s;
    //int k;
    pnode head = NULL;
    int end_of_file = 0;
    while(end_of_file!=EOF){
        end_of_file = scanf("%c", &s);
        if (s == 'A'){
            int num_of_v =0;
            scanf("%d",&num_of_v);
            pnode head1 = (pnode) malloc(sizeof(node));
            head1->node_num = 0;
            head1->edges = NULL;
            head1->next = NULL;
            for(int i=1;i<num_of_v;i++){
                pnode tmp = (pnode) malloc(sizeof(node));
                tmp->node_num = i;
                tmp->edges = NULL;
                tmp->next = NULL;
                add_node_V(head1,tmp);
            }
            head = head1;
        }
        if (s == 'n'){
            build_graph_cmd(&head);
        }
        if (s == 'B'){
            insert_node_cmd(&head);
        }
        if (s=='D'){
            delete_node_cmd(&head);
        }
        if (s=='S'){
            shortsPath_cmd(head);
        }
        if (s=='T'){
            TSP_cmd(head);
        }
    }
    return 0;
}







/*

void printGraph_cmd(pnode head){
    while(head){
        printf("node id: %d\n", head->node_num);
        pedge here = head->edges;
        while(here){
            printf("%d -> %d   w: %d\n", head->node_num, here->endpoint->node_num, here->weight);
            here= here->next;
        }
        head = head->next;
    }
}

*/