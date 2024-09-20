#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        string ans = "";
        bool endFlag = false;
        auto ask = [&](string s) {
            cout << "? " << s << endl;
            cout.flush();
            int answer;
            cin >> answer;
            return answer;
        };
        while ((int)ans.length() != n) {
            if (endFlag) {
                if (ask("0" + ans)) {
                    ans = "0" + ans;
                } else {
                    ans = "1" + ans;
                }
                continue;
            }
            if (ask(ans + "0")) {
                ans.push_back('0');
            } else {
                if (ask(ans + "1")) {
                    ans.push_back('1');
                } else {
                    endFlag = true;
                }
            }
        }
        cout << "! " << ans << endl;
        cout.flush();
    }
    return 0;
}

