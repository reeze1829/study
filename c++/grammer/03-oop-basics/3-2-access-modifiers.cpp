/*****************************************************************
 * 주제: 3-2. 접근 제어자(Access Modifiers)와 캡슐화
 * 작성일: 2026. 03. 01.
 * 설명: 
 * 1. public: 누구나 접근 가능한 외부 인터페이스
 * 2. private: 클래스 내부에서만 접근 가능한 자물쇠 (데이터 보호의 핵심)
 * 3. protected: 외부 접근은 막되, 상속받은 자식에게는 허용하는 가족 전용 공간
 * 4. Getter/Setter: private 멤버를 안전하게 다루는 '검문소'이자 '안전 통로'
 * 핵심: 캡슐화는 나중에 내부 로직을 고쳐도 외부 코드를 안 건드려도 되는 '유지보수성'을 위한 것!
 *****************************************************************/
#include <iostream>
#include <string>

class Student {
private:     // 외부에서 직접 수정 불가! (자물쇠)    // 데이터는 private로 숨기고, 필요한 기능만 public으로 열어줌!!
    int age;
    int id_number;          // 외부에서 몰라도 되는 민감한 정보

    void generateID() {     // 내부에서만 쓰는 보조 함수 (비공개 로직)
        id_number = age * 100 + 7; 
    }

protected:                  // 자식 클래스에게만 허용하는 보안 영역 - private은 자식도 못 쓰게 꽉 잠그는 것이고, protected는 "외부인은 안 되지만 내 자식은 마음대로 써라"는 가족용 공유 변수임!
    std::string school = "코딩 대학교";

public:                     // 외부 통로                                              // public(직접접근)
    std::string name;                                                                 
    void setAge(int a) {      //Setter: 값을 안전하게 설정하는 함수                    // 함수접근***(setter(입력), getter(출력)***) - 잘못된 데이터 방지(필터링)
        if (a < 0) {          // 검증 로직 추가 가능                                   //                            - 읽기전용,쓰기전용 설정
            std::cout << "나이는 음수가 될 수 없습니다!" << std::endl;                 //                            - 내부로직의 변화를 숨김(캡슐화)
            age = 0;                                                                  // - 변수를 private로 보호하면서 함수라는 안전통로를 통해 데이터를 검증하고 전달하는 방식!!!
        } else {                                                                      // private일때만 쓰이는 이유는 제어권 - 외부의 무분별한 접근을 차단하고 클래스 주인이 데이터의 생명주기를 완전히 통제하기 위해
            age = a;                                                                  //                             안전성 - main에서 무슨 짓을 해도 변수가 논리적 오류를 일으키지 않도록 방어막을 치기 위해
        }                                                                             //                             유연성(캡슐화) - 나중에 내부 로직이 바뀌어도 외부 코드를 건드리지 않기 위해 - 유지보수
        generateID();         // 나이가 설정될 때 내부적으로 ID도 생성!  
    }
    int getAge() {            //Getter: 값을 안전하게 읽어오는 함수
        return age;
    }
    void showInfo() {         // 전체 정보를 출력하는 기능
        std::cout << "[" << school << "] " << name << " (ID: " << id_number << ")" << std::endl;
    }
};

int main() {                   // 메인에서는 id_number가 어떻게 만들어지는지(generateID)알 필요도 없고 건드릴 수도 없음!! setAge만 하면 알아서 처리됨 --캡슐화!!
    Student s1;
    s1.name = "철수"; 
    // s1.age = -20;  에러! private이라 직접 접근 불가
    // s1.id_number = 123;  에러! 이것도 private이라 안 보임
    // s1.generateID();  에러! 내부 전용 함수라 호출 불가

    s1.setAge(20);    // 안전하게 함수를 통해 설정 (내부에서 ID 생성도 자동으로 일어남)
    
    std::cout << s1.name << "의 나이: " << s1.getAge() << "세" << std::endl;
    s1.showInfo();    // 캡슐화된 정보를 한 번에 확인

    return 0;
}
