#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;  // 修改：避免使用科学计数法

// 返回x的质因数集合
set<int> get_prime_factors(int x) {
    set<int> factors;
    if (x == 1) return factors;
    for (int d = 2; d * d <= x; d++) {
        while (x % d == 0) {
            factors.insert(d);
            x /= d;
        }
    }
    if (x > 1) factors.insert(x);
    return factors;
}

// 返回1到n的数的质因数等价类
vector<vector<int>> identify_equivalence_classes(int n) {
    map<set<int>, vector<int>> classes;
    for (int x = 1; x <= n; x++) {
        set<int> factors = get_prime_factors(x);
        classes[factors].push_back(x);
    }
    vector<vector<int>> result;

    // 修复：使用传统的迭代器语法
    for (map<set<int>, vector<int>>::const_iterator it = classes.begin(); it != classes.end(); ++it) {
        result.push_back(it->second);
    }
    return result;
}

// 计算两个数的最大公约数
int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// 提前声明回溯函数
void backtrack(int index, vector<int>& slots_to_assign, const vector<int>& avail_numbers,
    map<int, int>& current_assignment, set<int>& used,
    const vector<vector<int>>& coprime_slots, int& count);

// 解决单个测试用例，返回满足条件的方案数
int solve_case(int n, const vector<int>& a) {
    // 识别等价类
    vector<vector<int>> eq_classes = identify_equivalence_classes(n);

    // 确定已固定的槽位和可用的数
    map<int, int> fixed;
    set<int> available;
    for (int i = 1; i <= n; i++) available.insert(i);
    for (int i = 0; i < n; i++) {
        if (a[i] != 0) {
            if (available.find(a[i]) == available.end()) {
                return 0; // 重复赋值，不可能
            }
            fixed[i + 1] = a[i];
            available.erase(a[i]);
        }
    }

    // 预处理槽位之间的互质关系，使用对称性优化
    vector<vector<int>> coprime_slots(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (gcd(i, j) == 1) {
                coprime_slots[i].push_back(j);
                coprime_slots[j].push_back(i); // 利用对称性
            }
        }
    }

    // 预处理数与数之间的互质关系
    vector<set<int>> num_coprime(n + 1);
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= n; y++) {
            if (gcd(x, y) == 1) {
                num_coprime[x].insert(y);
            }
        }
    }

    // 确定需要分配的槽位和可用数
    vector<int> slots_to_assign;
    for (int i = 1; i <= n; i++) {
        if (fixed.find(i) == fixed.end()) {
            slots_to_assign.push_back(i);
        }
    }
    vector<int> avail_numbers(available.begin(), available.end());

    // 如果槽位数大于可用数，返回0
    if (slots_to_assign.size() > avail_numbers.size()) {
        return 0;
    }

    // 回溯法计数
    int count = 0;

    map<int, int> initial_assignment = fixed;
    set<int> used_numbers;
    for (map<int, int>::const_iterator it = fixed.begin(); it != fixed.end(); ++it) {
        used_numbers.insert(it->second);
    }

    // 调用回溯函数
    backtrack(0, slots_to_assign, avail_numbers, initial_assignment, used_numbers, coprime_slots, count);
    return count;
}

// 回溯函数定义
void backtrack(int index, vector<int>& slots_to_assign, const vector<int>& avail_numbers,
    map<int, int>& current_assignment, set<int>& used,
    const vector<vector<int>>& coprime_slots, int& count) {
    if (index == slots_to_assign.size()) {
        count = (count + 1) % MOD;
        return;
    }
    int slot = slots_to_assign[index];
    for (int num_index = 0; num_index < avail_numbers.size(); num_index++) {
        int num = avail_numbers[num_index];
        if (used.find(num) == used.end()) 
        {
            // 检查与已分配的互质槽位
            bool valid = true;
            for (map<int, int>::const_iterator it = current_assignment.begin(); it != current_assignment.end(); ++it) {
                int assigned_slot = it->first;
                int assigned_num = it->second;
                if (find(coprime_slots[slot].begin(), coprime_slots[slot].end(), assigned_slot) != coprime_slots[slot].end()) {
                    if (gcd(num, assigned_num) != 1) {
                        valid = false;
                        break;
                    }
                }
            }
            if (valid) {
                // 选择num分配给slot
                current_assignment[slot] = num;
                used.insert(num);
                backtrack(index + 1, slots_to_assign, avail_numbers, current_assignment, used, coprime_slots, count);
                // 撤销选择
                current_assignment.erase(slot);
                used.erase(num);
            }
        }
    }
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        cout << solve_case(n, a) << endl;
    }
    return 0;
}