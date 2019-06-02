/* Ali Masarwe 207907171 */
//
// Created by Ali Masarweh on 4/17/2019.
//

#pragma once

#ifndef _EDITOR_H_
#define _EDITOR_H_

#include <algorithm>
#include "Document.h"

using namespace std;

class Editor {
private:
	Document doc;
	bool is_number(const string & s);
	vector<string> split(const string & s, char delimiter);

public:
	Editor();
	void loop();
};

#endif // !_EDITOR_H_
