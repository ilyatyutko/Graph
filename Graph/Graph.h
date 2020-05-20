#pragma once
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <cassert>
#include <functional>
#include <algorithm>
#include <stack>
#include <queue>

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
			: from(_from)
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
			: from(source.from)
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
			if (this->from < toCompare.from) return true;
			if (this->from == toCompare.from)
			{
				if (this->to < toCompare.to) return true;
				if (this->to == toCompare.to)
				{
					if (this->value < toCompare.value) return true;
					if (this->value == toCompare.value)
						return this->isBidirectional < toCompare.isBidirectional;
				}
			}
			return false;
		}
		bool operator>(Edge<EdgeValue> const& toCompare) const
		{
			if (this->from > toCompare.from) return true;
			if (this->from == toCompare.from)
			{
				if (this->to > toCompare.to) return true;
				if (this->to == toCompare.to)
				{
					if (this->value > toCompare.value) return true;
					if (this->value == toCompare.value)
						return this->isBidirectional > toCompare.isBidirectional;
				}
			}
			return false;
		}
		bool operator==(Edge<EdgeValue> const& toCompare) const
		{
			return to == toCompare.to
				&& from == toCompare.from
				&& value == toCompare.value
				&& isBidirectional == toCompare.isBidirectional;
		}

		bool isLoop()const
		{
			return from == to;
		}
		bool hasDirection()const
		{
			return !isBidirectional;
		}
		bool isIncidentTo(topKey top)const
		{
			return from == top || top == to;
		}
		bool bounds(const topKey a, const  topKey b) const
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

		std::pair<topKey, topKey> GetIncidentTops()const
		{
			return std::make_pair(from, to);
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
			if (!isBidirectional)
			{
				isBidirectional = true;
				if (from > to)
					std::swap(from, to);
			}
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

		std::string ToString() const
		{
			if (isBidirectional)
				return std::string("from: " + std::to_string(from) + " to: " + std::to_string(to) + " value: " + std::to_string(value) + " biDirectional");
			else
				return  std::string("from: " + std::to_string(from) + " to: " + std::to_string(to) + " value: " + std::to_string(value));
		}

		template<class EdgeValue>
		struct CmpLexicographLess
		{
			bool operator()(Edge<EdgeValue> const& a, Edge<EdgeValue> const& b)const
			{
				return a < b;
			}
		};
		template<class EdgeValue>
		struct CmpLexicographMore
		{
			bool operator()(Edge<EdgeValue> const& a, Edge<EdgeValue> const& b)const
			{
				return a > b;
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
		friend class Graph;
	};

	class TopOverrange:std::exception
	{
	public:
		TopOverrange() : exception("NoSuchTopInGRAPH") {}
	};

	class Graph
	{
	private:
		std::map<topKey, std::string> tops;
		std::multiset<Edge<byte>> edges;

		std::multiset<Edge<byte>>::const_iterator FindEdgeIter(Edge<byte> const& toCompare) const
		{
			auto left = edges.lower_bound(toCompare);
			auto right = edges.upper_bound(toCompare);
			for (auto i = left; i != right; ++i)
				if (*i == toCompare)
					return i;
			return edges.end();
		}
		std::multiset<Edge<byte>>::const_iterator FindEdgeIter(topKey from, topKey to) const
		{
			assert(from >= 0);
			assert(from < static_cast<int>(tops.size()));
			assert(to >= 0);
			assert(to < static_cast<int>(tops.size()));
			Edge<byte> tmp(from, to, 1, true);
			return edges.find(tmp);
		}
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
				if (std::find_if(edges.begin()
					, edges.end()
					, Edge<byte>::CmpProvideTheSameWayTo<byte>(CompareEdge))
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

		void AddTop()
		{
			tops.insert(std::make_pair(tops.size(), std::to_string(tops.size())));
		}
		void AddTop(std::initializer_list<topKey> const& list)
		{
			AddTop();
			for (auto connectWith : list)
			{
				if (!hasTop(connectWith))
					throw TopOverrange();
				edges.insert(Edge<byte>(tops.size() - 1, connectWith, 1, true));
			}
		}
		void AddTop(std::list<topKey> const& list)
		{
			AddTop();
			for (auto connectWith : list)
			{
				if (!hasTop(connectWith))
					throw TopOverrange();
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
				if (!hasTop(connectWith))
					throw TopOverrange();
				edges.insert(Edge<byte>(tops.size() - 1, connectWith, 1, true));
			}
		}
		void AddTop(std::string str, std::list<topKey> const& list)
		{
			AddTop(str);
			for (auto connectWith : list)
			{
				if (!hasTop(connectWith))
					throw TopOverrange();
				edges.insert(Edge<byte>(tops.size() - 1, connectWith, 1, true));
			}
		}
		bool AreAdjacent(topKey from, topKey to)const
		{
			if (!hasTop(from))
				throw TopOverrange();
			if (!hasTop(to))
				throw TopOverrange();
			Edge<byte> tmp(from, to, 1, true);
			return edges.find(tmp) != edges.end();
		}
		void RemoveTop(topKey top)
		{
			if (!hasTop(top))
				throw TopOverrange();
			tops.erase(tops.find(top));
			std::map<int, std::string> toChangeTops;
			for (auto i = edges.begin(); i != edges.end();)
				if (i->isIncidentTo(top))
					i = edges.erase(i);
				else
					++i;
		}
		void RemoveTops(std::list<topKey> Deletelist)
		{
			Deletelist.sort();
			for (auto itr = Deletelist.rbegin(); itr != Deletelist.rend(); ++itr)
				this->RemoveTop(*itr);
		}
		int GetOrder()const
		{
			return tops.size();
		}
		std::list<topKey> GetConnectedTops(topKey from)const
		{
			if (!hasTop(from))
				throw TopOverrange();
			auto list = this->GetIncidentEdges(from);
			std::list<topKey> answer;
			for (auto itr = edges.begin(); itr != edges.end(); ++itr)
				if (itr->from == from || itr->to == from)
				{
					auto adding = (itr->from == from) ? itr->to : itr->from;
					if (std::find(answer.begin(), answer.end(), adding) == answer.end())
						answer.push_back(adding);
				}
			answer.sort();
			return answer;
		}
		int GetPower(topKey top)const
		{
			if (!hasTop(top))
				throw TopOverrange();
			return GetIncidentEdges(top).size();
		}
		int GetMaxPower()const
		{
			if (tops.size() == 0)
				return 0;
			int max = 0;
			for (auto i : tops)
			{
				auto tmp = this->GetPower(i.first);
				if (tmp > max)
					max = tmp;
			}
			return max;
		}
		int GetMinPower()const
		{
			if (tops.size() == 0)
				return 0;
			int max = this->GetPower(tops.begin()->first);
			for (auto i : tops)
			{
				auto tmp = this->GetPower(i.first);
				if (tmp > max)
					max = tmp;
			}
			return max;
		}
		topKey GetTopWithMaxPower()const
		{
			if (tops.size() == 0)
				throw std::exception("Empty Graph");
			int max = 0;
			topKey maxTop = -1;
			for (auto i : tops)
			{
				auto tmp = this->GetPower(i.first);
				if (tmp > max)
				{
					max = tmp;
					maxTop = i.first;
				}
			}
			return maxTop;
		}
		topKey GetTopWithMinPower()const
		{
			if (tops.size() == 0)
				throw std::exception("Empty Graph");
			int max = this->GetPower(tops.begin()->first);
			int maxTop = -1;
			for (auto i : tops)
			{
				auto tmp = this->GetPower(i.first);
				if (tmp > max)
				{
					max = tmp;
					maxTop = i.first;
				}
			}
			return maxTop;
		}

		void AddEdge(topKey from, topKey to)
		{
			if (!hasTop(from))
				throw TopOverrange();
			if (!hasTop(to))
				throw TopOverrange();
			edges.insert(Edge<byte>(from, to, 1, true));
		}
		void AddEdge(Edge<byte> const& edge)
		{
			if (!hasTop(edge.from))
				throw TopOverrange();
			if (!hasTop(edge.to))
				throw TopOverrange();
			edges.insert(edge);
		}
		void RemoveEdge(topKey from, topKey to)
		{
			if (!hasTop(from))
				throw TopOverrange();
			if (!hasTop(to))
				throw TopOverrange();
			edges.erase(this->FindEdgeIter(from, to));
		}
		void RemoveEdge(Edge<byte> const& edge)
		{
			auto i = this->FindEdgeIter(edge);
			if (i != edges.end())
				edges.erase(i);
		}
		void RemoveSomeEdge(topKey a, topKey b, int count)
		{
			auto tmp = Edge<byte>(a,b);
			auto left = edges.lower_bound(tmp);
			auto right = edges.upper_bound(tmp);
			for (int i = 0;
				i < count && left != right;
				++i)
				left = edges.erase(left);
		}
		void RemoveAllEdges(topKey from, topKey to)
		{
			if (!hasTop(from))
				throw TopOverrange();
			if (!hasTop(to))
				throw TopOverrange();
			auto tmp = Edge<byte>(from, to, 1, true);
			auto itrLeft = edges.lower_bound(tmp);
			auto itrRight = edges.upper_bound(tmp);
			if (itrLeft != itrRight)
				edges.erase(itrLeft, itrRight);
		}

		int CountOfEdges(Edge<byte> const& toCompare) const
		{
			return edges.count(toCompare);
		}
		int CountOfEdges(topKey from, topKey to)const
		{
			if (!hasTop(from))
				throw TopOverrange();
			if (!hasTop(to))
				throw TopOverrange();
			return this->GetAllEdges(from, to).size();
		}
		bool hasEdge(Edge<byte> const& toCompare) const
		{
			return CountOfEdges(toCompare) > 0;
		}
		bool hasEdge(topKey from, topKey to) const
		{
			if (!hasTop(from))
				throw TopOverrange();
			if (!hasTop(to))
				throw TopOverrange();
			return this->CountOfEdges(from, to) > 0;
		}
		Edge<byte> GetEdge(topKey from, topKey to) const
		{
			if (!hasTop(from))
				throw TopOverrange();
			if (!hasTop(to))
				throw TopOverrange();
			Edge<byte> tmp(from, to, 1, true);
			auto itr = edges.find(tmp);
			if (itr != edges.end())
				return *(itr);
			else
				throw std::exception("NoSuchEdge");
			//
		}
		bool hasTop(topKey top)const
		{
			if (top < FirstTop() || top > LastTop())
				return false;
			else return true;
		}
		/*Edge<byte> GetMinEdge(topKey from, topKey to) const
		{
			if (!hasEdge(from, to))
			{
			}
			auto list = this->GetAllEdges(from, to);
			auto result = *(list.begin());
			for (auto itr = list.begin(); itr != list.end(); ++itr)
				if (itr->value < result.value)
					result = *itr;
			return result;
		}
		Edge<byte> GetMaxEdge(topKey from, topKey to) const
		{
			auto list = this->GetAllEdges(from, to);
			auto result = *(list.begin());
			for (auto itr = list.begin(); itr != list.end(); ++itr)
				if (itr->value > result.value)
					result = *itr;
			return result;
		}*/
		std::list<Edge<byte>> GetAllEdges(topKey from, topKey to) const
		{
			if (!hasTop(from))
				throw TopOverrange();
			if (!hasTop(to))
				throw TopOverrange();
			Edge<byte> tmp(from, to, 1, true);
			std::list<Edge<byte>> answer;
			std::multiset<Edge<byte>>::iterator itrRight = (edges.upper_bound(tmp));
			std::multiset<Edge<byte>>::iterator itrLeft = (edges.lower_bound(tmp));
			for (auto i = itrLeft; i != itrRight; ++i)
				answer.push_back(*i);
			return answer;
		}
		std::list<Edge<byte>> GetAllEdges()  const
		{
			std::list<Edge<byte>> answer;
			for (auto& i : edges)
				answer.push_back(i);
			return answer;
		}
		std::list<Edge<byte>> GetIncidentEdges(topKey from)const
		{
			std::list<Edge<byte>> answer;
			for (auto& i : edges)
				if (i.isIncidentTo(from))
					answer.push_back(i);
			return answer;
		}
		std::pair<topKey, topKey> GetIncidentTops(Edge<byte> const& edge)const
		{
			return std::make_pair(edge.from, edge.to);
		}
		bool areIncident(topKey top, Edge<byte> const& edge)const
		{
			topKey a, b;
			std::tie(a, b) = this->GetIncidentTops(edge);
			return  a == top || top == b;
		}

		Graph GetSubGraphOf(std::vector<topKey> topList)  const
		{
			Graph answer;
			for (auto& top : topList)
			{
				if (!hasTop(top))
					throw TopOverrange();
				answer.AddTop(this->tops.find(top)->second);
			}
			for (auto& i : edges)
			{
				auto tmp = i.GetIncidentTops();
				if (std::find(topList.begin(), topList.end(), tmp.first) != topList.end()
					&& std::find(topList.begin(), topList.end(), tmp.second) != topList.end())
					answer.AddEdge(i);
			}
			return answer;
		}
		Graph GetSubGraphWithOut(std::vector<topKey> topList) const
		{
			Graph answer(*this);
			std::sort(topList.begin(), topList.end(), std::greater<int>());
			for (auto& i : topList)
				answer.RemoveTop(i);
			return answer;
		}
		Graph GetFullGraph()const
		{
			Graph result = *this;
			return result.FillGraph();
		}
		Graph& FillGraph()
		{
			for (auto from = tops.begin(); from != tops.end(); ++from)
				for(auto to = tops.begin(); to != tops.end(); ++to)
					if (from != to && !this->AreAdjacent(from->first, to->first))
					{
						this->AddEdge(from->first, to->first);
					}
			return *this;
		}
		Graph GetInvertedGraph()  const
		{
			Graph result = *this;
			for (auto from = tops.begin(); from != tops.end(); ++from)
				for (auto to = tops.begin(); to != tops.end(); ++to)
					if (from != to && this->AreAdjacent(from->first, to->first))
					{
						result.RemoveAllEdges(from->first, to->first);
					}
			return result;
		}
		Graph& InvertGraph()
		{
			*this = this->GetInvertedGraph();
			return *this;
		}
		/*
		Cycle FindCyclesFromTop()  const;
		Cycle FindSimpleCycles()  const;*/

		size_t FindDistance(topKey from, topKey to)  const
		{
			if (!hasTop(from))
				throw TopOverrange();
			if (!hasTop(to))
				throw TopOverrange();
			std::stack<std::pair<topKey, int>> topOrder;
			topOrder.push(std::make_pair(from, 0));
			std::vector<bool> areMarked(this->tops.size());
			areMarked[from] = 1;
			while (!topOrder.empty())
			{
				auto top = topOrder.top();
				topOrder.pop();

				if (top.first == to)
					return top.second;

				auto list = this->GetConnectedTops(top.first);
				int i = 0;
				for (auto i = list.begin(); i != list.end(); ++i)
					if (areMarked[*i] != 1)
					{
						areMarked[*i] = 1;
						topOrder.push(std::make_pair(*i, top.second + 1));
					}
			}
		}

		//bool IsomorthicallyLess(Graph const& toCompare) const;
		//bool IsomorthicallyMore(Graph const& toCompare) const;
		//bool isIsomorthisTo(Graph const& toCompare) const;
		//static bool areIsomorthic(Graph const& from, Graph const& to);
		topKey FirstTop() const
		{
			return tops.begin()->first;
		}
		topKey LastTop()const
		{
			if (this->tops.empty())
				throw std::exception("Empty Tops");
			return (--tops.end())->first;
		}
		int TopsCount()const
		{
			return tops.size();
		}

		std::list<topKey> GetTopsDeepSearch(topKey a)const
		{
			if (!hasTop(a))
				throw TopOverrange();
			std::list<topKey> result = {a};

			std::stack<topKey> topOrder;
			topOrder.push(a);
			std::vector<bool> areMarked(TopsCount());
			auto First = FirstTop();
			areMarked[a - First] = true;
			while (!topOrder.empty())
			{
				auto top = topOrder.top();
				topOrder.pop();

				auto list = this->GetConnectedTops(top);
				for(auto i = list.begin(); i != list.end(); ++i)
					if (areMarked[*i - First] == false)
					{
						areMarked[*i - First] = true;
						topOrder.push(*i);
						result.push_back(*i);
					}
			}
			return result;
		}
		std::list<topKey> GetTopsWideSearch(topKey a)const
		{
			if (!hasTop(a))
				throw TopOverrange();
			std::list<topKey> result = { a };

			std::queue<topKey> topOrder;
			topOrder.push(a);
			std::vector<bool> areMarked(this->tops.size());
			areMarked[a] = 1;
			while (!topOrder.empty())
			{
				auto top = topOrder.front();
				topOrder.pop();

				auto list = this->GetConnectedTops(top);
				for (auto i = list.begin(); i != list.end(); ++i)
					if (areMarked[*i] != 1)
					{
						areMarked[*i] = 1;
						topOrder.push(*i);
						result.push_back(*i);
					}
			}
			return result;
		}

		bool isEmpty() const
		{
			return edges.size() == 0;
		}
		bool isFull() const
		{
			auto preEnd = --(tops.end());
			for (auto f_itr = tops.begin(); f_itr != preEnd; ++f_itr)
			{
				auto tmp = f_itr;
				for (auto s_itr = ++tmp; s_itr != tops.end(); ++s_itr)
					if (!this->AreAdjacent(f_itr->first, s_itr->first)
						|| !this->AreAdjacent(s_itr->first, f_itr->first))
						return false;
			}
			return true;
		}
		bool isRegular()const
		{
			if (tops.size() == 0)
				return true;
			auto power = this->GetPower(tops.begin()->first);
			for (auto& i : tops)
				if (this->GetPower(i.first) != power)
					return false;
			return true;
		}
		bool isTree() const;
		bool isCycle()const
		{
			auto min = this->GetMinPower();
			auto max = this->GetMaxPower();
			return min == max && max == 2 && CountOfComponents() == 1;
		}
		bool isWheel()const
		{
			return (this->GetSubGraphWithOut({ this->GetTopWithMaxPower() }).isCycle());
		}
		bool isMulti() const
		{
			for (auto& i : edges)
				if (i.isLoop())
					return false;
			return true;
		}
		bool isSimple() const
		{
			if (this->isMulti())
			{
				auto preend = --tops.end();
				for (auto i = tops.begin(); i != preend; ++i)
				{
					auto tmp = ++i;
					for (auto s = tmp; s != tops.end(); ++s)
						if (this->CountOfEdges(i->first, s->first) > 1
							|| this->CountOfEdges(s->first, i->first) > 1)
							return false;
				}
				return true;
			}
			else
				return false;
		}
		bool isDirectioned()const
		{
			for (auto& i : edges)
				if (!i.isBidirectional)
					return true;
			return false;
		}
		bool isInterConnected() const
		{
			return this->CountOfComponents() == 1;
		}
		bool isDicotyledonous() const;
		int CountOfComponents() const
		{
			Graph tmp = *this;
			int i = 0;
			while (tmp.GetOrder() > 0)
			{
				auto tmpq = tmp.tops.begin()->first;
				auto qwe = tmp.GetTopsDeepSearch(tmpq);
				tmp.RemoveTops(qwe);
				++i;
			}
			return i;
		}

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
	/*enum Direction : unsigned char
	{
		Out = 0,
		InOut = 1
	};*/
}