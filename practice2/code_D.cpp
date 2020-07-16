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
struct node
{
	bool vis[41];
	int cnt;
};

std::vector<int> inp(MAX2);

node t[4*MAX2];

node single(int ans)
{
	node nq;
	for(int i=0;i<=40;i++)
		nq.vis[i]=0;

	nq.vis[ans] = 1;
	nq.cnt = 1;

	return nq;
}

node combine(node a,node b)
{
	node c;
	c.cnt=0;
	for(int i=0;i<=40;i++)
		c.vis[i] = (a.vis[i]|b.vis[i]);

	for(int i=0;i<=40;i++)
		c.cnt += (int)(c.vis[i]);

	return c;
}

node zinit()
{
	node a;
	for(int i=0;i<=40;i++)
		a.vis[i]=0;

	a.cnt = 0;

	return a;
}

void build(int v,int tl,int tr)
{
	if(tl==tr)
		t[v] = single(inp[tl]);

	else
	{
		int tm=(tl+tr)/2;

		build(2*v,tl,tm);
		build(2*v+1,tm+1,tr);

		t[v] = combine(t[2*v],t[2*v+1]);
	}
}

node seg(int v,int tl,int tr,int l,int r)
{
	if(l>r)
		return zinit();

	else if(tl==l && tr==r)
	{
		return t[v];
	}

	else
	{
		int tm=(tl+tr)/2;

		return combine(seg(2*v,tl,tm,l,min(r,tm)),seg(2*v+1,tm+1,tr,max(l,tm+1),r));
	}
}

void update(int v,int tl,int tr,int pos,int val)
{
	if(tl==tr)
		t[v] = single(val);

	else
	{
		int tm=(tl+tr)/2;

		if(pos<=tm)
			update(2*v,tl,tm,pos,val);
		else
			update(2*v+1,tm+1,tr,pos,val);

		t[v] = combine(t[2*v],t[2*v+1]);
	}
}

int main()
{
	fastio
	int n,m;

	cin>>n>>m;

	for(int i=0;i<n;i++)
		cin>>inp[i];

	build(1,0,n-1);

	for(int i=0;i<m;i++)
	{
		int type;
		cin>>type;

		if(type==1)
		{
			int x,y;
			cin>>x>>y;

			x--;
			y--;

			node ans;

			ans = seg(1,0,n-1,x,y);

			cout<<ans.cnt<<endl;
		}

		else
		{
			int pos,val;

			cin>>pos>>val;
			pos--;

			update(1,0,n-1,pos,val);

		}
	}
}
