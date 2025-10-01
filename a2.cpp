#include <algorithm>
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

        vector<int> pointer(n);
        priority_queue<pair<pair<int,int>,int>> queue;
        for (int i = 0; i < n; i++) {
            if (i != 0 && notes[i-1] == notes[i]) continue;
            pointer[i] = m-1;
            int idx = notes[i].first - (pattern[m-1].first - pattern[0].first);
            int idy = notes[i].second - (pattern[m-1].second - pattern[0].second);
            queue.push({{-idx, -idy}, i});
        }

        int c = 0;
        pair<int,int> prev = {1e9, 0};
        while (queue.size()) {
            auto entry = queue.top();
            queue.pop();
            if (prev != entry.first) {
                c++;
                prev = entry.first;
            }
            int i = entry.second;
            if (pointer[i]) {
                pointer[i]--;
                int idx = notes[i].first - (pattern[pointer[i]].first - pattern[0].first);
                int idy = notes[i].second - (pattern[pointer[i]].second - pattern[0].second);
                queue.push({{-idx, -idy}, i});
            }
        }

        cout << c << "\n";
    }
}
