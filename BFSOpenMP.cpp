#include<iostream>
#include <stdio.h>
#include<vector>
#include<deque>
#include <omp.h>
using namespace std;

/* 邻接表存储有向图 */
class Graph {
	int V;            	// 顶点的数量 
	vector<int> *adj;      	// 邻接表 

	void BFSUtil(int v, bool visited[]);
public:
	Graph(int V);        	// 构造函数 
	void addEdge(int v, int w); 	// 向图中添加一条边 
	void BFS(int v);   	// BFS遍历 
};

Graph::Graph(int V) {
	this->V = V;
	adj = new vector<int> [V]; 		// 初始化V条链表
}

void Graph::addEdge(int v, int w) {
	adj[v].push_back(w);     // 将w加到v的list 
}

/* 从顶点v出发广度优先搜索 */
void Graph::BFSUtil(int v, bool visited[]) {
	// BFS辅助队列 
	deque<int> queue;

	// 将当前顶点标记为已访问并压入队列 
	visited[v] = true;
	queue.push_back(v);

	//deque<int>::iterator i;

	while (!queue.empty()) {
		// 出队 
		v = queue.front();
		cout << v << " ";
		queue.pop_front();

		// 检测已出队的顶点s的所有邻接顶点
		// 若存在尚未访问的邻接点，访问它并压入队列
#pragma omp parallel for
		for (int i = 0; i < adj[v].size(); ++i) {
			//cout << "i=" << i << " thread_id=" << omp_get_thread_num() << endl;
			printf("i=%d, thread_id=%d\n", i, omp_get_thread_num());
			if (!visited[adj[v].at(i)]) {
				visited[adj[v].at(i)] = true;
				queue.push_back(adj[v].at(i));
			}
		}
	}
}

/** 广度优先搜索 **/
void Graph::BFS(int v) { 
	// 初始化访问标记数组 
	bool *visited = new bool[V];
	for (int i = 0; i < V; ++i)
		visited[i] = false;

	// 假设从给定顶点可以到达图的所有顶点 
	BFSUtil(v, visited);
}

Graph creatGraph()
{
	int M =10, N=20;
	Graph g(M*N);
//	Graph g(4);
//	g.addEdge(0, 1);
//	g.addEdge(0, 2);
//	g.addEdge(1, 2);
//	g.addEdge(2, 0);
//	g.addEdge(2, 3);
//	g.addEdge(3, 3);

	for(int i = 1; i<M; i++)
	{
		g.addEdge(0, i);
		for(int j=0; j<N; j++)
		{
			g.addEdge(i, j+i+N);
		}
	}
	return g;
}

int main() {

	Graph g = creatGraph();
	cout << "Following is BFS Traversal (starting from vertex 2) \n";
	clock_t t1 = clock();
	g.BFS(0);
	clock_t t2 = clock();
	cout << "time: " << t2 - t1 << endl;

	return 0;
}
