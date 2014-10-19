#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <stack>
#include <queue>
#include <map>
#include <sstream>
#include <ctime>
#include <numeric>
#include <cstring>
#include <functional>

using namespace std;

typedef vector<int> VI;
typedef pair<int, int> PII;
typedef vector<PII> VPII;
typedef vector<string> VS;
typedef map<string, int> MSI;
typedef long long int LL;
typedef unsigned long long int ULL;

#define REP(i, n) for (int i = 0; i < n; ++i)
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define FORD(i, a, b) for (int i = a-1; i >= b; --i)
#define ALL(x) x.begin(), x.end()
#define SIZE(x) (int)x.size()
#define FOREACH(it, c) for (__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define INF 1023456789
#define PB push_back
#define MP make_pair
#define DEBUG(x) cerr<<#x<<": "<<x<<endl;
#define ERR(...) fprintf(stderr, __VA_ARGS__);
#define EPS 1e-9

int main(void) {
    srand(time(NULL));
    cout << rand()%2134 << endl;
    double first = 1.4;
    DEBUG(first);

    return 0;
}

----------Extended GCD algorithm----------
struct ans {
    int x, y, gcd;
};

//To find an inverse of a mod n, a must be coprime with n and we sould run
//extGcd(a, n) and take the x value of the result - this is the inverse
//a * x + b * y = gcd(a,b)
ans extGcd(int a, int b) {
    //PRE: a > b ??? seems to work without it
    ans res;
    if (b == 0) {res.x=1; res.y=0; res.gcd=a;}
    else {
	ans prev = extGcd(b, a % b);
	res.x = prev.y; res.y = prev.x - (a / b) * prev.y; res.gcd = prev.gcd;
    }
    return res;
}

----------Online LCA O(n log n)----------
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_N 1001
#define MAX_LOG 10

struct interval {
    int in, out;
};

vector<int> graph[MAX_N];
int pred[MAX_N][MAX_LOG];
int depth[MAX_N];
interval processTimes[MAX_N];
int n; //number of vertices in the tree

int dfs(int v, int time) { 
    processTimes[v].in = ++time;
    for (int i=0; i<graph[v].size(); i++) {
	int cand = graph[v][i];
	if (depth[cand] == -1) {
	    depth[cand] = depth[v] + 1;
	    pred[cand][0] = v;
	    time = dfs(cand, time);
	}
    }
    processTimes[v].out = ++time;
    return time;
}

void calcPredTable(void) {
    int maxDepth = 0;
    for (int i=1; i<=n; i++) maxDepth = max(depth[i], maxDepth);
    for (int dist=2, j=1; dist <= maxDepth; j++, dist*=2) {
	for (int i=1; i<=n; i++) pred[i][j] = pred[pred[i][j-1]][j-1];
    }
}

void preprocess(int root) {
    for (int i=1; i<=n; i++) depth[i] = -1;
    depth[root] = 0; pred[root][0] = 0;
    dfs(root, 0);
    calcPredTable();
}

bool contains(interval a, interval b) {
    return (a.in < b.in && a.out > b.out);
}

int reachDepth(int v, int d) {
    if (depth[v] == d) return v;
    int i=0;
    while (depth[pred[v][i+1]] >= d) i++;
    return reachDepth(pred[v][i], d);
}

int lca(int va, int vb) {
    if (va == vb || contains(processTimes[va], processTimes[vb])) return va;
    if (contains(processTimes[vb], processTimes[va])) return vb;
    if (depth[va] > depth[vb]) va = reachDepth(va, depth[vb]);
    if (depth[va] < depth[vb]) vb = reachDepth(vb, depth[va]);
    while(va != vb) {
	int i=0;
	for (; pred[va][i+1] != pred[vb][i+1]; i++)
	    ;
	va = pred[va][i]; vb = pred[vb][i];
    }
    return va;
}

