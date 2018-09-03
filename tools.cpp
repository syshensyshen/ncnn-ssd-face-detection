
#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "tools.h"



int read_files(const std::string &path, std::vector<std::string> &files_name, int *files_number)
{
	//文件存储信息结构体 
	struct _finddata_t fileinfo;
	//保存文件句柄 
	long fHandle;
	//文件数记录器
	int i = 0;

	//std::string path = "F:/data/sample/face_angle/original/original/test/*.jpg";

	fHandle = _findfirst(path.c_str(), &fileinfo);

	if (-1L == fHandle)
	{
		std::cout << "no jpg files in " << path << std::endl;
	}
	else
	{
		do{
			i++;
			//printf("jpg name is: %s, jpg memory size is% d\n", fileinfo.name, fileinfo.size);
			files_name.push_back(fileinfo.name);
		} while (_findnext(fHandle, &fileinfo) == 0);
	}

	_findclose(fHandle);

	//printf("files number：%d\n", i);

	*files_number = i;
	return 0;
}

void readTxt(std::string &file, std::vector<std::string> &img_name, std::vector<std::string> &label)
{
	std::ifstream infile;
	infile.open(file.data());   //将文件流对象与文件连接起来 
	assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 

	std::string s;
	while (getline(infile, s))
	{
		//std::cout << s[s.length() -1] << std::endl;
		img_name.push_back(s.substr(0, s.length() - 2));
		label.push_back(s.substr(s.length() - 1, 1));
	}
	infile.close();             //关闭文件输入流 
}

template <typename Dtype>
void numbertostring(Dtype number, std::string &output)
{
	std::ostringstream buffer;
	buffer << number;
	output = buffer.str();
}

template
void numbertostring(float number, std::string &output);
template
void numbertostring(double number, std::string &output);
template
void numbertostring(int number, std::string &output);

template <typename Dtype>
std::string numbertostring(Dtype number)
{
	std::string output;
	std::ostringstream buffer;
	buffer << number;
	output = buffer.str();
	return output;
}
template
std::string numbertostring(int number);
template
std::string numbertostring(float number);
template
std::string numbertostring(double number);

void ftostring(float number, std::string &output)
{
	std::ostringstream buffer;
	buffer << number;
	output = buffer.str();	
}

void drawTextImg(cv::Mat &img, std::string text, cv::Point &origin, cv::Scalar &scalar, int thickness, int lineType)
{
	int font_face = cv::FONT_HERSHEY_COMPLEX;
	double font_scale = 2;
	//获取文本框的长宽  
	int baseline;
	cv::Size text_size = cv::getTextSize(text, font_face, font_scale, thickness, &baseline);
	cv::putText(img, text, origin, font_face, font_scale, scalar, thickness, 8, 0);
}