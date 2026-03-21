/*****************************************************************
 * 주제: 5-4. iterator (반복자: 컨테이너 순회의 표준)
 * 작성일: 2026. 03. 21.
 * [5-4. 핵심 요약]
 * 1. iterator: 컨테이너의 원소를 가리키는 '일반화된 포인터'.
 * 2. 공통 분모: 포인터와 사용법(*, ++, !=)이 같아 어떤 컨테이너든 똑같은 코드로 순회 가능.
 * 3. 범위: begin()은 첫 번째 요소, end()는 '마지막 요소의 다음'을 가리킴.
 *****************************************************************/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    vector<int>::iterator it;      // 반복자 선언 (컨테이너타입::iterator 변수명),  v.begin()은 10이 있는 위치를, v.end()는 30 다음 빈 공간을 가리킴 

    cout << "반복자로 출력: ";     // 반복자를 이용한 기본 순회
    for (it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";        // it은 포인터처럼 동작하므로 *를 붙여 '역참조'로 값을 꺼냄   
    }
    cout << endl;

    
    it = v.begin();                // 반복자를 이용한 값 수정
    *it = 100;                     // 첫 번째 요소를 100으로 변경
    cout << "수정 후 첫 요소: " << v[0] << endl;

    cout << "역순 출력: ";         // 역방향 반복자 (reverse_iterator) ,  rbegin()은 마지막 요소, rend()는 첫 번째 이전 공간을 가리킴 
    for (vector<int>::reverse_iterator rit = v.rbegin(); rit != v.rend(); ++rit) {
        cout << *rit << " ";
    }
    cout << endl;

    cout << "auto 활용 출력: ";    // (중요) auto 키워드 활용 (실무에서는 타입을 다 적기 힘드므로 auto 사용)
    for (auto iter = v.begin(); iter != v.end(); ++iter) {
        cout << *iter << " ";
    }
    cout << endl;

    return 0;
}

/* [기술적 원리]
 * 1. 일반화: 인덱스([]) 연산이 없는 자료구조(예: list, set)도 반복자만 있으면 순회 가능함.
 * 2. 반개방 범위 [begin, end): begin은 포함하지만 end는 포함하지 않는 구조임. 
 *    덕분에 'it != v.end()'라는 조건으로 루프를 돌리기 매우 깔끔함.
 * 3. 유효성 주의: 벡터에 push_back 등을 해서 메모리가 재할당되면 기존 반복자는 '무효화'될 수 있음.
 */
