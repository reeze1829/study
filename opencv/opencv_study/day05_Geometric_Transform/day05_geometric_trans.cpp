#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// --- 5일차: 기하학적 변환 실습 함수 정의 ---

// [show33] 세 점을 이용한 아핀 변환 (getAffineTransform)
void show33() {
    Mat src = imread("tekapo.bmp");
    if (src.empty()) return;

    Point2f srcPts[3], dstPts[3];
    srcPts[0] = Point2f(0, 0);
    srcPts[1] = Point2f(src.cols - 1.0f, 0.0f);
    srcPts[2] = Point2f(src.cols - 1.0f, src.rows - 1.0f);

    dstPts[0] = Point2f(50.0f, 50.0f);
    dstPts[1] = Point2f(src.cols - 100.0f, 100.f);
    dstPts[2] = Point2f(src.cols - 50.f, src.rows - 50.f);

    Mat M = getAffineTransform(srcPts, dstPts);
    Mat dst;
    warpAffine(src, dst, M, Size());

    imshow("Original", src);
    imshow("Affine Transform", dst);
    waitKey();
}

// [show34/36] 영상의 이동 및 확대 (Affine Matrix 직접 생성)
void show34_36() {
    Mat src = imread("tekapo.bmp");
    if (src.empty()) return;

    // 이동 변환 행렬 (x+150, y+100)
    Mat M_move = (Mat_<float>(2, 3) << 1, 0, 150, 0, 1, 100);
    Mat dst_move;
    warpAffine(src, dst_move, M_move, Size());

    // 확대 변환 (2배 확대)
    Mat M_scale = (Mat_<float>(2, 3) << 2, 0, 0, 0, 2, 0);
    Mat dst_scale;
    warpAffine(src, dst_scale, M_scale, Size(src.cols * 2, src.rows * 2));

    imshow("Moved", dst_move);
    imshow("Scaled x2", dst_scale);
    waitKey();
}

// [affine_scale] 보간법 비교 (Nearest vs Linear vs Cubic)
void affine_scale() {
    Mat src = imread("rose.bmp");
    if (src.empty()) return;

    Mat dst1, dst2, dst3;
    // 4배 확대 시 보간법 차이 확인
    resize(src, dst1, Size(), 4, 4, INTER_NEAREST); // 계단 현상 발생
    resize(src, dst2, Size(), 4, 4, INTER_LINEAR);  // 일반적
    resize(src, dst3, Size(), 4, 4, INTER_CUBIC);   // 고화질 부드러움

    imshow("Nearest", dst1(Rect(400, 400, 400, 400)));
    imshow("Linear", dst2(Rect(400, 400, 400, 400)));
    imshow("Cubic", dst3(Rect(400, 400, 400, 400)));
    waitKey();
}

// [show38] 영상의 회전 (getRotationMatrix2D)
void show38() {
    Mat src = imread("tekapo.bmp");
    if (src.empty()) return;

    Point2f center(src.cols / 2.0f, src.rows / 2.0f);
    Mat M = getRotationMatrix2D(center, 20.0, 1.0); // 중심기준 20도 회전
    
    Mat dst;
    warpAffine(src, dst, M, Size());

    imshow("Rotated 20 deg", dst);
    waitKey();
}

// [show39] 대칭 변환 (Flip)
void show39() {
    Mat src = imread("eastsea.bmp");
    if (src.empty()) return;

    Mat dst1, dst2, dst3;
    flip(src, dst1, 1);  // 좌우 대칭
    flip(src, dst2, 0);  // 상하 대칭
    flip(src, dst3, -1); // 상하좌우(원점) 대칭

    imshow("Original", src);
    imshow("Flip LR", dst1);
    imshow("Flip UD", dst2);
    imshow("Flip Both", dst3);
    waitKey();
}

// [show40] 마우스 콜백을 이용한 투영 변환 (Perspective)
Point2f srcQuad[4], dstQuad[4];
int cnt = 0;
Mat src_pers;

void on_mouse_pers(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_LBUTTONDOWN) {
        if (cnt < 4) {
            srcQuad[cnt++] = Point2f(x, y);
            circle(src_pers, Point(x, y), 5, Scalar(0, 0, 255), -1);
            imshow("Perspective Click", src_pers);
        }
        if (cnt == 4) {
            int w = 200, h = 300;
            dstQuad[0] = Point2f(0, 0);
            dstQuad[1] = Point2f(w - 1, 0);
            dstQuad[2] = Point2f(w - 1, h - 1);
            dstQuad[3] = Point2f(0, h - 1);

            Mat M = getPerspectiveTransform(srcQuad, dstQuad);
            Mat dst;
            warpPerspective(src_pers, dst, M, Size(w, h));
            imshow("Result Perspective", dst);
        }
    }
}

void show40() {
    src_pers = imread("card.bmp");
    if (src_pers.empty()) return;
    cnt = 0; // 카운트 초기화

    namedWindow("Perspective Click");
    setMouseCallback("Perspective Click", on_mouse_pers);
    imshow("Perspective Click", src_pers);
    waitKey();
}

// --- 메인 함수 ---
int main() {
    int choice;
    while (true) {
        cout << "\n****************************************" << endl;
        cout << "  [Day 05] 기하학적 변환 실습" << endl;
        cout << "  33.아핀변환  34.이동/확대  35.보간법비교" << endl;
        cout << "  38.회전      39.대칭변환   40.투영변환(카드)" << endl;
        cout << "  0.종료" << endl;
        cout << "****************************************" << endl;
        cout << "실습 번호 입력: ";

        if (!(cin >> choice)) break;
        if (choice == 0) break;

        switch (choice) {
            case 33: show33(); break;
            case 34: show34_36(); break;
            case 35: affine_scale(); break;
            case 38: show38(); break;
            case 39: show39(); break;
            case 40: show40(); break;
            default: cout << "목록의 번호를 선택하세요." << endl;
        }
        destroyAllWindows();
    }
    return 0;
}
