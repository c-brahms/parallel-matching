#include <algorithm>
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

        vector<int> pointer(u);
        priority_queue<pair<pair<int,ll>,int>> queue;
        for (int i = 0; i < u; i++) {
            pointer[i] = m-1;
            int idx = data[i].first - (pattern[m-1].first - pattern[0].first);
            int shift = pattern[m-1].second - pattern[0].second;
            ll idy = data[i].second;
            if (shift >= 0) idy = idy >> shift;
            else idy = idy << (-shift);
            queue.push({{-idx, idy}, i});
        }

        int c = 0;
        int prev = 1e9;
        ll mask = 0;
        while (queue.size()) {
            auto entry = queue.top();
            queue.pop();
            if (prev != entry.first.first) {
                c += popcount128(mask);
                mask = 0;
                prev = entry.first.first;
            }
            mask |= entry.first.second;
            int i = entry.second;
            if (pointer[i]) {
                pointer[i]--;
                int idx = data[i].first - (pattern[pointer[i]].first - pattern[0].first);
                int shift = pattern[pointer[i]].second - pattern[0].second;
                ll idy = data[i].second;
                if (shift >= 0) idy = idy >> shift;
                else idy = idy << (-shift);
                queue.push({{-idx, idy}, i});
            }
        }
        c += popcount128(mask);

        cout << c << "\n";
    }
}
