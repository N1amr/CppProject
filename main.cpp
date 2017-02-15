#include<bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
#ifdef N1AMR
  freopen("input", "r", stdin);
  int tc;
  cin >> tc;
  while (tc--)
#endif
  {
    int n2, n3, n5, n6;
    cin >> n2 >> n3 >> n5 >> n6;
    n5 = min(n5, n6);
    long long ans = 0;
    int x = min(n2, n5);
    ans += (long long) x * 256;
    n2 -= x;
    x = min(n2, n3);
    ans += (long long) x * 32;
    cout << ans << endl;
  }
}
