# 图

## 图的存储方式

### 邻接矩阵

一种存图方式，适合密集图，因为简单所以适合其他操作（比如翻转图）

```cpp
int mmp[MAX][MAX];
memset(mmp, 127, sizeof(mmp));//赋值无穷大
```

**遍历起点为 $n$ 的所有终点：**

```cpp
for (int i = 1; i < MAX; ++i) cout << mmp[n][i] << " ";
```

**添加一条从 $x$ 到 $y$ 的边：**

```cpp
mmp[x][y] = w;//w 为边权
```

### 朴素存图

非常朴素的存图方式

```cpp
vector<int> mmp[MAX];//MAX 为最大节点数
```

**遍历起点为 $n$ 的所有终点：**

```cpp
for (int to : mmp[n]) cout << to << " ";
```

**添加一条从 $x$ 到 $y$ 的边：**

```cpp
mmp[x].pushback(y);
```

### 链式前向星

链式前向星是一种高效的存图方式

```cpp
struct Edge{
    int to,nxt;
}edge[MAX << 1];//因为存边，所以大小是2倍最大节点数
int head[MAX];	//MAX 为最大节点数
int cnt;		//cnt 为一共有多少条边
```

$head[i]$ 表示节点 $i$ 为起点的第一条边在 $edge$ 数组中的索引

$edge[j]$ 表示终点为 $to$ 的一条边，要找的下一条边在 $edge$ 数组中的索引为 $nxt$ ，$j$ 只是索引没有具体意义

所以，比如要找起点为 $2$ 的边和终点，先从 $head[2]$ 找到第一条边的索引，再到 $edge$ 数组中寻找具体信息， 通过 $nxt$ 找到下一条边，当 $nxt==0$ 时，表示找完了

**遍历起点为 $n$ 的所有终点：**

```cpp
for(int i = head[n]; i; i = edge[i].nxt){
	cout << edge[i].to << " ";
}
```

**添加一条从 $x$ 到 $y$ 的边：**

```cpp
void add(int x,int y){
    edge[++cnt].to = y;
    edge[cnt].nxt = head[x];
    head[x] = cnt;
}
```

**如果要存边权：**

```cpp
struct Edge{
    int to,nxt,w;
}edge[MAX << 1];
int head[MAX];
int cnt;

void add(int x,int y, int w){
    edge[++cnt].to = y;
    edge[cnt].nxt = head[x];
    edge[cnt].w = w;
    head[x] = cnt;
}
```

### 

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

> 练练手？洛谷P3366 【模板】最小生成树
>
> https://www.luogu.com.cn/problem/P3366

## 狄杰斯特拉最短路

**任务：**

给定一个 $n$ 个点，$m$ 条有向边的带**非负**权图，求从 $s$ 出发，到每个点的最短距离，要求时间复杂度$$O(nlog\, n)$$

**分析：**

首先从起点考虑，有很多直达节点，找到距离最短的节点 $x$

那么，到节点 $x$ 的最短距离，就确定了（没有更短的边了）

那么，更新起点为 $x$ 的直达节点，它们到起点的距离更新为： $x$ 的距离加 $x$ 到节点的距离

现在，从起点考虑，有很多直达节点（加入刚刚跟新的），找到距离最短的节点 $y$ ......

不断循环，直到节点被考虑完。因为总是找最短距离，并且要维护，所以使用优先队列（堆）

**代码：**

```cpp
class node {
public:
    node(int pos, ll d): position(pos), dis(d){}
    int position;
    ll dis;
    bool operator<(const node& nd) const {
        return dis > nd.dis;
    }//在优先队列排序用
};

ll dis[MAX];//MAX 为最大节点数，dis 为要求的最短距
priority_queue<node> Q;

void dijkstra() {
    for (int i = 1;i <= N;i++) dis[i] = 2e9;//先假设距离无穷大
    dis[S] = 0;//S为起点
    Q.push(node(S, 0));
    while (!Q.empty()) {
        node top = Q.top();
        Q.pop();
        int pos = top.position;
        if (top.dis != dis[pos]) continue;
        //如果将要处理的点已经在其他方向处理过了，距离不符要跳过
        for (int i = head[pos]; i; i = edges[i].next) {//链式前向星存图
            int to = edges[i].to;
            ll w = edges[i].weight;
            if (dis[pos] + w < dis[to]) {
                dis[to] = dis[pos] + w;
                Q.push(node(to, dis[to]));
            }
        }
    }
}
```

