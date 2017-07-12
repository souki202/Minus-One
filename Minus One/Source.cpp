#include <iostream>
#include <unordered_map>
#include <queue>

int min[100000] = {0};
int min2[100000] = { 0 };
long long dp[100000] = {1, 0}; //全くDPではない模様
long long dp2[100000] = { 1, 0 };

int main() {
	int n, m, s, t;
	int len;
	std::cin >> n >> m >> s >> t;
	std::unordered_multimap<int, int> e;//from, to
	e.reserve(300000);
	for (int i = 0; i < m; i++) {
		int x, y;
		std::cin >> x >> y;
		e.insert(std::make_pair(x, y));
		e.insert(std::make_pair(y, x));
	}

	std::queue<std::pair<int, int>> q;
	q.push(std::make_pair(0, s));

	while (!q.empty()) {
		auto node = q.front(); q.pop();
		auto it = e.find(node.second);
		int count = e.count(node.second);
		for (int i = 0; i < count; i++, ++it) {
			auto next = node;
			next.first++;
			next.second = it->second;
			if (next.second == s || (min[next.second] > 0 && min[next.second] <= next.first)) {
				continue;
			}
			min[next.second] = next.first;
			dp[next.first]++;
			if (next.second == t) len = next.first;
			q.push(next);
		}
	}

	q.push(std::make_pair(0, t));
	while (!q.empty()) {
		auto node = q.front(); q.pop();
		auto it = e.find(node.second);
		int count = e.count(node.second);
		for (int i = 0; i < count; i++, ++it) {
			auto next = node;
			next.first++;
			next.second = it->second;
			if (next.second == t || (min2[next.second] > 0 && min2[next.second] <= next.first)) {
				continue;
			}
			min2[next.second] = next.first;
			dp2[next.first]++;
			q.push(next);
		}
	}

	long long count = 0;
	for (int i = 0; i <= len - 2; i++) {
			count += dp[i] * dp2[len - i - 2];
	}
	std::cout << count << std::endl;

	return 0;
}
