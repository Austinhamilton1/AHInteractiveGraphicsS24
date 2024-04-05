#pragma once
#include "BaseObject.h"
#include <vector>

class IndexBuffer : public BaseObject {
protected:
	unsigned int iboId;
	std::vector<unsigned short> indexData;

public:
	IndexBuffer();
	void SelectBuffer();
	void DeselectBuffer();
	inline std::vector<unsigned short>& GetIndexData() { return indexData; }
	inline int GetSize() { return indexData.size(); }
	void AddIndexData(unsigned int count, ...);
	void AddIndexData(unsigned short index);
	void StaticAllocate();
};