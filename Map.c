/*Yiran Zheng 12/13/15*/
/*Brandeis Map*/

/*Standard system stuff - these are the ONLY ones that may be used.*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/*Path to the map folder; may need to change this.*/
#include "MapPATH.h"

/*MAY NOT be modified, but should be viewed.*/
#include "Map.h" /*Map data parameters, structures, and functions.*/

/*MAY NOT be modified, and there is no need view them:*/
#include "MapData.h"   /*Functions to input the map data.*/
#include "MapInput.h"  /*Functions to get user input.*/
#include "MapOutput.h" /*Functions to produce output.*/

/*Use this to get the time to travel along an edge.*/
#define EdgeCost(X) ( (TimeFlag) ? Time(X) : Elength[X] )

/*Use this to print a leg of a route or tour.*/
void PrintLeg(int edge);

/***************************************************************************************/
/*GRAPH ADJACENCY LIST DATA STRUCTURE                                                  */
/***************************************************************************************/
typedef struct adjnode {/*construct node that represent the edge of the graph*/
	int edgeNumber;
	int from;
	int to;
	int cost;
	int totalcost;
	struct adjnode *next;
	char *label;
	struct adjnode *rsib; /*This is for part2b*/
	struct adjnode *prevsib;
} adj;
typedef adj *node;

