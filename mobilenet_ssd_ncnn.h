#ifndef _FACEVISA_MOBILENET_SSD_NCNN_FACE_DETECTIVE_HEADER_
#define _FACEVISA_MOBILENET_SSD_NCNN_FACE_DETECTIVE_HEADER_

#include <stdio.h>
#include <opencv2/core/core.hpp>

typedef void* syshen_DetectionHandle;

int syshen_CreateDetectEngine(syshen_DetectionHandle *handle);

int syshen_DetectFace(syshen_DetectionHandle handle, const cv::Mat &img, std::vector<std::vector<float> > &detections);

int syshen_ReleaseDetectEngine(syshen_DetectionHandle *handle);

#endif
