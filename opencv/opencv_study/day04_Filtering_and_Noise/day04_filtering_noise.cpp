#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// --- 4일차: 필터링과 노이즈 제거 실습 함수 정의 ---

// [show26] 엠보싱(Embossing) 필터 - 영상에 입체감 부여
void show26() {
    Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
    if (src.empty()) return;

    // 엠보싱 마스크 정의
    float data[] = { -1, -1, 0, -1, 0, 1, 0, 1, 1 };
    Mat emboss(3, 3, CV_32FC1, data);

    Mat dst;
    filter2D(src, dst, -1, emboss, Point(-1, -1), 128);

    imshow("Original", src);
    imshow("Embossing", dst);
    waitKey();
}

// [show27] 평균값 필터(Mean Filter) - 블러링 기초
void show27() {
    Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
    if (src.empty()) return;

    imshow("Original", src);

    // 커널 크기를 키울수록 더 부드러워짐 (3x3, 5x5)
    for (int ksize = 3; ksize <= 7; ksize += 2) {
        Mat dst;
        blur(src, dst, Size(ksize, ksize));
        String desc = format("Mean Filter %dx%d", ksize, ksize);
        imshow(desc, dst);
        waitKey();
    }
}

// [show28] 가우시안 필터(Gaussian Filter) - 자연스러운 블러링
void show28() {
    Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
    if (src.empty()) return;

    Mat dst;
    // 시그마(표준편차) 값을 조절하여 블러 강도 결정
    GaussianBlur(src, dst, Size(), 1.0);

    imshow("Original", src);
    imshow("Gaussian Blur", dst);
    waitKey();
}

// [show29] 언샤프 마스크 필터(Unsharp Mask) - 날카로운 영상(Sharpening)
void show30() {
    Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
    if (src.empty()) return;

    // 1. 가우시안 블러로 부드러운 영상 생성
    Mat blurred;
    GaussianBlur(src, blurred, Size(), 1.0);

    // 2. 원본에서 부드러운 영상을 빼서 날카로운 성분 강조
    // dst = 원본 + (원본 - 블러본) * 가중치
    float alpha = 1.0f;
    Mat dst = src + (src - blurred) * alpha;

    imshow("Original", src);
    imshow("Sharpening", dst);
    waitKey();
}

// [show31] 미디언 필터(Median Filter) - 소금-후추 잡음 제거에 탁월
void show31() {
    Mat src = imread("lenna.png", IMREAD_GRAYSCALE);
    if (src.empty()) return;

    // 인위적으로 노이즈 추가 (실습용)
    for (int i = 0; i < 500; i++) {
        int x = rand() % src.cols;
        int y = rand() % src.rows;
        src.at<uchar>(y, x) = (i % 2 == 0) ? 255 : 0;
    }

    Mat dst;
    medianBlur(src, dst, 3);

    imshow("Noisy Image", src);
    imshow("Median Filtered", dst);
    waitKey();
}

// [show32] 양방향 필터(Bilateral Filter) - 에지는 보존하며 배경만 블러링
void show32() {
    Mat src = imread("lenna.png", IMREAD_GRAYSCALE);
    if (src.empty()) return;

    Mat dst_gaussian, dst_bilateral;
    GaussianBlur(src, dst_gaussian, Size(), 5.0);
    bilateralFilter(src, dst_bilateral, -1, 10, 5);

    imshow("Original", src);
    imshow("Gaussian (Edge Blurred)", dst_gaussian);
    imshow("Bilateral (Edge Preserved)", dst_bilateral);
    waitKey();
}

// --- 메인 함수: 메뉴 선택기 ---
int main() {
    int choice;
    while (true) {
        cout << "\n****************************************" << endl;
        cout << "  [Day 04] 필터링과 노이즈 제거 실습" << endl;
        cout << "  26.엠보싱  27.평균값필터  28.가우시안  30.샤프닝" << endl;
        cout << "  31.미디언  32.양방향필터" << endl;
        cout << "  0.종료" << endl;
        cout << "****************************************" << endl;
        cout << "실습 번호 입력: ";

        if (!(cin >> choice)) break;
        if (choice == 0) break;

        switch (choice) {
        case 26: show26(); break;
        case 27: show27(); break;
        case 28: show28(); break;
        case 30: show30(); break;
        case 31: show31(); break;
        case 32: show32(); break;
        default: cout << "목록에 있는 번호를 선택해주세요." << endl;
        }
        destroyAllWindows();
    }
    return 0;
}
