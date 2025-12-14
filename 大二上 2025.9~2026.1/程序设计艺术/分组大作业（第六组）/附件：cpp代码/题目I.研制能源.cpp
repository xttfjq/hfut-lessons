#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;

class OptimizedEnergy {
private:
    int n, t, q;
    vector<int> p;
    vector<int> l;
    vector<int> allocations;
    // 计算边际收益
    double marginal_gain(int i) {
        if (allocations[i] >= l[i]) return 0.0;
        double current = p[i] * (allocations[i] * 1.0 / (l[i] + allocations[i]));
        double next_val = p[i] * ((allocations[i] + 1) * 1.0 / (l[i] + allocations[i] + 1));
        return next_val - current;
    }
    // 使用优先队列的贪心分配
    double allocate_with_pq() {
        allocations.assign(n, 0);
        // 使用最大堆存储(边际收益, 烧杯索引)
        priority_queue<pair<double, int>> pq;
        // 初始化优先队列
        for (int i = 0; i < n; i++) {
            if (l[i] > 0) {
                double gain = marginal_gain(i);
                if (gain > 0) {
                    pq.push({gain, i});
                }
            }
        }
        int remaining = t;
        while (remaining > 0 && !pq.empty()) {
            auto [gain, idx] = pq.top();
            pq.pop();
            allocations[idx]++;
            remaining--;
            // 更新这个烧杯的边际收益
            double new_gain = marginal_gain(idx);
            if (new_gain > 0) {
                pq.push({new_gain, idx});
            }
        }
        // 计算总期望
        double total = 0.0;
        for (int i = 0; i < n; i++) {
            if (allocations[i] > 0) {
                total += p[i] * (allocations[i] * 1.0 / (l[i] + allocations[i]));
            }
        }
        return total;
    }
public:
    OptimizedEnergy(int n_val, int t_val, int q_val, 
                   const vector<int>& p_vals, const vector<int>& l_vals) 
        : n(n_val), t(t_val), q(q_val), p(p_vals), l(l_vals), allocations(n, 0) {}
    vector<double> process_queries(const vector<pair<int, int>>& queries) {
        vector<double> results;
        for (const auto& query : queries) {
            int op = query.first;
            int idx = query.second - 1;
            // 更新物质α
            if (op == 1) {
                l[idx]++;
            } else {
                l[idx]--;
            }
            results.push_back(allocate_with_pq());
        }
        return results;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, t, q;
    cin >> n >> t >> q;
    
    vector<int> p(n), l(n);
    for (int i = 0; i < n; i++) cin >> p[i];
    for (int i = 0; i < n; i++) cin >> l[i];
    
    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].first >> queries[i].second;
    }
    
    OptimizedEnergy optimizer(n, t, q, p, l);
    auto results = optimizer.process_queries(queries);
    
    cout << fixed << setprecision(9);
    for (double res : results) {
        cout << res << "\n";
    }
    
    return 0;
}