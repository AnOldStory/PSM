#include <iostream>
#include <queue>

using namespace std;

struct Coord {
  int x, y;
  Coord() : x(-1), y(-1) {}
  Coord(int X, int Y) : x(X), y(Y) {}
};

struct target {
  int x, y, dist;
  target() : x(-1), y(-1), dist(-1) {}
  target(int X, int Y, int DIST) : x(X), y(Y), dist(DIST) {}
};
bool operator<(const target& a, const target& b) {
  if (a.dist == b.dist) {
    if (a.x == b.x) {
      return a.y < b.y;
    }
    return a.x < b.x;
  } else {
    return a.dist < b.dist;
  }
}

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int N, M, F;
int map[21][21];
int check[21][21];
Coord dest[21][21];
Coord car;

void init() {
  for (int i = 0; i < 21; i++) {
    for (int j = 0; j < 21; j++) {
      check[i][j] = 0;
    }
  }
}

void closest(target* tmps, int x, int y) {
  init();
  int flag = 1;
  queue<Coord> q;
  check[x][y] = 1;
  q.push(Coord(x, y));

  if (map[x][y] == -1) {
    tmps->x = x;
    tmps->y = y;
    tmps->dist = 1;
    return;
  }

  target ret = target(-1, -1, -1);
  while (!q.empty()) {
    Coord cur = q.front();
    q.pop();

    for (int i = 0; i < 4; i++) {
      int nx = cur.x + dx[i];
      int ny = cur.y + dy[i];
      if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;

      if (map[nx][ny] != 1 && check[nx][ny] == 0) {
        check[nx][ny] = check[cur.x][cur.y] + 1;
        if (map[nx][ny] == -1) {
          target tmp = target(nx, ny, check[cur.x][cur.y] + 1);
          if (ret.x == -1 || tmp < ret) ret = tmp;
        }
        q.push(Coord(nx, ny));
      }
    }
  }
  tmps->x = ret.x;
  tmps->y = ret.y;
  tmps->dist = ret.dist;
}

// 이동 좌표, 이동 거리
void move(target* tmps, int desx, int desy) {
  int x = car.x;
  int y = car.y;
  init();
  queue<Coord> q;
  check[x][y] = 1;
  q.push(Coord(x, y));

  while (!q.empty()) {
    Coord cur = q.front();
    q.pop();

    for (int i = 0; i < 4; i++) {
      int nx = cur.x + dx[i];
      int ny = cur.y + dy[i];
      if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;

      if (map[nx][ny] != 1 && check[nx][ny] == 0) {
        check[nx][ny] = check[cur.x][cur.y] + 1;
        if (desx == nx && desy == ny) {
          tmps->x = nx;
          tmps->y = ny;
          tmps->dist = check[nx][ny];
          return;
        }
        q.push(Coord(nx, ny));
      }
    }
  }
}

int main() {
  cin >> N >> M >> F;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> map[i][j];
    }
  }
  cin >> car.x >> car.y;
  car.x--;
  car.y--;
  int user_cnt = 0;
  for (int i = 0; i < M; i++) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;  // startx starty desx desy
    dest[x1 - 1][y1 - 1] = Coord(x2 - 1, y2 - 1);
    map[x1 - 1][y1 - 1] = -1;  // mark as start person
    user_cnt++;
  }

  while (user_cnt > 0) {
    target tmp;
    // cout << "[Before] -> " << car.x << " " << car.y << " " << F << endl;
    closest(&tmp, car.x, car.y);
    tmp.dist--;
    if (tmp.dist == -2) break;
    // cout << "[Find closest]" << tmp.x << " " << tmp.y << " used " << tmp.dist << endl;
    if (tmp.dist > F) break;
    F -= tmp.dist;
    car.x = tmp.x;
    car.y = tmp.y;

    map[tmp.x][tmp.y] = 0;

    target tmp2;
    // cout << "[Moved to] -> " << car.x << " " << car.y << " " << F << endl;
    move(&tmp2, dest[tmp.x][tmp.y].x, dest[tmp.x][tmp.y].y);
    tmp2.dist--;
    if (tmp.dist == -2) break;
    // cout << "[Moved]" << tmp2.x << " " << tmp2.y << " used " << tmp2.dist << endl;
    if (tmp2.dist > F) break;
    F += tmp2.dist;
    car.x = tmp2.x;
    car.y = tmp2.y;

    user_cnt--;
  }

  // cout << "asd" << user_cnt << endl;
  if (user_cnt == 0)
    cout << F << endl;
  else
    cout << -1 << endl;
  return 0;
}