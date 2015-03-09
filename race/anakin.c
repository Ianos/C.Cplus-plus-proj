#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int comp(const void*,const void*);
 
// A structure to represent a node in adjacency list
struct AdjListNode
{
   long long int dest;
   long long int weight;
    struct AdjListNode* next;
};
 
// A structure to represent an adjacency liat
struct AdjList
{
    struct AdjListNode *head;  // pointer to head node of list
};
 
// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph
{
    long long int V;
    struct AdjList* array;
};
 
// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(long long int dest,long long int weight)
{
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
 
// A utility function that creates a graph of V vertices
struct Graph* createGraph(long long int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
 
    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
     // Initialize each adjacency list as empty by making head as NULL
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
 
    return graph;
}
 
// Adds an edge to an undirected graph
void addEdge(struct Graph* graph,long long int src,long long int dest,long long int weight)
{
    // Add an edge from src to dest.  A new node is added to the adjacency
    // list of src.  The node is added at the begining
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
 
    // Since graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}
 
// Structure to represent a min heap node
struct MinHeapNode
{
   long long int  v;
   long long int dist;
};
 
// Structure to represent a min heap
struct MinHeap
{
    long long int size;      // Number of heap nodes present currently
    long long int capacity;  // Capacity of min heap
    long long int *pos;     // This is needed for decreaseKey()
    struct MinHeapNode **array;
};
 
// A utility function to create a new Min Heap Node
struct MinHeapNode* newMinHeapNode(long long int v,long long int dist)
{
    struct MinHeapNode* minHeapNode =
           (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}
 
// A utility function to create a Min Heap
struct MinHeap* createMinHeap(long long int capacity)
{
    struct MinHeap* minHeap =
         (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->pos = (long long int *)malloc(capacity * sizeof(long long int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
         (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}
 
// A utility function to swap two nodes of min heap. Needed for min heapify
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
 
// A standard function to heapify at given idx
// This function also updates position of nodes when they are swapped.
// Position is needed for decreaseKey()
void minHeapify(struct MinHeap* minHeap,long long int idx)
{
    long long int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < minHeap->size &&
        minHeap->array[left]->dist < minHeap->array[smallest]->dist )
      smallest = left;
 
    if (right < minHeap->size &&
        minHeap->array[right]->dist < minHeap->array[smallest]->dist )
      smallest = right;
 
    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode = minHeap->array[idx];
 
        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
 
        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
 
        minHeapify(minHeap, smallest);
    }
}
 
// A utility function to check if the given minHeap is ampty or not
long long int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}
 
// Standard function to extract minimum node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;
 
    // Store the root node
    struct MinHeapNode* root = minHeap->array[0];
 
    // Replace root node with last node
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
 
    // Update position of last node
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
 
    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return root;
}
 
// Function to decreasy dist value of a given vertex v. This function
// uses pos[] of min heap to get the current index of node in min heap
void decreaseKey(struct MinHeap* minHeap,long long int v,long long int dist)
{
    // Get the index of v in  heap array
    long long int i = minHeap->pos[v];
 
    // Get the node and update its dist value
    minHeap->array[i]->dist = dist;
 
    // Travel up while the complete tree is not hepified.
    // This is a O(Logn) loop
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);
 
        // move to parent index
        i = (i - 1) / 2;
    }
}
 
// A utility function to check if a given vertex
// 'v' is in min heap or not
bool isInMinHeap(struct MinHeap *minHeap,long long int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}
 
// A utility function used to print the solution
void printArr(long long int dist[],long long int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
 

int main()
{
    // create the graph given in above fugure
    long long int N,M,K,L,B,j,s,d,w,town,sum;
    struct Graph* graph = createGraph(N+1);
	scanf("%lld%lld%lld%lld%lld", &N, &L, &K, &L, &B);
	
	struct Graph* graph = createGraph(N+1);
	
	for (j=0; j<M; j++)		// diavazo tis akmes pou iparhoun kai einai M
	{
			scanf("%lld%lld%lld", &s, &d, &w)
			addEdge(graph, s, d, w);
					}
	
	long long int *apo=(long long int*)malloc((K-3)*sizeof(long long int)); //i-osti endiamesi poli sti diadromi apehei apo[i] apo to plisiestero gas station
	long long int *poleis=(long long int*)malloc((K-1)*sizeof(long long int));//poleis[i] einai (i+1)-osti poli sti diadromi
	// pada mas endiaferoun oi endiameses os pros apostaseis opote diavazoume ti proti
	scanf("%lld", &town);
	poleis[0]=town;
	for (j=1; j<K-1; j++)
	{
	scanf("%lld", &town);
	poleis[j]=town;
			}
	scanf("%lld", &town);
	poleis[K-1]=town;
	
	for (j=0; j<B; j++)
	{
			scanf("%lld", &dst);
			addEdge(graph, 0, dst, 0); //diavazo ta venzinadika kai ta sindeo me ti korifi 0
	}
	
	//dijkstra kai o theos voithos
	
	
	long long int V = graph->V;// Get the number of vertices in graph
   long long int dist[V];      // dist values used to pick minimum weight edge in cut
 
    // minHeap represents set E
    struct MinHeap* minHeap = createMinHeap(V);
 
    // Initialize min heap with all vertices. dist value of all vertices 
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
 
    // Make dist value of src vertex as 0 so that it is extracted first
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
 
    // Initially size of min heap is equal to V
    minHeap->size = V;
 
    // In the followin loop, min heap contains all nodes
    // whose shortest distance is not yet finalized.
    while (!isEmpty(minHeap))
    {
        // Extract the vertex with minimum distance value
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        long long int u = minHeapNode->v; // Store the extracted vertex number
 
        // Traverse through all adjacent vertices of u (the extracted
        // vertex) and update their distance values
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL)
        {
            long long int v = pCrawl->dest;
 
            // If shortest distance to v is not finalized yet, and weight of u-v
            // plus dist of u from src is less than dist value of v, then update
            // distance value of v
            if (isInMinHeap(minHeap, v) && pCrawl->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->weight;
 
                // update distance value in min heap also
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
 // edo teliose o dijkstra
 
	for (j=1; j<K-1; j++)
	apo[j-1]=dist[poleis[j]]; //tora o apo pinakas ehei oles tis sidomoteres apostaseis ton endiameson poleon apo ta venzinadika
	
	//sortaro ton apo pinaka
	
	qsort(apo,K-3,sizeof(long long int),&comp);
	
	sum=0;
	
	for (j=0; j<L; j++)
	{
	sum =sum+apo[j]; // kai ipologizo to sinoliko kostos anefodiasmou
	}
	
	
	
	 printf( "%lld\n", sum);
 
 
 
	
    //dijkstra(graph, 0);
 
    return 0;
}


int comp(const void * e,const void * f) 
{
   long long int* c;
    long long int* d;
    c=(long long int*)e;
    d=(long long int*)f;
  if (*c==*d)
    return 0;
  else
    if (*c < *d)
        return -1;
     else
      return 1;
}
