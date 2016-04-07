/*NAME AND DATE GOES HERE.*/
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
typedef struct adjnode {
	int edgeNumber;
	int from;
	int to;
	int length;
	struct adjnode *next;
} adj;
typedef adj *node;
node new_node(int en, int fr, int t, int leg) {
	node temp;
	temp = (node) malloc(sizeof(adj));
	if (temp == NULL) {
		printf("Malloc for a new position failed.");
		exit(1);
	}
	temp->edgeNumber = en;
	temp->from = fr;
	temp->to = t;
	temp->length = leg;
	temp->next = NULL;
	return temp;
}
node AdjList[MaxVertex];
void insertEdge(int i, int fr, int t, int leg) {
	node n = new_node(i, fr, t, leg);
	if (AdjList[fr] == NULL) {
		AdjList[fr] = n;
	} else {
		node temp = AdjList[fr];
		AdjList[fr] = n;
		n->next = temp;
	}
}
void constructAdjList() {
	int i;
	for (i = 0; i < nE; i++) {
		insertEdge(i, Estart[i], Eend[i], Elength[i]);
	}
}
/***************************************************************************************/
/*HEAP DATA STRUCTURE                                                                  */
/***************************************************************************************/
int heapDataNumber = 0;
node heap[MaxEdge];
void insertHeap(node n) {
	int weight = n->length;
	int parentPos;
	int currentLoc = heapDataNumber;
	heapDataNumber++;
	while (currentLoc > 0) {
		parentPos = (currentLoc - 1) / 2;
		if (heap[parentPos]->length < weight) {
			heap[currentLoc] = n;
			break;
		}
		heap[currentLoc] = heap[parentPos];
		currentLoc = parentPos;
	}
	if (currentLoc <= 0) {
		heap[0] = n;
	}
}
void percDown(int i) {
	int parent = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if ((right >= heapDataNumber) && (left >= heapDataNumber)) {
		return;
	} else if (right >= heapDataNumber) {
		i = left;
	} else {
		if (heap[left]->length <= heap[right]->length) {
			i = left;
		} else {
			i = right;
		}
	}
	if (heap[parent]->length > heap[i]->length) {
		node temp = heap[parent];
		heap[parent] = heap[i];
		heap[i] = temp;
		percDown(i);
	}
}
node deleteMin() {
	node min = heap[0];
	heapDataNumber--;
	heap[0] = heap[heapDataNumber];
	if (heapDataNumber > 0) {
		percDown(0);
	} else {
		heap[0] = NULL;
	}
	return min;
}

/***************************************************************************************/
/*Dijkstra Algorithm                                                                   */
/*DijkstraFlag=1 to supress output when Dijkstra is called from tour code.)            */
/***************************************************************************************/

