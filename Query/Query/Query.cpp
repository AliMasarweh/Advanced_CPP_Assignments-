/*
Ali Masarwe		207907171
*/

#include "Query.h"
#include "TextQuery.h"
#include <memory>
#include <set>
#include <algorithm>
#include <iostream>
#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <regex>
#include <cctype>
using namespace std;
////////////////////////////////////////////////////////////////////////////////
std::shared_ptr<QueryBase> QueryBase::factory(const string& s)
{
	regex words_regex("[\\w']+");
	regex not_words_regex("NOT[\\s]+[\\w']+");
	regex binary_words_regex("[\\w']+[\\s]+[\\w']+[\\s]+[\\w']+");
	regex and_words_regex("[\\w']+[\\s]+AND[\\s]+[\\w']+");
	regex or_words_regex("[\\w']+[\\s]+OR[\\s]+[\\w']+");
	regex num_words_regex("[\\w']+[\\s]+[\\d]+[\\s]+[\\w']+");
	smatch result;
	if (regex_search(s, result, not_words_regex)) {
		istringstream line(result[0]);
		string word;
		for (size_t i = 0; i < 2; i++)
		{
			line >> word;
		}
		return shared_ptr<QueryBase>(new NotQuery(word));
	}
	else if (regex_search(s, result, binary_words_regex)) {
		istringstream line(result[0]);
		string words[3];
		for (size_t i = 0; i < 3; i++)
		{
			line >> words[i];
		}
		int num = 0;
		if (regex_search(s, result, and_words_regex))
			return shared_ptr<QueryBase>(new AndQuery(words[0], words[2]));
		else if (regex_search(s, result, or_words_regex))
			return shared_ptr<QueryBase>(new OrQuery(words[0], words[2]));
		else if (regex_search(s, result, num_words_regex))
			return shared_ptr<QueryBase>(new NQuery(words[0], words[2], stoi(words[1])));
		else 
			throw invalid_argument("Unrecognized search");
	}
	else if (regex_search(s, result, words_regex)) {
		return shared_ptr<QueryBase>(new WordQuery(result[0]));
	}

	else
	{
		throw invalid_argument("Unrecognized search");
	}

	// if(s == "smart") return std::shared_ptr<QueryBase>(new WordQuery("smart"));
}


/*bool isinteger(std::string const& n)
{
	if (std::isdigit(n[0]) || (n.size() > 1 && (n[0] == '-' || n[0] == '+')))
	{
		for (std::string::size_type i{ 1 }; i < n.size(); ++i)
			if (!std::isdigit(n[i]))
				return false;

		return true;
	}
	return false;
}*/
////////////////////////////////////////////////////////////////////////////////
QueryResult NotQuery::eval(const TextQuery &text) const
{
	QueryResult result = text.query(query_word);
	auto ret_lines = std::make_shared<std::set<line_no>>();
	auto beg = result.begin(), end = result.end();
	auto sz = result.get_file()->size();

	for (size_t n = 0; n != sz; ++n)
	{
		if (beg == end || *beg != n)
			ret_lines->insert(n);
		else if (beg != end)
			++beg;
	}
	return QueryResult(rep(), ret_lines, result.get_file());

}

QueryResult AndQuery::eval(const TextQuery& text) const
{
	QueryResult left_result = text.query(left_query);
	QueryResult right_result = text.query(right_query);

	auto ret_lines = std::make_shared<std::set<line_no>>();
	std::set_intersection(left_result.begin(), left_result.end(),
		right_result.begin(), right_result.end(),
		std::inserter(*ret_lines, ret_lines->begin()));

	return QueryResult(rep(), ret_lines, left_result.get_file());
}

QueryResult OrQuery::eval(const TextQuery &text) const
{
	QueryResult left_result = text.query(left_query);
	QueryResult right_result = text.query(right_query);

	auto ret_lines =
		std::make_shared<std::set<line_no>>(left_result.begin(), left_result.end());

	ret_lines->insert(right_result.begin(), right_result.end());

	return QueryResult(rep(), ret_lines, left_result.get_file());
}
/////////////////////////////////////////////////////////
QueryResult NQuery::eval(const TextQuery &text) const
{
	QueryResult left_result = text.query(left_query);
	QueryResult right_result = text.query(right_query);

	auto file = left_result.get_file();


	auto ret_lines = std::make_shared<std::set<line_no>>();
	std::set_intersection(left_result.begin(), left_result.end(),
		right_result.begin(), right_result.end(),
		std::inserter(*ret_lines, ret_lines->begin()));
	auto ans = std::make_shared<std::set<line_no>>();
	regex words_regex("[\\w']+");
	smatch result;
	for (auto it = ret_lines->begin(); it != ret_lines->end();it++) {
		string row = file->at(*it);
		istringstream line(row);
		bool less_than_dist = false;
		int tmp = dist;
		string word;
		while (line >> word && !less_than_dist) {
			regex_search(word, result, words_regex);
			word = result[0];
			if (word == left_query) {
				while (tmp >= 0) {
					if (line >> word) {
						regex_search(word, result, words_regex);
						word = result[0];
						if (word == right_query) {
							less_than_dist = true;
							break;
						}
					}
					tmp--;
				}
			}
			else if (word == right_query) {
				while (tmp >= 0) {
					if (line >> word) {
						regex_search(word, result, words_regex);
						word = result[0];
						if (word == left_query) {
							less_than_dist = true;
							break;
						}
					}
					tmp--;
				}
			}
			tmp = dist;
		}
		if (less_than_dist) {
			ans->insert(*it);
		}
	}
	return QueryResult(rep(), ans, left_result.get_file());
}
/////////////////////////////////////////////////////////