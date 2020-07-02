#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <cmath>


using namespace std;

int solution(vector<string> lines) {
	int answer = 0;

	/*
	1. �Ľ�
	���� �ð��� ���� ������ ������ ��, ���۰� ��
	���̿��� 1�� ������ ĭ�� 0.001�ʾ� �ڷ� �Űܰ��� 
	���� ���� ������ ������ ã�ƾ� �� ��.
	6/15 00:00:00.00 �� �������� ���� ��� 01:00:04�� ���
	1*60*60 + 4.04 = 3604.04�� ǥ���ؾ� �Ѵ�. 
	*/
	
	//�켱 ���� �������� ������ 
	vector <string> temp_str;
	for (int i = 0; i < lines.size(); i++) {
		istringstream ss(lines[i]);
		string buffer;
		while (getline(ss, buffer, ' '))
			temp_str.push_back(buffer);
	}

	//���� �ð��� �� �ð��� ��� �Լ�
	vector <pair<int, int>> time;
	int temp_time_begin = 0;
	int temp_time_end = 0;

	for (int i = 0; i < temp_str.size(); i++) {
		//�ð� �Ľ�, ��ȯ
		if (i % 3 == 1) {
			istringstream ss(temp_str[i]);
			vector <string> vec_buffer;
			string buffer;
			while (getline(ss, buffer, ':'))
				vec_buffer.push_back(buffer);

			//stof�� ����� float ��ȯ�� ����� �ȵȴ�. 4.002�� float���� ��ȯ�ϸ� 4.00195�� �ȴ�.
			//double�� ���ϱ� �ȴ�. 
			temp_time_end = (stod(vec_buffer[0]) * 3600 + stod(vec_buffer[1]) * 60 + stod(vec_buffer[2])) * 1000;

		}
		else if (i % 3 == 2) {
			istringstream ss(temp_str[i]);
			string buffer;
			getline(ss, buffer, 's');

			//�ҿ� �Ǵ� �ð��� spent��� ������ ���� 
			int spent = stod(buffer) * 1000;

			temp_time_begin = temp_time_end - spent + 1;

			time.push_back(make_pair(temp_time_begin, temp_time_end));
		}
	}

	//���� ù��° �ð������� ������ �ð����� 0.001�ʾ� �����̸鼭 ������. 
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