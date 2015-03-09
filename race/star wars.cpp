#include <stdio.h>
#include <stdlib.h>
#include <limits.h>



struct AdjListNode
{
   long long int dest;
   long long int weight;
    struct AdjListNode* next;
};
 

struct AdjList
{
    struct AdjListNode *head;  
};
 

struct Graph
{
    long long int V;
    struct AdjList* array;
};
 

struct AdjListNode* newAdjListNode(long long int dest,long long int weight)
{
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
 

struct Graph* createGraph(long long int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
 
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
 
    return graph;
}
 
void addEdge(struct Graph* graph,long long int src,long long int dest,long long int weight)
{
   
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
 

    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}
 
struct MinHeapNode
{
   long long int  v;
   long long int dist;
};
 
struct MinHeap
{
    long long int size;      
    long long int capacity;  
    long long int *pos;     
    struct MinHeapNode **array;
};
 
struct MinHeapNode* newMinHeapNode(long long int v,long long int dist)
{
    struct MinHeapNode* minHeapNode =
           (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}
 
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
 
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
 
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
     
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode = minHeap->array[idx];
 

        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
 

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
 
        minHeapify(minHeap, smallest);
    }
}
 
long long int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}
 
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;
 

    struct MinHeapNode* root = minHeap->array[0];
 

    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
 

    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
 

    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return root;
}
 

void decreaseKey(struct MinHeap* minHeap,long long int v,long long int dist)
{
    
    long long int i = minHeap->pos[v];
 
 
    minHeap->array[i]->dist = dist;
 

    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {

        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);
 

        i = (i - 1) / 2;
    }
}
 

bool isInMinHeap(struct MinHeap *minHeap,long long int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}
 

void printArr(long long int dist[],long long int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
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

 

int main()
{

    long long int N,M,K,L,B,j,s,src,d,w,town,sum;
    
    scanf("%lld%lld%lld%lld%lld", &N, &M, &K, &L, &B);
    
    struct Graph* graph = createGraph(N+1);
	for (j=0; j<M; j++)		// diavazo tis akmes pou iparhoun kai einai M
	{
			scanf("%lld%lld%lld", &s, &d, &w);
			addEdge(graph, s, d, w);
					}
	
	long long int *apo=(long long int*)malloc((K-2)*sizeof(long long int)); //i-osti endiamesi poli sti diadromi apehei apo[i] apo to plisiestero gas station
	long long int *poleis=(long long int*)malloc((K)*sizeof(long long int));//poleis[i] einai (i+1)-osti poli sti diadromi
	// pada mas endiaferoun oi endiameses os pros apostaseis opote diavazoume ti proti
	for (j=0; j<K; j++)
	{
	scanf("%lld", &town);
	poleis[j]=town;
			}
	
	for (j=0; j<B; j++)
	{
			scanf("%lld", &d);
			addEdge(graph, 0, d, 0); //diavazo ta venzinadika kai ta sindeo me ti korifi 0
	}
	
	//dijkstra kai o theos voithos
	src=0;
	
	
	long long int V = graph->V;
   long long int dist[V];      
 
    
    struct MinHeap* minHeap = createMinHeap(V);
 
     
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
 
    
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
 
 
    minHeap->size = V;
    while (!isEmpty(minHeap))
    {
       
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        long long int u = minHeapNode->v; 
 
      
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL)
        {
            long long int v = pCrawl->dest;
 

            if (isInMinHeap(minHeap, v) && pCrawl->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->weight;

                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
 // edo teliose o dijkstra
 
 //ipologizo poso tha kapsei o anakin logo diadromis agona pou de to glitonei me tipota
             sum=0;
 struct AdjListNode* temp = NULL;
 
        for (j=0; j<K-1; j++){
            temp = graph->array[poleis[j]].head;
                 while (temp->dest != poleis[j+1])
                 {
                       temp=temp->next;
                       }//edo telionei to while
                       sum=sum+temp->weight;
                       }
                       
                       
            
 
 
 
 
 
 	for (j=1; j<K-1; j++)
	apo[j-1]=dist[poleis[j]]; //tora o apo pinakas ehei oles tis sidomoteres apostaseis ton endiameson poleon apo ta venzinadika
	
	//sortaro ton apo pinaka
	
	qsort(apo,K-2,sizeof(long long int),&comp);
	
	for (j=0; j<L; j++)
	{
	sum =sum+apo[j]; // kai ipologizo to sinoliko kostos anefodiasmou pernontas ta L prota
	}
	
	
	
	 printf( "%lld\n", sum);
	 
	 system("PAUSE");
	 
return 0;
 
}


