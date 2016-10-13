#include<bits/stdc++.h>

using namespace std;

#define Grid vector<string>
#define Long unsigned long long

#define EMPTY ('.')
#define WHITE_TURN 0
#define BLACK_TURN 1

#define INVALID(i, j) (i < 0 || j < 0 || i > 3 || j > 3)
#define GET(i, j) (g[i][j])

#define IS_EMPTY(i, j) (!INVALID(i, j) && GET(i, j) == EMPTY)
#define IS_WHITE(i, j) (!INVALID(i, j) && GET(i, j) != EMPTY && isupper(GET(i, j)))
#define IS_BLACK(i, j) (!INVALID(i, j) && GET(i, j) != EMPTY && islower(GET(i, j)))

#define IS_ENEMY(turn, i2, j2) (!INVALID(i2, j2) && (turn == BLACK_TURN && IS_WHITE(i2, j2) || turn == WHITE_TURN && IS_BLACK(i2, j2)))
#define WHITE_WINS(turn, i2, j2) (!INVALID(i2, j2) && turn == WHITE_TURN && GET(i2, j2) == 'q')
#define WHITE_LOSES(turn, i2, j2) (!INVALID(i2, j2) && turn == BLACK_TURN && GET(i2, j2) == 'Q')

set<Long> history;
map<char, vector<pair<int, int>>> moves;

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

bool solve(Grid g, int turn, int lvl, int m) {
//  if (history.count(gHash(g)) != 0)
//    return true;
//  else
//    history.insert(gHash(g));

  if (lvl == m)
    return false;

  queue<pair<pair<int, int>, pair<int, int>>> possible;

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (IS_ENEMY(turn, i, j) || IS_EMPTY(i, j))
        continue;

      char piece = GET(i, j);

      char type = (char) tolower(piece);
      auto mvs = moves[type];
      for (auto direction = mvs.begin(); direction != mvs.end(); direction++) {
        int i2 = i, j2 = j;

        while (true) {
          if (type != 'n')
            i2 += direction->first, j2 += direction->second;
          else
            i2 = i + direction->first, j2 = j + direction->second;

          if (IS_EMPTY(i2, j2)) {
            possible.push({{i,  j},
                           {i2, j2}});
          } else if (IS_ENEMY(turn, i2, j2)) {
            if (WHITE_WINS(turn, i2, j2))
              return true;
            else if (WHITE_LOSES(turn, i2, j2))
              return false;

            possible.push({{i,  j},
                           {i2, j2}});
            break;
          } else {
            break;
          }

          if (type == 'n')
            break;
        }
      }
    }
  }

  while (possible.size() > 0) {
    auto p = possible.front();
    possible.pop();

    int i = p.first.first,
        j = p.first.second,
        i2 = p.second.first,
        j2 = p.second.second;

    Grid newGrid = nextGrid(g, i, j, i2, j2);
    bool result = solve(newGrid, !turn, lvl + 1, m);
    if (turn == WHITE_TURN && result == true)
      return true;
    else if (turn == BLACK_TURN && result == false)
      return false;
  }

  return false;
}

int main() {
  init();
//  ios::sync_with_stdio(false);
#ifdef N1AMR_FILE
  freopen("input", "r", stdin);
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
#ifdef N1AMR
    for (int i = 0; i < 4; ++i) {
      getline(cin, line);
      sscanf(line.c_str(), "%c%c%c%c", &board[i][0], &board[i][1], &board[i][2], &board[i][3]);
    }
#else
    for (int i = 0; i < w + b; ++i) {
      getline(cin, line);
      sscanf(line.c_str(), "%c %c %d", &t, &r, &c);
      board[4 - c][r - 'A'] = t + (i >= w) * ('a' - 'A');
    }
#endif
    printf("%s\n", (solve(board, WHITE_TURN, 0, m) ? "YES" : "NO"));
  }
}
