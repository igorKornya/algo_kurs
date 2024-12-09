#include "arr.cpp"
#include <iostream>
using namespace std;

class DjSet
{
public:
	dynamic_arr<int> parent;
	dynamic_arr<int> rank;

	DjSet(int n) {
		parent = dynamic_arr<int>(n);
		rank = dynamic_arr<int>(n, 0);
		for (int i = 0; i < n; ++i) {
			parent[i] = i;
		}
	}

	int find(int x)
	{
		if (parent[x] != x)
		{
			parent[x] = find(parent[x]);
		}
		return parent[x];
	}

	int unite(int x, int y)
	{
		x = find(x);
		y = find(y);

		if (rank[x] < rank[y]) { parent[x] = y; }
		else if (rank[x] > rank[y]) { parent[y] = x; }
		else { parent[y] = x; if (rank[x] == rank[y]) { rank[y]++; } }
	}
};
