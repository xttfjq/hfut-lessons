#include <iostream>
using namespace std;
//数学公式法求第x个神奇数
long long findMagicNumber_formula(int x) {
    if (x <= 3) 
	{
        return 2 * x + 1;        //前3个：3,5,7
    } 
	else 
	{
        // 从第4个开始分组
        int group = (x - 4) / 3 + 2;  //组号从2开始
        int position = (x - 4) % 3;   //组内位置
        if (position == 0) return 4 * group;            //每组第一个：4的倍数
        else if (position == 1) return 4 * group + 1;   //每组第二个：4的倍数+1
 		else return 4 * group + 3;                      //每组第三个：4的倍数+3
    }
}
int main() {
    int T;
    cin >> T;
    while (T--) 
	{
        int x;
        cin >> x;
        cout << findMagicNumber_formula(x) << endl;
    }
    return 0;
}