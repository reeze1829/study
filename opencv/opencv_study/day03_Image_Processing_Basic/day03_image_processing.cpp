#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// --- 3일차: 영상 처리 기초 (밝기, 대비, 연산) 실습 함수 정의 ---

// [show20] 영상의 밝기 조절 (직접 연산 vs 함수)
void show20() {
	Mat src = imread("lenna.png", IMREAD_GRAYSCALE);
	if (src.empty()) return;

	// 1. 단순 더하기 (255가 넘으면 다시 0부터 시작하는 문제 발생 가능)
	Mat dst1 = src + 100; 

	// 2. saturate_cast를 이용한 안전한 밝기 조절
	Mat dst2 = src.clone();
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			dst2.at<uchar>(i, j) = saturate_cast<uchar>(src.at<uchar>(i, j) + 100);
		}
	}

	imshow("Original", src);
	imshow("Brightness +100", dst2);
	waitKey();
}

// [show21] 영상의 대비(Contrast) 조절
void show21() {
	Mat src = imread("lenna.png", IMREAD_GRAYSCALE);
	if (src.empty()) return;

	// s = (1 + alpha) * i
	float alpha = 1.0f; // 대비 계수
	Mat dst = src + (src - 128) * alpha;

	imshow("Original", src);
	imshow("High Contrast", dst);
	waitKey();
}

// [show22] 히스토그램 스트레칭 (Contrast Stretching)
void show22() {
	Mat src = imread("hawkes_bay.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) return;

	double minVal, maxVal;
	minMaxLoc(src, &minVal, &maxVal);

	// (i - min) / (max - min) * 255
	Mat dst = (src - minVal) / (maxVal - minVal) * 255;

	imshow("Original (Low Contrast)", src);
	imshow("Stretched (High Contrast)", dst);
	waitKey();
}

// [show23] 히스토그램 균일화 (Histogram Equalization)
void show23() {
	Mat src = imread("hawkes_bay.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) return;

	Mat dst;
	equalizeHist(src, dst);

	imshow("Original", src);
	imshow("Equalized", dst);
	waitKey();
}

// [show24] 영상의 산술 연산 (더하기, 빼기, 차이)
void show24() {
	Mat src1 = imread("lenna.png", IMREAD_GRAYSCALE);
	Mat src2 = imread("square.bmp", IMREAD_GRAYSCALE);
	if (src1.empty() || src2.empty()) return;

	Mat dst_add, dst_sub, dst_diff, dst_abs;
	add(src1, src2, dst_add);      // 더하기
	subtract(src1, src2, dst_sub); // 빼기
	absdiff(src1, src2, dst_diff); // 차이 (절대값)

	imshow("Add", dst_add);
	imshow("Subtract", dst_sub);
	imshow("AbsDiff", dst_diff);
	waitKey();
}

// [show25] 영상의 논리 연산 (AND, OR, XOR, NOT)
void show25() {
	Mat src1 = imread("lenna.png", IMREAD_GRAYSCALE);
	Mat src2 = imread("square.bmp", IMREAD_GRAYSCALE);
	if (src1.empty() || src2.empty()) return;

	Mat dst_and, dst_or;
	bitwise_and(src1, src2, dst_and);
	bitwise_or(src1, src2, dst_or);

	imshow("AND", dst_and);
	imshow("OR", dst_or);
	waitKey();
}

// --- 메인 함수: 메뉴 선택기 ---
int main() {
	int choice;
	while (true) {
		cout << "\n****************************************" << endl;
		cout << "  [Day 03] 영상 처리 기초 실습" << endl;
		cout << "  20.밝기조절  21.대비조절  22.스트레칭  23.균일화" << endl;
		cout << "  24.산술연산  25.논리연산" << endl;
		cout << "  0.종료" << endl;
		cout << "****************************************" << endl;
		cout << "실습 번호 입력: ";

		if (!(cin >> choice)) break;
		if (choice == 0) break;

		switch (choice) {
		case 20: show20(); break;
		case 21: show21(); break;
		case 22: show22(); break;
		case 23: show23(); break;
		case 24: show24(); break;
		case 25: show25(); break;
		default: cout << "목록에 있는 번호를 선택해주세요." << endl;
		}
		destroyAllWindows();
	}
	return 0;
}