----------Maximum Flow in a directed graph (derivation of the Dinic's method) 
O(n^4) with a VERY small const----------

#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define MAX_N 5001
const int inf = 2000000000; 

int begin[MAX_N];
int dist[MAX_N];
vector<int> graph[MAX_N];
int c[MAX_N][MAX_N];
bool vis[MAX_N];
queue<int> q;

void bfsIn(int v) {
    for (int i=0; i<graph[v].size(); i++) {
	int cand = graph[v][i];
	if (!vis[cand] && c[v][cand] > 0) {
	    vis[cand] = true; dist[cand] = dist[v] + 1;
	    q.push(cand);
	}
    }
}

bool bfs(int s, int t) {
    for (int i=s+1; i<=t; i++) {
	dist[i] = 0; vis[i] = false;
    }
    vis[s]=true; dist[s]=0; q.push(s);
    while(!q.empty()) {
	int v = q.front(); q.pop();
	bfsIn(v);
    }
    return vis[t];
}

int dfs(int v, int t, int min_cap) {
    int res = 0;
    if (v == t || min_cap == 0) return min_cap;
    for (int& i=begin[v]; i<graph[v].size(); i++) {
	int cand = graph[v][i];
	if (dist[cand] == dist[v]+1 && c[v][cand] > 0) {
	    int newFlow = dfs(cand, t, min(min_cap, c[v][cand]));
	    c[v][cand] -= newFlow;
	    c[cand][v] += newFlow;
	    min_cap -= newFlow;
	    res += newFlow;
	    if (min_cap == 0) break;
	}
    }
    return res;
}

int maxFlow(int s, int t) {
    long long result = 0;
    while (bfs(s,t)) {
        for (int i=s; i<=t; i++) begin[i] = 0;
        int init_cap = inf;
	result += dfs(s,t,init_cap);
    }
    return result;
}

----------Maximum matching in the bipartite graph O(n^2.5)----------
#include <algorithm>
using namespace std;
#define MAX_X 201
#define MAX_Y 401

vector<int> graph[MAX_X];
bool vis[MAX_X];
int matchX[MAX_X];
int matchY[MAX_Y];
int sizeX, sizeY;

int dfs(int x) {
    vis[x] = true;
    for (int i=0; i<graph[x].size(); i++) {
	int y = graph[x][i];
	if (matchY[y] == -1 || (!vis[matchY[y]] && dfs(matchY[y]))) {
	    matchY[y] = x;
	    matchX[x] = y;
	    return 1;
	}
    }
    return 0;
}

int maxMatching(void) {
    for (int i=1; i<=sizeX; i++) random_shuffle(graph[i].begin(), graph[i].end());
    for (int i=1; i<=sizeX; i++) matchX[i] = -1;
    for (int i=1; i<=sizeY; i++) matchY[i] = -1;
    int res = 0; bool change = true;
    while(change) {
	change = false;
	for (int i=1; i<=sizeX; i++) vis[i] = false;
	for (int i=1; i<=sizeX; i++) {
	    if (matchX[i] == -1 && !vis[i] && dfs(i)) { 
		res++; change = true; 
	    }
	}
    }
    return res;
}


----------KMP O(n + m)-------------
#include<string>
#include<cstdio>

#define MAX_M 1001

int prefixes[MAX_M];
std::string t, p;

//compute longest prefixes of P which are proper suffixes of P_q
int prefix() {
    prefixes[1] = 0;
    int k = 0;
    for(int q = 2; q <= p.length(); q++) {
        while (k > 0 && p[k] != p[q-1]) k = prefixes[k];
        if (p[k] == p[q-1]) k++;
        prefixes[q] = k;
    }
}
//print out shifts for which pattern occurs in target
void kmp(){
    prefix();
    int q = 0;
    for (int i = 1; i <= t.length(); i++) {
        while(q > 0 && p[q] != t[i-1]) q = prefixes[q];
        if (p[q] == t[i-1]) q++;
        if (q == p.length()) {
            printf("valid shift: %d\n", i - (int) p.length()); q = prefixes[q];
        }
    }
}


