/*
 *  ScoreItem.h
 *  Super Spray
 */

#ifndef __ScoreItem__
#define __ScoreItem__

// Object that stores the final score of the round and
// the name of the person who obtained it.
class ScoreItem
{
protected:
	int nameLength;
	char* name;
	int score;
	
public:
	ScoreItem();
	ScoreItem(int NameLength);
	~ScoreItem();
	
	void changeNameSize(int NewNameLength);
	inline char* getName() const { return name; };
	inline int getScore() const { return score; };
	void setName (char* Name);
	inline void setScore (int newScore) { score = newScore; };
	inline void incrementScore (int addScore) { score += addScore; };
	bool isDefined();
};

#endif