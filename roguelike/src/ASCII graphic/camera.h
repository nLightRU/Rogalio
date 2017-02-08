#pragma once
 
class Camera 
{
private: 
	const int _buffHeight = 20, _buffWidth = 20;
	char _buff[20][20];
public: 
	Camera();
	void printCamera();
};