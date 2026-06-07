#include "olcConsoleGameEngine.h"
#include <iostream>

using namespace std;

struct sBall
{
	float px, py;
	float vx, vy;
	float ax, ay;
	float radius;

	int id;
};

class CirclePhysics : public olcConsoleGameEngine
{
public:
	CirclePhysics()
	{
		m_sAppName = L"Circle Physics";
	}

private:
	vector<pair<float, float>> modelCircle;
	vector<sBall> vecBalls;

	void AddBall(float x, float y, float r = 5.0f)
	{
		sBall b;
		b.px = x; b.py = y;
		b.vx = 0; b.vy = 0;
		b.ax = 0; b.ay = 0;
		b.radius = r;

		b.id = vecBalls.size();
		vecBalls.emplace_back(b);

	}

public:
	bool OnUserCreate()
	{

		//Define circle model:
		modelCircle.push_back({ 0.0f, 0.0f });
		int nPoints = 20;
		for (int i = 0; i < nPoints; i++)
			modelCircle.push_back({ cosf(i / (float)(nPoints - 1) * 2.0f * 3.14159f), sinf(i / (float)(nPoints - 1) * 2.0f * 3.14159f) });

		float fDefaultRad = 4.0f;
		AddBall(ScreenWidth() * 0.25f, ScreenHeight() * 0.5f, fDefaultRad);
		AddBall(ScreenWidth() * 0.75f, ScreenHeight() * 0.5f, fDefaultRad);


		return true;
	}

	bool OnUserUpdate(float fElapsedTime)
	{

		// Clear screen
		Fill(0, 0, ScreenWidth(), ScreenHeight(), ' ');

		// Draw Balls:
		for (auto ball : vecBalls)
			DrawWireFrameModel(modelCircle, ball.px, ball.py, atan2f(ball.vy, ball.vx), ball.radius, FG_WHITE);

		return true;
	}


};

int main()
{
	CirclePhysics game;
	if (game.ConstructConsole(160, 120, 8, 8))
		game.Start();
	else
		wcout << L"Could not construct console" << endl;

	return 0;
}