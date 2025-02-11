#include <iostream>
#include "Animation.h"
#include "Sorts.h"

using namespace std;

// Funkcja wizualizujaca kolejne wartosci w tablicy
void Animation::drawArray(vector<pair<int, int>>vec)
{
	int frame = 0;
	const int frameWidth = 2;
	float BarWidth = (float)(GetScreenWidth() - frameWidth * numberOfPillars) / numberOfPillars;

	for (int i = 0;
		i < numberOfPillars;
		i++, frame += frameWidth)
	{
		Color color = findColor(vec[i].second);

		// Podaje ( { wspX skad mam zaczynac rysowac, wspY skad mam zaczac rysowac }, { podaje szerokosc slupka, a tu wysokosc }, { kolor } )
		DrawRectangleV(Vector2{ (float)i * BarWidth + frame, (float)GetScreenHeight() - vec[i].first },
			Vector2{ BarWidth, (float)vec[i].first },
			color);
	}
}

// Funkcja przypisuj�ca liczbom w wektorze losowe wartosci
void Animation::randomizeArray(vector<pair<int, int>>& vec)
{
	for (int i = 0; i < numberOfPillars; i++)
		vec[i] = { GetRandomValue(10, minWindowHeight), NORMAL };
}

// Funkcja pokazujaca ekran startowy	
void Animation::showMenuScreen()
{
	Font fontRegular = LoadFont("");
	int posY = 80;
	int fontSize = 40;
	const char* headerName = "Select a sorting algorithm: type 0-9";
	const char* fontName9 = "Work in progress";

	// Tekst g�owny
	int textWidth = MeasureTextEx(fontRegular, headerName, fontSize, fontSize / 10).x;
	DrawText(headerName, GetScreenWidth() / 2 - textWidth / 2, posY, fontSize, HEADER);

	fontSize = 25;
	posY += 170;

	////////////////////////////////////
	for (int i = 0; i < 9; i++)
	{
		textWidth = MeasureTextEx(fontRegular, algorithmsNames[i], fontSize, fontSize / 10).x;

		if (i % 3 == 0)
			DrawText(algorithmsNames[i], GetScreenWidth() / 5 - textWidth / 2, posY, fontSize, HEADER);
		else if (i % 3 == 1)
			DrawText(algorithmsNames[i], GetScreenWidth() / 2 - textWidth / 2, posY, fontSize, HEADER);
		else if (i % 3 == 2) {
			DrawText(algorithmsNames[i], GetScreenWidth() - GetScreenWidth() / 5 - textWidth / 2, posY, fontSize, HEADER);
			posY += 140;
		}
	}

	/////////////////////////////////////
	textWidth = MeasureTextEx(fontRegular, fontName9, fontSize, fontSize / 10).x;
	DrawText(fontName9, GetScreenWidth() / 2 - textWidth / 2, posY, fontSize, HEADER);
}

void Animation::checkAlgorithm()
{
	int key = GetCharPressed();

	if (key >= 48 && key <= 57)
	{
		Sorts o;
		switch (key)
		{
		case 48:
			o.bubble_sort(vec);
			break;
		case 49:
			o.select_sort(vec);
			break;
		case 50:
			o.insertion_sort(vec);
			break;
		case 51:
			o.counting_sort(vec);
			break;
		case 52:
			o.merge_sort(vec, 0, numberOfPillars - 1);
			break;
		}
		isShowMenuScreen = false;
		isExitMenuOpen = true;
	}
}

void Animation::displayAnimation(vector<pair<int, int>>vec)
{
	BeginDrawing();
	ClearBackground(BACKGROUND);
	drawArray(vec);
	EndDrawing();
}

void Animation::finalAnimation(vector<pair<int, int>>& vec)
{
	int key = 0;

	for (int i = 0; i < numberOfPillars; i++)
	{
		vec[i].second = SORTED;
		displayAnimation(vec);
	}
}

void Animation::exitMenu(vector<pair<int, int>>vec)
{
	int key = GetKeyPressed();

	if (key == KEY_Q)		//key 3
	{
		isExitMenuOpen = false;
		isRandomizeArray = true;
	}
	else
	{
		// WYSWIETL: "PRESS Q TO RETURN TO THE MENU"
		Font fontRegular = LoadFont("");
		const char* exitText = "Press q to return to the menu";
		int fontSize = 40;
		int posY = 80;
		Color color = findColor(EXITTEXT);

		int textWidth = MeasureTextEx(fontRegular, exitText, fontSize, fontSize / 10).x;
		DrawText(exitText, GetScreenWidth() / 2 - textWidth / 2, posY, fontSize, color);
	}
}

void Animation::sleep(int waitTime)
{
	std::chrono::milliseconds timespan(waitTime);
	std::this_thread::sleep_for(timespan);
}

void Animation::multipleColorAnimation(vector<pair<int, int>> myVec, int sleepValue, int index1, int index2, int index3)
{
	myVec.at(index1).second = SELECTED;
	if (index2 >= 0)
	{ 
		myVec.at(index2).second = SWAP;
		if (index3 >= 0)
			myVec.at(index3).second = SWAP2;
	}

	displayAnimation(myVec);
	sleep(sleepValue);
}

// Funkcja aktualizujaca kolory pilarow
Color  Animation::findColor(int pillarState)
{
	switch (pillarState)
	{
	case SELECTED:
		return RED;
		break;

	case SORTED:
		return GREEN;
		break;

	case EXITTEXT:
		return MAROON;
		break;

	case SWAP:
		return GOLD;
		break;

	case SWAP2:
		return LIME;
		break;

	default:
		return BLUE;
		break;
	}
}
