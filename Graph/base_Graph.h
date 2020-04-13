#pragma once
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <cassert>
#include <functional>
#include <algorithm>
#include "Edges.h"

//namespace TyutkoMath {
//	typedef int topKey;
//	typedef unsigned char byte;
//
//	template<class EdgeType>
//	class base_Graph
//	{
//	protected:
//		std::map<topKey, std::string> tops;
//		std::multiset<EdgeType> edges;
//		std::multiset<EdgeType>::const_iterator FindEdgeIter(EdgeType const& toCompare) const
//		{
//			return edges.find(toCompare);
//		}
//
//		base_Graph<EdgeType>()
//			:tops()
//			, edges()
//		{}
//		base_Graph<EdgeType>(base_Graph<EdgeType> const& source)
//			:tops(source.tops)
//			, edges(source.edges)
//		{}
//		base_Graph<EdgeType>(base_Graph<EdgeType>&& source)
//			:tops(std::move(source.tops))
//			, edges(std::move(source.edges))
//		{
//			source = base_Graph<EdgeType>();
//		}
//		base_Graph<EdgeType>& operator=(base_Graph<EdgeType> const& source)
//		{
//			*this = base_Graph<EdgeType>(source);
//		}
//		base_Graph<EdgeType>& operator=(base_Graph<EdgeType>&& source)noexcept
//		{
//			tops = std::move(source.tops);
//			edges = std::move(source.edges);
//			source = base_Graph<EdgeType>();
//		}
//
//		bool operator<(base_Graph<EdgeType> const& toCompare) = delete;
//		bool operator<=(base_Graph<EdgeType> const& toCompare) = delete;
//		bool operator>(base_Graph<EdgeType> const& toCompare) = delete;
//		bool operator>=(base_Graph<EdgeType> const& toCompare) = delete;
//		bool operator==(base_Graph<EdgeType> const& toCompare) = delete;
//
//		bool isSubGraph(base_Graph<EdgeType> const& toCompare) const
//		{
//			for (auto CompareEdge : toCompare.edges)
//				if (edges.find(CompareEdge) == edges.end())
//					return false;
//			return true;
//		}
//		bool isOverGraph(base_Graph<EdgeType> const& toCompare) const
//		{
//			for (auto CompareEdge : this->edges)
//				if (toCompare.edges.find(CompareEdge) == edges.end())
//					return false;
//			return true;
//		}
//		bool isEqualTo(base_Graph<EdgeType> const& toCompare) const
//		{
//			return this->isSubGraph<(toCompare) && this->isOverGraph>(toCompare);
//		}
//
//
//
//
//	};
//
//}