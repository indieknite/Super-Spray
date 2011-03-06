/*
 *  ScoreItem.h
 *  LaserSpray
 */

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
	bool isDefined();
	inline void increaseScore(int points) { score += points; };
};