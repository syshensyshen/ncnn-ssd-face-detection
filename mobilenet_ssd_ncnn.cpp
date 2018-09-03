#include <string>
#include <vector>
#include "net.h"

#include "mobilenet_ssd_ncnn.h"

using namespace std;
using ncnn::Net;
using ncnn::Mat;
using ncnn::Extractor;

//#define SSD_FACE_DEBUG

int syshen_CreateDetectEngine(syshen_DetectionHandle *handle)
{
	const char* protostr = "./templates/ncnn.proto";
	const char* modelstr = "./templates/ncnn.bin";
	Net *syshen_ssddetection = new (std::nothrow) Net();
	if (NULL == syshen_ssddetection)
	{
		return 0;
	}
	syshen_ssddetection->load_param(protostr);
	syshen_ssddetection->load_model(modelstr);

	*handle = syshen_ssddetection;

	return 0;
}

int syshen_DetectFace(syshen_DetectionHandle handle, const cv::Mat &img, std::vector<std::vector<float> > &detections)
{
	Net *syshen_ssddetection = (Net *)handle;

	float mean_vals[3] = { 104.0f, 117.0f, 123.0f };

	Mat in = Mat::from_pixels_resize(img.data, ncnn::Mat::PIXEL_BGR, img.cols, img.rows, 224, 224);

	in.substract_mean_normalize(mean_vals, 0);

	Mat out;

	Extractor ex = syshen_ssddetection->create_extractor();

	ex.set_light_mode(true);

	ex.input("data", in);

	ex.extract("detection_out", out);

// 	for (int i = 0; i < 1; i++)
// 	{
// 		Extractor ex = syshen_ssddetection->create_extractor();
// 
// 		ex.set_light_mode(true);
// 
// 		//ex.set_num_threads(4);
// 
// 		ex.input("data", in);
// 
// 		ex.extract("detection_out", out);
// 
// 		//ex.extract("conv6/dw_conv6/dw/relu", out);    
// 
// 	}

	//vector<vector<float> > detections;

#ifdef SSD_FACE_DEBUG
	printf("%d %d %d\n", out.w, out.h, out.c);
#endif

	for (int ih = 0; ih < out.h; ih++)
	{
		vector<float> detection;
		for (int iw = 0; iw < out.w; iw++)
		{
#ifdef SSD_FACE_DEBUG
			printf("%f ", out[iw + ih*out.w]);
#endif // SSD_FACE_DEBUG
			detection.push_back(out[iw + ih*out.w]);
		}
		detections.push_back(detection);
#ifdef SSD_FACE_DEBUG
		printf("\n");
#endif // SSD_FACE_DEBUG
		
	}

	return 0;
}

int syshen_ReleaseDetectEngine(syshen_DetectionHandle *handle)
{
	if (NULL == handle || NULL == *handle)
	{
		return 0;
	}

	Net *ssdDetect = (Net *)(*handle);

	delete ssdDetect;

	*handle = NULL;

	return 0;
}