#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// --- 7일차: 컬러 처리 및 영역 분할 실습 함수 정의 ---

// [show45] 컬러 채널 분리 (RGB -> R, G, B)
void show45() {
    Mat src = imread("lenna.png");
    if (src.empty()) return;

    vector<Mat> bgr;
    split(src, bgr); // 채널 분리

    imshow("Original", src);
    imshow("Blue Channel", bgr[0]);
    imshow("Green Channel", bgr[1]);
    imshow("Red Channel", bgr[2]);
    waitKey();
}

// [show46] HSV 색 공간에서 특정 색상 추출
void show46() {
    Mat src = imread("candies.png");
    if (src.empty()) return;

    Mat hsv, mask;
    cvtColor(src, hsv, COLOR_BGR2HSV);

    // 노란색 영역만 추출 (H: 20~30 범위)
    inRange(hsv, Scalar(20, 100, 100), Scalar(30, 255, 255), mask);

    Mat dst;
    src.copyTo(dst, mask);

    imshow("Original", src);
    imshow("Yellow Only", dst);
    waitKey();
}

// [show47] 이진화 (Thresholding) - 오츠(Otsu) 알고리즘
void show47() {
    Mat src = imread("coins.jpg", IMREAD_GRAYSCALE);
    if (src.empty()) return;

    Mat dst;
    // 자동으로 최적의 임계값을 찾아주는 OTSU 방식
    threshold(src, dst, 0, 255, THRESH_BINARY | THRESH_OTSU);

    imshow("Original", src);
    imshow("Otsu Binary", dst);
    waitKey();
}

// [show48] 모폴로지 연산 - 침식과 팽창 (Erode & Dilate)
void show48() {
    Mat src = imread("circuit.bmp", IMREAD_GRAYSCALE);
    if (src.empty()) return;

    Mat dst_erode, dst_dilate;
    erode(src, dst_erode, Mat());  // 깎기 (노이즈 제거)
    dilate(src, dst_dilate, Mat()); // 키우기 (구멍 메우기)

    imshow("Original", src);
    imshow("Erode", dst_erode);
    imshow("Dilate", dst_dilate);
    waitKey();
}

// [show50] 레이블링 (Labeling) - 객체 개수 세기 및 바운딩 박스
void show50() {
    Mat src = imread("coins.jpg", IMREAD_GRAYSCALE);
    if (src.empty()) return;

    Mat bin;
    threshold(src, bin, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

    Mat labels, stats, centroids;
    int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);

    Mat dst;
    cvtColor(src, dst, COLOR_GRAY2BGR);

    for (int i = 1; i < cnt; i++) { // 0번은 배경이므로 1부터 시작
        int* p = stats.ptr<int>(i);
        if (p[4] < 100) continue; // 너무 작은 객체는 무시 (면적 필터링)

        rectangle(dst, Rect(p[0], p[1], p[2], p[3]), Scalar(0, 0, 255), 2);
    }

    cout << "검출된 동전 개수: " << cnt - 1 << endl;
    imshow("Labeling Results", dst);
    waitKey();
}

// [show52] 외곽선 검출 (Contours)
void show52() {
    Mat src = imread("contours.bmp", IMREAD_GRAYSCALE);
    if (src.empty()) return;

    vector<vector<Point>> contours;
    findContours(src, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    Mat dst;
    cvtColor(src, dst, COLOR_GRAY2BGR);

    for (int i = 0; i < contours.size(); i++) {
        Scalar color(rand() & 255, rand() & 255, rand() & 255);
        drawContours(dst, contours, i, color, 2);
    }

    imshow("Contours", dst);
    waitKey();
}

// --- 메인 함수: 메뉴 선택기 ---
int main() {
    int choice;
    while (true) {
        cout << "\n****************************************" << endl;
        cout << "  [Day 07] 컬러 및 영역 분할 최종 실습" << endl;
        cout << "  45.채널분리  46.HSV추출  47.이진화(오츠)" << endl;
        cout << "  48.모폴로지  50.레이블링  52.외곽선추출" << endl;
        cout << "  0.종료" << endl;
        cout << "****************************************" << endl;
        cout << "실습 번호 입력: ";

        if (!(cin >> choice)) break;
        if (choice == 0) break;

        switch (choice) {
            case 45: show45(); break;
            case 46: show46(); break;
            case 47: show47(); break;
            case 48: show48(); break;
            case 50: show50(); break;
            case 52: show52(); break;
            default: cout << "목록의 번호를 선택하세요." << endl;
        }
        destroyAllWindows();
    }
    return 0;
}
