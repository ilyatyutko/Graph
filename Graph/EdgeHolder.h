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

namespace TyutkoMath {
	namespace GraphType
	{
		class base_GraphType
		{
		public:
			virtual inline bool hasLoops()const = 0;
			virtual inline bool hasMultiEdges() const = 0;
		};
		class Graph :public base_GraphType
		{
			virtual inline bool hasLoops()const override
			{
				return false;
			}
			virtual inline bool hasMultiEdges() const override
			{
				return false;
			}
		};
		class MultiGraph :public base_GraphType
		{
			virtual inline bool hasLoops()const override
			{
				return false;
			}
			virtual inline bool hasMultiEdges() const override
			{
				return true;
			}
		};
		class Pseudo :public base_GraphType
		{
			virtual inline bool hasLoops()const override
			{
				return false;
			}
			virtual inline bool hasMultiEdges() const override
			{
				return false;
			}
		};
	}

	template<class EdgeType, class GraphType>
	class EdgeHolder
	{
	protected:
		topKey from;
		topKey to;
		std::multiset<EdgeType> edges;
		GraphType type;
		inline bool isValudEdgeType()const 
		{ return dynamic_cast<base_Edge>(EdgeType(0,0)) != nullptr; }
		inline bool isValudGraphType()const 
		{ return dynamic_cast<GraphType::base_GraphType>(type) != nullptr; }
		inline bool isValid()const
		{
			return isValudEdgeType() && isValudGraphType();
		}

		inline bool isValidEdgeToInsert()const
		{}
			
	public:
		EdgeHolder<EdgeType, GraphType>(topKey from, topKey to, std::list<EdgeType> const& source)
			:from(from)
			,to(to)
			, edges(source)
		{
			std::assert(isValid());
		}
		EdgeHolder<EdgeType, GraphType>(topKey from, topKey to, std::list<EdgeType>&& source)
			: from(from)
			, to(to)
			, edges(std::move(source))
		{
			std::assert(isValid());
		}

		void InsertEdge(EdgeType const& edge)
		{
			if (this->isEmpty())
			{
			}
			else
			{
				if (edge.isLoop() && type.isPseudoHolder())
					this->edges.insert(edge);
				else if (type.isMultiHolder())
					this->edges.insert(edge);
			}
		}
		void RemoveEachEdge();
		void RemoveEdge(EdgeType const& edge);
		void RemoveMaxEdge();
		void RemoveMinEdge();

		std::multiset<EdgeType> GetEachEdge() const;
		EdgeType GetMaxEdge() const;
		EdgeType GetMinEdge() const;

		bool isEmpty();
		bool ifContains(EdgeType const& edge);
		inline bool isMultiHolder()const
		{
			return type.hasMultiEdges();
		}
		inline bool isPseudoHolder()const
		{
			return type.hasLoops();
		}

	};
}
