#ifndef LYXUTILS_H
#define LYXUTILS_H
//说明：一些常用工具函数
//项目-属性-配置属性-C/C++ -预处理器-预处理器定义中要添加_CRT_SECURE_NO_WARNINGS,否则getTimeString函数会出现线程不安全报错
#include <string>
#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <thread>

/**\自己封装的一个工具包，包含一些工具函数
  *\为了简洁起见可以在使用的时候对其中一些名字空间重命名
  *\比如：#define ual lyxutils::algorithms, 就可以用ual作为lyxutils::algorithms的别名
  *\相当于python中的import package as alias
  *\也可以在程序开头定义新的名字空间：namespace myIO=lyxutils::io
  */
namespace lyxutils
{
	/**\brief 获取当前时间的字符串
	  *\以HH:MM:SS格式返回时间字符串
	  */
	std::string getTimeString();
	/**\brief 创建一个名为folderPath的文件夹（如果已存在则不操作）
	  *\return true如果创建成功或者文件夹已存在
	  */
	bool createFolder(const std::string folderPath);
	/**\brief 打开一个文件作为日志
	  *\param[in] fileName 打开的文件名
	  *\return 追加写模式的日志文件
	  */
	std::ofstream* openLogFile(std::string fileName);
	/**\brief 向打开的日志文件写信息
	  *\param[in] log 日志文件
	  *\param[in] message 要写的信息
	  *\param[in] end 信息末尾的首尾字符（默认为"\n"，即自动回车换行）
	  */
	void writeLog(std::ofstream &log, std::string message, std::string end = "\n");
	/**\brief 给函数f计时
	  *\param[in] f 待计时的函数
	  *\note: 时间单位是毫秒，待计时的函数必须没有参数，如果有，可以按照以下方式调用：
	  *\比如函数f的签名是：int f(params)，其中params是参数列表，可对其如下计时
	  *\time=timeIt([&result,params](){result=f(params);});
	  */
	template<class Func>
	double timeIt(Func f)
	{
		double start, stop, duration;
		start = clock();
		f();
		stop = clock();
		duration = stop - start;
		return duration;
	}
	/**\brief 向控制台打印进度条
	  *\param[in] value 当前进度值(0~100)
	  *\param[in] delimiterL 进度条的左分隔符
	  *\param[in] increment 进度条的增量符号
	  *\param[in] delimiterR 右分隔符
	  *\param[in] status可以指明每一个输出时候的状态（比如"正在处理"、"正在读取"之类的）
	  *\note 调用参数value为0时会自动换行，为100时会自动打印进度结束并换行；中间其他进度不会换行
	  *\note 如果循环次数太多,可以在整百分比次数输出状态，如：
	  *\for(int i=0;i<total;++i){
	  *\	if(i%(total/100)==0)lyxutils::consoleProgressBar(i*100/total);
	  *\	//执行的操作
	  *\}
	  */
	void consoleProgressBar(int value, std::string delimiterL = "[", std::string increment = ">", std::string delimiterR = "]", std::string status = "");
	/**\brief 封装了一些字符串操作
	  */
	namespace str_utils
	{
		/**\brief 以给定的分隔符分割字符串
		  *\param[in] str 被分割的字符串
		  *\param[in] delimiter 分隔符(只能是单个字符的字符串，如果是多字符字符串，则每一个字符都可以作为分隔符)
		  */
		std::vector<std::string> split(const std::string &str, const std::string &delimiter);
		/**\brief 以字符串分割字符串
		  */
		std::vector<std::string> split_with_string(const std::string &str, const std::string &delString);
		std::string lower(const std::string &str);
		std::string upper(const std::string &str);
		/**\brief 以old代替new字符串
		  */
		std::string replace(const std::string &str, const std::string &oldStr, const std::string &newStr);
	}
	/**\brief 封装了一些读写操作
	  */
	namespace io
	{
		/**\brief 读取csv文件
		  *\param[in] fileName 输入文件名
		  *\param[out] table 用于保存读取数据的二维vector,table中每一个元素都是一个vector，每个vector保存一列数据
		  *\param[in] sep 分隔各列数据的分隔符,通常是","
		  *\param[out] report 记录读取过程基本信息及错误的字符串
		  *\param[in] fields 要读取的列数(-1代表着文件中的所有列)
		  *\param[in] read_header 是否把第一行作为表头
		  *\param[out] headers 表头(如果read_header为true)
		  *\param[in] numberOfRedirect 重定向的数据列数(即不保存在table中),应该小于总读取列数fields
		  *\param[in] directFunc 重定向函数，即对重定向数据列进行处理的函数
		  *\note:directFunc的参数的维数必须和numberOfRedirect相同
		  *\the 最后一个参数directFuncs可以如下定义来重定向点云文件的前几个字段(cloud_in是全局的点云指针)，
		  *\重定向的目的也在于此
				void direct(const std::vector<float> &vec) {
					pcl::PointXYZRGB pt = pcl::PointXYZRGB();
					pt.x = vec[0];
					pt.y = vec[1];
					pt.z = vec[2];
					pt.r = (uint8_t)(vec[3]);
					pt.g = (uint8_t)(vec[4]);
					pt.b = (uint8_t)(vec[5]);
					cloud_in->points.push_back(pt);
				}
		  *\补充：如果数据后面行的列数与要读取的列数不一致，多余的列数会忽略，不足的列数会填为0
		  */
		bool read_csv(const std::string &fileName, std::vector<std::vector<float> > &table, const std::string &sep, std::string &report,
			int fields = -1, bool read_header = false, std::vector<std::string> &headers = std::vector<std::string>(),
			int numberOfRedirect = 0, void(*directFunc)(const std::vector<float>&) = NULL);
		/**\brief 写csv文件
		  */
		template<class DataType>
		void write_csv(const std::string & fileName, const std::vector<std::vector<DataType>>& table, const std::string & sep)
		{
			std::ofstream ofs(fileName);
			ofs << std::setprecision(8);
			for (int i = 0; i < table[0].size(); ++i) {
				ofs << (*table.begin())[i];
				std::for_each(table.begin() + 1, table.end(), [i, &ofs, sep](const std::vector<DataType> &vec) {ofs << sep << vec[i]; });
				ofs << std::endl;
			}
			if (ofs.is_open()) {
				ofs.close();
			}
		}
		/**\brief 把点云写入csv文件
		  *\这是专用方法, PointCloudPtr is class pcl::PointCloud<pcl::PointType>::Ptr
		  *\之所以使用模板函数是为了脱开对点云库的依赖
		  */
		template<class PointCloudPtr,class DataType>
		void pc_to_csv(const std::string fileName, PointCloudPtr pc, const std::vector<std::vector<DataType> >&table, const std::string &sep, bool with_rgb = false)
		{
			std::ofstream ofs(fileName);
			ofs << std::setprecision(8);
			if (table.size() != 0 && table[0].size() != pc->points.size())
				throw exception("table中数据行数与点云中点数不一致!");
			for (int i = 0; i < pc->points.size(); ++i) {
				ofs << pc->points[i].x << sep << pc->points[i].y << sep << pc->points[i].z;
				if (with_rgb) {
					ofs << sep << unsigned(pc->points[i].r) << sep << unsigned(pc->points[i].g) << sep << unsigned(pc->points[i].b);
				}
				std::for_each(table.begin(), table.end(), [i, &ofs, sep](const std::vector<DataType> &vec) {ofs << sep << vec[i]; });
				ofs << std::endl;
			}
			if (ofs.is_open()) {
				ofs.close();
			}
		}
		/**\brief 检查文件是否存在
		  */
		bool fileExists(std::string fileName);
		/**\brief 这个类本意是封装一些固定格式文件读写操作，比如csv文件的快速读写
		  *\但是出于垃圾c++的原因，读写操作根本没法快；
		  *\这里试图把所有行读入，然后对每一行数据解析，因为每一行解析方法都一样，所以采用多线程，但是失败
		  *\失败情况为最后总是会莫名其妙随机丢最后几行数据，完全不知道什么原因；
		  *\不要再动！不要再动！不要再动！垃圾c++发展了这么多年还是通过原始的文件流读写、解析
		  */
		class FileHelper 
		{
		public:
			static bool load_csv(const std::string fileName, std::vector<std::vector<float> > &table, const std::string sep, const float fill=0.0,int n_jobs=std::thread::hardware_concurrency()) 
			{
				if (!lyxutils::io::fileExists(fileName))
					throw std::exception("文件不存在!");
				std::fstream inFile(fileName);
				std::string line;
				std::vector<std::string> lines;
				while (std::getline(inFile, line)) {
					lines.push_back(line);
				}
				int each = ceil(lines.size() / n_jobs);
				std::vector<std::thread> ts(n_jobs);
				std::vector<std::vector<std::vector<float> > >all_data;
				for (int i = 0; i < n_jobs; ++i) {
					all_data.push_back(std::vector<std::vector<float> >());
				}
				for (int i = 0; i < n_jobs; ++i) {
					std::function<void()> func = [&lines, &all_data, each, i, sep, fill]() {
						for (int j = i*each; j < (i + 1)*each&&j < lines.size(); ++j) {
							all_data[i].push_back(std::vector<float>());
							parseLineData(lines[j], *(all_data[i].end() - 1), sep, fill);
						}
					};
					std::thread th(func);
					ts[i] = std::move(th);
				}
				table.clear();
				for (int i = 0; i < n_jobs; ++i) {
					ts[i].join();
					for (int j = 0; j < all_data[i].size(); ++j) {
						if (all_data[i][j].size() != 0) {
							table.push_back(all_data[i][j]);
						}
					}
				}
			}
		private:
			static void parseLineData(const std::string line, std::vector<float> &output, const std::string sep, float fill)
			{
				std::vector<std::string> field_values = lyxutils::str_utils::split(line, sep);
				std::for_each(field_values.begin(), field_values.end(), [](std::string &str) {str = lyxutils::str_utils::replace(str, " ", ""); });
				output.clear();
				output.resize(field_values.size());
				for (int i = 0; i < field_values.size(); ++i) {
					try {
						output[i] = std::stof(field_values[i]);//将字符串转为float
					}
					catch (std::exception) {
						output[i] = fill;
					}
				}
			}
		};
	}
	/**\brief 封装了一些算法
	  */
	namespace algorithms 
	{
		const double PI = 3.1415926535897932;

