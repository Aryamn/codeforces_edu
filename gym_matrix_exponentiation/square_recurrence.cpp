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

lld siz ;

typedef vector<vector<lld>> matrix;
 
matrix mul(matrix a, matrix b)
{
	matrix c(siz+1,vector<lld>(siz+1));
 
	for(lld i=1;i<=siz;i++)
		for(lld j=1;j<=siz;j++)
			for(lld t=1;t<=siz;t++)
			{	
				c[i][j] += (a[i][t]*b[t][j]);
				c[i][j] %= mod;
			}
 
	return c;
}
 
matrix init()
{
	matrix a(siz+1,vector<lld>(siz+1));
 
	for(lld i=1;i<=siz;i++)
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
	lld n,k;
	cin>>n>>k;
	siz = n+3;


	matrix mat(siz+1,vector<lld>(siz+1,0));
	std::vector<lld> v(n);
	std::vector<lld> coff(n+1);	

	for(lld i=2;i<=n;i++)
		mat[i][i-1] = 1;

	for(lld i=0;i<n;i++)
		cin>>v[i];

	for(lld i=1;i<=n;i++)
		cin>>coff[i];

	for(lld i=1;i<=n;i++)
		mat[1][i] = coff[i];

	lld p,q,r;
	cin>>p>>q>>r;

	mat[1][n+1] = p;
	mat[1][n+2] = q;
	mat[1][n+3] = r;
	mat[n+1][n+1] = 1;
	mat[n+2][n+1] = 1;
	mat[n+2][n+2] = 1;
	mat[n+3][n+1] = 1;
	mat[n+3][n+2] = 2;
	mat[n+3][n+3] = 1;

	lld res=0;

		
	matrix ans = pow(mat,k);

	for(lld i=1;i<=n;i++)
	{
		res += ans[n][i]*v[n-i];
		res%=mod;
	}

	res = (res + ans[n][n+1])%mod;
	res = (res + ans[n][n+2]*n)%mod;
	res = (res + ans[n][n+3]*n*n)%mod;
		

	cout<<res%mod<<endl;
}