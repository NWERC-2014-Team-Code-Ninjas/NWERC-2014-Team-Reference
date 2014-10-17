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
