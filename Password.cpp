#include "Password.h"


#include <iostream>
using namespace std;
using namespace CSC2110;


Password::Password()//
{
	ListArray<String>*all_passwords = new ListArray<String>;
	all_words = all_passwords;
	ListArray<String>* possible_passwords = new ListArray<String>;
	viable_words = possible_passwords;
	
}
Password::~Password()//
{
	ListArrayIterator<String>* del_iter = all_words->iterator();
	while(del_iter->hasNext())
	{
		String* word = del_iter->next();
		delete word;
		
	}
	delete del_iter;
}
void Password::addWord(String* word)//
{	
	len = word->length();
	ListArrayIterator<String>* add_iter = viable_words->iterator();
	while(add_iter->hasNext())
	{ 
		if(word->length()!=len)return;
		word = add_iter->next();
		viable_words->add(word);
		all_words->add(word);
	}
	
}
void Password::guess(int try_password,int num_matches)
 {	
	int i=0;
	ListArray<String>* guess_words= viable_words;
	ListArrayIterator<String>* guess_iter = guess_words->iterator();
	while(guess_iter->hasNext())
	{
		if(num_matches != getNumMatches(all_words->get(try_password),guess_words->get(i)))
		{
			guess_words->remove(i);
		}
		i++;
		
	}
	
 }
int Password::getNumberOfPasswordsLeft()
 {
	int num_viable = viable_words->size();
	return num_viable;
 }
String* Password::getOriginalWord(int index)
{
	CSC2110::String* Og_word = all_words->get(index);
	return Og_word;
}


void Password::displayViableWords()
{
	
	ListArrayIterator<String>* temp_iter = viable_words->iterator();
	while(temp_iter->hasNext())
	{
		CSC2110::String* temp = temp_iter->next();
		temp->displayString();
	}	
}

 int Password::getNumMatches(String* curr_word, String* word_guess)
	{
		int matches=0;
			
		for(int x=0;x<len;x++)
		{
			
			if(curr_word->compare(word_guess)) 
				{
					matches++;
				}
			
		}
		return matches;
	}
int Password::bestGuess()
{
   int best_guess_index = -1;
   int best_num_eliminated = -1;
   int num_viable_passwords = getNumberOfPasswordsLeft();

   //loop over ALL words, even if they have been eliminated as the password
   int count = 1;
   ListArrayIterator<String>* all_iter = all_words->iterator();
   while(all_iter->hasNext())
   {
      CSC2110::String* original_word = all_iter->next();

      //loop over only those words that could still be the password
      //count up the number of matches between a possible password and a word in the original list
      int* count_num_matches = new int[len + 1];

      for (int i = 0; i < len; i++) 
      {
         count_num_matches[i] = 0;
      }

      ListArrayIterator<String>* viable_iter = viable_words->iterator();
      while(viable_iter->hasNext())
      {
         CSC2110::String* viable_word = viable_iter->next();
         int num_matches = getNumMatches(viable_word, original_word);
         count_num_matches[num_matches]++;
      }
      delete viable_iter;

      //find the largest number in the count_num_matches array
      //the largest number indicates the guess that will generate the most eliminations
      int most_num_matches = 0;
      for (int j = 0; j < len; j++) 
      {
         int curr_num_matches = count_num_matches[j];
         if (curr_num_matches > most_num_matches)
         {
            most_num_matches = curr_num_matches;
         }
      }

      //compute the fewest that can possibly be eliminated by guessing the current word (original list)
      int num_eliminated = num_viable_passwords - most_num_matches;

      //select the word to guess that maximizes the minimum number of eliminations (minimax)
      if (num_eliminated > best_num_eliminated)
      {
         best_num_eliminated = num_eliminated;
         best_guess_index = count;
      }
      
      count++;
      delete[] count_num_matches;
   }

   delete all_iter;
   return best_guess_index;  //return a 1-based index into the all_words list of words (careful)
}
