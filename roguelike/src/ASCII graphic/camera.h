#pragma once
 
class Camera 
{
private: 
	const int _buffHeight = 21, _buffWidth = 21;
	char _buff[21][21];
public: 
	Camera();
	void print();
	void setBuff(char buff[21][21]);
};