		/**\brief 计算点列表pList中的平均点坐标
		  *\param[in] pList 包含点的vector
		  *\param[out] average_x,average_y,average_z 计算的坐标平均值
		  */
		template<class PointType>
		void computeAverages(const std::vector<PointType*> &pList, double &average_x, double &average_y, double &average_z)
		{
			average_x = 0;
			average_y = 0;
			average_z = 0;
			for (int i = 0; i < pList.size(); ++i) {
				average_x += pList[i]->x;
				average_y += pList[i]->y;
				average_z += pList[i]->z;
			}
			if (pList.size() > 0) {
				average_x = average_x / pList.size();
				average_y = average_y / pList.size();
				average_z = average_z / pList.size();
			}
		}
		/**\brief 使用最小二乘法拟合平面
		  *\param[in] pList 输入点列表
		  *\param[out] a,b,c,d 输出的平面参数ax+by+cz+d=0同时a^2+b^2+c^2=1
		  */
		template<class PointType>
		void leastSquarePlaneFit(const std::vector<PointType*> &pList, double &a, double &b, double &c, double &d)
		{
			Eigen::Matrix3d A;
			double average_x, average_y, average_z;
			double sum_xx = 0, sum_xy = 0, sum_xz = 0;
			double sum_yy = 0, sum_yz = 0;
			double sum_zz = 0;
			computeAverages(pList, average_x, average_y, average_z);
			for (int i = 0; i < pList.size(); ++i) {
				sum_xx += (pList[i]->x - average_x)*(pList[i]->x - average_x);
				sum_xy += (pList[i]->x - average_x)*(pList[i]->y - average_y);
				sum_xz += (pList[i]->x - average_x)*(pList[i]->z - average_z);
				sum_yy += (pList[i]->y - average_y)*(pList[i]->y - average_y);
				sum_yz += (pList[i]->y - average_y)*(pList[i]->z - average_z);
				sum_zz += (pList[i]->z - average_z)*(pList[i]->z - average_z);
			}
			A << sum_xx, sum_xy, sum_xz,
				sum_xy, sum_yy, sum_yz,
				sum_xz, sum_yz, sum_zz;
			Eigen::EigenSolver<Eigen::Matrix3d> es(A);
			Eigen::Matrix3d D = es.pseudoEigenvalueMatrix();
			Eigen::Matrix3d V = es.pseudoEigenvectors();
			int mark = 0;
			double lamda = D(0, 0);
			for (int i = 0; i < 3; ++i) {
				if (D(i, i) < lamda) {
					mark = i;
					lamda = D(i, i);
				}
			}
			a = V(0, mark);
			b = V(1, mark);
			c = V(2, mark);
			d = -a*average_x - b*average_y - c*average_z;
			if (c < 0) {//keep c always positive
				a = -a;
				b = -b;
				c = -c;
				d = -d;
			}
		}
		/**\brief 计算给定点集到给定平面的平均距离
		  *\param[in] pList 点集
		  *\param[in] a,b,c,d 平面系数，a^2+b^2+c^2=1
		  *\param[out] average_dis 平均距离
		  */
		template<class PointType>
		void findAverageDistanceToPlane(const std::vector<PointType*> &pList, const double &a,
			const double &b, const double &c, const double &d, double &average_dis)
		{
			average_dis = 0;
			for (int i = 0; i < pList.size(); ++i) {
				average_dis += distanceToPlane(pList[i]->x, pList[i]->y, pList[i]->z, a, b, c, d);
			}
			average_dis = average_dis / pList.size();
		}
		/**\brief region growing algorithm,give a seed unit and grow out a whole region.mark each unit being growned
		  *\param[in] seed the given seed point(type is unit,define whichever type you think can represent the growing unit)
		  *\param[in] findNeighbors a function or functor that can find the neighbors of a given unit
		  *\param[in] growingCondition the growing condition for this algorithm
		  *\param[out] growingResult the growing result,a vector that contains all the growing resultant units
		  *\function or functor declarations:
		  *\std::vector<Unit>* findNeighbors(const Unit &center)
		  *\bool growingCondition(const Unit &center,const Unit &neighbor)
		  */
		template<class Unit, class UnaryOperation, class BinaryPredict>
		void regionGrowing(Unit &seed, UnaryOperation findNeighbors,
			BinaryPredict growingCondition, std::vector<Unit> &growingResult)
		{
			std::vector<Unit> *recursion = new std::vector<Unit>();
			growingResult.push_back(seed);
			recursion->push_back(seed);
			while (recursion->size() > 0)
			{
				Unit indexesTemp = (*recursion)[recursion->size() - 1];
				recursion->pop_back();
				std::vector<Unit>* neighbors = findNeighbors(indexesTemp);
				for (auto iterator = neighbors->begin(); iterator != neighbors->end(); iterator++) {
					if (growingCondition(indexesTemp, *iterator)) {
						growingResult.push_back(*iterator);
						recursion->push_back(*iterator);
					}
				}
				delete neighbors;
			}
			delete recursion;
		}
		/**\brief 使用葛立恒扫描算法得到有限点集的凸包
		  *\param[in] pList 输入点集
		  *\param[out] border 输出的凸包顶点
		  */
		template<class PointType>
		void findConvexHullBorder(const std::vector<PointType*> &pList, std::vector<PointType*> &border)
		{
			if (pList.size() < 3)
				throw exception("点数太少，无法确定外包多边形");
			//先复制一遍到border,然后在border上操作
			double x_min = pList[0]->x;
			int x_min_index = 0;
			border.push_back(pList[0]);
			for (int i = 1; i < pList.size(); ++i) {
				border.push_back(pList[i]);
				if (pList[i]->x < x_min || pList[i]->x == x_min&&pList[i]->y < pList[x_min_index]->y) {
					x_min = pList[i]->x;
					x_min_index = i;
				}
			}
			//把x最小的点移到开头
			PointType *pointTemp = border[x_min_index];
			border[x_min_index] = border[0];
			//border[0] = pointTemp;
			//逆时针排序点
			//sort(border.begin() + 1, border.end(), [&pointTemp](PointType *p1, PointType *p2)
				//->bool {return compareAngle(*pointTemp, *p1, *p2); });
			border.erase(border.begin());
			merge_sort(border, [&pointTemp](PointType *p1, PointType *p2)
				->bool {return compareAngle(*pointTemp, *p1, *p2); });
			border.insert(border.begin(), pointTemp);
			//去除共线的近点,保留远点
			for (auto it = border.begin() + 1; it != border.end();) {
				if ((it + 1) != border.end() && orientation(*pointTemp, **it, **(it + 1)) == 0) {
					it = border.erase(it);
				}
				else {
					it++;
				}
			}
			if (border.size() < 3)
				throw exception("点数不够，无法确定外包多边形");
			if (border.size() == 3)//刚好只有三个外包点,那到此就完成了,这三个点就是外包线
			{
				return;
			}
			//去除凹点
			auto first = border.begin() + 1;
			auto second = first + 1;
			auto third = second + 1;
			while (third != border.end()) {
				int orien = orientation(**first, **second, **third);
				if (orien != 2) {
					border.erase(second);
					second = first;
					first--;
					third = second + 1;//这里注意,erase了元素后后面的元素都会前移一位,而third不会自动前移,相当于third后移了
				}
				else {
					first++;
					second++;
					third++;
				}
			}
		}
		/**\brief 使用javis算法计算凸包
		  *\param[in] pList 输入点集
		  *\param[out] border 输出的凸包顶点
		  *\note: 这个函数输入的点集中的点必须有默认的无参构造函数
		  *\	  这个是我吃饱了撑的没事干写的，时间复杂度为O(nH),H为顶点数;说不定还不如gragam快(时间复杂度为O(nlogn))
		  */
		template<class PointType>
		void javisMarch(const std::vector<PointType*> &pList, std::vector<PointType*> &border)
		{
			if (pList.size() < 3)
				throw exception("点数太少，无法确定外包多边形");
			//求两点向量函数
			auto vector2P = [](const PointType &p1, const PointType &p2)->PointType& {
				PointType result;
				result.x = p2.x - p1.x;
				result.y = p2.y - p1.y;
				return result;
			};
			//计算三点构成的两个向量的夹角余弦值（0-PI，故余弦值越大夹角越小）,p1可以为NULL（此时计算水平方向与p2p3余弦值）
			auto turningAngle=[&vector2P](PointType *p1, PointType *p2, PointType *p3)->float
			{
				PointType v1;
				PointType v2;
				if (p1 == NULL) {
					v1.x = 1;
					v1.y = 0;
				}
				else {
					v1 = vector2P(*p1, *p2);
				}
				v2 = vector2P(*p2, *p3);
				return (v1.x*v2.x + v1.y*v2.y) / (sqrt(v1.x*v1.x + v1.y*v1.y)*sqrt(v2.x*v2.x + v2.y*v2.y));
			};
			//找到y最小的点并将其移到队首，同时赋值一遍pList为remainPts以防对原始点集的更改
			double yMin = pList[0]->y;
			int min_index = 0;
			std::vector<PointType*> remainPts;
			for (int i = 0; i < pList.size(); ++i) {
				remainPts.push_back(pList[i]);
				if (pList[i]->y < yMin) {
					yMin = pList[i]->y;
					min_index = i;
				}
			}
			PointType *pTemp = remainPts[0];
			remainPts[0] = remainPts[min_index];
			remainPts[min_index] = pTemp;
			//寻找凸包顶点
			PointType *p1, *p2;
			p1 = NULL;
			p2 = remainPts[0];
			border.push_back(p2);
			while (true) {
				if (remainPts.size() < 2)break;//如果remainPts中只剩一个点(起始点)，意味着所有点都是边界点
				float maxCos = -2.0;//任何一个cos值都会比这个大
				auto p3_pntr = remainPts.begin();//定位最大cos值（即最小左转角）的位置
				for (auto it = remainPts.begin(); it != remainPts.end(); ) {
					if ((*it)->x == p2->x && (*it)->y == p2->y) {
						//去除相同的点
						if (it != remainPts.begin()) {
							it = remainPts.erase(it);
						}
						else {
							++it;
						}
					}
					else {
						float cosVal = turningAngle(p1, p2, *it);
						if (cosVal > maxCos) {
							maxCos = cosVal;
							p3_pntr = it;
						}
						++it;
					}
				}
				p1 = p2;
				p2 = *p3_pntr;
				border.push_back(p2);
				remainPts.erase(p3_pntr);
				if (*(border.end() - 1) == border[0]) {
					//回到了起始点
					border.pop_back();
					break;
				}
			}
		}
		/**\brief 计算凸多边形面积
		  *\param[in] border 凸多边形边缘角点，可由函数lyxutils::algorithm::findConvexHull获取
		  *\注意：也可以自己给定角点，但是一定按照顺时针或逆时针顺序给定
		  */
		template<class PointType>
		double getConvexHullArea(const std::vector<PointType*> &border) 
		{
			if (border.size() < 3)
				throw std::exception("点数太少无法计算面积!");
			PointType *p1, *p2, *p3;
			double area = 0;
			int i = 1;
			p1 = border[0];
			while (i + 1 < border.size()) {
				p2 = border[i];
				p3 = border[i + 1];
				area += triangleArea(*p1, *p2, *p3);
				++i;
			}
			return area;
		}
		/**\brief 计算三角形（二维）的面积
		*/
		template<class PointType>
		double triangleArea(const PointType &vertice1, const PointType &vertice2, const PointType &vertice3)
		{
			double m_x = vertice2.x - vertice1.x;
			double m_y = vertice2.y - vertice1.y;
			double n_x = vertice3.x - vertice1.x;
			double n_y = vertice3.y - vertice1.y;
			return abs(m_x*n_y - m_y*n_x) / 2;
		}
		/**\brief find the orientation of the ordered triplet (p1,p2,p3)
		  *\function returns following values:
		  *\0-->if p1,p2,p3 are colinear (or if at least two of them are indentical)
		  *\1-->if clockwise
		  *\2-->if counterclockwise
		  */
		template<class PointType>
		int orientation(const PointType &p1, const PointType &p2, const PointType &p3)
		{
			double val = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);
			if (val == 0) return 0;  // colinear 
			return (val > 0) ? 1 : 2; // clock or counterclock wise 
		}
		/**\brief compare the two polar angles x-p1-p2 and x-p1-p3(counterclockwise)
		  *\return true if x-p1-p2 is smaller than x-p1-p3(or if p1p2<p1p3 when p1,p2,p3 are colinear)
		  */
		template<class PointType>
		bool compareAngle(const PointType &p1, const PointType &p2, const PointType &p3)
		{
			int o = orientation(p1, p2, p3);
			if (o == 0) {
				//return distance2DSquared(p1, p2) < distance2DSquared(p1, p3);
				//return distance2D(p1, p2) < distance2D(p1, p3);
				//这里假定的基点p1一定在最左边
				double v12_x = p2.x - p1.x;
				double v12_y = p2.y - p1.y;
				double v23_x = p3.x - p2.x;
				double v23_y = p3.y - p2.y;
				double innerProduct = v12_x*v23_x + v12_y*v23_y;
				return innerProduct > 0;
			}
			return (o == 2) ? true : false;
		}
		/**\brief find the squared Euclidean distance between two points
		*/
		template<class PointType>
		double distance2DSquared(const PointType &p1, const PointType &p2)
		{
			return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
		}
		/**\brief 计算二维平面点之间的距离
		  */
		template<class PointType>
		double distance2D(const PointType &p1, const PointType &p2)
		{
			return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
		}
		/**\brief 插入排序
		  */
		template<class Iterator,class BinaryComp>
		void insert_sort(Iterator begin, Iterator end, BinaryComp pred) 
		{
			for (auto it = begin; it + 1 != end; ++it) {
				for (auto it2 = it + 1; it2 != begin; --it2) {
					if (pred(*it2, *(it2 - 1))) {
						auto temp = *(it2 - 1);
						*(it2 - 1) = *it2;
						*it2 = temp;
					}
					else {
						break;
					}
				}
			}
		}
		/**\brief 归并排序,nlogn时间复杂度
		*/
		template<class DataType,class BinaryComp>
		void merge_sort(std::vector<DataType> &list, BinaryComp pred)
		{
			if (list.size() <= 1)
				return;
			int half = list.size() / 2;
			std::vector<DataType> pre;
			std::vector<DataType> post;
			for (int i = 0; i < half; ++i) {
				pre.push_back(list[i]);
			}
			for (int i = half; i < list.size(); ++i) {
				post.push_back(list[i]);
			}
			merge_sort(pre, pred);
			merge_sort(post, pred);
			//归并
			auto it1 = pre.begin();
			auto it2 = post.begin();
			for (int i = 0; i < list.size(); ++i) {
				if (it1 == pre.end()) {
					list[i] = *it2++;
				}
				else if (it2 == post.end()) {
					list[i] = *it1++;
				}
				else {
					list[i] = pred(*it1, *it2) ? *it1++ : *it2++;
				}
			}
		}
	}
	/**\brief 封装了颜色空间变换算法
	*/
	namespace colors 
	{
		/**\brief 将rgb颜色值转化为hsv颜色值
		  *\param[in] rgb为rgb颜色三维的向量,r,g,b范围为0~255整数
		  *\param[out] hsv为输出的hsv颜色值.h范围[0,359);s范围[0,1];v范围0~255整数
		  */
		void rgb2hsv(const std::vector<int> &rgb, std::vector<float> &hsv);
		/**\brief 将hsv颜色值转化为rgb颜色值
		*\param[in] hsv为输入的hsv颜色值.h范围[0,359);s范围[0,1];v范围0~255整数
		*\param[out] rgb为输出的rgb颜色三维的向量,r,g,b范围为0~255整数
		*/
		void hsv2rgb(const std::vector<float> &hsv, std::vector<int> &rgb);
	}
	/**\brief 封装了一些统计方法
	*/
	namespace stats
	{
		/**\brief 对一维数组求和，返回值为和
		  */
		template<class NumType>
		NumType sum(const std::vector<NumType> &vec)
		{
			NumType result = 0;
			for (auto it = vec.begin(); it != vec.end(); ++it)result += (*it);
			return result;
		}
		/**\brief 求和
		  *\param[in] vec 输入二维数组（第一个维度是索引行，第二个索引列，也即该数组必须是行向量组成的向量）
		  *\param[out] out_vec输出的一维数组
		  *\param[in] axis求和的方向（默认为-1，即全部求和）
		  *\note:如果给出求和方向，0表示把竖向轴上的各行元素求和；1表示把横向轴上的各列元素求和，得到的一维数组输出到out_vec中；
		  *\	 axis为-1（默认）则out_vec只含一个元素，这个元素是输入二维数组全部元素求和；
		  *\	 因为待求和的输入二维数组vec是行向量的向量，原则上各行允许列数不同，但是最好不要，意义也不大(而且各行求和可能出错，因为不能保证各行列数相同)
		  *\	 对空的数组也可以求和，不过得到的是0
		  *\例子（假定input_vec是一个二维数组）：
		  *\std::vector<float> sum;
		  *\lyxutils::stats::sum(input_vec,sum,axis=1);//各列求和
		*/
		template<class NumType>
		void sum(const std::vector<std::vector<NumType> > &vec, std::vector<NumType> &out_vec, int axis = -1)
		{
			if (vec.size() == 0 || vec[0].size() == 0) {
				out_vec.clear();
				out_vec.push_back(0);
				return;
			}
			if (axis == 0 || axis == -1)
			{
				//各行求和
				out_vec.resize(vec[0].size());
				for (NumType &s : out_vec)s = 0;
				for (int i = 0; i < out_vec.size(); ++i)
				{
					for (auto &row : vec) {
						out_vec[i] += row[i];
					}
				}
				if (axis == -1) {
					NumType result = sum(out_vec);
					out_vec.clear();
					out_vec.push_back(result);
				}
			}
			else if (axis == 1)
			{
				//各列求和
				out_vec.resize(vec.size());
				for (NumType &s : out_vec)s = 0;
				for (int i = 0; i < out_vec.size(); ++i)
				{
					for (auto &s : vec[i]) {
						out_vec[i] += s;
					}
				}
			}
			else {
				throw std::exception("axis参数错误!");
			}
		}
		/**\brief 求一维数组均值(这里要注意整数求和再求平均得到的依然是整数，会丢失精度，最好还是用float或者double类型数组)
		  */
		template<class NumType>
		NumType mean(const std::vector<NumType> &vec)
		{
			return sum(vec) / vec.size();
		}
		/**\brief 求二维数组的均值，参数意义参照sum函数
		  */
		template<class NumType>
		void mean(const std::vector<std::vector<NumType> > &vec, std::vector<NumType> &out_vec, int axis = -1)
		{
			sum(vec, out_vec, axis);
			if (axis == -1) {
				out_vec[0] /= (vec.size()*vec[0].size());
			}
			else if (axis == 0) {
				for (int i = 0; i < out_vec.size(); ++i) {
					out_vec[i] /= vec.size();
				}
			}
			else if (axis == 1) {
				for (int i = 0; i < out_vec.size(); ++i) {
					out_vec[i] /= vec[i].size();
				}
			}
		}
	}
	/**\brief 封装了一些几何计算方法
	*/
	namespace geom
	{
		/**\brief 点类
		*/
		class Point
		{
		public:
			double x, y;
			Point() :x(0), y(0) {}
			Point(double x_, double y_) :x(x_), y(y_) {}
		};
		/**\brief 向量类
		*/
		class Vec
		{

		};
		//待实现:
		//1.其他点类向Point的转换与其他Vec类向Vec的转换以及二者互转方法(包括向其他向量、点类转换的函数）
		//2.计算过两点的直线，向量内积，向量外积，向量模，点到直线距离，点到直线的垂足
	}
}
#endif // !UTILS_H