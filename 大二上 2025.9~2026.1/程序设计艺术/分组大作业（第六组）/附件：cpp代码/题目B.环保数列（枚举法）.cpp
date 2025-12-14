#include <iostream>
using namespace std;
//判断n是否是神奇数
bool isMagicNumber(long long n) 
{
    if (n <= 1) return false;
    if (n % 2 == 1) return true;		    //任何大于1的奇数都是神奇数
    if (n % 4 == 0 && n > 4) return true;	//任何能被4整除且大于4的偶数都是神奇数
    return false;
}
// 枚举法求第x个神奇数
long long findMagicNumber_enum(int x) 
{
    if (x <= 0) return 0;
    int count = 0;
    long long num = 1;
    while (count < x) 
	{
        num++;
        if (isMagicNumber(num)) count++;
    }
    return num;
}
int main() 
{
    int T;
    cin >> T;
    while (T--) 
	{
        int x;
        cin >> x;
        cout << findMagicNumber_enum(x) << endl;
    }
    return 0;
}
