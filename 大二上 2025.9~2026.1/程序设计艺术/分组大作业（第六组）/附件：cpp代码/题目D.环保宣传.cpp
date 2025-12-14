#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    int n, k;  // n：路口数，k：装置数
    cin >> n >> k;
    vector<int> cover(n - 1, 0);  // 存储每个区间的覆盖人数（共n-1个区间）

    // 读取n-1行数据：第i行对应"第i+1个路口"的所有通行路线
    for (int i = 0; i < n - 1; ++i)
    {  // i：0-based，对应题目中的"第i+1个路口"
        int len = n - (i + 1);  // 第i+1个路口的路线数量：到第n个路口最多有n-(i+1)条路线
        for (int j = 0; j < len; ++j) 
        {  // j：0-based，对应"到第(i+1)+(j+1)个路口"的路线
            int people;
            cin >> people;
            // 该路线经过的区间：从第i个区间到第i+j个区间（共j+1个区间）
            //区间i对应路口i+1和i+2之间
            for (int seg = i; seg <= i + j; ++seg) {
                cover[seg] += people;
            }
        }
    }

    // 滑动窗口计算连续k个区间的最大和
    int max_total = INT_MIN;
    int current_sum = 0;

    // 初始化第一个窗口（前k个区间）
    for (int i = 0; i < k; ++i) {
        current_sum += cover[i];
    }
    max_total = current_sum;

    // 滑动窗口更新
    for (int i = k; i < n - 1; ++i) {
        current_sum += cover[i] - cover[i - k];  // 加入新区间，移除旧区间
        if (current_sum > max_total) {
            max_total = current_sum;
        }
    }

    cout << max_total << endl;

    return 0;
}