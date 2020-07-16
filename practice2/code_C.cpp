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

struct node
{
	lld cnt[46];
	lld pref[46];
	lld inv;
};

std::vector<lld> inp(MAX2);
node t[4*MAX2];

node single(lld tl)
{
	node a;
	for(lld i=0;i<=45;i++)
	{
		a.cnt[i]=0;
		a.pref[i]=0;
	}

	a.cnt[tl]=1;

	for(lld i=45;i>=1;i--)
		a.pref[i-1] = a.pref[i]+ a.cnt[i-1];

	a.inv = 0;

	return a;
}

node combine(node a,node b)
{
	node c;
	lld ans=0;
	for(lld i=0;i<=45;i++)
	{
		c.cnt[i]=0;
		c.pref[i]=0;
	}

	for(lld i=0;i<=45;i++)
		c.cnt[i] = (a.cnt[i]+b.cnt[i]);

	for(lld i=45;i>=1;i--)
		c.pref[i-1] = c.pref[i]+(lld)c.cnt[i-1];

	for(lld i=1;i<=45;i++)
	{
		// if(b.cnt[i]==1)
		ans += ((b.cnt[i])*(a.pref[i+1]));
	}

	c.inv = a.inv + b.inv + ans;

	return c;
}

node init()
{
	node a;
	for(lld i=0;i<=45;i++)
	{
		a.cnt[i]=0;
		a.pref[i]=0;
	}

	a.inv=0;

	return a;
}

void build(lld v,lld tl,lld tr)
{
	if(tl==tr)
		t[v] = single(inp[tl]);

	else
	{
		lld tm=(tl+tr)/2;

		build(2*v,tl,tm);
		build(2*v+1,tm+1,tr);

		t[v] = combine(t[2*v],t[2*v+1]);
	}
}

node seg(lld v,lld tl,lld tr,lld l,lld r)
{
	if(l>r)
		return init();

	if(tl==l && tr==r)
		return t[v];

	else
	{
		lld tm=(tl+tr)/2;

		return combine(seg(2*v,tl,tm,l,min(r,tm)),seg(2*v+1,tm+1,tr,max(l,tm+1),r));
	}
}

void update(lld v,lld tl,lld tr,lld pos,lld val)
{
	if(tl==tr)
		t[v] = single(val);

	else
	{
		lld tm=(tl+tr)/2;

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
	lld n,m;

	cin>>n>>m;

	for(lld i=0;i<n;i++)
		cin>>inp[i];

	build(1,0,n-1);

	for(lld i=0;i<m;i++)
	{
		lld ty;
		cin>>ty;

		if(ty==1)
		{
			lld l,r;
			cin>>l>>r;
			l--;
			r--;

			node ans=seg(1,0,n-1,l,r);

			cout<<ans.inv<<endl;
		}

		else
		{
			lld pos,val;
			cin>>pos>>val;
			pos--;

			update(1,0,n-1,pos,val);
		}
	}

}
