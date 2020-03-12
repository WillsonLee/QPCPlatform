//#include "stdafx.h"
#include "Utils.h"
#include <io.h>
#include <direct.h>
#include <fstream>
#include <sstream>
#include <exception>

std::string lyxutils::getTimeString()
{
	time_t timep;
	time(&timep);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	return tmp;
}

bool lyxutils::createFolder(const std::string folderPath)
{
	if (_access(folderPath.c_str(), 0) == -1) {
		if (_mkdir(folderPath.c_str()) == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	return true;
}

std::ofstream * lyxutils::openLogFile(std::string fileName)
{
	std::ofstream *log = new std::ofstream();
	log->open(fileName, std::ios::app);
	return log;
}

void lyxutils::writeLog(std::ofstream & log, std::string message, std::string end)
{
	if (log.is_open()) {
		log << lyxutils::getTimeString() << "\t" << message << end;
	}
}

void lyxutils::consoleProgressBar(int value, std::string delimiterL, std::string increment, std::string delimiterR, std::string status)
{
	if (value == 0) {
		std::cout << std::endl;
	}
	std::cout << "\r";
	std::cout << delimiterL;
	for (int i = 0; i < value; ++i) {
		std::cout << increment;
	}
	for (int i = value; i < 100; ++i) {
		std::cout << " ";
	}
	std::cout << delimiterR;
	std::cout << value << "% ";
	if (status == "" || value == 100) {
		std::cout << "completed";
	}
	else {
		std::cout << status;
	}
	if (value == 100) {
		std::cout << std::endl;
	}
}

std::vector<std::string> lyxutils::str_utils::split(const std::string & str, const std::string & delimiter)
{
	std::vector<std::string> result = std::vector<std::string>();
	if (str == "") return result;
	char *chs = new char[str.length() + 1];
	std::strcpy(chs, str.c_str());
	char *d = new char[delimiter.length() + 1];
	std::strcpy(d, delimiter.c_str());
	char *p = std::strtok(chs, d);
	while (p) {
		std::string s = p;
		result.push_back(s);
		p = std::strtok(NULL, d);
	}
	delete chs, d;
	return result;
}

std::vector<std::string> lyxutils::str_utils::split_with_string(const std::string & str, const std::string & delString)
{
	std::vector<std::string> result = std::vector<std::string>();
	if (str == "") return result;
	size_t start = 0;
	size_t end = str.find(delString, start);
	while (end > start&&end < str.length()) {
		result.push_back(str.substr(start, end - start));
		start = end + delString.length();
		end = str.find(delString, start);
	}
	if (start < str.length()) {
		result.push_back(str.substr(start, str.length() - start));
	}
	return result;
}

std::string lyxutils::str_utils::lower(const std::string & str)
{
	std::string res = str;
	std::transform(res.begin(), res.end(), res.begin(), ::tolower);
	return res;
}

std::string lyxutils::str_utils::upper(const std::string & str)
{
	std::string res = str;
	std::transform(res.begin(), res.end(), res.begin(), ::toupper);
	return res;
}

std::string lyxutils::str_utils::replace(const std::string & str, const std::string & oldStr, const std::string & newStr)
{
	std::string res = str;
	size_t pos = res.find(oldStr, 0);
	while (pos < str.length()) {
		res.replace(pos, oldStr.length(), newStr);
		pos = res.find(oldStr, pos + oldStr.length());
	}
	return res;
}

bool lyxutils::io::read_csv(const std::string &fileName, std::vector<std::vector<float> > &table, const std::string &sep, std::string &report,
	int fields, bool read_header, std::vector<std::string> &headers, int numberOfRedirect, void(*directFunc)(const std::vector<float>&))
{
	if (!lyxutils::io::fileExists(fileName))
		throw std::exception("�ļ�������!");
	std::fstream inFile(fileName);
	std::stringstream ssReport;
	ssReport << lyxutils::getTimeString() << ":���ļ� " << fileName << std::endl;
	ssReport << "�ļ�����:" << std::endl;
	std::string line;
	bool first_time = true;
	int count = 0;
	int error_count = 0;
	while (std::getline(inFile, line)) {
		if (line == "")continue;
		count++;
		std::vector<std::string> field_values = lyxutils::str_utils::split(line, sep);
		std::for_each(field_values.begin(), field_values.end(), [](std::string &str) {str = lyxutils::str_utils::replace(str, " ", ""); });
		if (first_time) {
			first_time = false;
			fields = fields > field_values.size() ? (int)(field_values.size()) : fields;
			if (fields == -1)
				fields = field_values.size();
			ssReport << "�򿪵��ļ�����" << field_values.size() << "���ֶ�,��ȡ������ǰ" << fields << "���ֶ�" << std::endl;
			table.clear();
			for (int i = 0; i < fields - numberOfRedirect; ++i) {
				table.push_back(std::vector<float>());
			}
			if (read_header) {
				headers = field_values;
				count--;
				continue;
			}
		}
		try {
			std::vector<float> line_data = std::vector < float>(fields);
			for (int i = 0; i < fields; ++i) {
				if (i < field_values.size())
					line_data[i] = std::stof(field_values[i]);//���ַ���תΪfloat
				else {
					line_data[i] = 0;//���ʵ�ʶ�ȡ�����ֶ�������Ҫ����ֶ������������Ϊ0
					if (i == field_values.size()) {
						ssReport << "��" << count << "��������������" << fields << ",ֻ��" 
							<< field_values.size() << "�У���������Ѳ�Ϊ0" << std::endl;
					}
				}	
			}
			std::vector<float> redirectFields = std::vector<float>();
			for (int i = 0; i < fields; ++i) {
				if (i < numberOfRedirect) {
					redirectFields.push_back(line_data[i]);
				}
				else {
					table[i - numberOfRedirect].push_back(line_data[i]);
				}
			}
			if (numberOfRedirect > 0 && directFunc != NULL) {
				directFunc(redirectFields);
			}
		}
		catch (std::exception) {
			error_count++;
			ssReport << "��" << count << "�����ݳ���,�Ѻ���;��������Ϊ:";
			std::for_each(field_values.begin(), field_values.end(), [&ssReport](std::string str) {ssReport << str << " "; });
			ssReport << std::endl;
		}
	}
	if (inFile.is_open()) {
		inFile.close();
	}
	ssReport << "��ȡ�ļ�����" << count << "�зǿ�������,���д���" << error_count << "��" << std::endl;
	report = ssReport.str();
	return true;
}

bool lyxutils::io::fileExists(std::string fileName)
{
	return _access(fileName.c_str(), 0) == 0;
}

void lyxutils::colors::rgb2hsv(const std::vector<int>& rgb, std::vector<float>& hsv)
{
	int r = rgb[0];
	int g = rgb[1];
	int b = rgb[2];
	int cmax = r > g ? r : g;
	cmax = b > cmax ? b : cmax;
	int cmin = r < g ? r : g;
	cmin = b < cmin ? b : cmin;
	hsv.clear();
	for (auto i : { 0,1,2 })hsv.push_back(0);
	if (cmax != cmin)
	{
		if (cmax == r) {
			hsv[0] = 60 * (float)(g - b) / (cmax - cmin);
		}
		else if (cmax == g) {
			hsv[0] = 120 + 60 * (float)(b - r) / (cmax - cmin);
		}
		else {
			hsv[0] = 240 + 60 * (float)(r - g) / (cmax - cmin);
		}
		if (hsv[0] < 0)hsv[0] += 360;
	}
	if (cmax != 0)hsv[1] = float(cmax - cmin) / cmax;
	hsv[2] = cmax;
}

void lyxutils::colors::hsv2rgb(const std::vector<float>& hsv, std::vector<int>& rgb)
{
	float h = hsv[0];
	float s = hsv[1];
	float v = hsv[2];
	int hi = int(h / 60) % 6;
	float f = h / 60 - hi;
	float p = v*(1 - s);
	float q = v*(1 - f*s);
	float t = v*(1 - (1 - f)*s);
	rgb.clear();
	for (auto i : { 1,1,1 })rgb.push_back(0);
	switch (hi)
	{
	case 0:rgb[0] = (int)(v); rgb[1] = (int)(t); rgb[2] = (int)(p); break;
	case 1:rgb[0] = (int)(q); rgb[1] = (int)(v); rgb[2] = (int)(p); break;
	case 2:rgb[0] = (int)(p); rgb[1] = (int)(v); rgb[2] = (int)(t); break;
	case 3:rgb[0] = (int)(p); rgb[1] = (int)(q); rgb[2] = (int)(v); break;
	case 4:rgb[0] = (int)(t); rgb[1] = (int)(p); rgb[2] = (int)(v); break;
	case 5:rgb[0] = (int)(v); rgb[1] = (int)(p); rgb[2] = (int)(q); break;
	}
}
