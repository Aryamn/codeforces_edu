#include<bits/stdc++.h>
#define lld unsigned long long
#define pb push_back
#define mk make_pair
#define MAX (lld)1e18+7
#define lim (lld)1e9+7
#define MAX2 (lld)2e5+9
#define ff first
#define ss second
#define fastio ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;



lld power(lld x, lld y)  
{   lld res = 1;     x = x ; if (x == 0) return 0;  
  
    while (y > 0)  
    { if (y & 1) res = (res*x);  y = y>>1; x = (x*x) ;   }  
    return res;  } 


lld extend_gcd(lld a, lld b, lld& x, lld& y) {
    if (b == 0) { x = 1;y = 0;return a;}
    lld x1, y1;
    lld d = extend_gcd(b, a % b, x1, y1);
    x = y1; y = x1 - y1 * (a / b);return d;	}


const lld mod = 4294967296;

int X[8] = { 2, 1, -1, -2, -2, -1, 1, 2 }; 
int Y[8] = { 1, 2, 2, 1, -1, -2, -2, -1 }; 

typedef vector<vector<lld>> matrix;
const lld n=8;
matrix idn;
matrix mat(64,vector<lld>(64));
matrix dp[33];
matrix mul(matrix a, matrix b)
{
	matrix c(64,vector<lld>(64));

	for(lld i=0;i<64;i++)
		for(lld j=0;j<64;j++)
			for(lld t=0;t<64;t++)
			{	
				c[i][j] = (c[i][j]+(a[i][t])*(b[t][j])%mod)%mod;
				
			}

	return c;
}



matrix init()
{
	matrix a(64,vector<lld>(64));

	for(lld i=0;i<64;i++)
		a[i][i] = 1;

	return a;
}

matrix pow(matrix a,lld p)
{
	matrix res = idn;

	while(p>0)
	{
		if(p&1)
			res = mul(res,a);

		p/=2;

		a = mul(a,a);
	}

	return res;
}

void precal(matrix a,lld n)
{
	int i=0;
	while(n>0)
	{
		dp[i] = pow(a,n);
		n/=2;
		i++;
	}

	dp[i] = idn;
}

matrix sum(matrix a,matrix b)
{
	matrix c(64,vector<lld>(64));

	for(int i=0;i<64;i++)
	{
		for(int j=0;j<64;j++)
			c[i][j] = (a[i][j]+b[i][j])%mod;
	}

	return c;
}

matrix final(matrix a,lld power,lld n)
{
	if(n==0)
		return idn;
	
	else if(n==1)
		return a;

	else 
	{
		matrix temp = final(a,power+1,n/2);

		if(n%2==0)
			return (mul(temp,sum(idn,dp[power+1])));
		else
			return sum((mul(temp,sum(idn,dp[power+1]))),dp[power]);
	}


}

void possible(lld p,lld q)
{

	for(lld i=0;i<8;i++)
	{
		int x = p+X[i];
		int y = q+Y[i];

		if(x>=0 && y>=0 && x<n && y<n && (mat[8*(p)+q][8*(x)+y]==0 && mat[8*(x)+y][8*(p)+q]==0 ))
		{
			mat[8*(p)+q][8*(x)+y] = 1;
			mat[8*(x)+y][8*(p)+q] = 1;
			possible(x,y);
		}
	}
}

int main()
{
	fastio
	lld k,res=0;
	cin>>k;
	
	possible(0,0);
	idn = init();

	precal(mat,k);
	matrix ans = final(mat,0,k);

	for(int i=0;i<64;i++)
	{	
		res+=ans[0][i];
		res%=mod;
	}

	if(k!=0)
	cout<<(res+1)<<endl;
	
	else
		cout<<"1 \n";
}