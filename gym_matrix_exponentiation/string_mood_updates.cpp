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

struct matrix 
{
	lld arr[4];
};

matrix happy,sad,vowel,emp,idn;
matrix t[4*MAX2];
string s;

matrix combine(matrix a,matrix b)
{
	matrix c;
	c.arr[0] = a.arr[0]*b.arr[0] + a.arr[1]*b.arr[2];
	c.arr[1] = a.arr[0]*b.arr[1] + a.arr[1]*b.arr[3];
	c.arr[2] = a.arr[2]*b.arr[0] + a.arr[3]*b.arr[2];
	c.arr[3] = a.arr[2]*b.arr[1] + a.arr[3]*b.arr[3];

	c.arr[0]%=mod;
	c.arr[1]%=mod;
	c.arr[2]%=mod;
	c.arr[3]%=mod;

	return c;
}

void build(lld v,lld tl,lld tr)
{
	if(tl==tr)
	{
		if(s[tl]=='A'||s[tl]=='E'||s[tl]=='I'||s[tl]=='O'||s[tl]=='U')
			t[v] = vowel;

		else if(s[tl]=='H')
			t[v] = happy;

		else if(s[tl]=='S'||s[tl]=='D')
			t[v] = sad;

		else if(s[tl]=='?')
			t[v] = emp;

		else
			t[v] = idn;
	}

	else
	{
		lld tm=(tl+tr)/2;

		build(2*v,tl,tm);
		build(2*v+1,tm+1,tr);

		t[v] = combine(t[2*v],t[2*v+1]);
	}
}

void update(lld v,lld tl,lld tr,lld pos,char val)
{
	if(tl==tr)
	{
		if(val=='A'||val=='E'||val=='I'||val=='O'||val=='U')
			t[v] = vowel;

		else if(val=='H')
			t[v] = happy;

		else if(val=='S'||val=='D')
			t[v] = sad;

		else if(val=='?')
			t[v] = emp;

		else
			t[v] = idn;
	}

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
	lld n,q;
	cin>>n>>q;

	cin>>s;

	happy.arr[0] = happy.arr[2] = 1;
	happy.arr[1] = happy.arr[3] = 0;

	sad.arr[0] = sad.arr[2] = 0;
	sad.arr[1] = sad.arr[3] = 1;

	vowel.arr[0] = vowel.arr[3] = 0;
	vowel.arr[1] = vowel.arr[2] = 1;

	idn.arr[0] = idn.arr[3] = 1;
	idn.arr[1] = idn.arr[2] = 0;

	emp.arr[0] = 19;
	emp.arr[1] = 7;
	emp.arr[2] = 6;
	emp.arr[3] = 20;

	build(1,0,n-1);

	cout<<t[1].arr[0]<<endl;
	for(lld i=0;i<q;i++)
	{
		lld pos;
		char val;

		cin>>pos;
		cin>>val;

		pos--;

		update(1,0,n-1,pos,val);

		cout<<t[1].arr[0]<<endl;
	}
}