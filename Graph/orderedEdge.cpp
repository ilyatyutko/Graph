#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <cassert>
#include <functional>
#include <algorithm>
#include "base_Graph.h"

namespace TyutkoMath {
	
	orderedEdge& orderedEdge::reverse()
	{
		std::swap(from, to);
		return *this;
	}
	orderedEdge orderedEdge::GetReversed() const
	{
			orderedEdge tmp(*this);
			std::swap(tmp.from, tmp.to);
			return tmp;
	}
	orderedEdge orderedEdge::GetGeneralized() const
	{
		return unorderedEdge(from,to);
	}

	orderedEdge::orderedEdge(int from, int to) : base_Edge(from, to) {};
	orderedEdge::orderedEdge(base_Edge const& edge) : base_Edge(edge.from, edge.to) {};

	orderedEdge& orderedEdge::operator=(orderedEdge const& source)
	{
		from = source.from;
		to = source.to;
		return *this;
	}
	bool orderedEdge::operator<(orderedEdge const& toCompare) const
	{
		if (this->from < toCompare.from) return true;
		if (this->from == toCompare.from
			&& this->to < toCompare.to) return true;
		return false;
	}
	bool orderedEdge::operator>(orderedEdge const& toCompare) const
	{
		if (this->from > toCompare.from) return true;
		if (this->from == toCompare.from
			&& this->to > toCompare.to) return true;
		return false;
	}
	bool orderedEdge::operator==(orderedEdge const& toCompare) const
	{
		return to == toCompare.to
			&& from == toCompare.from;
	}

	bool orderedEdge::ifBounds(const topKey a, const  topKey b) const
	{
		return from == a && to == b;
	}
	bool orderedEdge::ifProvideTheSameWay(unorderedEdge const& toCompare) const
	{
		return this->from == toCompare.from && this->to == toCompare.to
			|| this->to == toCompare.from && this->from == toCompare.to;
	}
	bool orderedEdge::ifProvideTheSameWay(orderedEdge const& toCompare) const
	{
		return this->from == toCompare.from && this->to == toCompare.to;
	}
	bool orderedEdge::wentOutFrom(topKey top)const
	{
		return top == this->from;
	}
	bool orderedEdge::wentInTo(topKey top)const
	{
		return top == this->to;
	}

	std::string orderedEdge::ToString() const
	{
		return  std::string("from: " + std::to_string(from) + " to: " + std::to_string(to));
	}
}