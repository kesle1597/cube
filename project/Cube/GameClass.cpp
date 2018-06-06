#include "GameClass.h"

bool GameClass :: Initialize()
{
	TimeRecord = 0.0f;
	TimeAttackMode = false;
	TimeAttackMixing = false;
	TimeAttackIsReady = false;
	TimeAttackPlaying = false;

	return true;
}

float GameClass :: GetTimeRecord()
{
	return TimeRecord;
}

void GameClass :: SetTimeRecord(float time)
{
	TimeRecord = time;
}

bool GameClass :: GetTimeAttackMode()
{
	return TimeAttackMode;
}

void GameClass :: SetTimeAttackMode(bool mode)
{
	TimeAttackMode = mode;
}

bool GameClass :: GetTimeAttackMixing()
{
	return TimeAttackMixing;
}

void GameClass :: SetTimeAttackMixing(bool mixing)
{
	TimeAttackMixing = mixing;
}

bool GameClass :: GetTimeAttackIsReady()
{
	return TimeAttackIsReady;
}

void GameClass :: SetTimeAttackIsReady(bool isready)
{
	TimeAttackIsReady = isready;
}

bool GameClass :: GetTimeAttackPlaying()
{
	return TimeAttackPlaying;
}

void GameClass :: SetTimeAttackPlaying(bool playing)
{
	TimeAttackPlaying = playing;
}