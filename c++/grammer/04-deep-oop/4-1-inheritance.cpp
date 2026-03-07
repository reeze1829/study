/*****************************************************************
 * 주제: 4-1. inheritance (클래스 상속)
 * 작성일: 2026. 03. 07.
 * 핵심 요약:
 * 1. 기본 개념: 기존 클래스(Person)를 물려받아 새로운 클래스(Student) 정의.
 * 2. 생성 순서: 객체 생성 시 부모 생성자 -> 자식 생성자 순으로 호출됨.
 * 3. protected: 외부 접근은 차단하되, 자식 클래스에게는 접근을 허용하는 보안 설정.
 * 4. 상속 방식: public 상속을 통해 부모의 설계도를 안전하게 유지 및 확장.
 *****************************************************************/

#include <iostream>
#include <string>

// 생성자 호출 순서: 실행 결과에서 Person 생성자가 Student 생성자보다 먼저 출력!!
using namespace std;

class Person {                          // 부모 클래스
protected:                              // 자식 클래스에게는 접근을 허용
    string name;                        // name을 private으로 바꾸면 자식 클래스의 study() 함수에서 에러가 

public:
    Person(string n) : name(n) {
        cout << "부모 생성자 호출 (Person: " << name << ")" << endl;
    }
    
    void sleep() {
        cout << name << "이(가) 잠을 잡니다." << endl;
    }
}; 

class Student : public Person {         // 자식 클래스
private:
    int studentID;

public:
    Student(string n, int id) : Person(n), studentID(id) {    // 부모 클래스의 생성자를 명시적으로 호출 (초기화 리스트 활용)
        cout << "자식 생성자 호출 (Student ID: " << studentID << ")" << endl;
    }

    void study() {
        cout << name << " 학생이 공부를 합니다." << endl;      // 부모의 name이 protected이므로 자식에서 직접 접근 가능
    }
};

// ---------------------------------------------------------
// 상속의 3가지 방식 비교
// ---------------------------------------------------------

class Base {
public:    int pub = 1;
protected: int prot = 2;
private:   int priv = 3;
};


class DerivedPublic : public Base {   // Public 상속: 부모의 설계도를 그대로 유지 (가장 많이 사용)
    // pub: public, prot: protected, priv: 접근불가
};


class DerivedProtected : protected Base {  // Protected 상속: 외부 접근은 막고, 내 자식들에게만 물려줌
    // pub: protected, prot: protected, priv: 접근불가
};


class DerivedPrivate : private Base {      // Private 상속: 나까지만 쓰고 상속을 끊음 (강한 보안)
    // pub: private, prot: private, priv: 접근불가
};

int main() {
    cout << "--- 객체 생성 시작 ---" << endl;
    Student s1("홍길동", 20260001);
    cout << "--- 객체 생성 완료 ---" << endl;

    s1.sleep();            // 부모로부터 물려받은 기능
    s1.study();            // 자식만의 고유 기능

    /* 상속 방식 테스트 */
    DerivedPublic dp;
    dp.pub = 10;           // 외부에서 접근 가능
    
    DerivedProtected dprot;
    // dprot.pub = 10;     // Error: protected로 변했기 때문에 외부 접근 불가
    
    DerivedPrivate dpriv;
    // dpriv.pub = 10;     // Error: private으로 변했기 때문에 외부 접근 불가

    return 0;
}
  /*
 *
 * 1. 생성/소멸 순서
 * - 생성자: 부모(Base) -> 자식(Derived) 순으로 호출.
 * - 소멸자: 자식(Derived) -> 부모(Base) 순으로 호출 (생성의 역순).
 *
 * 2. 부모 생성자 호출
 * - 자식 생성자의 '초기화 리스트'에서 부모 생성자를 명시적으로 호출해야 함.
 * - 예: Student(...) : Person(n) {...}
 *
 * 3. protected 접근 제어자
 * - 외부(main 등)에서의 접근은 차단하지만, 상속받은 자식 클래스 내부에서는 
 * public처럼 자유롭게 접근을 허용함.
 *
 * 4. 상속 방식 
 * - public 상속: 부모의 접근 권한을 자식에게도 그대로 유지 (가장 권장됨).
 * - protected 상속: 부모의 public 멤버를 자식 이하에서 protected로 변경.
 * - private 상속: 부모의 모든 멤버를 자식 클래스 내부용(private)으로 봉인.
 *
 * 5. 설계 원칙 (IS-A)
 * - "Student IS-A Person" (학생은 사람이다) 관계가 성립할 때만 상속을 사용함.
 */