> 练练手？洛谷P4779 【模板】单源最短路径（标准版）
>
> https://www.luogu.com.cn/problem/P4779

补充：

1. 一般来说，使用狄杰斯特拉算法的带权图中不能有负权。有一个例外，当只有从起点出发的边是负权，其他边都是正权，狄杰斯特拉算法的计算结果也是正确的。

2. 狄杰斯特拉寻找一对多的最短路，如何寻找多对一的最短路？把图反过来！

3. 在图中找最短路，如果多条路径都最短，选择开销最少的。输出最短路径长，最小开销，以及路径。（PAT 甲级 **1030 Travel Plan**）

   ```cpp
   class Node{
   public:
       int pos, dis, cost;
       Node(int pos, int dis, int cost):pos(pos), dis(dis), cost(cost){}
       bool operator < (const Node& n) const{  // 综合判断
           if(dis == n.dis) return cost > n.cost;
           return dis > n.dis;
       }
   };
   
   // 输出路径
   void dfs(int end){ //倒着向前递归
       if(end == S){
           cout << S << " ";
           return;
       }
       dfs(pre[end]);
       cout << end << " ";  // 尾递归
   }
   ```

4. 要找多条最短路，修改代码

   ```cpp
   if(vis[u] && now.dis > dis[u]){
       continue;
   }
   ```

## 弗洛伊德最短路

**任务：**

给定一个 $n$ 个点的加权图，求任意起点到任意终点的最短距离，要求时间复杂度$O(n^3)$

**分析：**

考虑从起点 $i$ 到 终点 $j$ 的最短路

对于每一个可能的中转点 $k$ ，考虑先从 $i$ 到 $k$ ，再从 $k$ 到 $j$ 的距离

注意，代码中 $k$ 在最外面一层，是以中转点为驱动的查找

**代码：**

```cpp
int mmp[MAX][MAX];//邻接矩阵存图，MAX 为最大节点数

void init(){
    //初始化，假设 i 到 j 的距离无穷大，注意不要溢出
    for(int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) mmp[i][j] = 1e9;
    for(int i = 0; i < N; ++i) mmp[i][i] = 0;//到自己的距离为0
}

void floyd(){
    for(int k = 0; k < N; ++k)//N 为节点数
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                mmp[i][j] = min(mmp[i][j], mmp[i][k] + mmp[k][j]);
}
```

>   补充：弗洛伊德算法可以计算负权图，所有的最短路径算法不能有负权回路，否则最短路径长为负无穷，没有意义。

> 练练手？洛谷P1119 灾后重建
>
> https://www.luogu.com.cn/problem/P1119

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

## Johnson 全源最短路

**任务：**

给定一个包含 n 个结点和 m 条带权边的有向图，求所有点对间的最短路径长度，一条路径的长度定义为这条路径上所有边的权值和。注意：边权**可能**为负，且图中**可能**存在重边和自环。

**分析：**

先来看全源最短路的几个基本想法：

1. Floyd：时间复杂度为 $O(n^3)$，能够解决负权边，不能解决负环，而且很慢。
2. Dijkstra：以每个点为源点做一次 Dijkstra，时间复杂度为 $O(nm\log (n))$，时间上可以，但是 Dijkstra 只能解决非负权边，一旦出现负权边就得另想办法。
3. BellmanFord：以每个点为源点做一次 BellmanFord，时间复杂度为 $O(n^2m)$，能搞定所有权值情况，但是太慢。

Johnson 算法则通过一种方法来给每条边重新标注边权：

1. 我们新建一个虚拟节点（设它的编号为 0 ）。从这个点向其他所有点连一条边权为 0 的边。
2. 接下来用 Bellman-Ford 算法求出从 0 号点到其他所有点的最短路，记为 $h_i$ 。
3. 假如存在一条从 u 点到 v 点，边权为 w 的边，则我们将该边的边权重新设置为 $w+h_u-h_v$
4. 接下来以每个点为起点，跑 n 轮 Dijkstra 算法即可求出任意两点间的最短路了。

容易看出，该算法的时间复杂度是 $O(nm \log (m))$ 。

