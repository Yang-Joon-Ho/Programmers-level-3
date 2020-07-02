#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <cmath>


using namespace std;

int solution(vector<string> lines) {
	int answer = 0;

	/*
	1. 파싱
	시작 시간이 빠른 순서로 정렬한 후, 시작과 끝
	사이에서 1초 범위의 칸을 0.001초씩 뒤로 옮겨가며 
	가장 많이 들어오는 구간을 찾아야 할 듯.
	6/15 00:00:00.00 을 기준으로 예를 들어 01:00:04의 경우
	1*60*60 + 4.04 = 3604.04로 표기해야 한다. 
	*/
	
	//우선 공백 기준으로 나누고 
	vector <string> temp_str;
	for (int i = 0; i < lines.size(); i++) {
		istringstream ss(lines[i]);
		string buffer;
		while (getline(ss, buffer, ' '))
			temp_str.push_back(buffer);
	}

	//시작 시간과 끝 시간을 담는 함수
	vector <pair<int, int>> time;
	int temp_time_begin = 0;
	int temp_time_end = 0;

	for (int i = 0; i < temp_str.size(); i++) {
		//시간 파싱, 변환
		if (i % 3 == 1) {
			istringstream ss(temp_str[i]);
			vector <string> vec_buffer;
			string buffer;
			while (getline(ss, buffer, ':'))
				vec_buffer.push_back(buffer);

			//stof를 사용한 float 변환이 제대로 안된다. 4.002를 float으로 변환하면 4.00195가 된다.
			//double을 쓰니깐 된다. 
			temp_time_end = (stod(vec_buffer[0]) * 3600 + stod(vec_buffer[1]) * 60 + stod(vec_buffer[2])) * 1000;

		}
		else if (i % 3 == 2) {
			istringstream ss(temp_str[i]);
			string buffer;
			getline(ss, buffer, 's');

			//소요 되는 시간을 spent라는 변수에 넣음 
			int spent = stod(buffer) * 1000;

			temp_time_begin = temp_time_end - spent + 1;

			time.push_back(make_pair(temp_time_begin, temp_time_end));
		}
	}

	//이제 첫번째 시간서부터 마지막 시간까지 0.001초씩 움직이면서 봐야함. 
	for (int i = time[0].first; i <= time[time.size() - 1].second; i += 1) {
		int count = 0;

		for (int j = 0; j < time.size(); j++) {

			if (i > time[j].second) {
				time.erase(time.begin() + j);
			}

			if (i <= time[j].second && time[j].first < i + 1000) {
				count++;
			}

		}
		if (count == 0)
			i = time[0].first;
		else if (count > answer)
			answer = count;

	}

	return answer;
}

int main() {
	vector <string> lines = {
		"2016-09-15 23:59:59.999 0.001s" };


	solution(lines);
	
}