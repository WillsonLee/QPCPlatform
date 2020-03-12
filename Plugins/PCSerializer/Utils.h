#ifndef LYXUTILS_H
#define LYXUTILS_H
//˵����һЩ���ù��ߺ���
//��Ŀ-����-��������-C/C++ -Ԥ������-Ԥ������������Ҫ���_CRT_SECURE_NO_WARNINGS,����getTimeString����������̲߳���ȫ����
#include <string>
#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <thread>

/**\�Լ���װ��һ�����߰�������һЩ���ߺ���
  *\Ϊ�˼�����������ʹ�õ�ʱ�������һЩ���ֿռ�������
  *\���磺#define ual lyxutils::algorithms, �Ϳ�����ual��Ϊlyxutils::algorithms�ı���
  *\�൱��python�е�import package as alias
  *\Ҳ�����ڳ���ͷ�����µ����ֿռ䣺namespace myIO=lyxutils::io
  */
namespace lyxutils
{
	/**\brief ��ȡ��ǰʱ����ַ���
	  *\��HH:MM:SS��ʽ����ʱ���ַ���
	  */
	std::string getTimeString();
	/**\brief ����һ����ΪfolderPath���ļ��У�����Ѵ����򲻲�����
	  *\return true��������ɹ������ļ����Ѵ���
	  */
	bool createFolder(const std::string folderPath);
	/**\brief ��һ���ļ���Ϊ��־
	  *\param[in] fileName �򿪵��ļ���
	  *\return ׷��дģʽ����־�ļ�
	  */
	std::ofstream* openLogFile(std::string fileName);
	/**\brief ��򿪵���־�ļ�д��Ϣ
	  *\param[in] log ��־�ļ�
	  *\param[in] message Ҫд����Ϣ
	  *\param[in] end ��Ϣĩβ����β�ַ���Ĭ��Ϊ"\n"�����Զ��س����У�
	  */
	void writeLog(std::ofstream &log, std::string message, std::string end = "\n");
	/**\brief ������f��ʱ
	  *\param[in] f ����ʱ�ĺ���
	  *\note: ʱ�䵥λ�Ǻ��룬����ʱ�ĺ�������û�в���������У����԰������·�ʽ���ã�
	  *\���纯��f��ǩ���ǣ�int f(params)������params�ǲ����б��ɶ������¼�ʱ
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
	/**\brief �����̨��ӡ������
	  *\param[in] value ��ǰ����ֵ(0~100)
	  *\param[in] delimiterL ����������ָ���
	  *\param[in] increment ����������������
	  *\param[in] delimiterR �ҷָ���
	  *\param[in] status����ָ��ÿһ�����ʱ���״̬������"���ڴ���"��"���ڶ�ȡ"֮��ģ�
	  *\note ���ò���valueΪ0ʱ���Զ����У�Ϊ100ʱ���Զ���ӡ���Ƚ��������У��м��������Ȳ��ỻ��
	  *\note ���ѭ������̫��,���������ٷֱȴ������״̬���磺
	  *\for(int i=0;i<total;++i){
	  *\	if(i%(total/100)==0)lyxutils::consoleProgressBar(i*100/total);
	  *\	//ִ�еĲ���
	  *\}
	  */
	void consoleProgressBar(int value, std::string delimiterL = "[", std::string increment = ">", std::string delimiterR = "]", std::string status = "");
	/**\brief ��װ��һЩ�ַ�������
	  */
	namespace str_utils
	{
		/**\brief �Ը����ķָ����ָ��ַ���
		  *\param[in] str ���ָ���ַ���
		  *\param[in] delimiter �ָ���(ֻ���ǵ����ַ����ַ���������Ƕ��ַ��ַ�������ÿһ���ַ���������Ϊ�ָ���)
		  */
		std::vector<std::string> split(const std::string &str, const std::string &delimiter);
		/**\brief ���ַ����ָ��ַ���
		  */
		std::vector<std::string> split_with_string(const std::string &str, const std::string &delString);
		std::string lower(const std::string &str);
		std::string upper(const std::string &str);
		/**\brief ��old����new�ַ���
		  */
		std::string replace(const std::string &str, const std::string &oldStr, const std::string &newStr);
	}
	/**\brief ��װ��һЩ��д����
	  */
	namespace io
	{
		/**\brief ��ȡcsv�ļ�
		  *\param[in] fileName �����ļ���
		  *\param[out] table ���ڱ����ȡ���ݵĶ�άvector,table��ÿһ��Ԫ�ض���һ��vector��ÿ��vector����һ������
		  *\param[in] sep �ָ��������ݵķָ���,ͨ����","
		  *\param[out] report ��¼��ȡ���̻�����Ϣ��������ַ���
		  *\param[in] fields Ҫ��ȡ������(-1�������ļ��е�������)
		  *\param[in] read_header �Ƿ�ѵ�һ����Ϊ��ͷ
		  *\param[out] headers ��ͷ(���read_headerΪtrue)
		  *\param[in] numberOfRedirect �ض������������(����������table��),Ӧ��С���ܶ�ȡ����fields
		  *\param[in] directFunc �ض������������ض��������н��д���ĺ���
		  *\note:directFunc�Ĳ�����ά�������numberOfRedirect��ͬ
		  *\the ���һ������directFuncs�������¶������ض�������ļ���ǰ�����ֶ�(cloud_in��ȫ�ֵĵ���ָ��)��
		  *\�ض����Ŀ��Ҳ���ڴ�
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
		  *\���䣺������ݺ����е�������Ҫ��ȡ��������һ�£��������������ԣ��������������Ϊ0
		  */
		bool read_csv(const std::string &fileName, std::vector<std::vector<float> > &table, const std::string &sep, std::string &report,
			int fields = -1, bool read_header = false, std::vector<std::string> &headers = std::vector<std::string>(),
			int numberOfRedirect = 0, void(*directFunc)(const std::vector<float>&) = NULL);
		/**\brief дcsv�ļ�
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
		/**\brief �ѵ���д��csv�ļ�
		  *\����ר�÷���, PointCloudPtr is class pcl::PointCloud<pcl::PointType>::Ptr
		  *\֮����ʹ��ģ�庯����Ϊ���ѿ��Ե��ƿ������
		  */
		template<class PointCloudPtr,class DataType>
		void pc_to_csv(const std::string fileName, PointCloudPtr pc, const std::vector<std::vector<DataType> >&table, const std::string &sep, bool with_rgb = false)
		{
			std::ofstream ofs(fileName);
			ofs << std::setprecision(8);
			if (table.size() != 0 && table[0].size() != pc->points.size())
				throw exception("table����������������е�����һ��!");
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
		/**\brief ����ļ��Ƿ����
		  */
		bool fileExists(std::string fileName);
		/**\brief ����౾���Ƿ�װһЩ�̶���ʽ�ļ���д����������csv�ļ��Ŀ��ٶ�д
		  *\���ǳ�������c++��ԭ�򣬶�д��������û���죻
		  *\������ͼ�������ж��룬Ȼ���ÿһ�����ݽ�������Ϊÿһ�н���������һ�������Բ��ö��̣߳�����ʧ��
		  *\ʧ�����Ϊ������ǻ�Ī�������������������ݣ���ȫ��֪��ʲôԭ��
		  *\��Ҫ�ٶ�����Ҫ�ٶ�����Ҫ�ٶ�������c++��չ����ô���껹��ͨ��ԭʼ���ļ�����д������
		  */
		class FileHelper 
		{
		public:
			static bool load_csv(const std::string fileName, std::vector<std::vector<float> > &table, const std::string sep, const float fill=0.0,int n_jobs=std::thread::hardware_concurrency()) 
			{
				if (!lyxutils::io::fileExists(fileName))
					throw std::exception("�ļ�������!");
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
						output[i] = std::stof(field_values[i]);//���ַ���תΪfloat
					}
					catch (std::exception) {
						output[i] = fill;
					}
				}
			}
		};
	}
	/**\brief ��װ��һЩ�㷨
	  */
	namespace algorithms 
	{
		const double PI = 3.1415926535897932;

		/**\brief ������б�pList�е�ƽ��������
		  *\param[in] pList �������vector
		  *\param[out] average_x,average_y,average_z ���������ƽ��ֵ
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
		/**\brief ʹ����С���˷����ƽ��
		  *\param[in] pList ������б�
		  *\param[out] a,b,c,d �����ƽ�����ax+by+cz+d=0ͬʱa^2+b^2+c^2=1
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
		/**\brief ��������㼯������ƽ���ƽ������
		  *\param[in] pList �㼯
		  *\param[in] a,b,c,d ƽ��ϵ����a^2+b^2+c^2=1
		  *\param[out] average_dis ƽ������
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
		/**\brief ʹ�ø�����ɨ���㷨�õ����޵㼯��͹��
		  *\param[in] pList ����㼯
		  *\param[out] border �����͹������
		  */
		template<class PointType>
		void findConvexHullBorder(const std::vector<PointType*> &pList, std::vector<PointType*> &border)
		{
			if (pList.size() < 3)
				throw exception("����̫�٣��޷�ȷ����������");
			//�ȸ���һ�鵽border,Ȼ����border�ϲ���
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
			//��x��С�ĵ��Ƶ���ͷ
			PointType *pointTemp = border[x_min_index];
			border[x_min_index] = border[0];
			//border[0] = pointTemp;
			//��ʱ�������
			//sort(border.begin() + 1, border.end(), [&pointTemp](PointType *p1, PointType *p2)
				//->bool {return compareAngle(*pointTemp, *p1, *p2); });
			border.erase(border.begin());
			merge_sort(border, [&pointTemp](PointType *p1, PointType *p2)
				->bool {return compareAngle(*pointTemp, *p1, *p2); });
			border.insert(border.begin(), pointTemp);
			//ȥ�����ߵĽ���,����Զ��
			for (auto it = border.begin() + 1; it != border.end();) {
				if ((it + 1) != border.end() && orientation(*pointTemp, **it, **(it + 1)) == 0) {
					it = border.erase(it);
				}
				else {
					it++;
				}
			}
			if (border.size() < 3)
				throw exception("�����������޷�ȷ����������");
			if (border.size() == 3)//�պ�ֻ�����������,�ǵ��˾������,����������������
			{
				return;
			}
			//ȥ������
			auto first = border.begin() + 1;
			auto second = first + 1;
			auto third = second + 1;
			while (third != border.end()) {
				int orien = orientation(**first, **second, **third);
				if (orien != 2) {
					border.erase(second);
					second = first;
					first--;
					third = second + 1;//����ע��,erase��Ԫ�غ�����Ԫ�ض���ǰ��һλ,��third�����Զ�ǰ��,�൱��third������
				}
				else {
					first++;
					second++;
					third++;
				}
			}
		}
		/**\brief ʹ��javis�㷨����͹��
		  *\param[in] pList ����㼯
		  *\param[out] border �����͹������
		  *\note: �����������ĵ㼯�еĵ������Ĭ�ϵ��޲ι��캯��
		  *\	  ������ҳԱ��˳ŵ�û�¸�д�ģ�ʱ�临�Ӷ�ΪO(nH),HΪ������;˵����������gragam��(ʱ�临�Ӷ�ΪO(nlogn))
		  */
		template<class PointType>
		void javisMarch(const std::vector<PointType*> &pList, std::vector<PointType*> &border)
		{
			if (pList.size() < 3)
				throw exception("����̫�٣��޷�ȷ����������");
			//��������������
			auto vector2P = [](const PointType &p1, const PointType &p2)->PointType& {
				PointType result;
				result.x = p2.x - p1.x;
				result.y = p2.y - p1.y;
				return result;
			};
			//�������㹹�ɵ����������ļн�����ֵ��0-PI��������ֵԽ��н�ԽС��,p1����ΪNULL����ʱ����ˮƽ������p2p3����ֵ��
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
			//�ҵ�y��С�ĵ㲢�����Ƶ����ף�ͬʱ��ֵһ��pListΪremainPts�Է���ԭʼ�㼯�ĸ���
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
			//Ѱ��͹������
			PointType *p1, *p2;
			p1 = NULL;
			p2 = remainPts[0];
			border.push_back(p2);
			while (true) {
				if (remainPts.size() < 2)break;//���remainPts��ֻʣһ����(��ʼ��)����ζ�����е㶼�Ǳ߽��
				float maxCos = -2.0;//�κ�һ��cosֵ����������
				auto p3_pntr = remainPts.begin();//��λ���cosֵ������С��ת�ǣ���λ��
				for (auto it = remainPts.begin(); it != remainPts.end(); ) {
					if ((*it)->x == p2->x && (*it)->y == p2->y) {
						//ȥ����ͬ�ĵ�
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
					//�ص�����ʼ��
					border.pop_back();
					break;
				}
			}
		}
		/**\brief ����͹��������
		  *\param[in] border ͹����α�Ե�ǵ㣬���ɺ���lyxutils::algorithm::findConvexHull��ȡ
		  *\ע�⣺Ҳ�����Լ������ǵ㣬����һ������˳ʱ�����ʱ��˳�����
		  */
		template<class PointType>
		double getConvexHullArea(const std::vector<PointType*> &border) 
		{
			if (border.size() < 3)
				throw std::exception("����̫���޷��������!");
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
		/**\brief ���������Σ���ά�������
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
				//����ٶ��Ļ���p1һ���������
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
		/**\brief �����άƽ���֮��ľ���
		  */
		template<class PointType>
		double distance2D(const PointType &p1, const PointType &p2)
		{
			return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
		}
		/**\brief ��������
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
		/**\brief �鲢����,nlognʱ�临�Ӷ�
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
			//�鲢
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
	/**\brief ��װ����ɫ�ռ�任�㷨
	*/
	namespace colors 
	{
		/**\brief ��rgb��ɫֵת��Ϊhsv��ɫֵ
		  *\param[in] rgbΪrgb��ɫ��ά������,r,g,b��ΧΪ0~255����
		  *\param[out] hsvΪ�����hsv��ɫֵ.h��Χ[0,359);s��Χ[0,1];v��Χ0~255����
		  */
		void rgb2hsv(const std::vector<int> &rgb, std::vector<float> &hsv);
		/**\brief ��hsv��ɫֵת��Ϊrgb��ɫֵ
		*\param[in] hsvΪ�����hsv��ɫֵ.h��Χ[0,359);s��Χ[0,1];v��Χ0~255����
		*\param[out] rgbΪ�����rgb��ɫ��ά������,r,g,b��ΧΪ0~255����
		*/
		void hsv2rgb(const std::vector<float> &hsv, std::vector<int> &rgb);
	}
	/**\brief ��װ��һЩͳ�Ʒ���
	*/
	namespace stats
	{
		/**\brief ��һά������ͣ�����ֵΪ��
		  */
		template<class NumType>
		NumType sum(const std::vector<NumType> &vec)
		{
			NumType result = 0;
			for (auto it = vec.begin(); it != vec.end(); ++it)result += (*it);
			return result;
		}
		/**\brief ���
		  *\param[in] vec �����ά���飨��һ��ά���������У��ڶ��������У�Ҳ���������������������ɵ�������
		  *\param[out] out_vec�����һά����
		  *\param[in] axis��͵ķ���Ĭ��Ϊ-1����ȫ����ͣ�
		  *\note:���������ͷ���0��ʾ���������ϵĸ���Ԫ����ͣ�1��ʾ�Ѻ������ϵĸ���Ԫ����ͣ��õ���һά���������out_vec�У�
		  *\	 axisΪ-1��Ĭ�ϣ���out_vecֻ��һ��Ԫ�أ����Ԫ���������ά����ȫ��Ԫ����ͣ�
		  *\	 ��Ϊ����͵������ά����vec����������������ԭ���ϸ�������������ͬ��������ò�Ҫ������Ҳ����(���Ҹ�����Ϳ��ܳ�����Ϊ���ܱ�֤����������ͬ)
		  *\	 �Կյ�����Ҳ������ͣ������õ�����0
		  *\���ӣ��ٶ�input_vec��һ����ά���飩��
		  *\std::vector<float> sum;
		  *\lyxutils::stats::sum(input_vec,sum,axis=1);//�������
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
				//�������
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
				//�������
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
				throw std::exception("axis��������!");
			}
		}
		/**\brief ��һά�����ֵ(����Ҫע�������������ƽ���õ�����Ȼ���������ᶪʧ���ȣ���û�����float����double��������)
		  */
		template<class NumType>
		NumType mean(const std::vector<NumType> &vec)
		{
			return sum(vec) / vec.size();
		}
		/**\brief ���ά����ľ�ֵ�������������sum����
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
	/**\brief ��װ��һЩ���μ��㷽��
	*/
	namespace geom
	{
		/**\brief ����
		*/
		class Point
		{
		public:
			double x, y;
			Point() :x(0), y(0) {}
			Point(double x_, double y_) :x(x_), y(y_) {}
		};
		/**\brief ������
		*/
		class Vec
		{

		};
		//��ʵ��:
		//1.����������Point��ת��������Vec����Vec��ת���Լ����߻�ת����(��������������������ת���ĺ�����
		//2.����������ֱ�ߣ������ڻ����������������ģ���㵽ֱ�߾��룬�㵽ֱ�ߵĴ���
	}
}
#endif // !UTILS_H