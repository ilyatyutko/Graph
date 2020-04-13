#pragma once
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <cassert>
#include <functional>
#include <algorithm>

namespace TyutkoMath {
	typedef int topKey;
	typedef unsigned char byte;
	class unorderedEdge;
	class orderedEdge;

	class base_Edge
	{
	protected:
		topKey from;
		topKey to;

	public:
		base_Edge(topKey _from, topKey _to);
		base_Edge(base_Edge const& source);

		bool isLoop()const;
		bool isIncidentTo(topKey top)const;
		std::pair<topKey, topKey> GetIncidentTops()const;

		virtual std::string ToString() const = 0;

		friend class Graph;
		friend class orderedEdge;
		friend class unorderedEdge;
	};

	class unorderedEdge : public base_Edge
	{
	public:
		unorderedEdge(int from, int to);
		unorderedEdge(unorderedEdge const& edge);

		unorderedEdge& operator=(unorderedEdge const& source);
		bool operator<(unorderedEdge const& toCompare) const;
		bool operator>(unorderedEdge const& toCompare) const;
		bool operator==(unorderedEdge const& toCompare) const;

		bool ifBounds(const topKey a, const  topKey b) const;
		bool ifProvideTheSameWay(base_Edge const& toCompare) const;
		std::pair<orderedEdge, orderedEdge> getCutted() const;

		std::string ToString() const override;

		friend class orderedEdge;
	};

	class orderedEdge : public base_Edge
	{
	public:
		orderedEdge(int from, int to);
		orderedEdge(base_Edge const& edge);

		orderedEdge& operator=(orderedEdge const& source);
		bool operator<(orderedEdge const& toCompare) const;
		bool operator>(orderedEdge const& toCompare) const;
		bool operator==(orderedEdge const& toCompare) const;

		bool ifBounds(const topKey a, const  topKey b) const;
		bool ifProvideTheSameWay(unorderedEdge const& toCompare) const;
		bool ifProvideTheSameWay(orderedEdge const& toCompare) const;
		bool wentOutFrom(topKey top)const;
		bool wentInTo(topKey top)const;
		orderedEdge GetGeneralized() const;
		orderedEdge& reverse();
		orderedEdge GetReversed() const;

		std::string ToString() const override;
	};

	template<class EdgeValue>
	class orderedFilledEdge : public orderedEdge
	{
	public:
		EdgeValue value;
		orderedFilledEdge<EdgeValue>(topKey _from, topKey _to)
			: orderedEdge(_from, _to)
			, value(EdgeValue())
		{}
		orderedFilledEdge<EdgeValue>(topKey _from
			, topKey _to
			, EdgeValue _value = EdgeValue())
			: orderedEdge(_from, _to)
			, value(_value)
		{
			assert(_from >= 0);
			assert(_to >= 0);
		}

		orderedFilledEdge& operator=(orderedFilledEdge const& source)
		{
			from = source.from;
			to = source.to;
			value = EdgeValue(source.value);
		}
		orderedFilledEdge& operator=(orderedFilledEdge&& source)
		{
			from = source.from;
			to = source.to;
			value = std::move(source.value);
			source.value = EdgeValue();
		}
		bool operator<(orderedFilledEdge const& toCompare) const
		{
			if (this->from < toCompare.from) return true;
			if (this->from == toCompare.from)
			{
				if (this->to < toCompare.to) return true;
				if (this->to == toCompare.to
					&& this->value < toCompare.value) return true;
			}
			return false;
		}
		bool operator>(orderedFilledEdge const& toCompare) const
		{
			if (this->from > toCompare.from) return true;
			if (this->from == toCompare.from)
			{
				if (this->to > toCompare.to) return true;
				if (this->to == toCompare.to
					&& this->value > toCompare.value) return true;
			}
			return false;
		}
		bool operator==(orderedFilledEdge const& toCompare) const
		{
			return to == toCompare.to
				&& from == toCompare.from
				&& value == toCompare.value;
		}
	};

	template<class EdgeValue>
	class unorderedFilledEdge : public unorderedEdge
	{
	public:
		EdgeValue value;
		unorderedFilledEdge<EdgeValue>(unorderedFilledEdge const& source) : base_Edge(source.from, source.to)
			, value(source.value)
		{}
		unorderedFilledEdge<EdgeValue>(unorderedFilledEdge&& source) : base_Edge(source.from, source.to)
			, value(std::move(source.value))
		{}
		unorderedFilledEdge<EdgeValue>(topKey _from
			, topKey _to
			, EdgeValue _value = EdgeValue())
			: unorderedEdge(_from, _to)
			, value(_value)
		{
			assert(_from >= 0);
			assert(_to >= 0);
		}

		unorderedFilledEdge& operator=(unorderedFilledEdge const& source)
		{
			from = source.from;
			to = source.to;
			value = EdgeValue(source.value);
		}
		unorderedFilledEdge& operator=(unorderedFilledEdge&& source)
		{
			from = source.from;
			to = source.to;
			value = std::move(source.value);
			source.value = EdgeValue();
		}
		bool operator<(unorderedFilledEdge const& toCompare) const
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
		bool operator>(unorderedFilledEdge const& toCompare) const
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
		bool operator==(unorderedFilledEdge const& toCompare) const
		{
			return to == toCompare.to
				&& from == toCompare.from
				&& value == toCompare.value;
		}
		EdgeValue& operator*() const
		{
			return this->value;
		}
	};
}