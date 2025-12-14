#include <iostream>
#include <cstring>
using namespace std;
const int MAXN = 1000005;
int n;
int head[MAXN], to[2*MAXN], nxt[2*MAXN], idx;
long long v[MAXN];
long long dp[MAXN][2]; // 0: u not used, 1: u used
void addEdge(int a, int b) {
    to[idx] = b;
    nxt[idx] = head[a];
    head[a] = idx++;
}
void dfs(int u, int parent) {
    dp[u][0] = 0;
    dp[u][1] = 0;    
    long long sum = 0;
    for (int i = head[u]; i != -1; i = nxt[i]) {
        int child = to[i];
        if (child == parent) continue;
        dfs(child, u);
        sum += max(dp[child][0], dp[child][1]);
    }    
    dp[u][0] = sum; 
    for (int i = head[u]; i != -1; i = nxt[i]) {
        int child = to[i];
        if (child == parent) continue;
        long long cur = v[u] * v[child] + dp[child][0] + (sum - max(dp[child][0], dp[child][1]));
        if (cur > dp[u][1]) {
            dp[u][1] = cur;
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);   
    cin >> n;
    memset(head, -1, sizeof(head));
    idx = 0; 
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        addEdge(a, b);
        addEdge(b, a);
    }
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }   
    dfs(1, -1);  
    cout << max(dp[1][0], dp[1][1]) << endl; 
    return 0;
}
