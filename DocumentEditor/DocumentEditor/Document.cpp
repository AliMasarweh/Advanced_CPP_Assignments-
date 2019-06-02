/* Ali Masarwe 207907171 */
//
// Created by Ali Masarweh on 4/17/2019.
//


#include "Document.h"

Document::Document()
{
	current_line = 0;
	_size = 0;
	is_empty = true;
}

void Document::append(string input)
{
	if (is_empty) {
		_data.push_back(input);
		is_empty = false;
	}
	else {
		//if (_data.size() == _size) { _data.resize(_data.size() + 1); }
		_data.insert(_data.begin() + (++current_line), input);
	}
	_size++;
}

void Document::insert(string input)
{
	if (is_empty) {
		_data.push_back(input);
		is_empty = false;
	}
	else {
		//if (_data.size() == _size) {_data.resize(_data.size() + 1);}
		_data.insert(_data.begin() + (current_line++), input);
	}
	_size++;
}

string & Document::get_current_line()
{
	return _data[current_line];
}

void Document::set_current_line(int new_line)
{
	current_line = new_line % _data.size();
}

int Document::num_of_line() const
{
	return current_line;
}


void Document::replace_current_line(const string &  data)
{
	_data[current_line] = data;
}

void Document::delete_current_line()
{
	_data.erase(_data.begin() + current_line);
	this->set_current_line(current_line - 1);
}

int Document::search_for(const string & str)
{
	for (int i = 0; i < _data.size(); i++) {
		if (_data[(current_line + i) % _data.size()].find(str) != string::npos) {
			current_line = (current_line + i) % _data.size();
			return (current_line + i) % _data.size();
		}
	}
	return -1;
}

bool Document::empty()
{
	return is_empty;
}

void Document::print_all() const
{
	for (auto i = _data.begin(); i != _data.end(); i++)
		cout << *i << endl;
}