#pragma once

template<typename Object> inline void SafeRelease(Object& obj)
{
	if(obj != nullptr)
	{
		obj->Release();
		obj = nullptr;
	}
}

template<typename Object> inline void SafeArrayDelete(Object& obj)
{
	if(obj != nullptr)
	{
		delete[] obj;
		obj = nullptr;
	}
}

template<typename Object> inline void SafeDelete(Object& obj)
{
	if(obj != nullptr)
	{
		delete obj;
		obj = nullptr;
	}
}