void Dijkstra(int DijkstraFlag) {
	if (DijkstraFlag == 0){
		return;
	}else{
		constructAdjList();
		int marked[nV];
		int i;
		for(i = 0; i < nV; i++){
			marked[i] = -1;
		}
		int unmarked = nV-1;
		marked[Begin] = 1;
		while(unmarked > 0){
			
		}
		
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
	int i;
	/*constructAdjList();
	 for (i = 0; i < nV; i++) {
	 node temp = AdjList[i];
	 printf("current location: %d, ", i);
	 while(temp!=NULL){
	 printf("adjEdgeNumber: %d. ", temp->edgeNumber);
	 temp = temp->next;
	 }
	 printf(" end \n");
	 }*/
	/*node next = AdjList[8];
	int c = 0;
	while(next != NULL){
		insertHeap(next);
		next = next->next;
		c++;
	}
	while(heapDataNumber!=0){
		node n = deleteMin();
		printf("deleted weight: %d. ", n->length);
	}*/

	while (GetRequest()) {
		RouteOpen();
		TourFlag ? Tour() : Dijkstra(0);
		RouteClose();
	}
	return (0);
}



int i;
for(i = 0; i<10; i++){
    totalCost[i] = rand()/1000000;
}
int j;
for(j = 0; j<10; j++){
    insertHeap(AdjList[j]);
}
int k;
for(k = 0; k<9; k++){
    printf("current position %d, totalCost %d. from\n", k, totalCost[heap[k]->from]);
}
int x;
for(x = 0; x<9; x++){
    node n = deleteMin();
    printf("%d\n", totalCost[n->from]);
}

constructAdjList();

	totalCost[0] = 101;
	totalCost[1] = 470;
	totalCost[2] = 282;
	totalCost[3] = 1458;
	totalCost[4] = 1144;
	totalCost[5] = 984;
	totalCost[6] = 1457;
	totalCost[7] = 1622;
	totalCost[8] = 2007;
	totalCost[9] = 9867;
	int j;
	for (j = 0; j < 10; j++) {
		insertHeap(AdjList[j]);
	}
	int k;
	for (k = 0; k < 9; k++) {
		printf("current position %d, totalCost %d. from%d\n", k,
				totalCost[heap[k]->from], heap[k]->from);
	}
	delete(heap[0]);
	for (k = 0; k < 8; k++) {
		printf("current position %d, totalCost %d. from\n", k,
				totalCost[heap[k]->from]);
	}

current vertex: 0,  end 
current vertex: 1, adjEdgeNumber: 12. adjEdgeNumber: 8. adjEdgeNumber: 4. adjEdgeNumber: 0.  end 
current vertex: 2, adjEdgeNumber: 14. adjEdgeNumber: 11. adjEdgeNumber: 6. adjEdgeNumber: 1.  end 
current vertex: 3, adjEdgeNumber: 16. adjEdgeNumber: 10. adjEdgeNumber: 5. adjEdgeNumber: 2.  end 
current vertex: 4, adjEdgeNumber: 18. adjEdgeNumber: 9. adjEdgeNumber: 7. adjEdgeNumber: 3.  end 
current vertex: 5, adjEdgeNumber: 58. adjEdgeNumber: 56. adjEdgeNumber: 13.  end 
current vertex: 6, adjEdgeNumber: 64. adjEdgeNumber: 62. adjEdgeNumber: 60. adjEdgeNumber: 59.  end 
current vertex: 7, adjEdgeNumber: 66. adjEdgeNumber: 63.  end 
current vertex: 8, adjEdgeNumber: 100. adjEdgeNumber: 98. adjEdgeNumber: 72. adjEdgeNumber: 70. adjEdgeNumber: 68. adjEdgeNumber: 39.  end 
current vertex: 9, adjEdgeNumber: 399. adjEdgeNumber: 76. adjEdgeNumber: 74. adjEdgeNumber: 41.  end 
current vertex: 10, adjEdgeNumber: 401. adjEdgeNumber: 78. adjEdgeNumber: 77.  end 
current vertex: 11, adjEdgeNumber: 572. adjEdgeNumber: 404. adjEdgeNumber: 402. adjEdgeNumber: 400. adjEdgeNumber: 398. adjEdgeNumber: 396.  end 
current vertex: 12, adjEdgeNumber: 408. adjEdgeNumber: 406. adjEdgeNumber: 403.  end 
current vertex: 13, adjEdgeNumber: 573. adjEdgeNumber: 418. adjEdgeNumber: 416. adjEdgeNumber: 414. adjEdgeNumber: 412. adjEdgeNumber: 410. adjEdgeNumber: 407.  end 
current vertex: 14, adjEdgeNumber: 576. adjEdgeNumber: 574. adjEdgeNumber: 422. adjEdgeNumber: 420. adjEdgeNumber: 411.  end 
current vertex: 15, adjEdgeNumber: 585. adjEdgeNumber: 578. adjEdgeNumber: 424. adjEdgeNumber: 421. adjEdgeNumber: 413.  end 
current vertex: 16, adjEdgeNumber: 583. adjEdgeNumber: 579. adjEdgeNumber: 426.  end 
current vertex: 17, adjEdgeNumber: 430. adjEdgeNumber: 428. adjEdgeNumber: 427. adjEdgeNumber: 425. adjEdgeNumber: 415.  end 
current vertex: 18, adjEdgeNumber: 581. adjEdgeNumber: 483. adjEdgeNumber: 432.  end 
current vertex: 19, adjEdgeNumber: 485. adjEdgeNumber: 438. adjEdgeNumber: 436. adjEdgeNumber: 434. adjEdgeNumber: 433.  end 
current vertex: 20, adjEdgeNumber: 442. adjEdgeNumber: 440. adjEdgeNumber: 435. adjEdgeNumber: 429.  end 
current vertex: 21, adjEdgeNumber: 444. adjEdgeNumber: 431. adjEdgeNumber: 409.  end 
current vertex: 22, adjEdgeNumber: 448. adjEdgeNumber: 446.  end 
current vertex: 23, adjEdgeNumber: 454. adjEdgeNumber: 452. adjEdgeNumber: 450.  end 
current vertex: 24, adjEdgeNumber: 458. adjEdgeNumber: 456. adjEdgeNumber: 451.  end 
current vertex: 25, adjEdgeNumber: 593. adjEdgeNumber: 462. adjEdgeNumber: 460. adjEdgeNumber: 457.  end 
current vertex: 26, adjEdgeNumber: 459. adjEdgeNumber: 360. adjEdgeNumber: 355. adjEdgeNumber: 328. adjEdgeNumber: 86. adjEdgeNumber: 84.  end 
current vertex: 27, adjEdgeNumber: 108. adjEdgeNumber: 106. adjEdgeNumber: 104. adjEdgeNumber: 102.  end 
current vertex: 28, adjEdgeNumber: 114. adjEdgeNumber: 112. adjEdgeNumber: 110.  end 
current vertex: 29, adjEdgeNumber: 463. adjEdgeNumber: 120. adjEdgeNumber: 116. adjEdgeNumber: 105.  end 
current vertex: 30, adjEdgeNumber: 122. adjEdgeNumber: 118. adjEdgeNumber: 69.  end 
current vertex: 31, adjEdgeNumber: 126. adjEdgeNumber: 124.  end 
current vertex: 32, adjEdgeNumber: 134. adjEdgeNumber: 132. adjEdgeNumber: 130. adjEdgeNumber: 128.  end 
current vertex: 33, adjEdgeNumber: 138. adjEdgeNumber: 136.  end 
current vertex: 34, adjEdgeNumber: 142. adjEdgeNumber: 140.  end 
current vertex: 35, adjEdgeNumber: 146. adjEdgeNumber: 144. adjEdgeNumber: 143.  end 
current vertex: 36, adjEdgeNumber: 150. adjEdgeNumber: 148. adjEdgeNumber: 147. adjEdgeNumber: 139.  end 
current vertex: 37, adjEdgeNumber: 151. adjEdgeNumber: 92.  end 
current vertex: 38, adjEdgeNumber: 20.  end 
current vertex: 39, adjEdgeNumber: 24. adjEdgeNumber: 22.  end 
current vertex: 40, adjEdgeNumber: 26. adjEdgeNumber: 25. adjEdgeNumber: 17.  end 
current vertex: 41, adjEdgeNumber: 82. adjEdgeNumber: 80.  end 
current vertex: 42, adjEdgeNumber: 577. adjEdgeNumber: 472. adjEdgeNumber: 466.  end 
current vertex: 43, adjEdgeNumber: 474. adjEdgeNumber: 468.  end 
current vertex: 44, adjEdgeNumber: 584. adjEdgeNumber: 582. adjEdgeNumber: 580. adjEdgeNumber: 476. adjEdgeNumber: 475. adjEdgeNumber: 473. adjEdgeNumber: 470.  end 
current vertex: 45, adjEdgeNumber: 488. adjEdgeNumber: 486. adjEdgeNumber: 484. adjEdgeNumber: 482. adjEdgeNumber: 480. adjEdgeNumber: 478. adjEdgeNumber: 477.  end 
current vertex: 46, adjEdgeNumber: 260. adjEdgeNumber: 258. adjEdgeNumber: 256. adjEdgeNumber: 254.  end 
current vertex: 47, adjEdgeNumber: 586. adjEdgeNumber: 257.  end 
current vertex: 48, adjEdgeNumber: 587. adjEdgeNumber: 259.  end 
current vertex: 49, adjEdgeNumber: 262. adjEdgeNumber: 261.  end 
current vertex: 50, adjEdgeNumber: 270. adjEdgeNumber: 268. adjEdgeNumber: 266. adjEdgeNumber: 264.  end 
current vertex: 51, adjEdgeNumber: 272. adjEdgeNumber: 267.  end 
current vertex: 52, adjEdgeNumber: 276. adjEdgeNumber: 274. adjEdgeNumber: 265.  end 
current vertex: 53, adjEdgeNumber: 588. adjEdgeNumber: 282. adjEdgeNumber: 280. adjEdgeNumber: 278. adjEdgeNumber: 277.  end 
current vertex: 54, adjEdgeNumber: 284. adjEdgeNumber: 281.  end 
current vertex: 55, adjEdgeNumber: 288. adjEdgeNumber: 286.  end 
current vertex: 56, adjEdgeNumber: 294. adjEdgeNumber: 292. adjEdgeNumber: 290.  end 
current vertex: 57, adjEdgeNumber: 298. adjEdgeNumber: 296. adjEdgeNumber: 293. adjEdgeNumber: 283.  end 
current vertex: 58, adjEdgeNumber: 302. adjEdgeNumber: 300. adjEdgeNumber: 299. adjEdgeNumber: 15.  end 
current vertex: 59, adjEdgeNumber: 306. adjEdgeNumber: 304. adjEdgeNumber: 301.  end 
current vertex: 60, adjEdgeNumber: 310. adjEdgeNumber: 308. adjEdgeNumber: 295.  end 
current vertex: 61, adjEdgeNumber: 560. adjEdgeNumber: 558. adjEdgeNumber: 556. adjEdgeNumber: 554.  end 
current vertex: 62, adjEdgeNumber: 494. adjEdgeNumber: 492. adjEdgeNumber: 490.  end 
current vertex: 63, adjEdgeNumber: 498. adjEdgeNumber: 496. adjEdgeNumber: 491. adjEdgeNumber: 487.  end 
current vertex: 64, adjEdgeNumber: 502. adjEdgeNumber: 500. adjEdgeNumber: 497. adjEdgeNumber: 495.  end 
current vertex: 65, adjEdgeNumber: 508. adjEdgeNumber: 506. adjEdgeNumber: 504.  end 
current vertex: 66, adjEdgeNumber: 514. adjEdgeNumber: 512. adjEdgeNumber: 510. adjEdgeNumber: 507. adjEdgeNumber: 489.  end 
current vertex: 67, adjEdgeNumber: 518. adjEdgeNumber: 516. adjEdgeNumber: 513.  end 
current vertex: 68, adjEdgeNumber: 524. adjEdgeNumber: 522. adjEdgeNumber: 520. adjEdgeNumber: 519. adjEdgeNumber: 515.  end 
current vertex: 69, adjEdgeNumber: 528. adjEdgeNumber: 526. adjEdgeNumber: 509.  end 
current vertex: 70, adjEdgeNumber: 530. adjEdgeNumber: 527. adjEdgeNumber: 523.  end 
current vertex: 71, adjEdgeNumber: 532. adjEdgeNumber: 525.  end 
current vertex: 72, adjEdgeNumber: 536. adjEdgeNumber: 534. adjEdgeNumber: 533.  end 
current vertex: 73, adjEdgeNumber: 540. adjEdgeNumber: 538. adjEdgeNumber: 537.  end 
current vertex: 74, adjEdgeNumber: 544. adjEdgeNumber: 542. adjEdgeNumber: 541.  end 
current vertex: 75, adjEdgeNumber: 548. adjEdgeNumber: 546. adjEdgeNumber: 545.  end 
current vertex: 76, adjEdgeNumber: 564. adjEdgeNumber: 562. adjEdgeNumber: 559.  end 
current vertex: 77, adjEdgeNumber: 566. adjEdgeNumber: 565. adjEdgeNumber: 561.  end 
current vertex: 78, adjEdgeNumber: 570. adjEdgeNumber: 568. adjEdgeNumber: 567.  end 
current vertex: 79, adjEdgeNumber: 571. adjEdgeNumber: 550.  end 
current vertex: 80, adjEdgeNumber: 246. adjEdgeNumber: 244. adjEdgeNumber: 242. adjEdgeNumber: 240. adjEdgeNumber: 238.  end 
current vertex: 81, adjEdgeNumber: 248. adjEdgeNumber: 241.  end 
current vertex: 82, adjEdgeNumber: 250. adjEdgeNumber: 249. adjEdgeNumber: 243.  end 
current vertex: 83, adjEdgeNumber: 251. adjEdgeNumber: 245.  end 
current vertex: 84, adjEdgeNumber: 222.  end 
current vertex: 85, adjEdgeNumber: 590. adjEdgeNumber: 224. adjEdgeNumber: 223.  end 
current vertex: 86, adjEdgeNumber: 230. adjEdgeNumber: 228. adjEdgeNumber: 226.  end 
current vertex: 87, adjEdgeNumber: 591. adjEdgeNumber: 232.  end 
current vertex: 88, adjEdgeNumber: 156. adjEdgeNumber: 154.  end 
current vertex: 89, adjEdgeNumber: 160. adjEdgeNumber: 158. adjEdgeNumber: 155.  end 
current vertex: 90, adjEdgeNumber: 164. adjEdgeNumber: 162. adjEdgeNumber: 159. adjEdgeNumber: 157.  end 
current vertex: 91, adjEdgeNumber: 168. adjEdgeNumber: 166. adjEdgeNumber: 89. adjEdgeNumber: 87.  end 
current vertex: 92, adjEdgeNumber: 178. adjEdgeNumber: 176. adjEdgeNumber: 174. adjEdgeNumber: 170.  end 
current vertex: 93, adjEdgeNumber: 172. adjEdgeNumber: 171. adjEdgeNumber: 163.  end 
current vertex: 94, adjEdgeNumber: 182. adjEdgeNumber: 180. adjEdgeNumber: 175.  end 
current vertex: 95, adjEdgeNumber: 186. adjEdgeNumber: 184.  end 
current vertex: 96, adjEdgeNumber: 595. adjEdgeNumber: 190. adjEdgeNumber: 188. adjEdgeNumber: 177.  end 
current vertex: 97, adjEdgeNumber: 194. adjEdgeNumber: 192. adjEdgeNumber: 191. adjEdgeNumber: 19.  end 
current vertex: 98, adjEdgeNumber: 202. adjEdgeNumber: 200. adjEdgeNumber: 198. adjEdgeNumber: 196. adjEdgeNumber: 193.  end 
current vertex: 99, adjEdgeNumber: 206. adjEdgeNumber: 204.  end 
current vertex: 100, adjEdgeNumber: 61. adjEdgeNumber: 57. adjEdgeNumber: 30. adjEdgeNumber: 28.  end 
current vertex: 101, adjEdgeNumber: 47. adjEdgeNumber: 32.  end 
current vertex: 102, adjEdgeNumber: 34. adjEdgeNumber: 27. adjEdgeNumber: 23. adjEdgeNumber: 21.  end 
current vertex: 103, adjEdgeNumber: 67. adjEdgeNumber: 65. adjEdgeNumber: 40. adjEdgeNumber: 38. adjEdgeNumber: 36.  end 
current vertex: 104, adjEdgeNumber: 149. adjEdgeNumber: 145. adjEdgeNumber: 141. adjEdgeNumber: 137. adjEdgeNumber: 129. adjEdgeNumber: 125. adjEdgeNumber: 119. adjEdgeNumber: 99. adjEdgeNumber: 94. adjEdgeNumber: 42.  end 
current vertex: 105, adjEdgeNumber: 93. adjEdgeNumber: 48. adjEdgeNumber: 46. adjEdgeNumber: 44. adjEdgeNumber: 35.  end 
current vertex: 106, adjEdgeNumber: 131. adjEdgeNumber: 127. adjEdgeNumber: 123. adjEdgeNumber: 117. adjEdgeNumber: 111. adjEdgeNumber: 96. adjEdgeNumber: 95.  end 
current vertex: 107, adjEdgeNumber: 133. adjEdgeNumber: 81. adjEdgeNumber: 50. adjEdgeNumber: 49.  end 
current vertex: 108, adjEdgeNumber: 397. adjEdgeNumber: 350. adjEdgeNumber: 349. adjEdgeNumber: 79. adjEdgeNumber: 75. adjEdgeNumber: 71. adjEdgeNumber: 52. adjEdgeNumber: 37.  end 
current vertex: 109, adjEdgeNumber: 356. adjEdgeNumber: 352. adjEdgeNumber: 351. adjEdgeNumber: 113. adjEdgeNumber: 101. adjEdgeNumber: 54.  end 
current vertex: 110, adjEdgeNumber: 461. adjEdgeNumber: 358. adjEdgeNumber: 354. adjEdgeNumber: 353. adjEdgeNumber: 152. adjEdgeNumber: 135. adjEdgeNumber: 103. adjEdgeNumber: 97.  end 
current vertex: 111, adjEdgeNumber: 88. adjEdgeNumber: 85. adjEdgeNumber: 83. adjEdgeNumber: 51.  end 
current vertex: 112, adjEdgeNumber: 464. adjEdgeNumber: 423. adjEdgeNumber: 417. adjEdgeNumber: 405. adjEdgeNumber: 348. adjEdgeNumber: 347.  end 
current vertex: 113, adjEdgeNumber: 592. adjEdgeNumber: 453. adjEdgeNumber: 449. adjEdgeNumber: 445. adjEdgeNumber: 441. adjEdgeNumber: 364. adjEdgeNumber: 362. adjEdgeNumber: 359. adjEdgeNumber: 357.  end 
current vertex: 114, adjEdgeNumber: 369. adjEdgeNumber: 366. adjEdgeNumber: 361.  end 
current vertex: 115, adjEdgeNumber: 575. adjEdgeNumber: 471. adjEdgeNumber: 469. adjEdgeNumber: 467. adjEdgeNumber: 346. adjEdgeNumber: 345. adjEdgeNumber: 327.  end 
current vertex: 116, adjEdgeNumber: 517. adjEdgeNumber: 479. adjEdgeNumber: 447. adjEdgeNumber: 443. adjEdgeNumber: 439. adjEdgeNumber: 375. adjEdgeNumber: 371. adjEdgeNumber: 363.  end 
current vertex: 117, adjEdgeNumber: 535. adjEdgeNumber: 521. adjEdgeNumber: 455. adjEdgeNumber: 370. adjEdgeNumber: 368. adjEdgeNumber: 365.  end 
current vertex: 118, adjEdgeNumber: 552. adjEdgeNumber: 547. adjEdgeNumber: 394. adjEdgeNumber: 392. adjEdgeNumber: 391.  end 
current vertex: 119, adjEdgeNumber: 511. adjEdgeNumber: 505. adjEdgeNumber: 501. adjEdgeNumber: 499. adjEdgeNumber: 481. adjEdgeNumber: 437. adjEdgeNumber: 374. adjEdgeNumber: 372.  end 
current vertex: 120, adjEdgeNumber: 563. adjEdgeNumber: 503. adjEdgeNumber: 493. adjEdgeNumber: 378. adjEdgeNumber: 376. adjEdgeNumber: 373.  end 
current vertex: 121, adjEdgeNumber: 549. adjEdgeNumber: 393. adjEdgeNumber: 382. adjEdgeNumber: 380. adjEdgeNumber: 367. adjEdgeNumber: 330. adjEdgeNumber: 329. adjEdgeNumber: 227. adjEdgeNumber: 161.  end 
current vertex: 122, adjEdgeNumber: 384. adjEdgeNumber: 332. adjEdgeNumber: 331. adjEdgeNumber: 252. adjEdgeNumber: 247. adjEdgeNumber: 234. adjEdgeNumber: 229.  end 
current vertex: 123, adjEdgeNumber: 235. adjEdgeNumber: 233. adjEdgeNumber: 225. adjEdgeNumber: 216. adjEdgeNumber: 214. adjEdgeNumber: 183. adjEdgeNumber: 167.  end 
current vertex: 124, adjEdgeNumber: 210. adjEdgeNumber: 208. adjEdgeNumber: 197. adjEdgeNumber: 179. adjEdgeNumber: 173. adjEdgeNumber: 169. adjEdgeNumber: 165.  end 
current vertex: 125, adjEdgeNumber: 594. adjEdgeNumber: 212. adjEdgeNumber: 211. adjEdgeNumber: 199. adjEdgeNumber: 195.  end 
current vertex: 126, adjEdgeNumber: 314. adjEdgeNumber: 312. adjEdgeNumber: 287. adjEdgeNumber: 285. adjEdgeNumber: 279. adjEdgeNumber: 275. adjEdgeNumber: 273. adjEdgeNumber: 269.  end 
current vertex: 127, adjEdgeNumber: 344. adjEdgeNumber: 343. adjEdgeNumber: 316. adjEdgeNumber: 313. adjEdgeNumber: 271.  end 
current vertex: 128, adjEdgeNumber: 377. adjEdgeNumber: 342. adjEdgeNumber: 341. adjEdgeNumber: 289.  end 
current vertex: 129, adjEdgeNumber: 318. adjEdgeNumber: 305. adjEdgeNumber: 303. adjEdgeNumber: 297. adjEdgeNumber: 291.  end 
current vertex: 130, adjEdgeNumber: 555. adjEdgeNumber: 340. adjEdgeNumber: 339. adjEdgeNumber: 325.  end 
current vertex: 131, adjEdgeNumber: 322. adjEdgeNumber: 320. adjEdgeNumber: 319. adjEdgeNumber: 311. adjEdgeNumber: 307.  end 
current vertex: 132, adjEdgeNumber: 557. adjEdgeNumber: 386. adjEdgeNumber: 338. adjEdgeNumber: 337. adjEdgeNumber: 321.  end 
current vertex: 133, adjEdgeNumber: 569. adjEdgeNumber: 551. adjEdgeNumber: 390. adjEdgeNumber: 388. adjEdgeNumber: 387. adjEdgeNumber: 379.  end 
current vertex: 134, adjEdgeNumber: 389. adjEdgeNumber: 336. adjEdgeNumber: 335. adjEdgeNumber: 323.  end 
current vertex: 135, adjEdgeNumber: 589. adjEdgeNumber: 334. adjEdgeNumber: 333. adjEdgeNumber: 239.  end 
current vertex: 136, adjEdgeNumber: 90. adjEdgeNumber: 33. adjEdgeNumber: 29.  end 
current vertex: 137, adjEdgeNumber: 91. adjEdgeNumber: 73. adjEdgeNumber: 55. adjEdgeNumber: 43. adjEdgeNumber: 31.  end 
current vertex: 138, adjEdgeNumber: 45.  end 
current vertex: 139, adjEdgeNumber: 465. adjEdgeNumber: 419. adjEdgeNumber: 53.  end 
current vertex: 140, adjEdgeNumber: 326. adjEdgeNumber: 317. adjEdgeNumber: 315. adjEdgeNumber: 263. adjEdgeNumber: 255.  end 
current vertex: 141, adjEdgeNumber: 253. adjEdgeNumber: 237.  end 
current vertex: 142, adjEdgeNumber: 218. adjEdgeNumber: 209. adjEdgeNumber: 205. adjEdgeNumber: 203.  end 
current vertex: 143, adjEdgeNumber: 543. adjEdgeNumber: 539. adjEdgeNumber: 531. adjEdgeNumber: 529. adjEdgeNumber: 395. adjEdgeNumber: 381.  end 
current vertex: 144, adjEdgeNumber: 220. adjEdgeNumber: 213. adjEdgeNumber: 189. adjEdgeNumber: 187.  end 
current vertex: 145, adjEdgeNumber: 553. adjEdgeNumber: 385. adjEdgeNumber: 383. adjEdgeNumber: 236. adjEdgeNumber: 231.  end 
current vertex: 146, adjEdgeNumber: 221. adjEdgeNumber: 215. adjEdgeNumber: 185. adjEdgeNumber: 181.  end 
current vertex: 147, adjEdgeNumber: 219. adjEdgeNumber: 207. adjEdgeNumber: 201.  end 
current vertex: 148, adjEdgeNumber: 121. adjEdgeNumber: 115. adjEdgeNumber: 107.  end 
current vertex: 149, adjEdgeNumber: 153. adjEdgeNumber: 109.  end 
current vertex: 150, adjEdgeNumber: 324. adjEdgeNumber: 309.  end 
current vertex: 151, adjEdgeNumber: 217.  end 



