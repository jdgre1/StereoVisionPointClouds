#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace cv;
using namespace std;


void calibrate_camera(cv::Mat& intrinsicsMatrix, cv::Mat& distCoeffs, cv::Mat& R, cv::Mat& T);
void StereoVisionRun();
void undistort_live_images(cv::Mat& intrinsicsMatrix, cv::Mat& distCoeffs, cv::Mat& R, cv::Mat& T) {
    
    
    //Mat frame0, frame1;
    //--- INITIALIZE VIDEOCAPTURE objects:

    // = VideoCapture(cv::CAP_DSHOW);
    VideoCapture cap1; // = VideoCapture(cv::CAP_DSHOW);

    // open the default camera using default API
    // cap.open(0);
    // OR advance usage: select any API backend

    // Detect device 0:
    int deviceID_0 = 0;             // 0 = open default camera
    int apiID_0 = cv::CAP_ANY;      // 0 = autodetect default API

    // Detect device 1:
    int deviceID_1 = 1;             // 1 = open other camera
    int apiID_1 = cv::CAP_ANY;      // 0 = autodetect default API

    // open selected camera using selected API
    cap1.open(deviceID_1, apiID_1);
    //cap1.open(deviceID_1, apiID_1);

    // check if we succeeded
    if (!cap1.isOpened()) {
        cerr << "ERROR! Unable to open camera1\n";
        return;
    }

    //--- GRAB AND WRITE LOOP
    std::cout << "Start grabbing" << endl
        << "Press any key to terminate" << endl;

    bool grab_calibration_photos = true;
    if (grab_calibration_photos) {
        std::cout << "Start grabbing" << endl
            << "Press any key to terminate" << endl;

        // wait for a new frame from camera and store it into 'frame'

        // Number of frames to capture
        int num_frames = 100;

        // Start and end times
        time_t curr_time, prev;

        // Variable for storing video frames
        Mat frame;
        std::cout << "Capturing " << num_frames << " frames" << endl;

        // Start time
        time(&curr_time);
        time(&prev);

        // Grab a few frames
        int frame_count = 0;
        // Set 1 frame every 5 seconds as the frame rate - (enough time to change position of chessboard)
        for(size_t i = 0; i < num_frames; ++i) {
            //cap0.read(frame0);
            //cap1.read(frame1);

            Mat frame1;
            // Capture frame-by-fra´me
            cap1 >> frame1;

            Mat imageUndistorted;

            undistort(frame1, imageUndistorted, intrinsicsMatrix, distCoeffs);
            cv::Point a, b;
            a.x = 0;
            a.y = int(frame1.rows / 3);
            b.x = frame1.cols;
            b.y = int(frame1.rows / 3);
            cv::line(frame1, a, b, Scalar(0, 255, 0), 1, LINE_AA);
            cv::line(imageUndistorted, a, b, Scalar(0, 255, 0), 1, LINE_AA);

            a.x = 0;
            a.y = int(2 * frame1.rows / 3);
            b.x = frame1.cols;
            b.y = int(2 * frame1.rows / 3);
            cv::line(frame1, a, b, Scalar(0, 255, 0), 1, LINE_AA);
            cv::line(imageUndistorted, a, b, Scalar(0, 255, 0), 1, LINE_AA);

            a.x = 0;
            a.y = int(4 * frame1.rows / 5);
            b.x = frame1.cols;
            b.y = int(4 * frame1.rows / 5);
            cv::line(frame1, a, b, Scalar(0, 255, 0), 1, LINE_AA);
            cv::line(imageUndistorted, a, b, Scalar(0, 255, 0), 1, LINE_AA);

            a.x = 0;
            a.y = int(1 * frame1.rows / 5);
            b.x = frame1.cols;
            b.y = int(1 * frame1.rows / 5);
            cv::line(frame1, a, b, Scalar(0, 255, 0), 1, LINE_AA);
            cv::line(imageUndistorted, a, b, Scalar(0, 255, 0), 1, LINE_AA);

            a.x = 0;
            a.y = int(frame1.rows / 2);
            b.x = frame1.cols;
            b.y = int(frame1.rows / 2);
            cv::line(frame1, a, b, Scalar(0, 255, 0), 1, LINE_AA);
            cv::line(imageUndistorted, a, b, Scalar(0, 255, 0), 1, LINE_AA);

            a.y = 0;
            a.x = int(frame1.cols / 3);
            b.y = frame1.rows;
            b.x = int(frame1.cols / 3);
            cv::line(frame1, a, b, Scalar(0, 0, 255), 1, LINE_AA);
            cv::line(imageUndistorted, a, b, Scalar(0, 0, 255), 1, LINE_AA);

            a.y = 0;
            a.x = int(2 * frame1.cols / 3);
            b.y = frame1.rows;
            b.x = int(2 * frame1.cols / 3);
            cv::line(frame1, a, b, Scalar(0, 0, 255), 1, LINE_AA);
            cv::line(imageUndistorted, a, b, Scalar(0, 0, 255), 1, LINE_AA);

            a.y = 0;
            a.x = int(frame1.cols / 2);
            b.y = frame1.rows;
            b.x = int(frame1.cols / 2);
            cv::line(frame1, a, b, Scalar(0, 0, 255), 1, LINE_AA);
            cv::line(imageUndistorted, a, b, Scalar(0, 0, 255), 1, LINE_AA);

            a.y = 0;
            a.x = int(frame1.cols / 5);
            b.y = frame1.rows;
            b.x = int(frame1.cols / 5);
            cv::line(frame1, a, b, Scalar(0, 0, 255), 1, LINE_AA);
            cv::line(imageUndistorted, a, b, Scalar(0, 0, 255), 1, LINE_AA);

            a.y = 0;
            a.x = int(4 * frame1.cols / 5);
            b.y = frame1.rows;
            b.x = int(4 * frame1.cols / 5);
            cv::line(frame1, a, b, Scalar(0, 0, 255), 1, LINE_AA);
            cv::line(imageUndistorted, a, b, Scalar(0, 0, 255), 1, LINE_AA);
            imshow("Distorted", frame1);
            imshow("Undistorted", imageUndistorted);
            cv::waitKey();
            ++frame_count;
        }
    }
    
}
void printCWD(char* argv[]);
int main(int argc, char* argv[])
{
    bool calibrate_camera_bool = true;
    if (calibrate_camera_bool) {
        cv::Mat intrinsicsMatrix, distCoeffs, R, T;
        calibrate_camera(intrinsicsMatrix, distCoeffs, R, T);
        undistort_live_images(intrinsicsMatrix, distCoeffs, R, T);
    }
        
    bool check_frame_rate = false;
    if (check_frame_rate) {
        // Start default camera

        VideoCapture cap0;

        // Detect device 0:
        int deviceID_0 = 0;             // 0 = open default camera
        int apiID_0 = cv::CAP_ANY;      // 0 = autodetect default API

        // open selected camera using selected API
        cap0.open(deviceID_0, apiID_0);

        // check if we succeeded
        if (!cap0.isOpened()) {
            cerr << "ERROR! Unable to open camera0\n";
            return -1;
        }

        // With webcam get(CV_CAP_PROP_FPS) does not work.
        // Let's see for ourselves.
        // double fps = video.get(CV_CAP_PROP_FPS);
        // If you do not care about backward compatibility
        // You can use the following instead for OpenCV 3
        double fps = cap0.get(CAP_PROP_FPS);
        cout << "Frames per second using video.get(CAP_PROP_FPS) : " << fps << endl;

        // Number of frames to capture
        int num_frames = 1200;

        // Start and end times
        time_t start, end;

        // Variable for storing video frames
        Mat frame;
        cout << "Capturing " << num_frames << " frames" << endl;

        // Start time
        time(&start);

        // Grab a few frames
        for (int i = 0; i < num_frames; i++) {
            cap0 >> frame;
        }

        // End Time
        time(&end);

        // Time elapsed
        double seconds = difftime(end, start);
        cout << "Time taken : " << seconds << " seconds" << endl;

        // Calculate frames per second
        fps = num_frames / seconds;
        cout << "Estimated frames per second : " << fps << endl;

        // Release video
        cap0.release();
    }

    bool record_and_save = false;
    if (record_and_save) {
        //Mat frame0, frame1;
        //--- INITIALIZE VIDEOCAPTURE objects:

        VideoCapture cap0; // = VideoCapture(cv::CAP_DSHOW);
        VideoCapture cap1; // = VideoCapture(cv::CAP_DSHOW);
        std::vector<cv::Mat> frames_0, frames_1;
        // open the default camera using default API
        // cap.open(0);
        // OR advance usage: select any API backend

        // Detect device 0:
        int deviceID_0 = 0;             // 0 = open default camera
        int apiID_0 = cv::CAP_ANY;      // 0 = autodetect default API

        // Detect device 1:
        int deviceID_1 = 1;             // 1 = open other camera
        int apiID_1 = cv::CAP_ANY;      // 0 = autodetect default API

        // open selected camera using selected API
        cap0.open(deviceID_0, apiID_0);
        cap1.open(deviceID_1, apiID_1);

        // check if we succeeded
        if (!cap0.isOpened()) {
            cerr << "ERROR! Unable to open camera0\n";
            return -1;
        }

        if (!cap1.isOpened()) {
            cerr << "ERROR! Unable to open camera1\n";
            return -1;
        }

        //--- GRAB AND WRITE LOOP
        std::cout << "Start grabbing" << endl
            << "Press any key to terminate" << endl;
        
        bool grab_calibration_photos = true;
        if (grab_calibration_photos) {
            std::cout << "Start grabbing" << endl
                << "Press any key to terminate" << endl;

            // wait for a new frame from camera and store it into 'frame'

            // Number of frames to capture
            int num_frames = 100;

            // Start and end times
            time_t curr_time, prev;

            // Variable for storing video frames
            Mat frame;
            std::cout << "Capturing " << num_frames << " frames" << endl;

            // Start time
            time(&curr_time);
            time(&prev);

            // Grab a few frames
            int frame_count = 0;
            // Set 1 frame every 5 seconds as the frame rate - (enough time to change position of chessboard)
            float frame_rate = 0.5;
            while (frame_count < num_frames) {
                //cap0.read(frame0);
                //cap1.read(frame1);
           
                Mat frame0, frame1;
                // Capture frame-by-fra´me
                cap0 >> frame0;
                cap1 >> frame1;

                bool frame_error = false;
                // check if we succeeded
                if (frame0.empty()) {
                    cerr << "ERROR! blank frame of cam0 grabbed\n";
                    frame_error = true;
                }

                // check if we succeeded
                if (frame1.empty()) {
                    cerr << "ERROR! blank frame of cam1 grabbed\n";
                    frame_error = true;
                }

                if (!frame_error) {
                    time(&curr_time);
                    if (curr_time - prev >= 1. / frame_rate) {
                        ++frame_count;
                        prev = curr_time;
                        std::string frame_num_str = std::to_string(frame_count);
                        cv::imshow("frame0", frame0);
                        cv::imshow("frame1", frame1);
                        frames_0.push_back(frame0);
                        frames_1.push_back(frame1);
                        cv::waitKey(1000);
                        std::cout << "frame_count: " << frame_count << std::endl;
                    }
                }
            }

            std::string filename_frames = "../../data/frames_";
            for (size_t i = 0; i < frames_0.size(); ++i) {

                //write frames to file:
                cv::Mat temp = frames_0[i];
                cv::imwrite(filename_frames + "0_" + std::to_string(i) + ".png", temp);
                temp = frames_1[i];
                cv::imwrite(filename_frames + "1_" + std::to_string(i) + ".png", temp);
            }


        }
       
        bool grab_indefinitely = false;

        if (grab_indefinitely) {

            for (;;)
            {
                // wait for a new frame from camera and store it into 'frame'
                Mat frame0, frame1;
                // Capture frame-by-frame
                cap0 >> frame0;
                cap1 >> frame1;

                // check if we succeeded
                if (frame0.empty()) {
                    cerr << "ERROR! blank frame grabbed\n";
                    break;
                }

                // check if we succeeded
                if (frame1.empty()) {
                    cerr << "ERROR! blank frame grabbed\n";
                    break;
                }

                // show live and wait for a key with timeout long enough to show images
                cv::imshow("Live0", frame0);
                cv::imshow("Live1", frame1);
                //frames_0.push_back(frame0);
                if (cv::waitKey(5) >= 0)
                    break;

               
                //frames_1.push_back(frame1);
                //if (waitKey(5) >= 0)
                //    break;
            }
        }

        // the camera will be deinitialized automatically in VideoCapture destructor
        return 0;

    }
    return 0;
}

