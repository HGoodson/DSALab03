#if !defined PASSWORD_H
#define PASSWORD_H

# include "ListArray.h"
# include "Text.h"
using namespace CSC2110;

//complete the includes

class Password
{
   private:
      ListArray<String>* viable_words;  //the list of words that can still be the password
      ListArray<String>* all_words;  //the original list of words
      int len;  //the length of the first word entered is stored to check that all subsequent words have the same length

      //a private helper method to report the number of character matches between two Strings
      int getNumMatches(String* curr_word, String* word_guess);

   public:
	   Password();
	   ~Password();
	   //preconditions: words must be same length 
	   //				1st word sets standard for word length
	   //postconditions: words that break the mold are skipped over
	   void addWord(String* word);
	   //preconditions: (1-Based)
	   //postconditions: viable_words now points to a smaller list
	   void guess(int try_password,int num_matches);
	   int getNumberOfPasswordsLeft();
	   int bestGuess();
	   String* getOriginalWord(int index);
       void displayViableWords();
	   
};

#endif
