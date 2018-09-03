
#ifndef __FACEVISA_COLOR_TOOL_HRADER__
#define __FACEVISA_COLOR_TOOL_HRADER__

#include <io.h>
#include <vector>
#include <string>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

int read_files(const std::string &path, std::vector<std::string> &files_name, int *files_number);

void readTxt(std::string &file, std::vector<std::string> &img_name, std::vector<std::string> &label);

void ftostring(float number, std::string &output);

void drawTextImg(cv::Mat &img, std::string text, cv::Point &origin, cv::Scalar &scalar, int thickness, int lineType);

template <typename Dtype>
void numbertostring(Dtype number, std::string &output);

template <typename Dtype>
std::string numbertostring(Dtype number);

#endif