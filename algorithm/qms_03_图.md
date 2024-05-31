# 图

## 图的存储方式

### 邻接矩阵

### 邻接表

## 深度优先搜索（DFS）

对于当前结点，对于它的所有终点，未访问过就访问。

```cpp
const int INF = 1e9;
int graph[6][6] = {
	{0,12,10,INF,30,100},
	{INF,0,5,INF,INF,INF},
	{INF,INF ,0 ,50, INF,INF},
	{INF,INF,INF,0,INF,10},
	{INF,INF,INF,20,0,60},
	{INF,INF,INF,INF,INF,0}
};
bool vis[6];

void dfs(int node) {//对于邻接矩阵
	vis[node] = 1;
	cout << node << " ";
	for (int i = 0; i < 6; ++i) {//6个结点
		if (graph[node][i] > 0 && graph[node][i] < INF && !vis[i]) dfs(i);
	}
}
```

>   补充：不使用递归的DFS，用一个栈，反着压栈，到时候就正着取出。
>
>   ```cpp
>   void dfsNoR(int S) {
>   	stack<int> s;
>   	s.push(S);
>   	while (!s.empty()) {
>   		int node = s.top();
>   		s.pop();
>   		if (vis[node])continue;
>   		vis[node] = 1;
>   		cout << node << " ";
>   		for (int i = 5; i >= 0; --i) {
>   			if (graph[node][i] > 0 && graph[node][i] < INF && !vis[i]) s.push(i);
>   		}
>   	}
>   }
>   ```

## 广度优先搜索（BFS）

从队列取出当前结点，将它所有未访问的终点入队列。

```cpp
void bfs(int S) {//S为起点，图为邻接矩阵
	queue<int> q;
	q.push(S);
	vis[S] = 1;
	while (!q.empty()) {
		int node = q.front();
		q.pop();
		cout << node << " ";
		for (int i = 0; i < 6; ++i) {
			if (graph[node][i] > 0 && graph[node][i] < INF && !vis[i]) {
				vis[i] = 1;
				q.push(i);
			}
		}
	}
}
```

## Prim最小生成树

维护每个节点是否加入树和每个节点加入树的最小开销两个数组。总的时间复杂度：O（n^2）

1. 遍历，找到还没加入树并且加入树的开销最小的节点，加入
2. 更新两个数组
3. 回到第一步，直到每个节点都加入树

## 克鲁斯卡尔最小生成树

**任务：**

给定一个 $n$ 个点的无向图，用树的形式连接它们（生成树），要求树的总权最小（最小生成树）

**分析：**

关于树的特点：边==节点-1，没有环

因为要求树的权最小，先把所有边排序，优先考虑权小的边

如果加上这条边出现环，则跳过，反之加上它。一直处理到边==节点-1

环可以用并查集维护，总的时间复杂度：O（elog2e）

**核心代码：**

```cpp
class Edge {
public:
	Edge(int u = 0, int v = 0, int w = 0) :u(u), v(v), w(w) {}
	int u, v, w;
	bool operator<(const Edge& that) const {
		return this->w < that.w;
	}
};
Edge mmp[MAXM];

void kruskal() {
	sort(mmp, mmp + M);//先从小到大排序
	for (int i = 0; i < M; ++i) {
		if (getfa(mmp[i].u) == getfa(mmp[i].v)) continue;//树不包括环
		ans += mmp[i].w;//答案加边权
		setfa(mmp[i].v, mmp[i].u);//维护并查集
		cnt++;//边数
		if (cnt == N - 1) return;//边数==节点-1，结束
	}
}
```

## 狄杰斯特拉最短路

**任务：**

给定一个 $n$ 个点，$m$ 条有向边的带**非负**权图，求从 $s$ 出发，到每个点的最短距离，要求时间复杂度$O(nlog\, n)$

**分析：**

首先从起点考虑，有很多直达节点，找到距离最短的节点 $x$

那么，到节点 $x$ 的最短距离，就确定了（没有更短的边了）

那么，更新起点为 $x$ 的直达节点，它们到起点的距离更新为： $x$ 的距离加 $x$ 到节点的距离

现在，从起点考虑，有很多直达节点（加入刚刚跟新的），找到距离最短的节点 $y$ ......

不断循环，直到节点被考虑完。因为总是找最短距离，并且要维护，所以使用优先队列（堆）

**代码：**

