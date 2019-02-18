///////////////////////////////////////////////////////////////////////////////
// project1.hh
//
// The three algorithms specified in the project 1 requirements
// document, plus helper functions.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>

// Convenient typedef for a vector of strings.
typedef std::vector<std::string> string_vector;

// Load words from the file at the given path. The words vector is
// cleared, and then each word from the file is added to the
// vector. Returns true on success or fale on I/O error.
bool load_words(string_vector& words, const std::string& path) {
	std::string str1;
	words.clear();

	// TODO: implement this function, then delete this comment


	std::ifstream f(path);
	if (f.is_open()) {
		while (std::getline(f, str1)) {
			words.push_back(str1);
		}

		return true;
	}


	return false;

}

// Return true if string2 is a mirrored copy of string1, or false
// otherwise. In other words, return true if string1 is the reverse of
// string2. Return false when both strings are equal; by this rule,
// "aaa" is not a mirror of "aaa" even though they are technically the
// reverse of each other. Likewise "" is not a mirror of "". This
// function should be in-place, meaning that it only examines string1
// and string2 and never creates another string object.
bool is_mirrored(const std::string& string1, const std::string& string2) {
	int i = 0;
	int n = string2.size() - 1;
	
	if (string1 != string2) {
		while (i < string1.size() || n >= 0 ){
			if (string1[i] != string2[n]) {
				
				return false;
			}
			i++;
			n--;

		}
		return true;
	}

	return false;
}

// Return true if alleged_substring can be found as a substring of
// alleged_superstring. For example, "cat" is a substring of
// "catamaran"; "tama" is also a substring of "catamaran". This
// function should be in-place, meaning that it only examines string1
// and string2 and never creates another string object.
bool is_substring(const std::string& alleged_substring,
	const std::string& alleged_superstring) {
		
	if (alleged_superstring.find(alleged_substring) != std::string::npos)
		return true;
	return false;
}

// Return the character that occurs the most times in the given vector
// of strings. The vector must contain at least one character, so that
// the mode is defined. In the event of a tie (i.e. two characters
// have the same count), this function returns the tied character with
// the lesser ASCII code (i.e. the tied character that comes first in
// conventional alphabetical order).
char character_mode(const string_vector& strings) {
	int highest = 0;
	int highest_index;
	int counts[256] = { 0 }; //initialize array with zeroes
	for (int i = 0; i < strings.size(); i++) { //for each string in strings

		for (char c : strings[i]) {//for each char in string
			counts[(int)c]++; //increment 1 for every char found
		}

	}
	//find which char appears the most
	for (int i = 0; i < 256; i++) { 
		if (highest <= counts[i]) {
			highest = counts[i]; //assign highest value to current value
			highest_index = i;	//assign current index to the result


		}
	}



	return (char)highest_index;
}

// Return a longest string in the strings vector whose mirror is also
// in the vector. Strings are mirrors of each other in the same sense
//[ as described above for the is_mirrored(...) function. Either of the
// two mirrored strings may be returned; for example, if the vector
// contains both "cat" and "tac", this function is allowed to return
// either "cat" or "tac". If the vector contains no mirrored strings,
// returns an empty string.
std::string longest_mirrored_string(const string_vector& strings) {
	std::string best = ""; //empty string
	if (strings.empty()) {
		return "";
	}
	//nested for loop 
	for (int i = 0; i < strings.size(); i++) {
		for (int j = i + 1; j < strings.size(); j++) {
			std::string r = strings[j];//assign a string object to every string after the string being compared to
			reverse(r.begin(), r.end()); //swap the contents of the string 

			//check to see if mirrored, if so, determine if it is the longest mirrored string
			if (strings[i] == r) {
				if (best.size() < strings[i].size()) { 
					best = strings[i]; 
					break;
				}


			}
		}
	}

	
	return best;
}

// Return a vector of length exactly three, containing the longest
// substring trio from the string vector. A substring trio is three
// non-empty, distinct, strings a, b, and c such that a is a substring
// of b, b is a substring of c. This function returns the substring
// trio with the longest total length of a, b, and c. If the input
// vector does not contain a substring trio, return a vector
// containing exactly three empty strings.
string_vector longest_substring_trio(const string_vector& strings) {
	
	string_vector trio(3, ""); // a vector of 3 empty strings
	
	int best_length = 0;//assign 0 before comparing with the length of string subsets
	

	for (int i = 0; i < strings.size(); i++) {
		bool jump_back = false; //found1 is go to false every outer loop iteration


		for (int j = 0; j < strings.size(); j++) {

			if (jump_back == true) //go back to outer loop
				break;
			//determine if the string is a subset of the superstring
			if (strings[j].find(strings[i]) != std::string::npos && strings[j] != strings[i]) {
				
				for (int k = 0; k < strings.size(); k++) {

					if (strings[k].find(strings[j]) != std::string::npos && strings[k] != strings[j]) {
						int length = strings[k].size() + strings[j].size() + strings[i].size(); //add all the string sizes
						if (best_length < length) {
							best_length = length;
							trio[0] = strings[i]; //assign shortest substring to first index
							trio[1] = strings[j];
							trio[2] = strings[k];
							jump_back = true; //assign true to go back to outer loop
						}

					}
					else if (k == strings.size() - 1) //if loop doesn't find any matching subsets go back to outerloop
						jump_back = true;
				}


			}

		}
	}

	return trio;

}