/*****************************************************************
 * 주제: 4-4. operator-overloading (연산자 오버로딩 심화)
 * 작성일: 2026. 03. 13.
 * [4-4. 핵심 요약]
 * 1. 연산자 오버로딩: +, -, << 같은 기본 연산자를 객체에도 쓸 수 있게 재정의함.
 * 2. 다양한 연산자: 산술(+), 비교(==), 증감(++), 대입(=) 등 대부분의 기호가 가능.
 * 3. 코드 직관성: 객체를 기본 자료형(int, double)처럼 자연스럽게 다룰 수 있게 함.
 *****************************************************************/

#include <iostream>

using namespace std;

class Point {
private:
    int x, y;

public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    
    Point operator+(const Point& other) {                        //  [+] 산술 연산자: p1 + p2  // (const Point& other): 상대방 데이터를 읽기전용으로 별명(&)만 붙여 가져옴 (메모리 절약)
        return Point(this->x + other.x, this->y + other.y);
    }

    bool operator==(const Point& other) {                        //  [==] 비교 연산자: 두 좌표가 같은지 확인 (결과는 true/false)
        return (x == other.x && y == other.y);                   
    }

    Point& operator++() {                                        //  [++] 전위 증감 연산자: ++p1 (좌표를 1씩 증가)  // Point&: 증가된 나 자신을 그대로 돌려줘서 바로 다음 계산에 쓰이게 함
        x++;
        y++;
        return *this;                                            // 자기 자신의 참조를 반환하여 연속 계산 가능하게 함 ,  *this는 현재 객체 자신을 의미함
    }

    friend ostream& operator<<(ostream& os, const Point& p) {    // [<<] 출력 연산자 (friend: 남인 cout이 내 private 멤버인 x, y를 볼 수 있게 허용함)  // ostream& os: 출력 스트림(모니터)의 별명을 가져와서 거기에 데이터를 던짐
        os << "(" << p.x << ", " << p.y << ")";
        return os;                                               // os를 다시 돌려줘야 cout << p1 << p2; 처럼 이어서 출력 가능
    }
};

int main() {
    Point p1(10, 20);
    Point p2(10, 20);
    Point p3(5, 5);
  
    Point p4 = p1 + p3;                          // [테스트 1] 산술 연산
    cout << "p1 + p3 = " << p4 << endl;

    if (p1 == p2) {                              // [테스트 2] 비교 연산
        cout << "p1과 p2는 같은 위치에 있습니다." << endl;
    }

    cout << "증가 전 p1: " << p1 << endl;        // [테스트 3] 증감 연산
    ++p1;
    cout << "증가 후 p1: " << p1 << endl;

    return 0;
}

/*
 * 1. 전위(++a) vs 후위(a++): 두 방식은 오버로딩 시 매개변수 유무로 구분함 
 * (후위는 operator++(int) 처럼 int 인자를 넣어 약속함)
 * 2. 연산자 우선순위: 오버로딩을 해도 기존 연산자의 우선순위는 바뀌지 않음
 * 3. 얕은 복사 문제: 포인터 멤버가 있는 클래스는 반드시 [=] 대입 연산자를 
 * 직접 오버로딩하여 깊은 복사를 구현해야 메모리 오류가 안 남
 */
