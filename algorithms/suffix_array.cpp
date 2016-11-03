#include <bits/stdc++.h>

using namespace std;

#define MAXN 65536
#define MAXLG 17

struct entry {
  int p;
  pair<int, int> nr;
};


int cmp(entry a, entry b) {
  return a.nr < b.nr;
}

int main() {
  int P[MAXLG][MAXN];
  entry L[MAXN];

  string str = "mississippi";
  int n = str.length();

  for (int i = 0; i < n; i++)
    P[0][i] = str[i] - 'a';

  for (int stp = 1, cnt = 1; cnt < n; stp++, cnt *= 2) {
    for (int i = 0; i < n; i++) {
      L[i].nr.first = P[stp - 1][i];
      L[i].nr.second = (i + cnt < n) ? P[stp - 1][i + cnt] : -1;
      L[i].p = i;
    }
    sort(L, L + n, cmp);
    for (int i = 0; i < n; i++) {
      P[stp][L[i].p] = i > 0 && L[i].nr == L[i - 1].nr ?
                       P[stp][L[i - 1].p] : i;
    }
  }

  for (int i = 0; i < n; ++i) {
    cout << L[i].p << ": " << str.substr(L[i].p) << endl;
  }
  return 0;
}