void test_frame_recording() {

    /*
    ***********************************************************************************
    SEE: https://stackoverflow.com/questions/52068277/change-frame-rate-in-opencv-3-4-2
    Setting a frame rate doesn't always work like you expect. It depends on two things:

        What your camera is capable of outputting.
        Whether the current capture backend you're using supports changing frame rates.
    ***********************************************************************************
    Be careful with this strategy. Don't do this:
    while capturing:
        res, image = cap.read()
        time.sleep(1)
    ***********************************************************************************
    you need to make sure you're continually purging the camera's frame buffer otherwise you will start to see lag in your videos. 
    Something like the following should work:

    frame_rate = 10
    prev = 0

    while capturing:

        time_elapsed = time.time() - prev
        res, image = cap.read()

        if time_elapsed > 1./frame_rate:
            prev = time.time()

            # Do something with your image here.
            process_image()
    ***********************************************************************************
    */
}

void printCWD(char* argv[]) {
    char the_path[256];

    getcwd(the_path, 255);
    strcat(the_path, "/");
    strcat(the_path, argv[0]);

    printf("%s\n", the_path);

}

void calibrate_camera(cv::Mat& intrinsicsMatrix, cv::Mat& distCoeffs, cv::Mat& R, cv::Mat& T) {

    // Defining the dimensions of checkerboard
    int CHECKERBOARD[2]{ 7,10 };
    // Creating vector to store vectors of 3D points for each checkerboard image

    std::vector<std::vector<cv::Point3f> > objpoints;

    // Creating vector to store vectors of 2D points for each checkerboard image
    std::vector<std::vector<cv::Point2f> > imgpoints;

    //std::string filename_frames = "../../data/frames_";

    std::vector<cv::Point3f> objp;
    for (int i{ 0 }; i < CHECKERBOARD[1]; i++)
    {
        for (int j{ 0 }; j < CHECKERBOARD[0]; j++)
            objp.push_back(cv::Point3f(j, i, 0));
    }

    // Extracting path of individual image stored in a given directory
    std::vector<cv::String> images;

    // Path of the folder containing checkerboard images
    std::string path = "../../data/frame_1/*.png";
    cv::glob(path, images);
    cv::Mat frame, gray;

    // vector to store the pixel coordinates of detected checker board corners
    std::vector<cv::Point2f> corner_pts;
    bool success;

    // Looping over all the images in the directory
    for (int i{ 0 }; i < images.size(); i++) {
        frame = cv::imread(images[i]);
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
   
    // Finding checker board corners

        // If desired number of corners are found in the image then success = true 
        success = cv::findChessboardCorners(gray, cv::Size(CHECKERBOARD[0], CHECKERBOARD[1]), corner_pts, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FAST_CHECK | CALIB_CB_NORMALIZE_IMAGE);
        std::cout << "success? " << success << std::endl;

        /*

         * If desired number of corner are detected,

         * we refine the pixel coordinates and display

         * them on the images of checker board

        */
        if (success)

        {
            std::cout << "success!!!! " << success << std::endl;
            cv::TermCriteria criteria(cv::TermCriteria::MAX_ITER +
                cv::TermCriteria::EPS, 30, 0.001);

            // refining pixel coordinates for given 2d points.
            cv::cornerSubPix(gray, corner_pts, cv::Size(11, 11), cv::Size(-1, -1), criteria);
            // Displaying the detected corner points on the checker board

            cv::drawChessboardCorners(frame, cv::Size(CHECKERBOARD[0], CHECKERBOARD[1]), corner_pts, success);

            objpoints.push_back(objp);
            imgpoints.push_back(corner_pts);

        }

        cv::imshow("Image", frame);
        cv::waitKey(200);
    }

    cv::destroyAllWindows();

    //cv::Mat intrinsicsMatrix, distCoeffs, R, T;




    /*

     * Performing camera calibration by

     * passing the value of known 3D points (objpoints)

     * and corresponding pixel coordinates of the

     * detected corners (imgpoints)

    */

    cv::calibrateCamera(objpoints, imgpoints, cv::Size(gray.rows, gray.cols), intrinsicsMatrix, distCoeffs, R, T);

    std::cout << "\n\intrinsicsMatrix : " << intrinsicsMatrix << std::endl;

    std::cout << "\n\ndistCoeffs : " << distCoeffs << std::endl;

    std::cout << "\n\nRotation vector : " << R << std::endl;

    std::cout << "\n\nTranslation vector : " << T << std::endl;

    std::cout << "objpoints.size() = " << objpoints.size() << std::endl;

    return;

    
}