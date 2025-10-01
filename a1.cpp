#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

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

        priority_queue<array<int, 4>> queue;
        for (int i = 0; i < m; i++) {
            int idx = notes[0].first - (pattern[i].first - pattern[0].first);
            int idy = notes[0].second - (pattern[i].second - pattern[0].second);
            queue.push({-idx, -idy, i, 0});
        }

        int c = 0, vx = 1e9, vy = 1e9;
        while (queue.size()) {
            auto w = queue.top();
            queue.pop();
            if (vx != w[0] || vy != w[1]) {
                vx = w[0];
                vy = w[1];
                c++;
            }
            if (w[3] != n-1) {
                w[3]++;
                int idx = notes[w[3]].first - (pattern[w[2]].first - pattern[0].first);
                int idy = notes[w[3]].second - (pattern[w[2]].second - pattern[0].second);
                queue.push({-idx, -idy, w[2], w[3]});
            }
        }

        cout << c << "\n";
    }
}
