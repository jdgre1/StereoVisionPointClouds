#include <pch.h> 
#include <stereo_vis_pcd.h>
#include <filesystem>

using namespace cv;
using namespace std;

namespace fs = std::filesystem;


bool getDesktopResolution(int& screenHeight, int& screenWidth);


void StereoVisionRun() {
	StereoVisionPCD sv_pcd;
}


bool getDesktopResolution(int& screenWidth, int& screenHeight) {

	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	screenWidth = desktop.right;
	screenHeight = desktop.bottom;

	return ((desktop.right > 0) & (desktop.bottom > 0)) ? true : false;
}


