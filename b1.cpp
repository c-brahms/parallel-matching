#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using ll = __int128;

int popcount128(__int128 value) {
    uint64_t lower = static_cast<uint64_t>(value);
    uint64_t upper = static_cast<uint64_t>(value >> 64);
    return __builtin_popcountll(lower) + __builtin_popcountll(upper);
}

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> notes;
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        notes.push_back({x, y});
    }
    sort(notes.begin(), notes.end());

    vector<pair<int, ll>> data;
    ll one_bit = 1;
    for (int i = 0; i < notes.size(); i++) {
        if (i == 0 || notes[i-1].first != notes[i].first) {
            data.push_back({notes[i].first, one_bit << notes[i].second});
        } else {
            data[data.size() - 1].second |= (one_bit << notes[i].second);
        }
    }
    int u = data.size();

    int q;
    cin >> q;

    while (q--) {
        int m;
        cin >> m;
        vector<pair<int, int>> pattern;
        for (int i = 1; i <= m; i++) {
            int x, y;
            cin >> x >> y;
            pattern.push_back({x, y});
        }
        sort(pattern.begin(), pattern.end());

        priority_queue<pair<array<int, 3>,ll>> queue;
        for (int i = 0; i < m; i++) {
            int idx = data[0].first - (pattern[i].first - pattern[0].first);
            int shift = pattern[i].second - pattern[0].second;
            ll idy = data[0].second;
            if (shift >= 0) idy = idy >> shift;
            else idy = idy << (-shift);
            queue.push({{-idx, i, 0},idy});
        }

        ll mask = 0;
        int c = 0, vx = 1e9;
        while (queue.size()) {
            auto w = queue.top();
            queue.pop();
            if (vx != w.first[0]) {
                c += popcount128(mask);
                vx = w.first[0];
                mask = 0;
            }
            mask |= w.second;
            if (w.first[2] != u-1) {
                w.first[2]++;
                int idx = data[w.first[2]].first - (pattern[w.first[1]].first - pattern[0].first);
                int shift = pattern[w.first[1]].second - pattern[0].second;
                ll idy = data[w.first[2]].second;
                if (shift >= 0) idy = idy >> shift;
                else idy = idy << (-shift);
                queue.push({{-idx, w.first[1], w.first[2]},idy});
            }
        }
        c += popcount128(mask);

        cout << c << "\n";
    }
}
