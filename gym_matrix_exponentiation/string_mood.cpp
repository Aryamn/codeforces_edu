#include<bits/stdc++.h>
#define lld long long
#define pb push_back
#define mk make_pair
#define MAX (lld)1e18+7
#define lim (lld)1e9+7
#define MAX2 (lld)2e5+9
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


lld extend_gcd(lld a, lld b, lld& x, lld& y) {
    if (b == 0) { x = 1;y = 0;return a;}
    lld x1, y1;
    lld d = extend_gcd(b, a % b, x1, y1);
    x = y1; y = x1 - y1 * (a / b);return d;	}

lld rowNum[]={-1,0,0,1};
lld colNum[]={0,-1,1,0};

typedef vector<vector<lld>> matrix;

matrix mul(matrix a, matrix b)
{
	matrix c(k+1,vector<lld>(k+1));

	for(lld i=1;i<=2;i++)
		for(lld j=1;j<=2;j++)
			for(lld t=1;t<=2;t++)
			{	
				c[i][j] += (a[i][t]*b[t][j]);
				c[i][j] %= mod;
			}

	return c;
}

matrix init()
{
	matrix a(k+1,vector<lld>(k+1));

	for(lld i=1;i<=k;i++)
		a[i][i] = 1;

	return a;
}

matrix pow(matrix a,lld p)
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

int main()
{
	fastio

	lld n;
	cin>>n;

	matrix ans(k+1,vector<lld>(k+1));

	ans[1][1] = 19;
	ans[1][2] = 7;
	ans[2][1] = 6;
	ans[2][2] = 20;

	matrix res = pow(ans,n);

	cout<<res[1][1]<<endl;
}