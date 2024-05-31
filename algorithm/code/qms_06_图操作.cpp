#include<iostream>
#include<cstring>
#include<queue>
#include<cmath>
#include<stack>
using namespace std;

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
int dis[6];


void dfs(int node) {
	vis[node] = 1;
	cout << node << " ";
	for (int i = 0; i < 6; ++i) {
		if (graph[node][i] > 0 && graph[node][i] < INF && !vis[i]) dfs(i);
	}
}


void dfsNoR(int S) {
	stack<int> s;
	s.push(S);
	while (!s.empty()) {
		int node = s.top();
		s.pop();
		if (vis[node])continue;
		vis[node] = 1;
		cout << node << " ";
		for (int i = 5; i >= 0; --i) {
			if (graph[node][i] > 0 && graph[node][i] < INF && !vis[i]) s.push(i);
		}
	}
}

void bfs(int S) {
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

class dij_node {
public:
	dij_node(int pos, int d) : position(pos), dis(d) {}
	int position;
	int dis;
	bool operator<(const dij_node& nd) const {
		return dis > nd.dis;
	}
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


int dis_2d[6][6];
void floyd() {
	memcpy(dis_2d, graph, sizeof(graph));
	for (int k = 0; k < 6; ++k)
		for (int i = 0; i < 6; ++i)
			for (int j = 0; j < 6; ++j)
				dis_2d[i][j] = min(dis_2d[i][j], dis_2d[i][k] + dis_2d[k][j]);
}


int main() {
	memset(vis, 0, sizeof(vis));
	dfs(0);
	cout << endl << endl;

	memset(vis, 0, sizeof(vis));
	dfsNoR(0);
	cout << endl << endl;


	memset(vis, 0, sizeof(vis));
	bfs(0);
	cout << endl << endl;


	dijkstra(0);
	for (int i = 0; i < 6; ++i) cout << dis[i] << " ";
	cout << endl << endl;


	floyd();
	for (int j = 0; j < 6; ++j) {
		for (int i = 0; i < 6; ++i) cout << dis_2d[j][i] << " ";
		cout << endl;
	}
	
	return 0;
}