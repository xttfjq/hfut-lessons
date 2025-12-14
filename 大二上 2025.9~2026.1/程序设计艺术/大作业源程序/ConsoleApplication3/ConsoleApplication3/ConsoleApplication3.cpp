
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;

struct Volunteer {
    int ti, ci, pi;
    int sgn_ci;
    int start_time, end_time;
};

int sgn(int x) {
    return x > 0 ? 1 : -1;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<Volunteer> volunteers(m);

    for (int i = 0; i < m; ++i) {
        int ti, ci, pi;
        cin >> ti >> pi >> ci;
        volunteers[i].ti = ti;
        volunteers[i].ci = ci;
        volunteers[i].pi = pi;
        volunteers[i].sgn_ci = sgn(ci);
        volunteers[i].start_time = ti;
        volunteers[i].end_time = ti + abs(ci);
    }

    int q;
    cin >> q;
    vector<int> wi(q);
    vector<int> xi(q);
    for (int i = 0; i < q; ++i) {
        cin >> wi[i] >> xi[i];
    }

    // 对每个任务进行处理
    for (int qid = 0; qid < q; ++qid) {
        int wi_q = wi[qid];
        int xi_q = xi[qid];

        // 针对当前任务，重新建立事件和志愿者之间的连接图
        map<pair<int, int>, vector<int>> events;
        for (int i = 0; i < m; ++i) {
            int ti = volunteers[i].ti;
            int ci = volunteers[i].ci;
            int sgn_ci = volunteers[i].sgn_ci;
            int start_t = ti;
            int end_t = min(ti + abs(ci), wi_q); // 志愿者的结束时间不能超过任务的最晚时间
            if (start_t > end_t) continue; // 志愿者在任务时间范围外

            for (int t = start_t; t <= end_t; ++t) {
                int p = volunteers[i].pi + (t - ti) / sgn_ci;
                if (p < 1 || p > n) continue;
                events[{t, p}].push_back(i);
            }
        }

        // 建立志愿者之间的连接图
        vector<set<int>> adj(m);
        for (auto& event : events) {
            const vector<int>& vol_list = event.second;
            int k = vol_list.size();
            for (int i = 0; i < k; ++i) {
                int u = vol_list[i];
                for (int j = i + 1; j < k; ++j) {
                    int v = vol_list[j];
                    adj[u].insert(v);
                    adj[v].insert(u);
                }
            }
        }

        vector<int> source_volunteers;
        vector<int> sink_volunteers;

        // 找到能够在 1 号点的志愿者作为源点
        for (int i = 0; i < m; ++i) {
            int sgn_ci = volunteers[i].sgn_ci;
            int t = volunteers[i].ti + sgn_ci * (1 - volunteers[i].pi);
            if (t >= volunteers[i].start_time && t <= volunteers[i].end_time && t <= wi_q) {
                if ((volunteers[i].pi + sgn_ci * (t - volunteers[i].ti)) == 1) {
                    source_volunteers.push_back(i);
                }
            }
        }

        // 找到能够在 xi_q 号点的志愿者作为汇点
        for (int i = 0; i < m; ++i) {
            int sgn_ci = volunteers[i].sgn_ci;
            int t = volunteers[i].ti + sgn_ci * (xi_q - volunteers[i].pi);
            if (t >= volunteers[i].start_time && t <= volunteers[i].end_time && t <= wi_q) {
                if ((volunteers[i].pi + sgn_ci * (t - volunteers[i].ti)) == xi_q) {
                    sink_volunteers.push_back(i);
                }
            }
        }

        if (source_volunteers.empty() || sink_volunteers.empty()) {
            cout << -1 << endl;
            continue;
        }

        // 使用 BFS 搜索最短路径
        vector<int> distance(m, -1);
        queue<int> q_bfs;
        for (int s : source_volunteers) {
            distance[s] = 1;
            q_bfs.push(s);
        }

        int min_volunteers = -1;
        set<int> sink_set(sink_volunteers.begin(), sink_volunteers.end());
        while (!q_bfs.empty()) {
            int u = q_bfs.front();
            q_bfs.pop();
            if (sink_set.count(u)) {
                min_volunteers = distance[u];
                break;
            }
            for (int v : adj[u]) {
                if (distance[v] == -1) {
                    distance[v] = distance[u] + 1;
                    q_bfs.push(v);
                }
            }
        }

        cout << min_volunteers << endl;
    }

    return 0;
}