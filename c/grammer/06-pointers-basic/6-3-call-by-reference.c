/*
 * 주제: 6-3. 주소에 의한 호출 (Call-by-Reference)
 * 날짜: 2026-03-26
 * 핵심: 함수에게 원본 리모컨(주소)을 주면, 함수 밖의 데이터를 직접 조종할 수 있음!
 */

#include <stdio.h>
void swap(int* a, int* b) {        // 두 변수의 값을 바꿈 (Swap), 원본의 주소를 받아야 진짜로 바꿀 수 있음, int* a : 정수형 변수의 주소를 받겠다는 뜻임
    int temp = *a;                 // a가 가리키는 집(원본)의 물건을 잠시 보관
    *a = *b;                       // b네 집 물건을 a집으로 옮김
    *b = temp;                     // 보관했던 a물건을 b집으로 옮김
}

void get_min_max(int arr[], int size, int* min_res, int* max_res) {    // 함수 하나로 두 가지 결과 가져오기(Min-Max), return은 하나뿐이지만, 주소라는 바구니를 던져주면 여러 결과를 담아올 수 있음
    *min_res = arr[0];                                                 // 던져준 바구니(주소)에 첫 번째 값을 담음
    *max_res = arr[0];                                                 

    for (int i = 1; i < size; i++) {
        if (arr[i] < *min_res) *min_res = arr[i];                  // 더 작은 걸 발견하면 원본 바구니 교체
        if (arr[i] > *max_res) *max_res = arr[i];                  // 더 큰 걸 발견하면 원본 바구니 교체    
    }
}

int main() {                                            
    int x = 10, y = 20;
    printf("--- Swap 실습 ---\n");             // Swap 실습(리모컨 전달)
    printf("전: x=%d, y=%d\n", x, y);
    
    swap(&x, &y);                              // 주소(&)를 던져야 함수가 원본을 고침!
    printf("후: x=%d, y=%d (성공!)\n\n", x, y);


                                              
    int data[5] = {40, 10, 90, 70, 50};        // 응용 실습 (다중 결과 반환)
    int low, high;                             // 결과 담을 빈 바구니들 

    printf("--- 응용 실습 (Min-Max) ---\n");
    get_min_max(data, 5, &low, &high);         // low와 high의 주소를 알려줘서 함수가 직접 채우게 함 - 여기 빈 바구니 주소 줄 테니까 결과 좀 채워줘! 라는 뜻
    
    printf("배열 내 최저: %d, 최고: %d\n", low, high);

    return 0;
}

// 1. 값만 보내면? (Call-by-Value) -> 함수가 복사본만 가지고 놀다 끝남 (원본 불변)
// 2. 주소(&)를 보내면? (Call-by-Reference) -> 함수가 원본 위치로 찾아와서 직접 수정함
// 3. scanf("%d", &n)에서 &를 붙이는 이유도 바로 이 원격 조종 때문임!
// 4. 리턴은 하나뿐이지만, 주소를 여러 개 던지면(바구니) 결과도 여러 개 받아올 수 있음! (Min-Max 예제)
