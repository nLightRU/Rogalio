#pragma once
 
class ASCIICamera 
{
private: 
	const int _buffHeight = 21, _buffWidth = 21;
	char _buff[21][21];
public: 
	ASCIICamera();
	void print();
	void setBuff(char buff[21][21]);
};