/* Ali Masarwe 207907171 */
//
// Created by Ali Masarweh on 4/17/2019.
//

#pragma once

#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Document {
private:
	vector<string> _data;
	int current_line;
	int _size;
	bool is_empty;


public:
	/* The cconstructor */
	Document();
	/* Appends lines to the current line in the vector */
	void append(string);
	/* Inserts lines before the current line in the vector */
	void insert(string);
	/* Retuns the string in the vector at the current line */
	string& get_current_line();
	/* Prints all the strings in the vector */
	void print_all() const;
	/* Sets the current line ot the (input argument % size) */
	void set_current_line(int);
	/* Returns the number of the current line */
	int num_of_line() const;
	/* Replaces the current line to the input argument */
	void replace_current_line(const string&);
	/* Deletes the current line */
	void delete_current_line();
	/* Searchs for the input argument in the vector */
	int search_for(const string&);
	/* Returns true if the vector is empty */
	bool empty();
};
#endif // !_DOCUMENT_H_
