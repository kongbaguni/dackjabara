#ifndef __APP_INLINE_FUNCTIONS_H__
#define __APP_INLINE_FUNCTIONS_H__
#include "cocos2d.h"
#include "CRandom.h"
USING_NS_CC;
namespace timeUtil
{
	static inline void getTimeM(int& iMin, int& iSec)
	{
		time_t rawtime;
		time (&rawtime);
		static struct tm * timeinfo;
		timeinfo = localtime (&rawtime);

		iMin = timeinfo->tm_min;
		iSec = timeinfo->tm_sec;
	}
	static inline void getTimeH(int& iHour, int& iMin)
	{
		time_t rawtime;
		time (&rawtime);
		static struct tm * timeinfo;
		timeinfo = localtime (&rawtime);

		iHour = timeinfo->tm_hour;
		iMin = timeinfo->tm_min;
	}
	static inline void getDate(int& iYear, int&iMonth, int&iDay)
	{
		time_t rawtime;
		time (&rawtime);
		static struct tm * timeinfo;
		timeinfo = localtime (&rawtime);

		iYear = timeinfo->tm_year+1900;
		iMonth = timeinfo->tm_mon+1;
		iDay = timeinfo->tm_mday;
	}
	static inline void getDateTime(int& iYear, int&iMonth, int&iDay, int&iHour, int&iMin, int&iSec)
	{
		time_t rawtime;
		time (&rawtime);
		static struct tm * timeinfo;
		timeinfo = localtime (&rawtime);

		iYear = timeinfo->tm_year+1900;
		iMonth = timeinfo->tm_mon+1;
		iDay = timeinfo->tm_mday;
		iHour = timeinfo->tm_hour;
		iMin = timeinfo->tm_min;
		iSec = timeinfo->tm_sec;
	}

	

	static inline long millisecondNow()
	{
		struct timeval now;
        gettimeofday(&now, NULL);
		return (now.tv_sec * 1000 + now.tv_usec / 1000);
	}

}

namespace textUtil
{
	static inline const char* addCommaText(double number)
	{
		if(number<1000)
		{
			return CCString::createWithFormat("%d",(int)number)->getCString();
		}
		static char result[20]="";
		char buf[20];
		int data[10] = {0};
		int a, c=number;
		int index=0;
		while(c) /* 뒤에서부터 3자리씩 잘라서 data에 저장.. */
		{
			a = c%1000;
			c = c/1000;
			data[index++] = a;
		}
		a = index-1;
		sprintf(buf,"%d", data[a]);
		strcpy(result,buf);

		for(--a ; a>=0; --a) /* data[]에 저장된 뒤쪽부터 result에 추가시킴.. */
		{
			sprintf(buf,",%03d", abs(data[a]));
			strcat(result,buf);
		}
		return CCString::createWithFormat("%s",result)->getCString();
	}

	static inline void replaceText(std::string& stringA, const std::string searchTxt, const std::string replaceText)
	{
		size_t size;
		while(true)
		{
			size = stringA.find(searchTxt);
			if(size==std::string::npos)
			{
				break;
			}
			stringA.replace(size,searchTxt.length(),replaceText);
		}
	}
}
namespace shuffleUtil
{
	static inline void shuffle(char* pOutputData, int size)
	{
        CRandom* pRandom = CRandom::getInstnace();
		std::vector<int> list;
		for(int i=0; i<size; i++)
		{
			int a = pOutputData[i];
			list.push_back(a);
		}

		for(int i=0; i<list.size(); i++)
		{			
			int rnd = pRandom->Random(list.size());
			std::vector<int>::iterator it = list.begin()+rnd;
			pOutputData[i] = (char)list[rnd];
			list.erase(it);
			if(list.size()==0)
			{
				break;
			}
		}
	}

	static inline void shuffle(int* pOutputData, int size)
	{
        CRandom* pRandom = CRandom::getInstnace();
		std::vector<int> list;
		for(int i=0; i<size; i++)
		{
			int a = pOutputData[i];
			list.push_back(a);
		}

		for(int i=0; i<list.size(); i++)
		{			
			int rnd = pRandom->Random(list.size());
			std::vector<int>::iterator it = list.begin()+rnd;
			pOutputData[i] = list[rnd];
			list.erase(it);
			if(list.size()==0)
			{
				break;
			}
		}
	}

}


#endif//__APP_INLINE_FUNCTIONS_H__
