ll n, m; cin >> n >> m;
vc<vc<ll>> g(n);
vc<edge> ed;
for (int i = 0;i < m;++i) {
    ll u, v, w; cin >> u >> v >> w;
    g[u - 1].push_back(sz(ed));
    ed.push_back({ u - 1, v - 1, 0, w });
    g[v - 1].push_back(sz(ed));
    ed.push_back({ v - 1, u - 1, 0, 0 });
}
vc<ll> dist(n);
ll curD = (1<<30);
auto bfs = [&]() -> bool {
    dist.assign(n, INF);
    queue<ll> q;
    q.push(0);
    dist[0] = 0;
    while (sz(q)) {
        auto u = q.front(); q.pop();
        for (auto vi : g[u]) {
            int v = ed[vi].to;
            if (dist[v] == INF and ed[vi].cap - ed[vi].flow >= curD) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist[n - 1] != INF;
};
vc<ll> ptr(n, 0);
auto dfs = [&](auto dfs, int u, ll M) -> ll {
    if (u == n - 1) return M;
    for (;ptr[u] < sz(g[u]);++ptr[u]) {
        int i = g[u][ptr[u]];
        auto e = ed[g[u][ptr[u]]];
        if (dist[e.to] - dist[e.u] != 1) continue;
        if (e.cap - e.flow >= curD) {
            ll fl = dfs(dfs, e.to, min(M, e.cap-e.flow));
            if (fl > 0) {
                ed[i].flow += fl;
                ed[i^1].flow -= fl;
                return fl;
            }
        }
    }
    return 0;
};
ll ans = 0;
for (;curD;curD>>=1)
while (bfs()) {
    ptr.assign(n, 0);
    while (1) {
        ll fl = dfs(dfs, 0, INF);
        if (fl == 0) break;
        ans += fl;
    }
}
cout << ans;
