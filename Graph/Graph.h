#pragma once
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <cassert>



namespace TyutkoMath {
	typedef int topKey;
	typedef unsigned char byte;


	template <class EdgeValue>
	class Edge
	{
	private:
		topKey from;
		topKey to;
		bool isBidirectional;
		EdgeValue value;
		Edge<EdgeValue>();
	public:
		Edge<EdgeValue>(topKey _from
			, topKey _to
			, EdgeValue _value = EdgeValue()
			, bool _isBidirectional = true)
			:from(_from)
			, to(_to)
			, isBidirectional(_isBidirectional)
			, value(_value)
		{
			assert(_from >= 0);
			assert(_to >= 0);
			if (from > to && isBidirectional)
				std::swap(from, to);
		}
		Edge<EdgeValue>(Edge const& source)
			:from(source.from)
			, to(source.to)
			, isBidirectional(source.isBidirectional)
			, value(source.value)
		{}
		Edge<EdgeValue>(Edge&& source) noexcept
			:from(source.from)
			, to(source.to)
			, isBidirectional(source.isBidirectional)
			, value(std::move(source.value))
		{
			source.value = EdgeValue();
		}

		Edge<EdgeValue>& operator=(Edge<EdgeValue> const& source)
		{
			from = source.from;
			to = source.to;
			isBidirectional = source.isBidirectional;
			value = EdgeValue(source.value);
		}
		Edge<EdgeValue>& operator=(Edge<EdgeValue>&& source)
		{
			from = source.from;
			to = source.to;
			isBidirectional = source.isBidirectional;
			value = std::move(source.value);
			source.value = EdgeValue();
		}


		bool operator<(Edge<EdgeValue> const& toCompare) const
		{
			return (from < toCompare.from) ? true :
				(from == toCompare.from) ? to < toCompare.to : false;
		}
		bool operator>(Edge<EdgeValue> const& toCompare) const
		{
			return (from > toCompare.from) ? true :
				(from == toCompare.from) ? to > toCompare.to : false;
		}
		bool operator==(Edge<EdgeValue> const& toCompare) const
		{
			bool b = (from == toCompare.from)
				&& (to == toCompare.to)
				&& (isBidirectional == toCompare.isBidirectional)
				&& (value == toCompare.value);
			return b;
		}
		bool lowerWayThan(Edge<EdgeValue> const& toCompare) const
		{
			if (this->provideTheSameWay(toCompare))
				return value < toCompare.value;
			return false;
		}
		bool UpperWayThan(Edge<EdgeValue> const& toCompare)const
		{
			if (this->provideTheSameWay(toCompare))
				return value > toCompare.value;
			return false;
		}

		bool bounds(topKey a, topKey b) const
		{
			if (from == a && to == b)
				return true;
			if (isBidirectional)
				return (from == b && to == a);
			return false;
		}

		bool provideTheSameWay(Edge<EdgeValue> const& toCompare) const
		{
			Edge<EdgeValue> rev = toCompare.GetReversed();
			return (from == toCompare.from)
				&& (to == toCompare.to)
				|| (from == rev.from)
				&& (to == rev.to);
		}

		template<class EdgeValue>
		struct CmpLexicographLess
		{
			bool operator()(Edge<EdgeValue> const& a, Edge<EdgeValue> const& b)
			{
				return (a.from < b.from) ? true :
					(a.from == b.from) ? a.to < b.to : false;
			}
		};
		template<class EdgeValue>
		struct CmpLexicographMore
		{
			bool operator()(Edge<EdgeValue> const a, Edge<EdgeValue> const& b)
			{
				return (a.from > b.from) ? true :
					(a.from == b.from) ? a.to > b.to : false;
			}
		};

		template<class EdgeValue>
		struct CmpProvideTheSameWayTo
		{
			Edge<EdgeValue> toCompare;
			CmpProvideTheSameWayTo(Edge<EdgeValue> const& b)
				:toCompare(b)
			{}


