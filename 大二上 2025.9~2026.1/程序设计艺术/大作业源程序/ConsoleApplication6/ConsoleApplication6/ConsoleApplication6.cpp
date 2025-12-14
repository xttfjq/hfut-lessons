#include <iostream>
using namespace std;
int main()
{
	int m, n, r = 1;
	cin >> m;
	cin>>n;
	r = m % n;//空1
	while (m%n)
	{
	m = n;
	n = r;
	}
	
	cout << "m and n's gcd is " << n;
	return 0;
}