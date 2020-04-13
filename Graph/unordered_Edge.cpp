#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <cassert>
#include <functional>
#include <algorithm>
#include "Graph.h"

namespace TyutkoMath {
	unorderedEdge::unorderedEdge(int from, int to) : base_Edge(std::min(from, to), std::max(from, to)) {}
	unorderedEdge::unorderedEdge(unorderedEdge const& edge) : base_Edge(edge.from, edge.to) {}

	unorderedEdge& unorderedEdge::operator=(unorderedEdge const& source)
	{
		from = source.from;
		to = source.to;
		return *this;
	}
	bool unorderedEdge::operator<(unorderedEdge const& toCompare) const
	{
		if (this->from < toCompare.from) return true;
		if (this->from == toCompare.from
			&& this->to < toCompare.to) return true;
		return false;
	}
	bool unorderedEdge::operator>(unorderedEdge const& toCompare) const
	{
		if (this->from > toCompare.from) return true;
		if (this->from == toCompare.from
			&& this->to > toCompare.to) return true;
		return false;
	}
	bool unorderedEdge::operator==(unorderedEdge const& toCompare) const
	{
		return to == toCompare.to
			&& from == toCompare.from;
	}


	bool unorderedEdge::ifBounds(const topKey a, const  topKey b) const
	{
		return (from == b && to == a || from == a && to == b);
	}
	bool unorderedEdge::ifProvideTheSameWay(base_Edge const& toCompare) const
	{
		return this->from == toCompare.from && this->to == toCompare.to
			|| this->to == toCompare.from && this->from == toCompare.to;
	}
	std::pair<orderedEdge, orderedEdge> unorderedEdge::getCutted() const
	{

		return std::make_pair(
		orderedEdge(this->from, this->to)
		,orderedEdge(this->to, this->from) );
	}

	std::string unorderedEdge::ToString() const
	{
		return  std::string("from: " + std::to_string(from) + " to: " + std::to_string(to) + std::string(" and back"));
	}
}