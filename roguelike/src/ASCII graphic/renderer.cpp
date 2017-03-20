#include "renderer.h"
#include <iostream>
#include <Windows.h>

Renderer::Renderer() 
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
	std::cout << player.getMana() << "/" << player.getMaxMana();
	std::cout << std::endl;
}

void Renderer::showGameplayScreen(Player player) 
{
	printControlTips();
	std::cout << std::endl;

	showHealth(player);
	showMana(player);
	showExperience(player); 
	std::cout << std::endl;
}