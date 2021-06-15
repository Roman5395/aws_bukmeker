#pragma once
class DoneRate
{
private:	
	int eventNum;
	char DateOfEvent[20];
	int RatePrice;
	char EventType[40];
	char teamOrParticipant[40];
	int id;

public:
	int search(int);
	void write();
	void create();
	void showData();
	void deleted();
	static int count();
	void read(int);
	void edit();
	int setId();
	int valiidation();
};

