#ifndef __GAMECLASS_H__
#define __GAMECLASS_H__

class GameClass
{
public:
	bool Initialize();
	float GetTimeRecord();
	void SetTimeRecord(float);
	bool GetTimeAttackMode();
	void SetTimeAttackMode(bool);
	bool GetTimeAttackMixing();
	void SetTimeAttackMixing(bool);
	bool GetTimeAttackIsReady();
	void SetTimeAttackIsReady(bool);
	bool GetTimeAttackPlaying();
	void SetTimeAttackPlaying(bool);

private:
	float TimeRecord;
	bool TimeAttackMode;
	bool TimeAttackMixing;
	bool TimeAttackIsReady;
	bool TimeAttackPlaying;
};

#endif