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
	base_Edge::base_Edge(topKey _from
		, topKey _to)
		:from(_from)
		, to(_to)
	{
		assert(_from >= 0);
		assert(_to >= 0);
	}
	base_Edge::base_Edge(base_Edge const& source)
		:from(source.from)
		, to(source.to)
	{}
	bool base_Edge::isLoop()const
	{
		return from == to;
	}
	bool base_Edge::isIncidentTo(topKey top)const
	{
		return from == top || top == to;
	}
	std::pair<topKey, topKey> base_Edge::GetIncidentTops()const
	{
		return std::make_pair(from, to);
	}
}