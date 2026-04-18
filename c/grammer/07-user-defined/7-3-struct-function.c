/*
 * 주제: 7-3. 구조체와 함수 (Pass by Value vs Pass by Reference)
 * 날짜: 2026-04-18
 * 핵심: 구조체는 덩치가 크므로 주소를 통해 효율적으로 제어한다.
 */

#include <stdio.h>

struct Student {
    char name[20];
    int score;
};

// 값 전달 방식 (비효율적)
// 구조체 전체가 복사되어 들어옴 -> 원본 수정 불가능
void failUpdate(struct Student s) {
    s.score = 100;                        // 여기서 s는 복사본일 뿐! 함수가 끝나면 사라짐 
}

// 주소 전달 방식 (효율적 / 국룰)
// 구조체의 주소만 전달됨 (8byte) -> 화살표(->)로 원본 수정 가능 
void successUpdate(struct Student *p) {
    p->score = 100;                       // 주소를 알고 있으므로 메인에 있는 진짜 상자(s1)를 열어서 고침!
}

int main() {
    struct Student s1 = {"홍길동", 80};

    printf("초기 점수: %d\n", s1.score);

    // 값 전달 테스트 (원본 변화 없음)
    failUpdate(s1);
    printf("값 전달 함수 호출 후: %d (복사본만 수정됨)\n", s1.score);

    // 주소 전달 테스트 (원본 수정 성공)
    successUpdate(&s1); // 주소(&)를 던져줌
    printf("주소 전달 함수 호출 후: %d (원본 수정 완료!)\n", s1.score);

    return 0;
}

// [핵심 요약]
// 1. 점(.)은 내 손에 든 상자를 열 때 (변수)
// 2. 화살표(->)는 주소지로 찾아가서 상자를 열 때 (포인터)
// 3. 구조체는 덩치가 커서 주소만 주고받는 것이 성능상 압도적으로 유리함

// 4. 압도적으로 유리한 이유는!!? (메모리 분석)
// - 값 전달(failUpdate): Student 구조체가 100개 담긴 배열이라면? 
//   호출할 때마다 수천 바이트를 메모리에 복사해야 함 (CPU 비명 발생)
// - 주소 전달(successUpdate): 구조체 크기가 1GB여도 딱 8바이트(주소값)만 전달함.

// 5. 안전 장치 - const의 사용
// "수정은 안 하고 출력만 하고 싶은데, 속도 때문에 주소로 보내고 싶을 때"는?
// void printStudent(const struct Student *p) { 
//     printf("%d", p->score); 
//     // p->score = 100; <- const 때문에 수정 시도 시 컴파일 에러 발생 (보안 강화)
// }
