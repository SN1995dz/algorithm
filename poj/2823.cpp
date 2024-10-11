#include <iostream>
#include <vector>
#include <cassert>
#include <deque>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    assert(n >= k);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    deque<pair<int, int> > maxDq, minDq;
    for (int i = 0; i < k; ++i) {
        while (!maxDq.empty() && maxDq.back().first <= a[i]) maxDq.pop_back();
        maxDq.push_back(make_pair(a[i], i));
        while (!minDq.empty() && minDq.back().first >= a[i]) minDq.pop_back();
        minDq.push_back(make_pair(a[i], i));
    }
    vector<int> ansMax, ansMin;
    ansMax.push_back(maxDq.front().first);
    ansMin.push_back(minDq.front().first);
    for (int i = k; i < n; ++i) {
        while (!maxDq.empty() && maxDq.back().first <= a[i]) maxDq.pop_back();
        maxDq.push_back(make_pair(a[i], i));
        while (!minDq.empty() && minDq.back().first >= a[i]) minDq.pop_back();
        minDq.push_back(make_pair(a[i], i));
        if (maxDq.front().second <= i - k) maxDq.pop_front();
        if (minDq.front().second <= i - k) minDq.pop_front();
        ansMax.push_back(maxDq.front().first);
        ansMin.push_back(minDq.front().first);
    }
    for (int i = 0; i < (int)ansMin.size(); ++i) cout << ansMin[i] << " ";
    cout << endl;
    for (int i = 0; i < (int)ansMax.size(); ++i) cout << ansMax[i] << " ";
    return 0;
}

