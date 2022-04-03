#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>

using namespace std;
using namespace cv;

int main() {
    VideoCapture cap;
    cap.open("/Users/chenxuan/Downloads/test_video.mov");
    if (!cap.isOpened()) {
        cout << "could not load video data..." << endl;
        return -1;
    }
    Mat frame;
    namedWindow("tracker demo", WINDOW_AUTOSIZE);
    Ptr<Tracker> tracker = TrackerKCF::create();
    cap.read(frame);
    Rect ROI = selectROI("tracker demo", frame);
    if (ROI.width == 0 || ROI.height == 0) {
        return -1;
    }
    tracker -> init(frame, ROI);
    while (cap.read(frame)) {
        tracker -> update(frame, ROI);
        rectangle(frame, ROI,Scalar(0, 0, 255), 2, 8, 0);
        imshow("tracker demo", frame);
        char c = waitKey(20);
        if (c == 27) {
            break;
        }
    }
    cap.release();
    waitKey(0);
    return 0;
}
