#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<climits>
#include<cstdio>
using namespace std;
typedef long long ll;

// ---------- 定义边结构 ----------
struct Edge {
    int to;     // 目标节点
    int rev;    // 反向边在目标节点的索引
    ll cap;     // 容量
    Edge(int _to, int _rev, ll _cap) : to(_to), rev(_rev), cap(_cap) {}
};

// ---------- 全局变量 ----------
vector<vector<Edge>> g;  // 图的邻接表
vector<int> level;       // BFS 分层图
vector<int> iter;        // 当前弧优化

// ---------- 添加边 ----------
void add_edge(int from, int to, ll cap) {
    g[from].push_back(Edge(to, g[to].size(), cap));
    g[to].push_back(Edge(from, g[from].size() - 1, 0));
}

// ---------- BFS 构建分层图 ----------
void bfs(int s) {
    fill(level.begin(), level.end(), -1);
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (auto& e : g[v]) {
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
    }
}

// ---------- DFS 寻找增广路径 ----------
ll dfs(int v, int t, ll f) {
    if (v == t) return f;
    for (int& i = iter[v]; i < g[v].size(); i++) {
        Edge& e = g[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {
            ll d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                g[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

// ---------- Dinic 最大流 ----------
ll max_flow(int s, int t) {
    ll flow = 0, f;
    while (true) {
        bfs(s);
        if (level[t] < 0) return flow;  // 无法再增广
        fill(iter.begin(), iter.end(), 0);
        while ((f = dfs(s, t, LLONG_MAX)) > 0)
            flow += f;
    }
}

// ---------- 主函数 ----------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;             // 输入节点数 N 和边数 M

    g.assign(N + 1, vector<Edge>());
    level.assign(N + 1, -1);
    iter.assign(N + 1, 0);

    for (int i = 0; i < M; i++) {
        int u, v;
        ll cap;
        cin >> u >> v >> cap;  // 输入边信息
        cout << "边 " << i << ": " << u << "->" << v << " 容量=" << cap << endl;
        add_edge(u, v, cap);
    }

    cout << max_flow(1, N) << "\n";  // 输出最大流
    return 0;
}