```cpp
class dij_node {
public:
	dij_node(int pos, int d) : position(pos), dis(d) {}
	int position;
	int dis;
	bool operator<(const dij_node& nd) const {
		return dis > nd.dis;
	}//在优先队列排序用
};

void dijkstra(int S) {
	priority_queue<dij_node> Q;
	for (int i = 0; i < 6; i++) dis[i] = INF;
	dis[S] = 0;
	Q.push(dij_node(S, 0));
	while (!Q.empty()) {
		dij_node top = Q.top();
		Q.pop();
		int pos = top.position;
		if (top.dis != dis[pos]) continue;
		for (int i = 0; i < 6; ++i) {
			if (graph[pos][i] > 0 && graph[pos][i] < INF && dis[pos] + graph[pos][i] < dis[i]) {
				dis[i] = dis[pos] + graph[pos][i];
				Q.push(dij_node(i, dis[i]));
			}
		}
	}
}
```

>   补充：一般来说，使用狄杰斯特拉算法的带权图中不能有负权。有一个例外，当只有从起点出发的边是负权，其他边都是正权，狄杰斯特拉算法的计算结果也是正确的。

## 弗洛伊德最短路

**任务：**

给定一个 $n$ 个点的加权图，求任意起点到任意终点的最短距离，要求时间复杂度$O(n^3)$

**分析：**

考虑从起点 $i$ 到 终点 $j$ 的最短路

对于每一个可能的中转点 $k$ ，考虑先从 $i$ 到 $k$ ，再从 $k$ 到 $j$ 的距离

注意，代码中 $k$ 在最外面一层，是以中转点为驱动的查找

**代码：**

```cpp
int dis_2d[6][6];
void floyd() {
	memcpy(dis_2d, graph, sizeof(graph));
	for (int k = 0; k < 6; ++k)
		for (int i = 0; i < 6; ++i)
			for (int j = 0; j < 6; ++j)
				dis_2d[i][j] = min(dis_2d[i][j], dis_2d[i][k] + dis_2d[k][j]);
}
```

>   补充：弗洛伊德算法可以计算负权图，所有的最短路径算法不能有负权回路，否则最短路径长为负无穷，没有意义。

## 贝尔曼-福特最短路

Dijkstra算法不能解决带有负权边的问题，而Bellman-ford算法可以解决带有**负权边**的问题，是求解带负权边的单源最短路问题的经典算法。时间复杂度是O(nm)，核心思想是”松弛操作”。缺点是时间复杂度过高。但它也有特别的用处，一般用于实现通过m次迭代求出从起点到终点不超过m条边构成的最短路径。

**基本思路**

n次迭代，每一次循环所有m个边。迭代次数是有实际意义的，比如**迭代了k次，那么求的最短距离就是从1号点经过不超过k条边走到n号点的最短距离**。

我们这里用a,b,w表示存在一条从a走到b的边，权重是w。遍历所有边的时候更新一下其他点的距离，即用当前这个点更新和它相连的点距离起点的距离。

我们这里用dist数组表示每个点到起点的距离，那么更新操作就是

```cpp
dist[b]=min(dist[b],dist[a]+w)
```

这样就可以更新和a相连的b点距离起点的距离，这个更新的过程就是”松弛操作”。

循环n次之后对所有的边一定满足`dist[b]<=dist[a]+w`，这个叫”三角不等式”。

Bellman-ford算法可以判断图中存不存在负权回路。在第n次迭代的时候又更新了某些边的话，就说明路径中一定存在环，并且是负权回路。

## SPFA最短路

解决带负权边的单源最短路问题还有一个常用的算法是SPFA算法，SPFA算法的时间复杂度一般是O(m)，最坏是O(nm)。 

SPFA 算法是 Bellman-Ford算法 的队列优化算法的别称，通常用于求含负权边的单源最短路径，以及判负权环。

与狄杰斯特拉最短路思想不同，当一个节点被处理，SPFA 不保证已经找到最短路径。如果在一次处理中 v 节点的最短路径被更新，它的所有后续节点都要更新一遍，然后 v 节点的最短路径**可能**再次被更新，它的所有后续节点都要再次更新一遍……直到稳定。

## 拓扑排序

可以帮助找到环

## 关键路径

1.   计算结点的最早发生时间$ve$和最晚发生时间$vl$

2.   计算活动（路径）的最早发生时间$e$和最晚发生时间$l$，若路径$a_i$连接节点$v_j$和$v_k$：
     $$
     e(a_i)=ve(v_j)
     $$

     $$
     l(a_i)=vl(v_k)-dut(j,k)
     $$

     其中$dut(j,k)$表示路径$a_i$的权。

3.   活动（路径）的最早发生时间$e$和最晚发生时间$l$相等的，就是关键路径。