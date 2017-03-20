#include "ASCIIrenderer.h"
#include <iostream>
#include <Windows.h>

ASCIIRenderer::ASCIIRenderer() 
{

}

void printControlTips() 
{
	std::cout << "w - up, a - left, s - down, d - right" << std::endl;
	std::cout << "p - exit, e - interact" << std::endl;
}

void setTextColor(unsigned char attr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr);
}

void showHealth(Player player) 
{
	setTextColor(FOREGROUND_INTENSITY + FOREGROUND_RED);
	std::cout << "HEALTH ";
	setTextColor(FOREGROUND_RED + FOREGROUND_GREEN + FOREGROUND_BLUE);
	std::cout << player.getHealth() << "/" << player.getMaxHealth();
	std::cout << std::endl;
}

void showMana(Player player)
{
	setTextColor(FOREGROUND_INTENSITY + FOREGROUND_BLUE);
	std::cout << "MANA ";
	setTextColor(FOREGROUND_RED + FOREGROUND_GREEN + FOREGROUND_BLUE);
	std::cout << player.getMana() << "/" << player.getMaxMana();
	std::cout << std::endl;
}

void showExperience(Player player)
{
	unsigned char attr = FOREGROUND_BLUE;
	for (int i = 0; i < 6; i++)
		attr += FOREGROUND_GREEN;

	setTextColor(attr);
	std::cout << "EXPERIENCE ";
	setTextColor(FOREGROUND_RED + FOREGROUND_GREEN + FOREGROUND_BLUE);
	std::cout << std::endl;
}

void showBorder() 
{
	setTextColor(FOREGROUND_INTENSITY + FOREGROUND_BLUE);
	for (int i = 0; i < 20; i++)
		std::cout << "#";
	setTextColor(FOREGROUND_RED + FOREGROUND_GREEN + FOREGROUND_BLUE);
	std::cout << std::endl;
}

void showFloors(Dungeon dungeon) 
{
	std::cout << "FLOOR " << dungeon.getCurrentFloorNumber() + 1 << "/";
	std::cout << dungeon.getFloors().size() << std::endl;
}

void ASCIIRenderer::setCamera(ASCIICamera cam) 
{
	char buff[21][21]; 
	for (int i = 0; i < _camera.getBuffHeight(); i++)
		for (int j = 0; j < _camera.getBuffWidth(); j++)
			buff[i][j] = cam.showBuffLine(i)[j];
	_camera.setBuff(buff);
}

void ASCIIRenderer::showGameplayScreen(Player player, Dungeon dungeon) 
{
	system("cls");

	printControlTips();
	std::cout << std::endl;

	showHealth(player);
	showMana(player);
	showExperience(player); 
	showFloors(dungeon);

	_camera.print();
}