			bool operator()(Edge const& a)
			{
				return toCompare.provideTheSameWay(a);
			}
		};

		std::string ToString() const
		{
			return std::string("from: " + std::to_string(from) + " to: " + std::to_string(to));
		}
		std::list<Edge<EdgeValue>> cut() const
		{
			if (isBidirectional)
			{
				Edge<EdgeValue> tmp(*this);
				tmp.isBidirectional = false;
				return std::list<Edge<EdgeValue>>{ tmp, tmp.reversed()};
			}
			else
				return std::list<Edge<EdgeValue>> {*this};
		}
		Edge<EdgeValue>& generalize()
		{
			isBidirectional = true;
			if (from > to)
				std::swap(from, to);
			return *this;
		}
		Edge<EdgeValue> GetGeneralized() const
		{
			Edge<EdgeValue> tmp(*this);
			tmp.isBidirectional = true;
			if (from > to)
				std::swap(tmp.from, tmp.to);
			return tmp;
		}
		Edge<EdgeValue>& reverse()
		{
			if (!isBidirectional)
				std::swap(from, to);
			return *this;
		}
		Edge<EdgeValue> GetReversed() const
		{
			if (!isBidirectional)
				return *this;
			else
			{
				Edge<EdgeValue> tmp(*this);
				std::swap(tmp.from, tmp.to);
				return tmp;
			}
		}
		friend class Graph;
	};

	class Graph
	{
	private:
		std::map<topKey, std::string> tops;
		std::set<Edge<byte>> edges;
	public:
		Graph()
			:tops()
			, edges()
		{}
		Graph(Graph const& source)
			:tops(source.tops)
			, edges(source.edges)
		{}
		Graph(Graph&& source) noexcept
			:tops(std::move(source.tops))
			, edges(std::move(source.edges))
		{
			source = Graph();
		}

		Graph& operator=(Graph const& source)
		{
			*this = Graph(source);
		}
		Graph& operator=(Graph&& source)noexcept
		{
			tops = std::move(source.tops);
			edges = std::move(source.edges);
			source = Graph();
		}
		bool operator<(Graph const& toCompare) const
		{
			for (auto CompareEdge : toCompare.edges)
				if (std::find_if(edges.begin(), edges.end(), Edge<byte>::CmpProvideTheSameWayTo<byte>(CompareEdge))
					== edges.end())
					return false;
			return true;
		}
		bool operator>(Graph const& toCompare) const
		{
			for (auto CompareEdge : this->edges)
				if (std::find_if(edges.begin(), edges.end(), Edge<byte>::CmpProvideTheSameWayTo<byte>(CompareEdge))
					== edges.end())
					return false;
			return true;
		}
		bool operator==(Graph const& toCompare) const
		{
			return this->operator<(toCompare) && this->operator>(toCompare);
		}

		//bool IsomorthicallyLess(Graph const& toCompare) const;
		//bool IsomorthicallyMore(Graph const& toCompare) const;

		//bool isIsomorthisTo(Graph const& toCompare) const;
		//static bool areIsomorthic(Graph const& a, Graph const& b);
		bool hasEdge(Edge<byte> CompareEdge) const
		{
			return std::find_if(edges.begin(), edges.end(), Edge<byte>::CmpProvideTheSameWayTo<byte>(CompareEdge)) == edges.end();
		}
		bool hasEdge(topKey a, topKey b) const
		{
			return std::find_if(edges.begin(), edges.end(), [=](Edge<byte> &edge) { return edge.bounds(a, b);} ) != edges.end();
		}
		std::set<Edge<byte>>::iterator GetEdgeIter(Edge<byte> toCompare) const
		{
			return (std::find_if(edges.begin(), edges.end(), [=](Edge<byte>& edge) { return edge.operator==(toCompare); }));
		}
		std::set<Edge<byte>>::iterator GetEdgeIter(topKey a, topKey b) const
		{
			return (std::find_if(edges.begin(), edges.end(), [=](Edge<byte>& edge) { return edge.bounds(a, b); }));
		}

