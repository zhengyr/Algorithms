/*Yiran Zheng 12/13/15*/
/*Brandeis Map - Tour .h file*/
/*For Part2, I only use the minimum spanning tree and then traverse the whole tree using DFS to find a tour*/
/*For the second part of Part2, I have some ideas and only work out part of it: */
/* As said in class, there is the triangle unwquality and I perform it in my spanning tree*/
/* however, only the part when the current edge lead to a leaf vertex works.
the other part when the current edge's sibling lead to a lead vertex doesn't work*/
/*To see the result, see the end of the code and use the commented code
The whole path is only a little bit shorter than the minimimum spanning tree algorithm*/
/*For further shotcut, I have some ideas using All Pairs Minimum Pair path.
Suppose that in the all pairs minimum pair path table, each element in the table contains the path from vertex i to vertex j
As we walk through our minimum spanning tree, each time we mark a new vertex, we would check if there is a shorter
path from visited vertex to our new vertex based on the table, then we would check if the shorter path contains all vertices
that are in our old minimum spanning tree path. If yes, then we would replace old path with the shorter one. 
I feel like this should work but I don't really know how exactly I could construct a table where each element is a path so I did not
write it*/
node ResultEdgeSet[MaxEdge];
int EdgeSetNum;
int marked[MaxVertex];
node newAdj[MaxVertex];
void consructNewAdj(){/*construct a minimum spanning tree*/
	int i;
	for (i = 0; i < MaxVertex; i++){
		newAdj[i] = NULL;
	}
	for (i = 0; i < MaxEdge; i++){
		if (ResultEdgeSet[i] != NULL){
			node n = ResultEdgeSet[i];
			if (newAdj[ResultEdgeSet[i]->from] != NULL){
				node temp = newAdj[ResultEdgeSet[i]->from];
				temp->prevsib = n;
				newAdj[ResultEdgeSet[i]->from] = n;
				n->rsib = temp;
			}
			else{
				newAdj[ResultEdgeSet[i]->from] = n;
			}
		}
	}
}
void tourOutput(int beg){/*output the result*/
	node adj = newAdj[beg];
	if (marked[beg] != 0){
		marked[beg] = 0;
		while (adj != NULL){
			if (marked[adj->to] != 0){
				PrintLeg(adj->edgeNumber);
				tourOutput(adj->to);
				PrintLeg(ReverseEdge(adj->edgeNumber));
			}
			adj = adj->rsib;
		}
	}
}
/*checking if we could perform a short cut here if node n's sib is a leaf*/
node checkShortcut(node n){
	node sib = n->rsib;
	if ((newAdj[n->to] == NULL) &&
		(sib != NULL)){
		node temp = AdjList[n->to];
		while (temp != NULL){
			if (temp->to == sib->to){
				break;
			}
			temp = temp->next;
		}
		if (temp == NULL){
			return NULL;
		}
		/*(newAdj[temp->to] == NULL) &&*/
		if (EdgeCost(n->edgeNumber) + EdgeCost(sib->edgeNumber) > EdgeCost(temp->edgeNumber)){
			n->rsib = sib->rsib;
			PrintLeg(temp->edgeNumber);
			return sib;
		}
	}
	return NULL;
}
/*this is checking if node n's previous sibling is a leaf and if we could perform a short cut. 
node checkShortcut2(node n){
	node sib = n->prevsib;
	if ((newAdj[n->to] == NULL) &&
		(sib != NULL)){
		node temp = AdjList[n->to];
		while (temp != NULL){
			if (temp->to == sib->to){
				break;
			}
			temp = temp->next;
		}
		if (temp == NULL){
			return NULL;
		}
		if (EdgeCost(n->edgeNumber) + EdgeCost(sib->edgeNumber) > EdgeCost(temp->edgeNumber)){
			return temp;
		}
	}
	return NULL;
}*/
void tourOutput2(int beg){
	node adj = newAdj[beg];
	if (marked[beg] != 0){
		marked[beg] = 0;
		while (adj != NULL){
			if (marked[adj->to] != 0){
				PrintLeg(adj->edgeNumber);
				node check = checkShortcut(adj);/*checking if we could perform a shotcut here*/
				/*node check2 = NULL;
				if(adj->rsib != NULL){
					check2 = checkShortcut2(adj->rsib);
				}*/
				if (check == NULL /*&& check2 == NULL*/){
					tourOutput2(adj->to);
					PrintLeg(ReverseEdge(adj->edgeNumber));
				}/*if(check2 !=NULL){
					tourOutput2(adj->to);
					PrintLeg(ReverseEdge(check2->edgeNumber));
					node sib = adj->rsib;
					PrintLeg(ReverseEdge(sib->edgeNumber));
					adj->rsib = sib->rsib;
				}*/else{
					tourOutput2(check->to);
					PrintLeg(ReverseEdge(check->edgeNumber));
				}
			}
			adj = adj->rsib;
		}
	}
}

void Tour() {/*find the minimum spanning tree*/
	int c;
	for (c = 0; c < MaxEdge; c++){/*reset everything*/
		heap[c] = NULL;
		ResultEdgeSet[c] = NULL;
		AllEdges[c] = NULL;
	}
	for (c = 0; c < MaxVertex; c++){
		AdjList[c] = NULL;
		marked[c] = 0;
	}
	EdgeSetNum = 0;
	constructAdjList();
	int unmarkedVertex = nV;
	node start = AdjList[Begin];
	for (c = 0; c < 5; c++){/*take the fisrt five vertex off*/
		marked[c] = 1;
	}
	marked[Begin] = 1;
	unmarkedVertex--;
	while (start != NULL){/*insert adjancent edge of this vertex*/
		insertHeap(start);
		start = start->next;
	}
	while (unmarkedVertex > 1 && heapDataNumber != 0){/*start the algorithm*/
		node temp = deleteMin();
		int theUnMarkVertexNum;
		if (marked[temp->to] != 1){
			theUnMarkVertexNum = temp->to;
		}else{
			continue;
		}
		marked[theUnMarkVertexNum] = 1;
		unmarkedVertex--;
		ResultEdgeSet[temp->edgeNumber] = temp;
		node adj = AdjList[theUnMarkVertexNum];
		while (adj != NULL){
			if (marked[adj->to] != 1){
				insertHeap(AllEdges[adj->edgeNumber]);
			}
			adj = adj->next;
		}
	}
	if (unmarkedVertex > 0){ /*if the graph is not connected*/
		puts("ERROR: UNCONNECTED GRAPH"); 
	}
	consructNewAdj();
	/*take the first five vertex off*/
	for (c = 0; c < 5; c++){
		marked[c] = 0;
	}
	/*tourOutput2(Begin);*/
	/*to see the short version, use the above comment*/
	tourOutput(Begin);
}