node new_node(int en, int fr, int t, int leg, char l[]) {/*initialize node*/
	node temp;
	temp = (node) malloc(sizeof(adj)+ sizeof(char)*MaxLabel);
	if (temp == NULL) {
		printf("Malloc for a new position failed.");
		exit(1);
	}
	temp->edgeNumber = en;
	temp->from = fr;
	temp->to = t;
	temp->cost = EdgeCost(en);
	temp->next = NULL;
	temp->label = l;
	temp->totalcost = ((TourFlag) ? temp->cost : InfiniteCost);
	temp->rsib = NULL;
	temp->prevsib = NULL;
	return temp;
}
node AdjList[MaxVertex];
node AllEdges[MaxEdge];
void insertEdge(int i, int fr, int t, int leg, char l[]) {/*insert edge into adjancent list*/
	node n = new_node(i, fr, t, leg, l);
	if (AdjList[fr] == NULL) {
		AdjList[fr] = n;
	} else {
		node temp = AdjList[fr];
		AdjList[fr] = n;
		n->next = temp;
	}
	AllEdges[i] = n;
	
}/*construct the adjancent list*/
void constructAdjList() {
	int i;
	for (i = 0; i < MaxEdge; i++) {
		insertEdge(i, Estart[i], Eend[i], Elength[i], Vlabel[Eend[i]]);
	}
}
/***************************************************************************************/
/*HEAP DATA STRUCTURE                                                                  */
/***************************************************************************************/
int heapDataNumber = 0;
node heap[MaxEdge];
void percUp(int i) {/*search up to find the right pisition*/
	if (i == 0) {
		return;
	}
	int parent = (i - 1) / 2;
	if (heap[parent]->totalcost > heap[i]->totalcost) {
		node temp = heap[parent];
		heap[parent] = heap[i];
		heap[i] = temp;
		percUp(parent);
	}
}
void insertHeap(node n) {/*insert into heap*/
	if (n == NULL) {
		return;
	}
	heap[heapDataNumber] = n;
	int i = heapDataNumber;
	heapDataNumber++;
	percUp(i);
}
void percDown(int i) {/*search down to find the right position*/
	int parent = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if ((right >= heapDataNumber) && (left >= heapDataNumber)) {
		return;
	} else if (right >= heapDataNumber) {
		i = left;
	} else {
		if (heap[left]->totalcost <= heap[right]->totalcost) {
			i = left;
		} else {
			i = right;
		}
	}
	if (heap[parent]->totalcost > heap[i]->totalcost) {
		node temp = heap[parent];
		heap[parent] = heap[i];
		heap[i] = temp;
		percDown(i);
	}
}
node deleteMin() {/*delete the minimum node in the heap*/
	if (heapDataNumber == 0) {
		return NULL;
	}
	node min = heap[0];
	heapDataNumber--;
	heap[0] = heap[heapDataNumber];
	heap[heapDataNumber] = NULL;
	if (heapDataNumber > 0) {
		percDown(0);
	} else {
		heap[0] = NULL;
	}
	return min;
}
int search(node n) {/*search the right position*/
	int en = n->edgeNumber;
	int j;
	for (j = 0; j < heapDataNumber; j++) {
		if (heap[j]->edgeNumber == en) {
			return j;
		}
	}
	return -1;
}
void delete(node n) {/*delete the node in the heap*/
	if (n == NULL) {
		return;
	}
	int position = search(n);
	if (position == -1) {
		return;
	}
	heapDataNumber--;
	if (heapDataNumber == position){
		heap[heapDataNumber] = NULL;
		return;
	}
	heap[position] = heap[heapDataNumber];
	heap[heapDataNumber] = NULL;
	if (heapDataNumber == 0 || heapDataNumber == 1) {
		return;
	}
	int parent = (position - 1) / 2;
    if (heap[position]->totalcost < heap[parent]->totalcost) {
        percUp(position);
	} else {
		percDown(position);
	}
    
}
/***************************************************************************************/
/*Dijkstra Algorithm                                                                   */
/*DijkstraFlag=1 to supress output when Dijkstra is called from tour code.)            */
/***************************************************************************************/
int path[MaxVertex];
void printResult(int i){/*recurisively print the result*/
	if(i == Begin){
		return;
	}else{
		int previous = path[i];
		printResult(previous);
		node edge = AdjList[previous];
		int edgeNum = -1;
		while(edge != NULL){
			if(edge->to == i){
				edgeNum = edge->edgeNumber;
				break;
			}
			edge = edge->next;
		}
		PrintLeg(edgeNum);
	}

}
void Dijkstra(int DijkstraFlag) {
	int a;
	for (a = 0; a < MaxVertex; a++){/*initialize everything*/
		AdjList[a] = NULL;
		heap[a] = NULL;
	}
	if (DijkstraFlag == 1) {
		return;
	} else {
		constructAdjList();/*construct the adjancent list*/
		int marked[MaxVertex];
		int i;
		for (i = 0; i < MaxVertex; i++) {/*insert vertex into heap and reset marked and path*/
			marked[i] = -1;
			path[i] = -1;
            if(AdjList[i]!=NULL){
                insertHeap(AdjList[i]);
            }
		}
		AdjList[Begin]->totalcost = 0;
		delete(AdjList[Begin]);
		insertHeap(AdjList[Begin]);
		int unmarked = nV;
		while (unmarked > 0) {/*start the algorithm*/
			node v = deleteMin();
            if(v==NULL){
                break;
            }
			if(marked[v->from]==-1){/*if the minimum node is not marked*/
                unmarked--;
                marked[v->from]= 1;
                while(v != NULL){/*add adjancent vertex*/
                    if(marked[v->to]==-1){
                        int calculatedcost = AdjList[v->from]->totalcost + v->cost;
                        if(AdjList[v->to]->totalcost > calculatedcost){
                            AdjList[v->to]->totalcost = calculatedcost;
                            delete(AdjList[v->to]);
                            insertHeap(AdjList[v->to]);
                            path[v->to] = v->from;
                        }
                    }
                    v = v->next;
                }
			}

		}
		printResult(Finish);/*print result*/
	}
}

/***************************************************************************************/
/*CAMPUS TOUR                                                                          */
/***************************************************************************************/
#include "Tour.h"

/***************************************************************************************/
/*MAIN PROGRAM (don't modify)                                                          */
/***************************************************************************************/
int main() {
	GetVertices();
	GetEdges();
	while (GetRequest()) {
		RouteOpen();
		TourFlag ? Tour() : Dijkstra(0);
		RouteClose();
	}
	return (0);
}