> 证明：[Studying Father's luogu blog](https://www.luogu.com.cn/blog/StudyingFather/johnson-algorithm)
>
> 例题：洛谷P5905 【模板】Johnson 全源最短路
>
> https://www.luogu.com.cn/problem/P5905

## SPFA最短路

解决带负权边的单源最短路问题还有一个常用的算法是SPFA算法，SPFA算法的时间复杂度一般是O(m)，最坏是O(nm)。 

SPFA 算法是 Bellman-Ford算法 的队列优化算法的别称，通常用于求含负权边的单源最短路径，以及判负权环。

```cpp
void spfa(int s){
    queue<int> q; //spfa用队列
    for(int i=1; i<=N; i++) {
        dis[i]=INF; //带权图初始化
        vis[i]=0; //记录点i是否在队列中
    }
    q.push(s); dis[s]=0; vis[s]=1; //起点入队，进行标记
    while(!q.empty()){
        int u=q.front();
        q.pop(); 
        vis[u]=0; //出队标记
        for(int i=head[u]; i; i=edge[i].next) {
            int v=edge[i].to;

            if(dis[v]>dis[u]+edge[i].dis) {
                dis[v]=dis[u]+edge[i].dis;

                // 因为节点v的最短路径发生了变化，后续的节点可能也会发生变化，所以v入队再次处理
                if(vis[v]==0) {
                vis[v]=1;
                q.push(v);
                }
            }
        }
    }
}
```

> 练练手？洛谷P4779 【模板】单源最短路径（标准版）
>
> https://www.luogu.com.cn/problem/P4779

现在思考如果存在负环会出现什么情况，负环上的节点会一次又一次地加入队列，最短距离一次又一次的缩小，永远不会停止循环。

我们可以记录每个节点的入队次数，如果某个节点的入队次数大于N，则出现负环。

## 拓扑排序

**任务：**

在一个家族中，给出每个人的后代的信息。输出一个序列，使得每个人的后辈都比那个人后列出。如果有多种不同的序列，输出任意一种即可。

**分析：**

首先找到祖先，换句话说在这个有向无环图中找到一个入度为0的点，将其加入答案队列，再将它的所有儿子入度减一。

再次找到一个入度为0的点，将其加入答案队列，再将它的所有儿子入度减一。

如此循环，直到处理完。

**代码：**

```cpp
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

int N;
int in[105];

class edge{
    public:
    int v, next;
    edge(int v = 0, int next = 0){
        this->v = v;
        this->next = next;
    }
};

edge e[10000];
int cnt, head[105];
vector<int> ans;

void addedge(int u, int v){
    e[++cnt] = edge(v, head[u]);
    head[u] = cnt;
}

void toposort(){
    queue<int> q;

    for(int i=1; i<=N; i++){
        if(in[i] == 0) {
            q.push(i);
            ans.push_back(i);
        }
    }

    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i = head[u]; i ; i = e[i].next){
            int v = e[i].v;
            in[v]--;
            if(in[v] == 0){
                q.push(v);
                ans.push_back(v);
            }
        }
    }
}

int main(){
    cin >> N;
    for(int i = 1; i <= N; i++){
        int son;
        while(1){
            cin >> son;
            if(son == 0) break;
            addedge(i, son);
            in[son]++;
        }
    }
    toposort();
    for(int i: ans) cout << i << " ";

    return 0;
}
```

> 例题：洛谷B3644 【模板】拓扑排序 / 家谱树
>
> https://www.luogu.com.cn/problem/B3644

拓扑排序也可以帮助找到环

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

## 二分图

**概念与结论**

设 G=(V,E) 是一个无向图，如果顶点集合 V 可分割为两个互不相交的子集 (A,B)，并且每条边 (i,j)∈E 的两个端点 i 和 j 分别属于这两个不同的顶点子集，则称图 G 为一个二分图。

树一定是二分图。可以把本层节点归入一个集合，把父亲和儿子归入另外一个集合，对于每一层这样操作，就得到了二分图。

对于顶点数为n的二分图, 假设划分的两个集合顶点数分别为m , n-m. 显然这个二分图的最大边数为m*(n-m), 即每个顶点与对面集合所有顶点都形成的边。

**任务**

> [2022 RoboCom 世界机器人开发者大赛-本科组（省赛）-- 第五题 树与二分图](https://blog.csdn.net/qq_60775983/article/details/125738638)

给定一棵树, 最多能加多少边使得它仍是二分图。

**思路**

从树的顶点开始，用dfs染一遍色，分出两个集合，最多能加多少边就是最大边数减去原来的边数。