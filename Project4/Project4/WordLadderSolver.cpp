// WordLadderSolver.cpp

// This is an incomplete, and thus incorrect, implementation of WordLadderSolver
// functionality.  Your job is to change WordLadderSolverImpl to a correct,
// hopefully efficient, implementation.  You can change it any way you like,
// subject to restrictions in the spec (e.g., that the only C++ library
// containers you are allowed to use are vector, list, stack, and queue (and
// string); if you want anything fancier, implement it yourself).

#include "WordLadderSolver.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <list>
#include <cctype>
#include <algorithm>
#include <functional>
using namespace std;

const int MAX_WORDS = 100003; // prime number
void removeNonLetters(string& s);

class WordLadderSolverImpl
{
public:
	WordLadderSolverImpl() {}
	~WordLadderSolverImpl() {}
	void createWordList(const vector<string>& words);
	int buildLadder(string start, string end, vector<string>& ladder);
	bool contains(string word);
	string findNextWord(string word, vector<string> used);
	
private:
	list<string> m_words[MAX_WORDS]; // open hash table
};

void WordLadderSolverImpl::createWordList(const vector<string>& words)
{
	for (string word : words)
	{
		removeNonLetters(word);
		// hash function defined in <functional>
		hash<std::string> hash_fn;
		size_t bucket = hash_fn(word) % MAX_WORDS;
		
		// if word is valid and not already in the table
		if ( ! word.empty()  &&  find(m_words[bucket].begin(), m_words[bucket].end(), word) == m_words[bucket].end())
			m_words[bucket].push_back(word);
	}
}

bool WordLadderSolverImpl::contains(string word)
{
	hash<std::string> hash_fn;
	size_t bucket = hash_fn(word) % MAX_WORDS;
	
	// open hash table means there is only one possible bucket value for a word
	if (find(m_words[bucket].begin(), m_words[bucket].end(), word) != m_words[bucket].end())
		return true;
	
	return false;
}

int WordLadderSolverImpl::buildLadder(string start, string end, vector<string>& ladder)
{
	ladder.clear();
	removeNonLetters(start);
	
	if (!contains(start))
		return 1;
	
	removeNonLetters(end);
	
	if (!contains(end))
		return 2;
	
	if (start == end)
		return 3;
	
	// FIFO structure of queue finds shortest path between words (checks all 2 word vectors, then 3 word, etc...)
	queue<vector<string>> m_paths;
	
	// words already checked
	vector<string> m_used;
	
	// start word (all vectors of words will be built from this vector)
	vector<string> firstWord;
	firstWord.push_back(start);
	m_paths.push(firstWord);
	
	string next;
	
	for (;;)
	{
		// all vector paths have been checked and there is no word path between the two words
		if (m_paths.size() == 0)
		{
			return -1;
		}
		
		vector<string> current = m_paths.front();
		m_paths.pop();
		
		for (;;)
		{
			// finds the next word in the path if there is one
			next = findNextWord(current.back(), m_used);
			
			// found the path!
			if (next == end)
			{
				current.push_back(end);
				ladder = current;
				return 0;
			}
			
			// another step in the path
			else if (next != "")
			{
				// create vector with the additional step and add it to the possible paths
				vector<string> m_next = current;
				m_next.push_back(next);
				m_paths.push(m_next);
			}
			
			// no more possible steps in the vector under inspection -> exit loop and inspect next vector
			else if (next == "")
				break;
			m_used.push_back(next);
		}
	}
	return -1;
}

string WordLadderSolverImpl::findNextWord(string word, vector<string> used)
{
	string nextWord;
	for (int i = 0; i < word.length(); i++)
	{
		for (char ch = 'a'; ch <= 'z'; ch++)
		{
			nextWord = word;
			nextWord = nextWord.replace(i, 1, 1, ch); // replaces a single char
			
			// if nextWord is in the wordlist and it hasn't already been used
			if (contains(nextWord) && nextWord != word && find(used.begin(), used.end(), nextWord) == used.end())
				return nextWord;
			
			nextWord = word;
			nextWord = nextWord.insert(i, 1, ch); // adds a single char somewhere in word
			if (contains(nextWord) && nextWord != word && find(used.begin(), used.end(), nextWord) == used.end())		return nextWord;
			
			if (i == word.length() - 1)
			{
				nextWord = word;
				nextWord = nextWord.insert(i + 1, 1, ch); // appends a char to the end
				if (contains(nextWord) && find(used.begin(), used.end(), nextWord) == used.end() && nextWord != word)
					return nextWord;
			}
		}
		
		if (i < word.length() - 1) // swaps two adjacent letters
		{
			nextWord = word;
			swap (nextWord[i], nextWord[i+1]);
			if (contains(nextWord) && find(used.begin(), used.end(), nextWord) == used.end() && nextWord != word)
				return nextWord;
		}
		
		nextWord = word;
		nextWord = nextWord.erase(i, 1); // deletes a single char
		
		if (contains(nextWord) && find(used.begin(), used.end(), nextWord) == used.end() && nextWord != word)
			return nextWord;
	}
	return ""; // no valid words can be made from word
}

void removeNonLetters(string& s)
{
	string::iterator to = s.begin();
	for (char ch : s)
	{
		if (isalpha(ch))
		{
			*to = tolower(ch);
			to++;
		}
	}
	s.erase(to, s.end());  // chop off everything from "to" to end.
}

//******************** WordLadderSolver functions **********************************

// These functions simply delegate to WordLadderSolverImpl's functions.
// You probably don't want to change any of this code.

WordLadderSolver::WordLadderSolver()
{
	m_impl = new WordLadderSolverImpl;
}

WordLadderSolver::~WordLadderSolver()
{
	delete m_impl;
}

void WordLadderSolver::createWordList(const vector<string>& words)
{
	m_impl->createWordList(words);
}

int WordLadderSolver::buildLadder(string start, string end, vector<string>& ladder)
{
	return m_impl->buildLadder(start, end, ladder);
}