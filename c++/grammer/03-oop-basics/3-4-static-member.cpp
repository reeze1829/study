/*****************************************************************
 * 주제: 3-4. static (정적 멤버)
 * 작성일: 2026. 03. 05.
 * 핵심 요약:
 * 1. static 변수: 객체마다 생성되지 않고, 모든 객체가 '공유'하는 단 하나의 변수.
 * 2. static 함수: 객체 없이 클래스 이름만으로 호출 가능 (Student::getCount()).
 * 3. 외부 초기화: 클래스 설계도와 별개로 메모리 공간을 확보하는 과정 (필수).
 * 4. 주소 확인: s1, s2가 서로 다른 객체임에도 동일한 static 변수 주소를 가짐을 증명.
 *****************************************************************/
#include <iostream>
#include <string>

class Student {
private:
    static int studentCount;                          // 정적 멤버 변수 선언 (설계도에 표시) - 모든 객체가 공유하는 변수! 클래스명::변수명으로 접근
    std::string name;

public:
    Student(std::string n) : name(n) {
        studentCount++;                               // 객체가 생성될 때마다 공용 카운트 증가
        std::cout << "  [생성] " << name << " 학생이 등록되었습니다." << std::endl;
    }

    ~Student() {
        studentCount--;                               // 객체가 사라질 때마다 공용 카운트 감소
        std::cout << "  [소멸] " << name << " 학생이 퇴실했습니다." << std::endl;
    }

    static int getCount() {                           // 정적 멤버 함수: 객체 없이 클래스 이름으로 호출 가능 - 특정 객체의 데이터(name 등)는 건드릴 수 없고, 오직 static 변수만 다룰 수 있음.
        return studentCount;
    }
    
    void checkAddress() {                             // 정적 변수의 주소를 확인하는 함수
        std::cout << "  [" << name << "가 접근한 카운트 주소]: " << &studentCount << std::endl;
    }
};


int Student::studentCount = 0;                        // ***정적 변수는 클래스 외부에서 반드시 초기화해야 함!***  -- 
                                                      //  클래스 내부의 선언은 설계도일 뿐이며, 실제 메모리 공간을 확보하고 중복 생성을 막기 위해 클래스 외부에서 단 한 번 명시적으로 초기화함!!
int main() {
    std::cout << " 객체 생성 전 카운트: " << Student::getCount() << " (객체 없이도 호출 가능)" << std::endl;

    Student s1("철수");
    Student s2("영희");

    std::cout << "\n 주소값 비교 (정적 변수는 하나만 존재함을 증명함)";
    s1.checkAddress();
    s2.checkAddress();

    {
        std::cout << "\n 지역 블록 내 학생 추가" << std::endl;
        Student s3("길동");
        std::cout << "   현재 학생 수: " << Student::getCount() << "명" << std::endl;
    }                                                                                       // s3 소멸

    std::cout << "\n 블록 종료 후 학생 수: " << Student::getCount() << "명" << std::endl;

    return 0;
    // 메인 함수가 종료되면서 s1, s2 순서로 소멸자가 호출되고 카운트가 줄어듬!!
    // 객체는 사라져도 static 변수인 studentCount와 getCount() 함수는 프로그램이 끝날 때까지 메모리에 남아있음!
}   // 여기서 s1, s2가 최종 소멸하며 카운트는 0이 됨
