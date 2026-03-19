/*****************************************************************
 * 주제: 5-3. string-class (C++ 표준 문자열 std::string)
 * 작성일: 2026. 03. 19.
 * [5-3. 핵심 요약]
 * 1. std::string: C의 char*를 대체하는 문자열 클래스로, 메모리 관리(크기 조절)가 자동임.
 * 2. 연산자 오버로딩: +, +=, ==, < 등을 통해 문자열을 마치 숫자처럼 직관적으로 다룸.
 * 3. 안전성: 버퍼 오버플로우(공간 부족) 걱정 없이 문자열을 마음껏 확장 가능함.
 *****************************************************************/

#include <iostream>
#include <string>                                  // std::string을 사용하기 위한 필수 헤더k

using namespace std;

int main() {
   
    string str1 = "Hello";                         // 선언 및 초기화
    string str2 = "World";

    string str3 = str1 + " " + str2;               // 문자열 결합 (Concatenation)  ,  + 연산자로 간단히 합칠 수 있음 (내부적으로 메모리 재할당 발생)
    cout << "결합된 문자열: " << str3 << endl;

    if (str1 != str2) {                            // 문자열 비교 (Comparison) , == 연산자로 값 자체가 같은지 바로 확인 가능 (strcmp 불필요)
        cout << "두 문자열은 다릅니다." << endl;
    }

    cout << "문자열 길이: " << str3.length() << endl;      // 길이 확인 및 접근  ,   .length() 또는 .size()를 사용함 (마지막 NULL 문자 제외 순수 글자 수)
    cout << "3번째 글자: " << str3[2] << endl;      // 배열처럼 인덱스 접근 가능

    str1 += " C++";                                // 문자열 추가 및 수정 , 기존 문자열 뒤에 덧붙이기    
    cout << "수정된 str1: " << str1 << endl;

    string target = "World";                       // 문자열 찾기 (Find) ,  찾고자 하는 문자열이 시작되는 인덱스를 반환함
    size_t found = str3.find(target);
    if (found != string::npos) {                   // npos는 "찾지 못함"을 뜻하는 상수
        cout << target << "의 위치: " << found << endl;
    }
                   
    string sub = str3.substr(0, 5);                // 부분 문자열 추출 (Substring),  "Hello" 추출,  substr(시작인덱스, 개수)   
    cout << "추출된 부분 문자열: " << sub << endl;

    return 0;
}

/*
 * [기술적 원리 메모]
 * 1. 객체 기반: string은 내부적으로 char 배열을 동적으로 관리하는 객체임
 * 2. 끝 문자: C의 char*와 달리 내부적으로 길이를 저장하므로 '\0'(NULL)에만 의존하지 않음
 * 3. c_str(): 기존 C언어 함수(printf 등)와 호환이 필요할 때 'str.c_str()'를 사용하여 
 *    char* 타입을 얻을 수 있음
 * 4. npos: 'no position'의 약자로, 검색 실패 시 반환되는 특수한 상수값
 * 5. 성능 주의: 문자열을 + 연산자로 계속 합치면 내부적으로 새로운 메모리 할당이 
 *    반복되어 성능이 저하될 수 있음 (매우 큰 작업 시에는 reserve() 고려)
 */
