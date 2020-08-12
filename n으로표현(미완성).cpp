// https://programmers.co.kr/learn/courses/30/lessons/42895?language=cpp
// set에 관한 설명글 : https://blockdmask.tistory.com/79

#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

/* ex) N = 5이고 cnt가 2이면 
res = 55임 
*/ 
int get_basic_number(int N, int cnt) {
	int res = 0;

	while (cnt > 0) {
		cnt -= 1;
		res += N * pow(10, cnt);
	}

	return res;
}

int solution(int N, int number) {
	int answer = -1;

	const int MIN = 8;

	//MIN 크기 만큼 0으로 초기화
	vector <set <int>> s(MIN); 

	int idx = 1;

	/* N이 5라면 벡터 s에
	5, 55, 555 ... 55555555 가 들어감
	*/
	for (int i = 0; i < s.size(); i++) {
		s[i].insert(get_basic_number(N, idx));
		idx++;
	}

	/*
	루프 맨 처음 상태를 보자, 
	i = 1, j = 0, i - j - 1 = 0이다.

	s[1]에 op1 (= 5), op2 (= 5)를 사칙연산 수행한 
	값들이 들어가는데, 오름차순으로 저장된다. 
	(set은 실제로 tree 구조이다.) 
	*/

	for (int i = 1; i < MIN; i++) {
		for (int j = 0; j < i; j++) {
			for (const auto & op1 : s[j]) {
				for (const auto &op2 : s[i - j - 1]) {
					s[i].insert(op1 + op2);
					s[i].insert(op1 - op2);
					s[i].insert(op1 * op2);

					if (op2 != 0)
						s[i].insert(op1 / op2);
				}
			}
		}
		// i + 1이 곧 N의 개수이다. 
		// number가 구하고자 하는 수 이므로 
		// set s에서 number 가 나오면 사용한 N의 개수를 구하고
		// 반복문을 빠져나온다.
		if (s[i].find(number) != s[i].end()) {
			answer = i + 1;
			break;
		}
	}

	return answer;
}

int main() {
	
	int N, number, result;

	result = solution(5, 12);

	cout << result;
}
