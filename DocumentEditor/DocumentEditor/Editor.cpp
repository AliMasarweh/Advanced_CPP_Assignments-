/* Ali Masarwe 207907171 */
//
// Created by Ali Masarweh on 4/17/2019.
//

#include "Editor.h"
#include <sstream>

/* Initliazes a vector of the file to be edited */

Editor::Editor()
{
	doc = Document();
}

void Editor::loop()
{
	string input;
	while (getline(cin,input)) {
		//Quit
		if (input.compare("Q") == 0) {
			return;
		}
		//Print
		else if (input.compare("p") == 0) {
			cout << doc.get_current_line() << endl;
		}
		//Print current line %tab current line
		else if (input.compare("n") == 0) {
			cout << doc.num_of_line()+1 << /*Chech how to tab */ "\t" << doc.get_current_line() << endl;
		}
		//Print all lines
		else if (input.compare("%p") == 0) {
			doc.print_all();
		}
		//is number
		else if (is_number(input)) {
			doc.set_current_line(stoi(input)-1);
			cout << doc.get_current_line() << endl;
		}
		//Append next to the line
		else if (input == "a") {
			getline(cin, input);
			while (input != ".") {
				doc.append(input);
				getline(cin, input);
			}
		}
		//Insert before the line
		else if (input == "i") {
			getline(cin, input);
			while (input != ".") {
				doc.insert(input);
				getline(cin, input);
			}
		}
		//Change line to the after c
		else if (input == "c") {
			getline(cin, input);
			while (input != ".") {
				doc.replace_current_line(input);
				getline(cin, input);
			}
		}
		//Delete this line
		else if (input.compare("d") == 0) {
			doc.delete_current_line();
		}
		//Search for text after 
		else if (input.at(0) == '/') {
			int indx = -1;
			if((indx = doc.search_for(input.substr(1, input.size()))!= -1))
				cout << doc.get_current_line() << endl;
		}
		// Replace with this format /to_be_replace/to_replace
		else if (input.substr(0,2).compare("s/") == 0) {
			input = input.substr(2, input.size());
			vector<string> results = split(input, '/');
			if (results.size() >= 2) {
				int line_of_old = doc.search_for(results[0]);
				if (line_of_old != -1) {
					doc.set_current_line(line_of_old);
					//Replacing the part of result[0] to results[1]
					doc.get_current_line().replace(
						doc.get_current_line().find(results[0])
						, results[0].length(), results[1]);
				}
			}
		}
	}
}

/* returns true if the string consist of number in Z (no fraction or irrationals) */
bool Editor::is_number(const string& s)
{
	return !s.empty() && find_if(s.begin(),
		s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

/* Splits the string by the given iterator */
vector<string> Editor::split(const string& s, char delimiter)
{
	vector<string> tokens;
	string token;
	istringstream tokenStream(s);
	while (getline(tokenStream, token, delimiter))
	{
		if (token != "") {
			tokens.push_back(token);
		}
	}
	return tokens;
}