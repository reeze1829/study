#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 기초 및 행렬 조작 실습 함수 정의

// [show1] 이미지 읽기, 속성 출력 및 복제
void show1() {
    Mat image1 = imread("lenna.png");
    Mat image2 = imread("dog.jpg");
    if (image1.empty() || image2.empty()) {
        cerr << "에러: 이미지 파일을 찾을 수 없습니다." << endl;
        return;
    }
    Mat image3 = image1.clone();
    cout << "--- Image Info ---" << endl;
    cout << "Size: " << image1.cols << "x" << image1.rows << " | Channels: " << image1.channels() << endl;

    imshow("LENNA", image1);
    imshow("DOG", image2);
    imshow("Clone", image3);
    waitKey();
}

// [show2] 행렬 생성 및 색상 지정
void show2() {
    Mat img1(400, 600, CV_8UC3, Scalar(255, 0, 0)); // Blue
    Mat img2(400, 600, CV_8UC3, Scalar(0, 255, 0)); // Green
    imshow("Blue Matrix", img1);
    imshow("Green Matrix", img2);
    waitKey();
}

// [show3] 특수 행렬 생성 (Zeros, Ones, Eye)
void show3() {
    Mat mat1 = Mat::zeros(3, 3, CV_32FC1);
    Mat mat2 = Mat::ones(3, 3, CV_32FC1);
    Mat mat3 = Mat::eye(3, 3, CV_32FC1);
    cout << "Zeros:\n" << mat1 << "\nOnes:\n" << mat2 << "\nIdentity:\n" << mat3 << endl;
}

// [show4] 얕은 복사(참조) vs 깊은 복사(Clone)
void show4() {
    Mat img1 = imread("dog.bmp");
    if (img1.empty()) return;

    Mat img2 = img1.clone(); // 깊은 복사
    Mat img4 = img1;         // 얕은 복사 (참조)

    img1.setTo(Scalar(0, 255, 255)); // 원본을 노란색으로 변경

    imshow("Clone (Safe)", img2);
    imshow("Reference (Changed)", img4);
    waitKey();
}

// [show5] 관심 영역(ROI) 설정 및 반전
void show5() {
    Mat img1 = imread("lenna.png");
    if (img1.empty()) return;

    Mat img2 = img1(Rect(200, 200, 200, 200)); // ROI 참조
    img2 = ~img2; // 선택 영역 색상 반전

    imshow("ROI Inverse", img1);
    waitKey();
}

// [show6] at()을 이용한 픽셀 직접 접근
void show6() {
    Mat mat1 = Mat::zeros(3, 4, CV_8UC1);
    for (int i = 0; i < mat1.rows; i++) {
        for (int j = 0; j < mat1.cols; j++) {
            mat1.at<uchar>(i, j)++;
        }
    }
    cout << "Pixel Access (at):\n" << mat1 << endl;
}

// [show7] 행렬 메타데이터 출력
void show7() {
    Mat img1 = imread("lenna.png");
    if (img1.empty()) return;
    cout << "Rows: " << img1.rows << ", Cols: " << img1.cols << endl;
}

// [show8] 행/열 참조 연산
void show8() {
    Mat mat1 = Mat::zeros(3, 3, CV_32FC1);
    Mat row = mat1.row(0); // 첫 번째 행 참조
    cout << "First Row Reference:\n" << row << endl;
}

// [show9] InputArray 기초
void show9() {
    Mat mat1 = Mat::eye(3, 3, CV_32FC1);
    cout << "InputArray Test:\n" << mat1 << endl;
}

// --- 메인 함수: 메뉴 선택기 ---
int main() {
    int choice;
    while (true) {
        cout << "\n****************************************" << endl;
        cout << "  [Day 01] OpenCV 기초 및 행렬 조작 실습" << endl;
        cout << "  1.이미지IO  2.행렬생성  3.특수행렬  4.복사비교" << endl;
        cout << "  5.ROI반전   6.픽셀접근  7.메타데이터 8.행참조" << endl;
        cout << "  9.배열출력  0.종료" << endl;
        cout << "****************************************" << endl;
        cout << "실습 번호 입력: ";
        
        if (!(cin >> choice)) break; // 숫자가 아닌 입력 시 종료
        if (choice == 0) break;

        switch (choice) {
            case 1: show1(); break;
            case 2: show2(); break;
            case 3: show3(); break;
            case 4: show4(); break;
            case 5: show5(); break;
            case 6: show6(); break;
            case 7: show7(); break;
            case 8: show8(); break;
            case 9: show9(); break;
            default: cout << "1~9 사이의 번호를 선택해주세요." << endl;
        }
        destroyAllWindows(); // 각 실습 종료 후 모든 창 닫기
    }
    cout << "프로그램을 종료합니다." << endl;
    return 0;
}















