//인접행렬그래프.c 소스파일
#include <stdio.h>
#include "queue.h"


#define MAX_VERTICES 50
#define TRUE 1;
#define FALSE 0;

int visited[MAX_VERTICES]; // 전역변수는 0으로 자동 초기화
typedef struct GraphType {
     int n;
     int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

void graph_init(GraphType *g) // 그래프 초기화 
{
	//여기 코드 추가 
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;

}

void insert_edge(GraphType *g, int start, int end) // 간선 삽입 연산
{
	if( start >= g->n || end >= g->n ){
		fprintf(stderr,"그래프: 정점 번호 오류");
		return;
	}
     
	//여기 코드 추가 
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

void insert_vertex(GraphType *g, int v) // 정점 삽입 연산
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프 정점의 개수 초과");
		return;
	}
	//여기 코드 추가 
	g->n++;
}

/* 깊이 우선 탐색
depth_first_search(v)
v를 방문되었다고 표시;
for all u ∈ (v에 인접한 정점) do 
	   if (u가 아직 방문되지 않았으면)
		then depth_first_search(u)
*/
void dfs_mat(GraphType *g, int v) // 깊이 우선 탐색
{
     int u;
     visited[v] = 1;     
     printf("%d ", v);
	  
 	 //여기 코드 추가 
	 printf("정점 %d => ", v);
	 for (u = 0; u < g->n; u++)
		 if (g->adj_mat[v][u] && !visited[u])
			 dfs_mat(g, u);

}

/* 넓이 우선 탐색
breadth_first_search(v) 
v를 방문되었다고 표시;
큐 Q에 정점 v를 삽입;
while (not is_empty(Q)) do 
	큐 Q에서 정점 w를 삭제;
	for all u ∈ (w에 인접한 정점) do 
		if (u가 아직 방문되지 않았으면) then 	u를 방문되었다고 표시;
u를 큐 Q에 삽입;
							
*/
void bfs_mat(GraphType *g, int v) // 넓이 우선 탐색
{  
	int w;
	QueueType q;
	init(&q);     /* 큐 초기화 */
	visited[v] = TRUE;          // 정점 v 방문 표시 
	printf("%d ", v);
	           
	//여기 코드 추가 
	enqueue(&q, v);
	while (!is_empty(&q)) {
		v = dequeue(&q);
		for (w=0; w<g->n; w++)
			if (g->adj_mat[v][w] && !visited[w]) {
				visited[w] = TRUE;
				printf("%d 방문 -> ", w);
				enqueue(&q, w);
			}
	}
}

 void visited_init()
{
	int i;
	for (i = 0; i < MAX_VERTICES; i++)
		visited[i] = 0;
}

int main(void)
{
	GraphType g;
	graph_init(&g);

	insert_vertex(&g, 0);
	insert_vertex(&g, 1);
	insert_vertex(&g, 2);
	insert_vertex(&g, 3);

	insert_edge(&g, 0, 1);
	insert_edge(&g, 1, 2);
	insert_edge(&g, 2, 3);
	insert_edge(&g, 3, 0);
	insert_edge(&g, 0, 2);

	printf("\n깊이 우선 탐색\n");
	dfs_mat(&g, 0); printf("\n");

	visited_init();
	dfs_mat(&g, 1); printf("\n");
	
	visited_init();
	dfs_mat(&g, 2); printf("\n");

	visited_init();
	dfs_mat(&g, 3); printf("\n");
	printf("\n넓이 우선 탐색\n");

	visited_init();
	bfs_mat(&g, 0); printf("\n");
	
	visited_init();
	bfs_mat(&g, 1); printf("\n");
	
	visited_init();
	bfs_mat(&g, 2); printf("\n");
	
	visited_init();
	bfs_mat(&g, 3); printf("\n");
}



