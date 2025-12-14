#include <iostream>
using namespace std;
int main()
{
	double N,M,K;
	cin>>N>>M>>K;
	int count=0;
	while(N>M)
	{
		N=N*(1-K*1.0/100);
		count++;
	}
	cout<<count<<endl;
	return 0;
}
