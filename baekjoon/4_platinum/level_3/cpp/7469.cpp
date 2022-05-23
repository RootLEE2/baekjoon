#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAX_N 100005
#define MAX_LENGTH 100005
#define NUM_OF_ALPHABET 26
#define INF 0x3f3f3f3f
#define SQUARE(x) ((x) * (x))
#define MOD(x) ((x) % 1000000007)
typedef long long ll;
// log2(100000) == 16.609xxx
// log2(200000) == 17.609xxx
// log2(500000) == 18.931xxx
// log2(1000000) == 19.931xxx

int n, m;
int numArr[MAX_N];

vector<int> segTree[1 << 18];  // int segTree[4 * MAX_N];

int idx_query(int node, int tl, int tr, int l, int r, int val) {
  if (r < l) return 0;
  if (tl == l && tr == r) {
    return lower_bound(segTree[node].begin(), segTree[node].end(), val) - segTree[node].begin();
  }

  int doubleNode = node << 1;  // int doubleNode = 2 * node;
  int tm = (tl + tr) >> 1;  // int tm = (tl + tr) / 2;

  int leftChild = idx_query(doubleNode, tl, tm, l, min(tm, r), val);
  int rightChild = idx_query(doubleNode + 1, tm + 1, tr, max(tm + 1, l), r, val);

  return leftChild + rightChild;
}

void sort_queries(int node, int tl, int tr) {
  if (tl == tr) return;

  int doubleNode = node << 1;  // int doubleNode = 2 * node;
  int tm = (tl + tr) >> 1;  // int tm = (tl + tr) / 2;

  sort_queries(doubleNode, tl, tm);
  sort_queries(doubleNode + 1, tm + 1, tr);

  sort(segTree[node].begin(), segTree[node].end());
}

void update_query(int node, int tl, int tr, int idx, int val) {
  if (idx < tl || tr < idx) return;

  segTree[node].push_back(val);

  if (tl == tr) return;

  int doubleNode = node << 1;  // int doubleNode = 2 * node;
  int tm = (tl + tr) >> 1;  // int tm = (tl + tr) / 2;

  update_query(doubleNode, tl, tm, idx, val);
  update_query(doubleNode + 1, tm + 1, tr, idx, val);
}

void solve() {
  sort_queries(1, 1, n);

  for (int q = 0; q < m; q++) {
    int i, j, k;
    cin >> i >> j >> k;

    int left = -1e9;
    int right = 1e9;

    int ans = -1e9;

    while (left <= right) {
      int mid = (left + right) >> 1;  // int mid = (left + right) / 2;

      if (idx_query(1, 1, n, i, j, mid) < k) {
        ans = max(ans, mid);
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }

    cout << ans << '\n';
  }
}

void input() {
  cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    int num;
    cin >> num;

    update_query(1, 1, n, i, num);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);

  input();
  solve();

  return 0;
}
