#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<utility>
#include<queue>
#include<stack>
#include<cstring>
#include<set>
#include<map>
#include<unordered_map>
#include<unordered_set>
#include<cmath>
#include<numeric>
#include<bitset>
#include<sstream>
#include<functional>
#include<cstdio>

// 常用类型别名
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vl vector<ll>
#define vvi vector<vector<int>>
#define vvl vector<vector<ll>>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for(int i = a; i < b; ++i)
#define per(i, a, b) for(int i = a; i > b; --i)
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define MOD 1000000007
#define EPS 1e-9

using namespace std;

// 常用常量
const int N = 1e5 + 10;
const int dx[] = {-1, 0, 1, 0}; // 上下左右
const int dy[] = {0, 1, 0, -1};

// 快速IO
void fast_io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

// 快速幂
ll quick_pow(ll a, ll b, ll mod = MOD) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// GCD和LCM
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

// 常用数学函数
bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// 前缀和
template<typename T>
vector<T> prefix_sum(const vector<T>& arr) {
    vector<T> prefix(arr.size() + 1, 0);
    for (int i = 0; i < (int)arr.size(); ++i) {
        prefix[i + 1] = prefix[i] + arr[i];
    }
    return prefix;
}

// 二维前缀和
template<typename T>
vector<vector<T>> prefix_sum_2d(const vector<vector<T>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    vector<vector<T>> prefix(n + 1, vector<T>(m + 1, 0));
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            prefix[i][j] = prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1] + matrix[i-1][j-1];
        }
    }
    return prefix;
}

// 并查集模板
struct DSU {
    vector<int> f;
    vector<int> sz;
    
    DSU(int n) {
        f.resize(n);
        sz.resize(n, 1);
        for (int i = 0; i < n; ++i) f[i] = i;
    }
    
    int find(int x) {
        return f[x] == x ? x : (f[x] = find(f[x]));
    }
    
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) swap(x, y);
        f[y] = x; 
        sz[x] += sz[y];
        return true;
    }
    
    bool same(int x, int y) { return find(x) == find(y); }
    int size(int x) { return sz[find(x)]; }
};

// 线段树模板（区间求和）
struct SegTree {
    vector<ll> tree;
    vector<ll> lazy;
    int n;
    
    SegTree(int size) {
        n = size;
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }
    
    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = (start + end) / 2;
        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
    
    void push_down(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node] * (end - start + 1);
            if (start != end) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
    
    void update(int node, int start, int end, int l, int r, int val) {
        push_down(node, start, end);
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            lazy[node] += val;
            push_down(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        update(2 * node, start, mid, l, r, val);
        update(2 * node + 1, mid + 1, end, l, r, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
    
    ll query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        push_down(node, start, end);
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        ll p1 = query(2 * node, start, mid, l, r);
        ll p2 = query(2 * node + 1, mid + 1, end, l, r);
        return p1 + p2;
    }
};

// 图论算法
// 邻接表表示的图
struct Graph {
    int n;
    vector<vector<pii>> adj; // 邻接表 <节点, 权重>
    
    Graph(int size) {
        n = size;
        adj.resize(n);
    }
    
    void add_edge(int u, int v, int w = 1, bool directed = false) {
        adj[u].push_back(make_pair(v, w));
        if (!directed) adj[v].push_back(make_pair(u, w));
    }
    
    // BFS（无权最短路）
    vector<int> bfs(int start) {
        vector<int> dist(n, -1);
        queue<int> q;
        dist[start] = 0;
        q.push(start);
        
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = 0; i < (int)adj[u].size(); ++i) {
                int v = adj[u][i].first;
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return dist;
    }
    
    // Dijkstra算法（单源最短路）
    vector<ll> dijkstra(int start) {
        vector<ll> dist(n, LLINF);
        dist[start] = 0;
        priority_queue<pll, vector<pll>, greater<pll>> pq;
        pq.push(make_pair(0, start));
        
        while (!pq.empty()) {
            pll top = pq.top(); pq.pop();
            ll d = top.first;
            int u = top.second;
            if (d > dist[u]) continue;
            
            for (int i = 0; i < (int)adj[u].size(); ++i) {
                int v = adj[u][i].first;
                int w = adj[u][i].second;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
        return dist;
    }
};

// Kruskal算法（最小生成树）
struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

ll kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    ll total_weight = 0;
    
    for (int i = 0; i < (int)edges.size(); ++i) {
        const Edge& edge = edges[i];
        if (!dsu.same(edge.u, edge.v)) {
            dsu.unite(edge.u, edge.v);
            total_weight += edge.w;
        }
    }
    
    return total_weight;
}

// 解决方案
void solve() {
    
    
}

int main() {
    fast_io();
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}