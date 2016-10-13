#include<bits/stdc++.h>

using namespace std;

#define EMPTY ('.')
#define Grid vector<string>
#define INVALID(i, j) (i < 0 || j < 0 || i > 3 || j > 3)
#define GET(i, j) (g[i][j])
#define BLOCKED(c, i2, j2) (INVALID(i2, j2) || islower(c) && islower(GET(i2, j2))  || isupper(c) && isupper(GET(i2, j2)))
#define ATTACKABLE(c, i2, j2) (!BLOCKED(c, i2, j2) && GET(i2, j2) != EMPTY)
#define WHITE_WINS(turn, i2, j2) (!INVALID(i2, j2) && turn == 0 && GET(i2, j2) == 'q')
#define WHITE_LOSES(turn, i2, j2) (!INVALID(i2, j2) && turn == 1 && GET(i2, j2) == 'Q')
#define Long unsigned long long

set<Long> history;
map<char, vector<pair<int, int>>> moves;

Long gHash(const Grid &g) {
  Long ans = 0;

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      ans *= 9;

      char c = g[i][j];
      if (c == 'Q') ans += 1;
      else if (c == 'N') ans += 2;
      else if (c == 'B') ans += 3;
      else if (c == 'R') ans += 4;
      else if (c == 'q') ans += 5;
      else if (c == 'n') ans += 6;
      else if (c == 'b') ans += 7;
      else if (c == 'r') ans += 8;
    }
  }

  return ans;
}

Grid nextGrid(Grid g, int i, int j, int i2, int j2) {
  g[i2][j2] = g[i][j];
  g[i][j] = EMPTY;
  return g;
}

void print(Grid g, int lvl = 0) {
#ifdef N1AMR
  char c;
  string indent(lvl * 5, ' ');
  for (int i = 0; i < 4; ++i) {
    cout << indent;
    for (int j = 0; j < 4; ++j) {
      c = g[i][j];
      cout << (c ? c : '.');
    }
    cout << endl;
  }
  cout << endl;
#endif
}

bool solve(Grid g, int turn, int lvl, int m) {
//  if (history.count(gHash(g)) != 0)
//    return true;
//  else
//    history.insert(gHash(g));

  print(g, lvl);

  if (lvl == m)
    return false;

  bool ans = 1;
  vector<pair<pair<int, int>, pair<int, int>>> possible;

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      char c = g[i][j];
      if (turn == 0 && islower(c) || turn == 1 && isupper(c) || c == EMPTY)
        continue;

      char type = tolower(c);
      auto mvs = moves[type];
      for (auto p = mvs.begin(); p != mvs.end(); p++) {
        int i2 = i, j2 = j;

        if (type != 'n') {
          bool cont = 1;
          while (cont) {
            i2 += p->first, j2 += p->second;
            if (BLOCKED(c, i2, j2)) break;
            if (ATTACKABLE(c, i2, j2)) {
              if (WHITE_WINS(turn, i2, j2))
                return true;
              else if (WHITE_LOSES(turn, i2, j2))
                return false;

              cont = 0;
            }
            possible.push_back({{i,  j},
                                {i2, j2}});
          }
        } else {
          i2 = i + p->first, j2 = j + p->second;
          if (!BLOCKED(c, i2, j2)) {
            if (WHITE_WINS(turn, i2, j2))
              return true;
            else if (WHITE_LOSES(turn, i2, j2))
              return false;
            possible.push_back({{i,  j},
                                {i2, j2}});
          }
        }
      }
    }
  }
  while (possible.size() > 0) {
    auto p = possible.back();
    possible.pop_back();

    int i = p.first.first,
        j = p.first.second,
        i2 = p.second.first,
        j2 = p.second.second;
    if (!solve(nextGrid(g, i, j, i2, j2), !turn, lvl + 1, m))
      return false;
  }

  return ans;
}

void init() {
  moves['q'].push_back({1, 0});
  moves['q'].push_back({-1, 0});
  moves['q'].push_back({0, 1});
  moves['q'].push_back({0, -1});
  moves['q'].push_back({1, 1});
  moves['q'].push_back({1, -1});
  moves['q'].push_back({-1, 1});
  moves['q'].push_back({-1, -1});


  moves['r'].push_back({1, 0});
  moves['r'].push_back({-1, 0});
  moves['r'].push_back({0, 1});
  moves['r'].push_back({0, -1});

  moves['b'].push_back({1, 1});
  moves['b'].push_back({1, -1});
  moves['b'].push_back({-1, 1});
  moves['b'].push_back({-1, -1});

  for (int i = -2; i <= 2; ++i)
    for (int j = -2; j <= 2; ++j)
      if (i != 0 && j != 0 && i != j && i != -j)
        moves['n'].push_back({i, j});
}

int main() {
  init();
//  ios::sync_with_stdio(false);
#ifdef N1AMR
  freopen("in", "r", stdin);
#endif
  string line;
  int tc;
  getline(cin, line);
  sscanf(line.c_str(), "%d", &tc);
  while (tc--)
//#endif
  {
    history.clear();

    int w, b, m, c;
    char t, r;

    getline(cin, line);
    sscanf(line.c_str(), "%d %d %d\n", &w, &b, &m);
    Grid board(4, string(4, EMPTY));
//#ifdef N1AMR
//    for (int i = 0; i < 4; ++i)
//      for (int j = 0; j < 4; ++j)
//        scanf("%d", &board[i][j]);
//
//#else
    for (int i = 0; i < w + b; ++i) {
      getline(cin, line);
      sscanf(line.c_str(), "%c %c %d", &t, &r, &c);
      board[4 - c][r - 'A'] = t + (i >= w) * ('a' - 'A');
    }
//#endif
    print(board, 0);
    printf("%s\n", (solve(board, 0, 0, m) ? "YES" : "NO"));
  }
}
