/*
 * 주제: 3-4. 이중 반복문 심화 (nested-loops-star)
 * 날짜: 2026-03-04
 * 내용: 
 * 1. 이중 루프의 좌표 설계: i(행)와 j(열)의 관계식을 활용한 다양한 도형 출력
 * 2. 공백과 별의 독립 루프 제어: 한 줄 내에서 여러 for문을 나란히 배치하는 테크닉 숙달
 * 3. 피라미드 공식 도출: 홀수 수열(2n+1) 규칙을 코드로 변환하여 대칭 구조 구현
 * 4. 마름모(Diamond) 알고리즘: 상단 피라미드와 하단 역피라미드의 결합 및 경계 조건(중앙행 중복) 처리
 */
#include <stdio.h>

int main() {
    printf("왼쪽 정렬 직각삼각형 \n");                    // 왼쪽 정렬 직각삼각형 - 줄 번호(i)가 곧 별의 개수 (정비례 관계!)
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= i; j++) {
            printf("*");
        }
        printf("\n");
    }
    printf("\n");

    printf("역방향 직각삼각형 \n");                       // 역방향 직각삼각형 - j가 5부터 시작해서 i보다 클 때까지만 감소함 (깎아내려 개수 줄이기)
    for (int i = 0; i < 5; i++) {
        for (int j = 5; j > i; j--) {
            printf("*");
        }
        printf("\n");
    }
    printf("\n");
  
    printf("오른쪽 정렬 직각삼각형 \n");     // 오른쪽 정렬 직각삼각형 - [공백 루프] 먼저 돌리고, 그 옆에 [별 루프] 이어 붙이기 (오른쪽 정렬)
    for (int i = 0; i < 5; i++) {
        for (int j = 4; j > i; j--) printf(" ");          // 공백: 4-3-2-1-0 (줄어드는 공백만큼 별이 밀림)
        for (int k = 0; k <= i; k++) printf("*");          // 별: 1-2-3-4-5
        printf("\n");
    }
    printf("\n");

    printf("오른쪽 정렬 역삼각형 \n");       // 오른쪽 정렬 역삼각형 - 공백은 늘어나고(0->4), 별은 줄어듦(5->1) (대각선 반전)
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < i; j++) printf(" ");          // 공백: 0-1-2-3-4
        for (int k = 5; k > i; k--) printf("*");          // 별: 5-4-3-2-1
        printf("\n");
    }
    printf("\n");

    printf("피라미드 \n");                                  // 피라미드 - 공백(4->0) + 별 홀수 공식(2*i + 1) (중심 잡기)
    for (int i = 0; i < 5; i++) {
        for (int j = 4; j > i; j--) printf(" ");            // 왼쪽 여백 확보
        for (int k = 0; k < (2 * i + 1); k++) printf("*");  // 홀수 공식으로 양옆 대칭 별 찍기
        printf("\n");
    }
    printf("\n");
  
    printf("마름모 \n");                                    // 마름모 - [위쪽 5줄] + [아래쪽 4줄]
    for (int i = 0; i < 5; i++) {                           // 위쪽 (5줄)
        for (int j = 4; j > i; j--) printf(" ");
        for (int k = 0; k < (2 * i + 1); k++) printf("*");
        printf("\n");
    }
  
    for (int i = 0; i < 4; i++) {                           // 아래쪽 (4줄: 중앙 9개 줄은 겹치지 않게 4줄만 출력함)
        for (int j = 0; j <= i; j++) printf(" ");           // 공백: 1-2-3-4
        for (int k = 0; k < (2 * (3 - i) + 1); k++) printf("*");  // 별: 7-5-3-1 (남은 줄에 맞춰 홀수로 감소함)
        printf("\n");
    }

    return 0;
}
