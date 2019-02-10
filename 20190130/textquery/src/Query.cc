/// @file    Query.cc
/// @data    2019-02-02 10:49:56
 
#include "Query.h"
#include "TextQuery.h"
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <memory>
#include <iterator>
#include <algorithm>

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::shared_ptr; 
using std::vector;
using std::set;
using std::inserter; 
using std::set_intersection;
 
Query::Query(const string &word)
: _query(new WordQuery(word))
{}

Query::Query(std::shared_ptr<Query_base> query)
: _query(query)
{}

std::ostream &operator<<(std::ostream &os, const Query &query) {
    return os << query.rep(); 
}

string Query::rep() const {
    return _query->rep();
}

QueryResult Query::eval(const TextQuery &tq) const {
    return _query->eval(tq);
}

WordQuery::WordQuery(const std::string &s)
: _word(s)
{}

string WordQuery::rep() const {
    return _word;
}

QueryResult WordQuery::eval(const TextQuery &tq) const {
    return tq.query(_word);
}

NotQuery::NotQuery(const Query &query)
: _query(query) 
{}

QueryResult NotQuery::eval(const TextQuery& tq) const {
    QueryResult result = _query.eval(tq);

    shared_ptr<set<line_no> > ret_lines(new set<line_no>);

	QueryResult::line_it beg = result.begin(), end = result.end();

	vector<string>::size_type sz = result.get_file()->size();
    for (size_t n = 0; n != sz; ++n) {
		if (beg == end || *beg != n) 
			ret_lines->insert(n);
		else if (beg != end) 
			++beg;
	}
	return QueryResult(rep(), ret_lines, result.get_file());
}

string NotQuery::rep() const {
    return "~(" + _query.rep() + ")";
}

Query operator~(const Query &operand) {
    return shared_ptr<Query_base>(new NotQuery(operand));
}

BinaryQuery::BinaryQuery(const Query &lhs, const Query &rhs, const string oprand) 
: _lhs(lhs)
, _rhs(rhs)
, _opSym(oprand)
{}

string BinaryQuery::rep() const 
{ 
    return "(" + _lhs.rep() + " "  + _opSym + " " + _rhs.rep() + ")";
}

AndQuery::AndQuery(const Query &left, const Query &right)
: BinaryQuery(left, right, "&") 
{}

QueryResult AndQuery::eval(const TextQuery& tq) const {
    QueryResult left = _lhs.eval(tq), right = _rhs.eval(tq);
    shared_ptr<set<line_no>> newLines(new set<line_no>);  
    set_intersection(left.begin(), left.end(), 
                   right.begin(), right.end(),
                   inserter(*newLines, newLines->begin()));

    return QueryResult(rep(), newLines, left.get_file());
}

Query operator&(const Query &lhs, const Query &rhs) {
    return shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

OrQuery::OrQuery(const Query &lhs, const Query &rhs)
: BinaryQuery(lhs, rhs, "|") 
{}

QueryResult OrQuery::eval(const TextQuery& tq) const {
    QueryResult right = _rhs.eval(tq), left = _lhs.eval(tq);  

	shared_ptr<set<line_no>> newLines(new set<line_no>(left.begin(), left.end()));

	newLines->insert(right.begin(), right.end());
    return QueryResult(rep(), newLines, left.get_file());
}

Query operator|(const Query &lhs, const Query &rhs)
{
    return shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}
