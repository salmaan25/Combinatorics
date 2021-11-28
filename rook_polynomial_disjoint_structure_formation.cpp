#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ff first
#define ss second
#define endl "\n"
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x.size())
int powmod(int a,int l, int md){a%=md; int res=1;while(l){if(l&1)res=res*a%md;l/=2;a=a*a%md;}return res;}
int binpow(int a,int l){int res=1;while(l){if(l&1)res=res*a;l/=2;a=a*a;}return res;}
int invmod(int a, int md){return powmod(a,md-2,md);}
typedef long long ll; typedef unsigned long long ull; typedef long double ld;
typedef vector<int> vi; typedef pair<int, int> ii; typedef vector< ii > vii;
#define pb push_back
int __set(int b, int i) {return b|(1LL<<i);} //set ith bit
int __unset(int b, int i) {return b&(~(1UL<<i));}
int __check(int b, int i) {return b&(1LL<<i);} //returns 0 if ith bit is 0
int mulmod(int a, int b, int md) {return (((a%md)*(b%md))%md+md)%md;}
int addmod(int a, int b, int md) {return ((a%md+b%md)%md+md)%md;}
int submod(int a, int b, int md) {return (((a%md-b%md)%md)+md)%md;}
int divmod(int a, int b, int md) {return mulmod(a, powmod(b, md-2, md), md);} //if md is prime;
const ll inf = 0xFFFFFFFFFFFFFFFL; //very large number
priority_queue<int, vector<int>, greater<int> > pq; //for min priority_queue
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

int n,m,k,seen[10][10],mat[10][10],mat1[10][10],dx[]={0,0,1,-1},dy[]={1,-1,0,0};
vii bad;

void dfs(int r, int c, vi& seenr, vi& seenc, int& no,vi& row1, vi& col1) {
	seen[r][c]=1;
	row1.pb(r);
	col1.pb(c);
	for(int i = 0; i < 4; i++) {
		int rr=dx[i]+r,cc=dy[i]+c;
		if(rr>=n || rr < 0 || cc >= m && cc < 0)
			continue;
		if(seen[rr][cc] || !mat1[rr][cc])
			continue;
		if(seenr[rr] || seenc[cc])
			no=1;
		row1.pb(rr);
		col1.pb(cc);
		dfs(rr,cc,seenr,seenc,no,row1,col1);
	}
}

int solve(vi& row, vi& col) {
	memset(mat1,0,sizeof(mat1));
	memset(seen,0,sizeof(seen));
	vi rowpos(n,0),colpos(m,0);
	for(int j = 0; j < n; j++)
		rowpos[row[j]]=j;
	for(int j = 0; j < m; j++)
		colpos[col[j]]=j;
	for(int i = 0; i < k; i++) {
		int ff=0;
		mat1[rowpos[bad[i].ff]][colpos[bad[i].ss]]=1;

		// for(int j = 0; j < n; j++) {
		// 	for(int l = 0; l < m; l++) {
		// 		if(row[j]==bad[i].ff && col[l]==bad[i].ss) {
		// 			ff=1;
		// 			mat1[j][l]=1;
		// 			break;
		// 		}
		// 	}
		// 	if(ff)
		// 		break;
		// }
	}
	vi seenr(n,0),seenc(m,0);
	int no=0;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(!seen[i][j] && mat1[i][j]) {
				if(seenr[i] || seenc[j]) {
					return 0;
				}
				vi row1,col1;
				dfs(i,j,seenr,seenc,no,row1,col1);
				if(no)
					return 0;
				for(int vv: row1)
					seenr[vv]=1;
				for(int vv: col1)
					seenc[vv]=1;
			}
		}
	}
	for(int i: row)
		cout<<i+1<<" ";
	cout<<endl;
	for(int i: col)
		cout<<i+1<<" ";
	cout<<endl;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++)
			cout<<mat1[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
	return 1;
}
signed main(void)
{
	IOS;
	cin>>n>>m; //row*col
	cin>>k; //num of bad points
	for(int i = 0; i < k; i++) {
		int r,c; cin>>r>>c;
		mat[r-1][c-1]=1;
		bad.pb({r-1,c-1});
	}
	vi row(n,0),col(m,0);
	for(int i = 0; i < n; i++)
		row[i]=i;
	// col = {0,4,1,2,3,5,6};
	// solve(row,col);
	do {
		for(int i = 0; i < m; i++)
			col[i]=i;
		do {
			int x = solve(row,col);
			if(x)
				return 0;

		} while(next_permutation(all(col)));
	} while(next_permutation(all(row)));
	return 0;
}