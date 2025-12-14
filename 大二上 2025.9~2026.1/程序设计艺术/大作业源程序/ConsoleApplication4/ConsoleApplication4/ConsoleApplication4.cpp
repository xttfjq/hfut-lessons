#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

struct Volunteer {
    int t, c, p;  // 活动开始时间、速度、初始位置
};

struct Task {
    int w, x;  // 最迟完成时间、目标位置
};

struct State {
    int time, pos, cost;
    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Volunteer> volunteers(m);
    for (int i = 0; i < m; i++) {
        cin >> volunteers[i].t >> volunteers[i].c >> volunteers[i].p;
    }

    int q;
    cin >> q;
    vector<Task> tasks(q);
    for (int i = 0; i < q; i++) {
        cin >> tasks[i].w >> tasks[i].x;
    }

    // 找到最大时间
    int max_time = 0;
    for (const auto& vol : volunteers) {
        max_time = max(max_time, vol.t + abs(vol.c));
    }
    for (const auto& task : tasks) {
        max_time = max(max_time, task.w);
    }

    // DP: dp[time][pos] = 到达该状态所需的最小志愿者数
    vector<vector<int>> dp(max_time + 2, vector<int>(n + 2, INT_MAX));
    dp[0][1] = 0;

    // 按时间顺序处理
    for (int t = 0; t <= max_time; t++) {
        for (int pos = 1; pos <= n; pos++) {
            if (dp[t][pos] == INT_MAX) continue;

            // 尝试使用每个志愿者
            for (const auto& vol : volunteers) {
                if (vol.t < t) continue;  // 志愿者还没开始

                int start_time = max(t, vol.t);
                if (start_time > vol.t + abs(vol.c)) continue;

                if (vol.c > 0) {
                    // 向右移动
                    int move_time = min(vol.c, vol.t + vol.c - start_time);
                    int end_pos = min(n, vol.p + move_time);
                    int end_time = start_time + move_time;

                    if (vol.p >= pos) {
                        // 可以接上
                        int wait_time = vol.p - pos;
                        if (start_time >= t + wait_time) {
                            dp[end_time][end_pos] = min(dp[end_time][end_pos], dp[t][pos] + 1);
                        }
                    }
                }
                else {
                    // 向左移动
                    int move_time = min(-vol.c, vol.t - vol.c - start_time);
                    int end_pos = max(1, vol.p - move_time);
                    int end_time = start_time + move_time;

                    if (vol.p <= pos) {
                        // 可以接上
                        int wait_time = pos - vol.p;
                        if (start_time >= t + wait_time) {
                            dp[end_time][end_pos] = min(dp[end_time][end_pos], dp[t][pos] + 1);
                        }
                    }
                }
            }

            // 等待到下一时刻（不换志愿者）
            if (t + 1 <= max_time) {
                dp[t + 1][pos] = min(dp[t + 1][pos], dp[t][pos]);
            }
        }
    }

    // 回答查询
    for (const auto& task : tasks) {
        int ans = INT_MAX;
        for (int t = 0; t <= task.w; t++) {
            ans = min(ans, dp[t][task.x]);
        }
        cout << (ans == INT_MAX ? -1 : ans) << "\n";
    }

    return 0;
}
