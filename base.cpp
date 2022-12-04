#include <bits/stdc++.h>
#include <math.h>
typedef long long ll;
using namespace std;
ll i, j, t, a, n, m, b, c, d, f, g;
int x[100100];
int main()
{
  ios::sync_with_stdio(0);
	cin.tie(0);

	n=1000000000;
	m=0;
	for (a=2; a<n; a++)
	{
		if (n%a==0) m++; 
	}
	if (m==0) cout<<"Prime number"<<endl; 
		else cout<<"Composite number"<<endl; 
}
/*

*/
