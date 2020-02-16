// spiiUtils.h

#ifndef SPIIUTILS_H_INCLUDED
#define SPIIUTILS_H_INCLUDED

namespace Utils
{
	template <class T>
	void DeleteVectorElements(std::vector<T> &container)
	{
		if(!container.empty())
		{
			u32 iC=container.size();
			for(u32 i=0;i<iC;i++)
			{
				delete container[i];
			};
			container.clear();
		};
	};
};

#endif // SPIIUTILS_H_INCLUDED
