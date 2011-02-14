/*
 *  highScores.h
 *  LaserSpray
 */

#define MAX_NUM_HIGHSCORES		10
#define NO_SCORE				0
#define EMPTY_CHAR				0

#include <string>

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
	inline char* getName() const { return name; }
	inline int getScore() const { return score; }
	void setName (char* Name);
	inline void setScore (int newScore) { score = newScore; }
	bool isDefined();
	inline void increaseScore(int points) { score += points; }
};

// Object that stores a collection of ScoreItems in highest to lowest score order.
class HighScoreTable
{
	protected:
	int nameLength;
	int maxScores;
	int numEntries;
	ScoreItem* table;
	
	public:
	HighScoreTable(int NameLength, int MaxScores);
	~HighScoreTable();
	
	void addScoreItem(ScoreItem newScore);
	inline char* getName(int pos) const { return table[pos].getName(); }
	inline int getScore(int pos) const { return table[pos].getScore(); }
	inline int isDefined(int pos) const { return table[pos].isDefined(); }

	bool isBetterScore(int newScore, int curScore);
	void insertScore(char* name, int score);
};