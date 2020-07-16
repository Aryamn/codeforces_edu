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

int rowNum[]={-1,0,0,1};
int colNum[]={0,-1,1,0};

struct wrap
{
	int arr[4];
};

// int t[4*MAX2][4];
// int inp[MAX2][4];

wrap t[4*MAX2];
wrap inp[MAX2];

int r;

wrap combine(wrap b,wrap c)
{
	wrap a;

	a.arr[0] = (b.arr[0])*(c.arr[0])+(b.arr[1])*(c.arr[2]);
	a.arr[0] %= r;
	a.arr[1] = (b.arr[0])*(c.arr[1])+(b.arr[1])*(c.arr[3]);
	a.arr[1] %= r;
	a.arr[2] = (b.arr[2])*(c.arr[0])+(b.arr[3])*(c.arr[2]);
	a.arr[2] %= r;
	a.arr[3] = (b.arr[2])*(c.arr[1])+(b.arr[3])*(c.arr[3]);
	a.arr[3] %= r;

	return a;
}

wrap init()
{
	wrap a;
	a.arr[0]=a.arr[3]=1;
	a.arr[2]=a.arr[1]=0;

	return a;
}

void build(int v,int tl,int tr)
{
	if(tl==tr)
	{
		for(int i=0;i<4;i++)
			t[v].arr[i] = inp[tl].arr[i];
	}

	else
	{
		int tm=(tl+tr)/2;

		build(2*v,tl,tm);
		build(2*v+1,tm+1,tr);

		t[v] = combine(t[2*v],t[2*v+1]);
	}
}

wrap prod(int v,int tl,int tr,int l,int r)
{
	if(l>r)
		return init();

	if(tl==l && tr==r)
		return t[v];

	else
	{
		int tm=(tl+tr)/2;

		return combine( prod(2*v,tl,tm,l,min(tm,r)) , prod(2*v+1,tm+1,tr,max(tm+1,l),r) );

	}

}

int main()
{
	fastio
	int n,m;
	cin>>r>>n>>m;

	

	for(int i=0;i<n;i++)
	{
		cin>>inp[i].arr[0]>>inp[i].arr[1]>>inp[i].arr[2]>>inp[i].arr[3];
	}

	build(1,0,n-1);

	for(int i=0;i<m;i++)
	{
		int l,r;
		cin>>l>>r;
		l--;
		r--;

		wrap ans;

		ans=prod(1,0,n-1,l,r);

		printf("%d %d\n",ans.arr[0],ans.arr[1] );
		printf("%d %d\n\n",ans.arr[2],ans.arr[3] );
	}


}