		void AddTop()
		{
			tops.insert(std::make_pair(tops.size(), std::to_string(tops.size())));
		}
		void AddTop(std::initializer_list<topKey> const& list)
		{
			AddTop();
			for (auto connectWith : list)
			{
				assert(connectWith >= 0);
				assert(connectWith < static_cast<int>(tops.size()));
				edges.insert(Edge<byte>(tops.size() - 1, connectWith, 1, true));
			}
		}
		void AddTop(std::string str)
		{
			tops.insert(std::make_pair(tops.size(), str));
		}
		void AddTop(std::string str, std::initializer_list<topKey> const& list)
		{
			AddTop(str);
			for (auto connectWith : list)
			{
				assert(connectWith >= 0);
				assert(connectWith < static_cast<int>(tops.size()));
				edges.insert(Edge<byte>(tops.size() - 1, connectWith, 1, true));
			}
		}
		std::list<Edge<byte>> GetEdges()  const
		{
			std::list<Edge<byte>> answer;
			for (auto i : edges)
				answer.push_back(i);
			return answer;
		}
		std::list<Edge<byte>> GetEdges(topKey a, topKey b)  const
		{
			std::list<Edge<byte>> answer;
			for (auto i : edges)
				if(i.bounds(a,b))
					answer.push_back(i);
			return answer;
		}
		void InsertEdge(topKey from, topKey to)
		{
			assert(from >= 0);
			assert(from < static_cast<int>(tops.size()));
			assert(to >= 0);
			assert(to < static_cast<int>(tops.size()));
			edges.insert(Edge<byte>(from, to, 1, true));
		}
		void RemoveEdges(topKey a, topKey b)
		{
			std::set<Edge<byte>>::iterator tmp;
			while ((tmp = this->GetEdgeIter(a, b)) != this->edges.end())
				this->edges.erase(tmp);
		}
		void RemoveEdge(Edge<byte> edge)
		{
			std::set<Edge<byte>>::iterator tmp;
			if ((tmp = this->GetEdgeIter(edge)) != this->edges.end())
				this->edges.erase(tmp);
		}
		void RemoveEdge(topKey a, topKey b)
		{
			std::set<Edge<byte>>::iterator tmp;
			if ((tmp = this->GetEdgeIter(a, b)) != this->edges.end())
				this->edges.erase(tmp);
		}
		/*
		Graph GetSubGraphOf(std::vector<topKey>)  const;
		Graph GetSubGraphWithOut(std::vector<topKey>) const;
		Graph GetAdditionGraph()  const;

		Cycle FindCycles()  const;
		Cycle FindSimpleCycles()  const;

		size_t FindDistance()  const;


		void RemoveTop(topKey);
		void RemoveTop(std::string);

		std::list<std::string> GetTops()  const;
		std::list<std::string> GetEdges()  const;

		bool isEmpty() const;
		bool isFull() const;
		bool isTree() const;
		bool isMulti() const;
		bool isPseudo() const;
		bool isInterConnected() const;
		int CountOfComponents() const;*/

	};

	
//	class Cycle
//	{
//	public:
//		Cycle(std::vector<int>&);
//		Cycle(std::vector<int>&&);
//		std::vector<topKey> topList;
//		std::list<Cycle> GetSimpleCycles;
//
//		bool isSimple();
//
//		std::ostream& Print(std::ostream&);
//	};
//	class Route
//	{
//	public:
//		Route(std::vector<int>&);
//		Route(std::vector<int>&&);
//		std::vector<topKey> topList;
//
//		bool isSimple();
//
//		std::ostream& Print(std::ostream&);
//	};
	enum Direction : unsigned char
	{
		Out = 0,
		InOut = 1
	};
}