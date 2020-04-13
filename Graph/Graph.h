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
	typedef int topKey;
	typedef unsigned char byte;

	//class Graph: public base_Graph
	//{
		/*void AddTop()
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
				edges.insert(base_Edge<byte>(tops.size() - 1, connectWith, defaultEdgeLength, EdgesAreNotOriented));
			}
		}
		void AddTop(std::vector<topKey> const& list)
		{
			AddTop();
			for (auto connectWith : list)
			{
				assert(connectWith >= 0);
				assert(connectWith < static_cast<int>(tops.size()));
				edges.insert(base_Edge<byte>(tops.size() - 1, connectWith, defaultEdgeLength, EdgesAreNotOriented));
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
				edges.insert(base_Edge<byte>(tops.size() - 1, connectWith, defaultEdgeLength, EdgesAreNotOriented));
			}
		}
		void AddTop(std::string str, std::vector<topKey> const& list)
		{
			AddTop(str);
			for (auto connectWith : list)
			{
				assert(connectWith >= 0);
				assert(connectWith < static_cast<int>(tops.size()));
				edges.insert(base_Edge<byte>(tops.size() - 1, connectWith, defaultEdgeLength, EdgesAreNotOriented));
			}
		}
		bool AreAdjacent(topKey from, topKey to)const
		{
			assert(from >= 0);
			assert(from < static_cast<int>(tops.size()));
			assert(to >= 0);
			assert(to < static_cast<int>(tops.size()));
			base_Edge<byte> tmp(from, to, defaultEdgeLength, EdgesAreNotOriented);
			return edges.find(tmp) != edges.end();
		}
		void RemoveTop(topKey top)
		{
			tops.erase(tops.find(top));
			std::map<int, std::string> toChangeTops;
			for (auto i = tops.begin(); i != tops.end(); ++i)
				if (i->first > top)
				{
					toChangeTops.insert(std::make_pair(i->first - 1, i->second));
					i = tops.erase(i);
					if (i == tops.end())break;
				}
			for (auto& i : toChangeTops)
				tops.insert(i);

			for (auto i = edges.begin(); i != edges.end();)
				if (i->isIncidentTo(top))
				{
					i = edges.erase(i);
					if (i == edges.end())break;
				}
				else
					++i;
			std::multiset<base_Edge<byte>> toChangeEdges;
			for (auto i = edges.begin(); i != edges.end(); ++i)
			{
				if (i->from > top)
				{
					if (i->to > top)
					{
						toChangeEdges.insert(
							base_Edge<byte>(i->from - 1, i->to - 1, i->value, i->isBidirectional));
						i = edges.erase(i);
					}
					else
					{
						toChangeEdges.insert(
							base_Edge<byte>(i->from - 1, i->to, i->value, i->isBidirectional));
						i = edges.erase(i);
					}

				}
				else if (i->to > top)
				{
					toChangeEdges.insert(
						base_Edge<byte>(i->from, i->to - 1, i->value, i->isBidirectional));
					i = edges.erase(i);
				}
				else ++i;
				if (i == edges.end())break;
			}
			for (auto& i : toChangeEdges)
				edges.insert(i);
		}*/
		//int GetOrder()const
		//{
		//	return tops.size();
		//}
		//std::list<topKey> GetConnectedTops(topKey from)const
		//{
		//	auto list = this->GetIncidentEdges(from);
		//	std::list<topKey> answer;
		//	for (auto itr = edges.begin(); itr != edges.end(); ++itr)
		//	{
		//		if ((*itr).isBidirectional)
		//		{
		//			auto adding = (itr->from == from) ? itr->to : itr->from;
		//			if (std::find(answer.begin(), answer.end(), adding) == answer.end())
		//				answer.push_back(adding);
		//		}
		//		else
		//			if (itr->from == from && std::find(answer.begin(), answer.end(), itr->to) == answer.end())
		//				answer.push_back(itr->to);
		//	}
		//	answer.sort();
		//	return answer;
		//}
		//int GetPower(topKey top)const
		//{
		//	return GetIncidentEdges(top).size();
		//}
		//int GetMaxPower()const
		//{
		//	if (tops.size() == 0)
		//		return 0;
		//	int max = 0;
		//	for (auto i : tops)
		//	{
		//		auto tmp = this->GetPower(i.first);
		//		if (tmp > max)
		//			max = tmp;
		//	}
		//	return max;
		//}
		//int GetMinPower()const
		//{
		//	if (tops.size() == 0)
		//		return 0;
		//	int max = this->GetPower(tops.begin()->first);
		//	for (auto i : tops)
		//	{
		//		auto tmp = this->GetPower(i.first);
		//		if (tmp > max)
		//			max = tmp;
		//	}
		//	return max;
		//}
		//topKey GetTopWithMaxPower()const
		//{
		//	if (tops.size() == 0)
		//		throw std::exception("Empty Graph");
		//	int max = 0;
		//	topKey maxTop = -1;
		//	for (auto i : tops)
		//	{
		//		auto tmp = this->GetPower(i.first);
		//		if (tmp > max)
		//		{
		//			max = tmp;
		//			maxTop = i.first;
		//		}
		//	}
		//	return maxTop;
		//}
		//topKey GetTopWithMinPower()const
		//{
		//	if (tops.size() == 0)
		//		throw std::exception("Empty Graph");
		//	int max = this->GetPower(tops.begin()->first);
		//	int maxTop = -1;
		//	for (auto i : tops)
		//	{
		//		auto tmp = this->GetPower(i.first);
		//		if (tmp > max)
		//		{
		//			max = tmp;
		//			maxTop = i.first;
		//		}
		//	}
		//	return maxTop;
		//}
		//int CountOfEdgesBetween(topKey from, topKey to)const
		//{
		//	return this->GetEachEdge(from, to).size();
		//}

		//void InsertEdge(topKey from, topKey to, byte size = 1, bool bidirectional = true)
		//{
		//	assert(from >= 0);
		//	assert(from < static_cast<int>(tops.size()));
		//	assert(to >= 0);
		//	assert(to < static_cast<int>(tops.size()));
		//	edges.insert(base_Edge<byte>(from, to, size, bidirectional));
		//}
		//void InsertEdge(base_Edge<byte> const& edge)
		//{
		//	edges.insert(edge);
		//}
		//void RemoveEdges(topKey from, topKey to)
		//{
		//	assert(from >= 0);
		//	assert(from < static_cast<int>(tops.size()));
		//	assert(to >= 0);
		//	assert(to < static_cast<int>(tops.size()));
		//	/*while ((tmp = this->FindEdgeIter(from, to)) != this->edges.end())
		//		this->edges.erase(tmp);*/
		//	auto tmp = base_Edge<byte>(from, to, defaultEdgeLength, EdgesAreNotOriented);
		//	auto itrLeft = edges.lower_bound(tmp);
		//	auto itrRight = edges.upper_bound(tmp);
		//	edges.erase(itrLeft, itrRight);
		//}
		//void RemoveEdge(base_Edge<byte> const& edge)
		//{
		//	auto i = this->FindEdgeIter(edge);
		//	if (i != edges.end())
		//		edges.erase(i);
		//}
		//void RemoveSomeEdge(topKey a, topKey b)
		//{
		//	std::multiset<base_Edge<byte>>::iterator tmp;
		//	if ((tmp = this->FindEdgeIter(a, b)) != this->edges.end())
		//		this->edges.erase(tmp);
		//}

		//bool hasEdge(base_Edge<byte> const& toCompare) const
		//{
		//	auto left = edges.lower_bound(toCompare);
		//	auto right = edges.upper_bound(toCompare);
		//	for (auto i = left; i != right; ++i)
		//		if (*i == toCompare)
		//			return true;
		//	return false;
		//}
		//base_Edge<byte> GetAnyEdge(topKey from, topKey to) const
		//{
		//	assert(from >= 0);
		//	assert(from < static_cast<int>(tops.size()));
		//	assert(to >= 0);
		//	assert(to < static_cast<int>(tops.size()));
		//	base_Edge<byte> tmp(from, to, defaultEdgeLength, EdgesAreNotOriented);
		//	auto itr = edges.find(tmp);
		//	if (itr != edges.end())
		//		return *(itr);
		//	else
		//		return base_Edge<byte>();
		//}
		//base_Edge<byte> GetMinEdge(topKey from, topKey to) const
		//{
		//	auto list = this->GetEachEdge(from, to);
		//	auto result = *(list.begin());
		//	for (auto itr = list.begin(); itr != list.end(); ++itr)
		//		if (itr->value < result.value)
		//			result = *itr;
		//	return result;
		//}
		//base_Edge<byte> GetMaxEdge(topKey from, topKey to) const
		//{
		//	auto list = this->GetEachEdge(from, to);
		//	auto result = *(list.begin());
		//	for (auto itr = list.begin(); itr != list.end(); ++itr)
		//		if (itr->value > result.value)
		//			result = *itr;
		//	return result;
		//}
		//std::list<base_Edge<byte>> GetEachEdge(topKey from, topKey to) const
		//{
		//	assert(from >= 0);
		//	assert(from < static_cast<int>(tops.size()));
		//	assert(to >= 0);
		//	assert(to < static_cast<int>(tops.size()));
		//	base_Edge<byte> tmp(from, to, defaultEdgeLength, EdgesAreNotOriented);
		//	std::list<base_Edge<byte>> answer;
		//	std::multiset<base_Edge<byte>>::iterator itrRight = (edges.upper_bound(tmp));
		//	std::multiset<base_Edge<byte>>::iterator itrLeft = (edges.lower_bound(tmp));
		//	for (auto i = itrLeft; i != itrRight; ++i)
		//		answer.push_back(*i);
		//	return answer;
		//}
		//std::list<base_Edge<byte>> GetAllEdges()  const
		//{
		//	std::list<base_Edge<byte>> answer;
		//	for (auto& i : edges)
		//		answer.push_back(i);
		//	return answer;
		//}
		//std::list<base_Edge<byte>> GetIncidentEdges(topKey from)const
		//{
		//	std::list<base_Edge<byte>> answer;
		//	for (auto& i : edges)
		//		if (i.isIncidentTo(from))
		//			answer.push_back(i);
		//	return answer;
		//}
		//std::pair<topKey, topKey> GetIncidentTops(base_Edge<byte> const& edge)const
		//{
		//	return std::make_pair(edge.from, edge.to);
		//}
		//bool areIncident(topKey top, base_Edge<byte> const& edge)const
		//{
		//	topKey a, b;
		//	std::tie(a, b) = this->GetIncidentTops(edge);
		//	return  a == top || top == b;
		//}

		//Graph GetSubGraphOf(std::vector<topKey> topList)  const
		//{
		//	Graph answer;
		//	for (auto& i : topList)
		//	{
		//		answer.AddTop(this->tops.find(i)->second);
		//	}
		//	for (auto& i : edges)
		//	{
		//		auto tmp = i.GetIncidentTops();
		//		if (std::find(topList.begin(), topList.end(), tmp.first) != topList.end()
		//			&& std::find(topList.begin(), topList.end(), tmp.second) != topList.end())
		//			answer.InsertEdge(i);
		//	}
		//	return answer;
		//}
		//Graph GetSubGraphWithOut(std::vector<topKey> topList) const
		//{
		//	Graph answer(*this);
		//	std::sort(topList.begin(), topList.end(), std::greater<int>());
		//	for (auto& i : topList)
		//		answer.RemoveTop(i);
		//	return answer;
		//}
		//static Graph GetFullGraph(int topsCount)
		//{
		//	if (topsCount == 0)
		//		return Graph();
		//	else if (topsCount < 0)
		//		throw std::exception("Tops Count can't be less than 0");
		//	std::vector<int> topsToConnect;
		//	topsToConnect.reserve(topsCount);
		//	Graph result;
		//	result.AddTop();
		//	for (int i = 1; i < topsCount; ++i)
		//	{
		//		topsToConnect.push_back(i - 1);
		//		result.AddTop(topsToConnect);
		//	}
		//	return result;
		//}
		//Graph& FillGraph(int addEdgesWithLength = defaultEdgeLength)
		//{
		//	
		//}
		///*Graph GetAdditionGraph()  const;

		//Cycle FindCycles()  const;
		//Cycle FindSimpleCycles()  const;

		//size_t FindDistance()  const;*/

		////bool IsomorthicallyLess(Graph const& toCompare) const;
		////bool IsomorthicallyMore(Graph const& toCompare) const;
		////bool isIsomorthisTo(Graph const& toCompare) const;
		////static bool areIsomorthic(Graph const& from, Graph const& to);

		//bool isEmpty() const
		//{
		//	return edges.size() == 0;
		//}
		//bool isFull() const
		//{
		//	auto preEnd = --(tops.end());
		//	for (auto f_itr = tops.begin(); f_itr != preEnd; ++f_itr)
		//	{
		//		auto tmp = f_itr;
		//		for (auto s_itr = ++tmp; s_itr!=tops.end();++s_itr)
		//			if (!this->AreAdjacent(f_itr->first, s_itr->first)
		//				|| !this->AreAdjacent(s_itr->first, f_itr->first))
		//				return false;
		//	}
		//	return true;
		//}
		//bool isRegular()const
		//{
		//	if (tops.size() == 0)
		//		return true;
		//	auto power = this->GetPower(tops.begin()->first);
		//	for (auto& i : tops)
		//		if (this->GetPower(i.first) != power)
		//			return false;
		//	return true;
		//}
		//bool isTree() const;
		//bool isCycle()const
		//{
		//	return this->GetMaxPower() == this->GetMinPower() == 2 && CountOfComponents() == 1;
		//}
		//bool isWheel()const
		//{
		//	return (this->GetSubGraphWithOut({ this->GetTopWithMaxPower() }).isCycle());
		//}
		//bool isMulti() const
		//{
		//	for (auto& i : edges)
		//		if (i.isLoop())
		//			return false;
		//	return true;
		//}
		//bool isSimple() const
		//{
		//	if (this->isMulti())
		//	{
		//		auto preend = --tops.end();
		//		for (auto i = tops.begin(); i != preend; ++i)
		//		{
		//			auto tmp = ++i;
		//			for (auto s = tmp; s != tops.end(); ++s)
		//				if (this->CountOfEdgesBetween(i->first, s->first) > 1
		//					|| this->CountOfEdgesBetween(s->first, i->first) > 1)
		//					return false;
		//		}
		//		return true;
		//	}
		//	else
		//		return false;
		//}
		//bool isDirectioned()const
		//{
		//	for (auto& i : edges)
		//		if (!i.isBidirectional)
		//			return true;
		//	return false;
		//}
		//bool isInterConnected() const
		//{
		//	return this->CountOfComponents() == 1;
		//}
		//bool isDicotyledonous() const;
		//int CountOfComponents() const;

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
//}