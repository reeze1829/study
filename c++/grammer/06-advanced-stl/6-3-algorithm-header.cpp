/*****************************************************************
 * 주제: 6-3. algorithm-header (STL 알고리즘 함수 활용)
 * 작성일: 2026. 03. 27.
 * [6-3. 핵심 요약]
 * 1. algorithm 헤더: 컨테이너의 데이터를 처리하는 표준 함수 집합
 * 2. 범위 지정: 보통 begin()과 end() 반복자를 넘겨서 작업 범위를 정함
 * 3. 성능: 직접 구현하는 것보다 훨씬 빠르고 검증된 최적화 알고리즘 사용
 *****************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>                  // 필수 헤더!
#include <random>                     // shuffle용

using namespace std;

int main() {
    vector<int> v = {40, 10, 50, 20, 30};
    // std::sort(정렬)
    // [v.begin(), v.end()) 범위를 오름차순으로 정렬 (평균 O(N log N))
    sort(v.begin(), v.end());
    cout << "[sort] 오름차순 정렬 결과: ";
    for (int n : v) cout << n << " ";             // 10 20 30 40 50
    cout << endl;
    
    // std::reverse (반전)
    // 순서를 완전히 뒤집음
    reverse(v.begin(), v.end());
    cout << "[reverse] 뒤집기 결과: ";
    for (int n : v) cout << n << " "; // 50 40 30 20 10
    cout << endl;
    
    // std::find (찾기)
    // 데이터가 있는지 찾고, 가리키는 반복자를 반환
    // find는 순차 탐색이므로 데이터가 많으면 map/set보다 느림 (O(N))
    // 하지만 vector처럼 정렬되지 않은 곳에서 하나를 찾을 땐 가장 편한 도구임
    int target = 30;
    auto it = find(v.begin(), v.end(), target);

    if (it != v.end()) {
        cout << "[find] " << target << "을(를) 찾았습니다!" << endl;
    } else {
        cout << "[find] 데이터를 찾지 못했습니다." << endl;
    }

    // std::max_element / min_element(최대/최소)
    // 반환값이 값이 아니라 위치(반복자)이므로 값을 보려면 *를 붙여야 함
    // cout << *max_it; (O)  cout << max_it; (X - 에러 발생)
    auto max_it = max_element(v.begin(), v.end());
    auto min_it = min_element(v.begin(), v.end());
    cout << "[max/min] 최댓값: " << *max_it << ", 최솟값: " << *min_it << endl;

    // std::shuffle (뒤섞기)
    // random_device와 mt19937은 C++11 이후 권장되는 진짜 무작위 생성기
    random_device rd;
    mt19937 g(rd());
    shuffle(v.begin(), v.end(), g);

    cout << "[shuffle] 무작위 섞기 결과: ";
    for (int n : v) cout << n << " ";
    cout << endl;

    return 0;
}

/*
 * [알고리즘 함수의 철학]
 * 1. 직접 짜지 마라: sort나 find는 이미 세계 최고의 천재들이 최적화해둔 코드
 * 2. 반복자가 핵심: 알고리즘 함수는 컨테이너가 뭔지 몰라도 됩니다. 오직 반복자만 있으면 작동함
 * 3. 반개방 범위: 항상 [begin, end) 즉, 시작은 포함하고 끝은 포함하지 않는 범위를 다룸
 */
