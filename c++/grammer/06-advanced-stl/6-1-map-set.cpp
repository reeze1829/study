/*****************************************************************
 * 주제: 6-1. map-set (연관 컨테이너: Key-Value 및 집합)
 * 작성일: 2026. 03. 23.
 * [6-1. 핵심 요약]
 * 1. std::set: 중복을 허용하지 않는 원소들의 집합 (자동 오름차순 정렬)
 * 2. std::map: Key와 Value가 쌍(pair)을 이루는 구조 (사전식 구조)
 * 3. 탐색 효율: 내부적으로 '이진 탐색 트리' 구조를 사용하여 검색 속도가 매우 빠름
 *****************************************************************/

#include <iostream>
#include <set>
#include <map>
#include <string>

using namespace std;

int main() {
    
    set<int> s;                                   // std::set 실습 (중복 없는 집합)
    s.insert(30);
    s.insert(10);                                 // set은 '값' 자체가 '키'. 중복 검사 후 없으면 추가, 있으면 무시
    s.insert(20);
    s.insert(10);                                 // 중복 데이터 삽입 시도 (무시됨)

    cout << "[set] 요소 출력 (자동 정렬됨): ";
    for (int n : s) cout << n << " ";             // 10 20 30 출력
    cout << endl;

    map<string, int> inventory;                  // std::map 실습 (Key-Value 쌍)
                                                 // map<Key타입, Value타입>
    
    inventory.insert(make_pair("Apple", 5));     // 데이터 삽입 방법 1: insert와 pair 활용
                                                 // 데이터 삽입 방법 2: 배열처럼 [] 연산자 활용 (가장 많이 씀)
    inventory["Banana"] = 10;                    // [] 연산자의 특징: 키가 없으면 새로 생성하고, 이미 있으면 값을 갱신함
    inventory["Orange"] = 3;

    cout << "[map] Apple의 수량: " << inventory["Apple"] << endl;

    cout << "[map] 전체 목록:" << endl;                                   // 반복자를 이용한 map 순회
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {      // map의 요소는 pair객체이므로 .first(Key), .second(Value)로 접근
        cout << "- " << it->first << " : " << it->second << "개" << endl; // map의 요소는 내부적으로 pair<const Key, Value> 구조로 저장됨
    }                                                                     // .first는 수정 불가능한 Key, .second는 수정 가능한 Value

    
    string target = "Cherry";                                    // 데이터 찾기 (find)
    if (inventory.find(target) == inventory.end()) {
        cout << target << "은(는) 목록에 없습니다." << endl;
    }

    return 0;
}

/*
 * 1. 자동 정렬: set과 map은 데이터를 넣기만 해도 Key값을 기준으로 자동 정렬
 * 2. 검색 성능: O(log N)의 시간 복잡도를 가짐 (데이터가 100만 개라도 약 20번의 비교로 찾음)
 * 3. 중복 불허: 하나의 Key에 하나의 Value만 존재할 수 있음 (중복 Key 필요시 multimap 사용)
 * 4. 이진 탐색 트리: 내부적으로 'Red-Black Tree'라는 균형 잡힌 트리 구조를 사용함
 * 이 덕분에 데이터가 아무리 많아도 성능이 급격히 떨어지지 않고 일정하게 유지
 * 5. 요소의 수명: vector와 달리 요소를 추가/삭제해도 다른 요소들의 메모리 주소가 바뀌지 않음
 * (즉, 다른 반복자들이 무효화되지 않는 장점!)
 */
