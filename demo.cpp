// Tencent is pleased to support the open source community by making ncnn available.
//
// Copyright (C) 2017 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include <stdio.h>
//#include <algorithm>
#include <vector>
//#include <opencv2/opencv.hpp>
#include <functional>
#include <time.h>

#include "mobilenet_ssd_ncnn.h"
#include "tools.h"


using namespace std;
using namespace cv;

int main(int argc, char** argv)
{

	std::string path = std::string(argv[1]);
	std::vector<std::string> files_name;
	int files_number;
	read_files(path + "*.jpg", files_name, &files_number);

	syshen_DetectionHandle handle;

	syshen_CreateDetectEngine(&handle);

	for (std::vector<std::string>::iterator it = files_name.begin(); it != files_name.end(); it++)
	{
		cv::Mat img = cv::imread(path + *it);
		vector<vector<float> > detections;
		double start = clock();
		syshen_DetectFace(handle, img, detections);
		double end = clock();
		for (vector<vector<float> >::iterator bbox = detections.begin(); bbox!= detections.end(); bbox++)
		{
			vector<float> b = *bbox;
			if (b[1] < 0.3) {
				continue;
			}
			int x = static_cast<int>(b[2] * img.cols);
			int y = static_cast<int>(b[3] * img.rows);
			int w = static_cast<int>(b[4] * img.cols - x);
			int h = static_cast<int>(b[5] * img.rows - y);
			cv::rectangle(img, cv::Rect(x, y, w, h), cv::Scalar(0, 0, 255), 2, 2);
			std::string conf;
			numbertostring(b[1], conf);
			drawTextImg(img, conf, cv::Point(x, y), cv::Scalar(0, 0, 255), 1, 2);
		}
		std::cout << "time consume is: " << end - start << " ms" << std::endl;
		cv::imshow("img", img);
		cv::waitKey(0);
	}

	syshen_ReleaseDetectEngine(&handle);

	system("pause");
	return 0;
}
