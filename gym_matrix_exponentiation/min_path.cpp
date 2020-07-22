#include<bits/stdc++.h>
#define lld long long
#define pb push_back
#define mk make_pair
#define MAX (lld)2e18+7
#define lim (lld)1e9+7
#define MAX2 (lld)2e5+9
#define ff first
#define ss second
#define fastio ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;

const lld mod=lim;


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

lld n;

matrix mul(matrix a, matrix b)
{
	matrix c(n+1,vector<lld>(n+1,MAX));

	for(lld i=1;i<=n;i++)
		for(lld j=1;j<=n;j++)
		{
			lld flag=0;	
			for(lld t=1;t<=n;t++)
			{	
				if(a[i][t]!=MAX && b[t][j]!=MAX)
				{	
					flag=1;
					c[i][j] = min(c[i][j],(a[i][t]+b[t][j]));
				}

			}

			if(!flag)
				c[i][j] = MAX;
		}

	return c;
}

matrix init()
{
	matrix a(n+1,vector<lld>(n+1,MAX));

	for(lld i=1;i<=n;i++)
		a[i][i] = 0;

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

	lld m,k,total=MAX;
	cin>>n>>m>>k;

	matrix graph(n+1,vector<lld>(n+1,MAX));
	matrix ans(n+1,vector<lld>(n+1,MAX));

	for(lld i=1;i<=m;i++)
	{
		lld l,r,w;
		cin>>l>>r>>w;

		graph[l][r]=w;
	}

	ans = pow(graph,k);

	for(lld i=1;i<=n;i++)
	{
		for(lld j=1;j<=n;j++)
		{	
			total = min(total,ans[i][j]);
		}
	}

	if(total>=MAX)
		cout<<"IMPOSSIBLE"<<endl;

	else
		cout<<total<<endl;
}