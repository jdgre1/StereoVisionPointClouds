#pragma once
#ifndef STEREO_VISION_PCD__H__
#define STEREO_VISION_PCD__H__

#include <pch.h>

#define HAS_CUDA 1

class StereoVisionPCD {

public:

	struct StereoVisionParams {

		
		
	};

	// Constructor
	StereoVisionPCD();

	// Rule of 3
	// 1. Destructor
	~StereoVisionPCD();

	// 2. Copy assignment operator
	StereoVisionPCD& operator=(StereoVisionPCD&) = default;

	// 3. Copy constructor  //FaceLibrary(const FaceLibrary&) = delete; // (if to disable copy constructor) 
	                     
	

private:
	std::string m_random_crap = "hello";
	StereoVisionParams m_stereoVisParams;
	
};


#endif