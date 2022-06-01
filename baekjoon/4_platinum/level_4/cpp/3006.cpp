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

int N;
int arrIdx[MAX_N];

int segTree[1 << 18];  // int segTree[4 * MAX_N];

void update_query(int node, int tl, int tr, int idx, int delta) {
  if (idx < tl || tr < idx) return;

  segTree[node] += delta;
  
  if (tl == tr) return;

  int doubleNode = node << 1;  // int doubleNode = 2 * node;
  int tm = (tl + tr) >> 1;  // int tm = (tl + tr) / 2;

  update_query(doubleNode, tl, tm, idx, delta);
  update_query(doubleNode + 1, tm + 1, tr, idx, delta);
}

int sum_queries(int node, int tl, int tr, int l, int r) {
  if (r < l) return 0;
  if (tl == l && tr == r) return segTree[node];

  int doubleNode = node << 1;  // int doubleNode = 2 * node;
  int tm = (tl + tr) >> 1;  // int tm = (tl + tr) / 2;

  int leftChild = sum_queries(doubleNode, tl, tm, l, min(tm, r));
  int rightChild = sum_queries(doubleNode + 1, tm + 1, tr, max(tm + 1, l), r);

  return leftChild + rightChild;
}

void build_seg_tree(int node, int tl, int tr) {
  if (tl == tr) {
    segTree[node] = 1;
    return;
  }

  int doubleNode = node << 1;  // int doubleNode = 2 * node;
  int tm = (tl + tr) >> 1;  // int tm = (tl + tr) / 2;

  build_seg_tree(doubleNode, tl, tm);
  build_seg_tree(doubleNode + 1, tm + 1, tr);

  segTree[node] = segTree[doubleNode] + segTree[doubleNode + 1];
}
void solve() {
  build_seg_tree(1, 1, N);

  int left = 1;
  int right = N;
  int mid = (left + right) >> 1;  // int mid = (left + right) / 2;

  bool flag = N & 1;
  
  for (int i = 1; i <= mid; i++) {
    cout << sum_queries(1, 1, N, 1, arrIdx[i] - 1) << '\n';
    update_query(1, 1, N, arrIdx[i], -1);

    if (flag && i == mid) break;

    cout << sum_queries(1, 1, N, arrIdx[N - i + 1] + 1, N) << '\n';
    update_query(1, 1, N, arrIdx[N - i + 1], -1);
  }
}

void input() {
  cin >> N;

  for (int i = 1; i <= N; i++) {
    int arrVal;
    cin >> arrVal;

    arrIdx[arrVal] = i;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);

  input();
  solve();

  return 0;
}
