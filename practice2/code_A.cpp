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

lld teven[4*MAX2],todd[4*MAX2];
std::vector<lld> even;
std::vector<lld> odd;

void buildeven(lld v,lld tl,lld tr)
{
	if(tl==tr)
		teven[v] = even[tl];
	else
	{
		lld tm=(tl+tr)/2;
		buildeven(2*v,tl,tm);
		buildeven(2*v+1,tm+1,tr);

		teven[v] = teven[2*v]+teven[2*v+1];
	}

}

lld sumeven(lld v,lld tl,lld tr,lld l,lld r)
{
	if(l>r)
		return 0;
	else if(tl==l && r==tr)
		return teven[v];
	else
	{
		lld tm=(tl+tr)/2;
		return sumeven(2*v,tl,tm,l,min(r,tm))+sumeven(2*v+1,tm+1,tr,max(l,tm+1),r);
	}
}

void updateeven(lld v,lld tl,lld tr,lld pos,lld val)
{
	if(tl==tr)
		teven[v]=val;

	else
	{
		lld tm=(tl+tr)/2;

		if(pos<=tm)
			updateeven(2*v,tl,tm,pos,val);

		else
			updateeven(2*v+1,tm+1,tr,pos,val);

		teven[v] = teven[2*v]+teven[2*v+1];
	}
}

void buildodd(lld v,lld tl,lld tr)
{
	if(tl==tr)
		todd[v] = odd[tl];
	else
	{
		lld tm=(tl+tr)/2;
		buildodd(2*v,tl,tm);
		buildodd(2*v+1,tm+1,tr);

		todd[v] = todd[2*v]+todd[2*v+1];
	}

}

lld sumodd(lld v,lld tl,lld tr,lld l,lld r)
{
	if(l>r)
		return 0;
	else if(tl==l && r==tr)
		return todd[v];
	else
	{
		lld tm=(tl+tr)/2;
		return sumodd(2*v,tl,tm,l,min(r,tm))+sumodd(2*v+1,tm+1,tr,max(l,tm+1),r);
	}
}

void updateodd(lld v,lld tl,lld tr,lld pos,lld val)
{
	if(tl==tr)
		todd[v]=val;

	else
	{
		lld tm=(tl+tr)/2;

		if(pos<=tm)
			updateodd(2*v,tl,tm,pos,val);

		else
			updateodd(2*v+1,tm+1,tr,pos,val);

		todd[v] = todd[2*v]+todd[2*v+1];
	}
}

int main()
{
	fastio
	lld n,x,m;
	cin>>n;

	for(lld i=0;i<n;i++)
	{
		cin>>x;
		if(i%2==0)
		{
			even.pb(x);
			odd.pb(0);
		}

		else
		{
			odd.pb(x);
			even.pb(0);
		}
	}

	buildeven(1,0,n-1);
	buildodd(1,0,n-1);

	cin>>m;

	for(lld i=0;i<m;i++)
	{
		lld type;
		cin>>type;

		if(type==1)
		{
			lld l,r;
			cin>>l>>r;
			l--;
			r--;
			lld ans =sumeven(1,0,n-1,l,r)-sumodd(1,0,n-1,l,r);
			
			if(l%2==0)
				cout<<ans<<endl;

			else
				cout<<-ans<<endl;
		}

		else
		{
			lld pos,val;
			cin>>pos>>val;

			pos--;

			if(pos%2==0)
				updateeven(1,0,n-1,pos,val);
			else
				updateodd(1,0,n-1,pos,val);

		}
	}
}
