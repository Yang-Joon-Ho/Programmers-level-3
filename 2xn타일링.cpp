#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(int n) {
	
	int bef = 1;
	int aft = 1;
	int temp = 0;

	if (n == 1) return 1;
	for (int i = 1; i < n; i++) {
		
		temp = aft % 1000000007;
		aft = (temp + bef) % 1000000007;
		bef = temp;

	}

	return aft;
}

int main() {

	int answer = solution(50);

	cout << answer << endl;
}
