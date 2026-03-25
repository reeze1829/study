#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// --- 2일차: 입출력 및 이벤트 처리 실습 함수 정의 ---

// [show10] 카메라(웹캠) 입력 및 출력
void show10() {
    VideoCapture cap(0); // 0번 카메라 오픈
    if (!cap.isOpened()) return;

    Mat frame;
    while (true) {
        cap >> frame; // 한 프레임 받아오기
        if (frame.empty()) break;
        imshow("Camera", frame);
        if (waitKey(10) == 27) break; // ESC 누르면 종료
    }
}

// [show11] 동영상 파일 읽기 및 출력
void show12() {
    VideoCapture cap("video1.mp4");
    if (!cap.isOpened()) return;

    Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;
        imshow("Video", frame);
        if (waitKey(10) == 27) break;
    }
}

// [show13] 동영상 저장 (VideoWriter)
void show13() {
    VideoCapture cap(0);
    int fourcc = VideoWriter::fourcc('M', 'J', 'P', 'G');
    VideoWriter output("output.avi", fourcc, 30, Size(640, 480));

    Mat frame;
    while (true) {
        cap >> frame;
        output << frame;
        imshow("Recording...", frame);
        if (waitKey(10) == 27) break;
    }
}

// [show14] 다양한 도형 그리기 (선, 사각형, 원)
void show14() {
    Mat img(400, 600, CV_8UC3, Scalar(255, 255, 255));
    line(img, Point(50, 50), Point(200, 50), Scalar(0, 0, 255), 3);
    rectangle(img, Rect(50, 100, 200, 150), Scalar(255, 0, 0), 2);
    circle(img, Point(400, 200), 50, Scalar(0, 255, 0), -1);
    putText(img, "OpenCV Drawing", Point(50, 350), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,0));
    imshow("Draw", img);
    waitKey();
}

// [show16] 키보드 이벤트 처리
void show16() {
    Mat img = imread("lenna.png");
    imshow("img", img);
    while (true) {
        int key = waitKey();
        if (key == 'i' || key == 'I') {
            img = ~img; // 'i' 누르면 색상 반전
            imshow("img", img);
        }
        else if (key == 27) break; // ESC 종료
    }
}

// [show17] 마우스 이벤트 처리 (마우스 클릭 시 좌표 출력)
void on_mouse(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_LBUTTONDOWN) {
        cout << "Click: " << x << ", " << y << endl;
    }
}
void show17() {
    Mat img = imread("lenna.png");
    namedWindow("Mouse Test");
    setMouseCallback("Mouse Test", on_mouse);
    imshow("Mouse Test", img);
    waitKey();
}

// [show18] 트랙바를 이용한 밝기 조절
void on_trackbar(int pos, void* userdata) {
    Mat img = *(Mat*)userdata;
    Mat dst = img + pos;
    imshow("Trackbar", dst);
}
void show18() {
    Mat img = imread("lenna.png", IMREAD_GRAYSCALE);
    int pos = 0;
    namedWindow("Trackbar");
    createTrackbar("Brightness", "Trackbar", &pos, 100, on_trackbar, &img);
    imshow("Trackbar", img);
    waitKey();
}

// [show19] 마스크 연산을 이용한 영상 합성
void show19() {
    Mat src = imread("airplane.bmp");
    Mat mask = imread("mask_plane.bmp", IMREAD_GRAYSCALE);
    Mat dst = imread("sky.bmp");
    
    // 비행기(src)에서 마스크 영역만 따와서 배경(dst)에 복사
    src.copyTo(dst, mask);
    
    imshow("Composite", dst);
    waitKey();
}

// --- 메인 함수: 메뉴 선택기 ---
int main() {
    int choice;
    while (true) {
        cout << "\n****************************************" << endl;
        cout << "  [Day 02] 입출력 및 이벤트 처리 실습" << endl;
        cout << "  10.카메라  12.파일읽기  13.영상저장  14.도형그리기" << endl;
        cout << "  16.키보드  17.마우스    18.트랙바    19.마스크합성" << endl;
        cout << "  0.종료" << endl;
        cout << "****************************************" << endl;
        cout << "실습 번호 입력: ";
        
        if (!(cin >> choice)) break;
        if (choice == 0) break;

        switch (choice) {
            case 10: show10(); break;
            case 12: show12(); break;
            case 13: show13(); break;
            case 14: show14(); break;
            case 16: show16(); break;
            case 17: show17(); break;
            case 18: show18(); break;
            case 19: show19(); break;
            default: cout << "목록에 있는 번호를 선택해주세요." << endl;
        }
        destroyAllWindows();
    }
    return 0;
}
