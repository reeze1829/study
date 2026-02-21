/*****************************************************************
 * 주제: 2-2. 참조에 의한 호출 (Call-by-Reference)
 * 작성일: 2026. 02. 21.
 * 설명: 
 * - 함수 매개변수로 참조자(&)를 사용하여 원본 변수를 직접 수정하는 법 학습
 * - Call-by-Value(복사)와 Call-by-Reference(공유)의 차이 비교
 * - const 참조자를 활용한 데이터 보호 및 성능 최적화(Safety & Speed) 실습
 *****************************************************************/

#include <iostream>

void swapByValue(int a, int b) {        // 값에 의한 호출
    int temp = a;
    a = b;
    b = temp;
}

void swapByRef(int &a, int &b) {        // 참조에 의한 호
    int temp = a;
    a = b;
    b = temp;                           // 그냥 변수 쓰듯 쓰는데 원본이 바뀜!
}

void printData(const int &ref) {        // const를 붙이면 안전하게 읽기만 할 수도 있음
    std::cout << "const 참조자로 출력: " << ref << std::endl;          // ref = 100; 별명을 통해 원본 값을 바꾸려는 시도, 주석을 풀면 에러: const 약속을 어겼기 때문에 컴퓨터가 실행 파일 생성을 거부함.
}                                                                     // const &는 원본은 안전하게 지키면서 성능은 빠르게 

int main() {
    int val1 = 10, val2 = 20;
    swapByValue(val1, val2);            // 값에 의한 호출 테스트
    std::cout << "Value 후: " << val1 << " " << val2 << " (그대로)" << std::endl;

    swapByRef(val1, val2);                                                           // 참조에 의한 호출 테스트
    std::cout << "Ref 후  : " << val1 << " " << val2 << " (바뀜!)" << std::endl;     // 주소(&)를 넘길 필요 없이 그냥 변수 이름만 던지면 됨!
    printData(val1);
    // 가독성 - 함수 내부에서 역참조 연산자(*)를 쓸필요 없이 그냥 일반변수 쓰듯이 사용
    // 편의성 - 함수를 호출할때 swap(&a, &b)처럼 주소를 따서 보낼 필요가 없음! swap(a, b) 하면 끝!
    // 성능 - 거대한 데이터를 복사하지 않고 이름표만 빌려주는 것이라 메모리와 속도면에서 좋음!
    // 안전성(const) - 성능은 챙기면서 원본이 바뀌는 것은 방지함
    return 0;
}
