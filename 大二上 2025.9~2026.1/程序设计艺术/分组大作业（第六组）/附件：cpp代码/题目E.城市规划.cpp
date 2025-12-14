#include <iostream>
#include <cstring>
using namespace std;
const int MAXN = 1005;
int n, A, B;
int x[MAXN], y[MAXN], t[MAXN];
bool visited[MAXN][MAXN];
struct State {
    int a, b, step;
};
State q[MAXN * MAXN]; 
int bfs() {
    memset(visited, 0, sizeof(visited));
    int front = 0, rear = 0;
    State start;
    start.a = A;
    start.b = B;
    start.step = 0;
    q[rear++] = start;
    visited[A][B] = true;
    while (front < rear) {
        State cur = q[front++];
        int nxA = x[cur.a];
        int nxB = x[cur.b];
        if (!visited[nxA][nxB]) {
            if (t[nxA] != t[nxB]) {
                return cur.step + 1;
            }
            visited[nxA][nxB] = true;
            State next;
            next.a = nxA;
            next.b = nxB;
            next.step = cur.step + 1;
            q[rear++] = next;
        }
        int nyA = y[cur.a];
        int nyB = y[cur.b];
        if (!visited[nyA][nyB]) {
            if (t[nyA] != t[nyB]) {
                return cur.step + 1;
            }
            visited[nyA][nyB] = true;
            State next;
            next.a = nyA;
            next.b = nyB;
            next.step = cur.step + 1;
            q[rear++] = next;
        }
    }
    return -1;
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> A >> B;
        for (int i = 0; i < n; i++) {
            cin >> x[i] >> y[i] >> t[i];
        }
        cout << bfs() << endl;
    }
    return 0;
}
