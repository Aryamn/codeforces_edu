#include<bits/stdc++.h>
#define lld long long
#define pb push_back
#define mk make_pair
#define MAX (lld)1e18+7
#define lim (lld)1e9+7
#define MAX2 (int)2e5+9
#define ff first
#define ss second
#define fastio ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;

const lld mod=lim;
const int k=2;

lld power(lld x, lld y, lld p)  
{   lld res = 1;     x = x % p; if (x == 0) return 0;  
  
    while (y > 0)  
    { if (y & 1) res = (res*x) % p;  y = y>>1; x = (x*x) % p;   }  
    return res;  } 


int extend_gcd(int a, int b, int& x, int& y) {
    if (b == 0) { x = 1;y = 0;return a;}
    int x1, y1;
    int d = extend_gcd(b, a % b, x1, y1);
    x = y1; y = x1 - y1 * (a / b);return d;	}


typedef vector<vector<double>> matrix;

matrix mul(matrix a, matrix b)
{
	matrix c(k+1,vector<double>(k+1));

	for(int i=1;i<=2;i++)
		for(int j=1;j<=2;j++)
			for(int t=1;t<=2;t++)
				c[i][j] += (a[i][t]*b[t][j]);

	return c;
}

matrix init()
{
	matrix a(k+1,vector<double>(k+1));

	for(int i=1;i<=k;i++)
		a[i][i] = 1.0;

	return a;
}

matrix pow(matrix a,int p)
{
	matrix res = init();

	while(p>0)
	{
		if(p&1)
			res = mul(res,a);

		p/=2;

		a = mul(a,a);
	}

	return res;
}

int rowNum[]={-1,0,0,1};
int colNum[]={0,-1,1,0};

int main()
{
	fastio

	int n;
	double p;

	cin>>n>>p;

	matrix ans(k+1,vector<double>(k+1));

	ans[1][1] = 1-p;
	ans[1][2] = p;
	ans[2][1] = p;
	ans[2][2] = 1-p;

	matrix res = pow(ans,n);

	printf("%.7lf\n", res[1][1]);
}
