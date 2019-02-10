/// @file    Query.h
/// @data    2019-02-02 10:42:14
 
#ifndef __QUERY_H__
#define __QUERY_H__
    
#include "TextQuery.h"
#include <memory>
#include <string>

class Query_base {
    friend class Query;  
protected:
    typedef TextQuery::line_no line_no;
    virtual ~Query_base() { }
private:
    virtual QueryResult eval(const TextQuery&) const = 0; 
	virtual std::string rep() const = 0;
};

class Query {
    friend Query operator~(const Query &);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
public:
    Query(const std::string&);
    
    QueryResult eval(const TextQuery&) const; 
	std::string rep() const;
private:
    Query(std::shared_ptr<Query_base>);
    std::shared_ptr<Query_base> _query;
};

std::ostream &operator<<(std::ostream &, const Query &);

class WordQuery
: public Query_base
{
    friend class Query;
    WordQuery(const std::string &s);

    QueryResult eval(const TextQuery &t) const;
	std::string rep() const;

    std::string _word; 
};

class NotQuery
: public Query_base
{
    friend Query operator~(const Query &);
    NotQuery(const Query &);

	std::string rep() const;
    QueryResult eval(const TextQuery&) const;

    Query _query;
};

class BinaryQuery
: public Query_base
{
protected:
    BinaryQuery(const Query &, const Query &, std::string); 
	std::string rep() const; 

    Query _lhs, _rhs;
    std::string _opSym; 
};

class AndQuery
: public BinaryQuery 
{
    friend Query operator&(const Query&, const Query&);
    AndQuery(const Query &, const Query &);

    QueryResult eval(const TextQuery&) const;
};

class OrQuery: public BinaryQuery {
    friend Query operator|(const Query&, const Query&);
    OrQuery(const Query &, const Query &); 

    QueryResult eval(const TextQuery&) const;
};

#endif
