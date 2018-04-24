#include <bits/stdc++.h>
using namespace std;


int main()
{
	int n;
	scanf("%d", &n);
	int golden = (int)(n * 0.1);
	int sliver = golden + (int)(n * 0.2);
	int bronze = sliver + (int)(n * 0.3);
	int newGolden = ceil(n * 0.1);
	int newSliver = newGolden + ceil(n * 0.2);
	int newBronze = newSliver + ceil(n * 0.3);
	printf("%d %d %d\n", newGolden - golden, newSliver - sliver, newBronze - bronze);

	return 0;
}
