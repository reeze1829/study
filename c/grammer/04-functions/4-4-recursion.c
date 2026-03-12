/*
 * 주제: 4-4. 재귀 함수 (Recursion)
 * 날짜: 2026-03-12
 * 내용: 
 * 1. 탈출 조건: if (n <= 1) 처럼 멈추는 지점이 없으면 무한 재귀에 빠짐
 * 2. 스택(Stack) 구조: 함수가 호출될 때마다 메모리에 박스가 쌓임
 * 3. 역순 반환: 가장 나중에 호출된 함수가 가장 먼저 값을 반환하며 위로 전달함
 */

#include <stdio.h>
// 재귀 함수는 문제를 잘게 쪼개어 끝(바닥)까지 내려간 뒤, 바톤을 터치하듯 결과를 들고 다시 올라오는 과정임!
// 팩토리얼 함수: 재귀의 정석
int factorial(int n) {
  
    if (n <= 1) {                                               // 내려가는 길 (Down / 호출 단계)
        printf("  [바닥] n이 1에 도달! 이제 계산하며 위로 올라갑니다.\n");
        return 1;                                               // 가장 안쪽 인형(바닥)에서 1을 들고 나감
    }

    printf("  [Down] %d! 구하기 위해 %d * factorial(%d) 호출 및 대기\n", n, n, n - 1);
    
    int result = n * factorial(n - 1);                         
    // 1. factorial(n-1)이 값을 구해올 때까지 이 줄에서 기다림 (대기)
    // 2. 밑에 놈이 값을 던져주면(return), 그 값을 가져와서 내 숫자 n과 곱함 (계산)
    // 3. 계산된 최종 결과값을 내 위에 놈에게 던져줌 (보고)
    
    printf("  [Up] 아래에서 가져온 값과 내 숫자 %d를 곱해 %d 반환\n", n, result);    // 올라오는 길 (Up / 반환 단계)
    return result;
}

void count_down(int n) {                                        // 카운트다운 함수: 재귀의 흐름 이해
    if (n < 0) return;                                          // 탈출 조건
    
    printf("%d ", n);   
    count_down(n - 1);  
}

int main() {
    printf("--- 팩토리얼 실험 (5!) ---\n");
    int final_result = factorial(5);
    printf("최종 결과: %d\n\n", final_result);

    printf("--- 카운트다운 실험 ---\n");
    count_down(5);
    printf("\n--- 실험 종료 ---\n");

    return 0;
}

/*
 * [핵심 정리]
 * 1. 스택 오버플로우 : 탈출 조건이 없으면 메모리(Stack)가 꽉 차서 프로그램 강제 종료.
 * 2. 재귀 vs 반복문 : 재귀는 코드가 간결해지지만(트리 탐색 등), 메모리 사용량은 반복문보다 많을 수 있음.
 * 3. 동작 원리 : 먼저 부른 놈이 가장 나중에 끝나는 LIFO(Last In First Out) 구조.
 * 4. 바톤 터치 : 아래 함수가 return한 값을 위 함수가 받아 n과 곱하며 거슬러 올라감.
 */
