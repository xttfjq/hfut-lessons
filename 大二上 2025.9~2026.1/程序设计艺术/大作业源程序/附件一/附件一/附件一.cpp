#include <iostream> // 确保包含了这个头文件
#include <list>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    list<int> circle;
    for (int i = 1; i <= N; ++i) {
        circle.push_back(i);
    }

    auto it = circle.begin();
    while (circle.size() > 1) {
        // 跳过 M-1 个小朋友
        for (int i = 1; i < M; ++i) {
            it++;
            if (it == circle.end()) {
                it = circle.begin(); // 如果到了末尾就从头开始
            }
        }
        // 删除当前小朋友
        it = circle.erase(it);
    }

    // 输出最后一个小朋友
    cout << circle.front() << endl; // 确保使用 std::endl

    return 0;
}
