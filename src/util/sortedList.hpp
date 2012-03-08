/*
 * fonctions.hpp
 *
 *  Created on: 28 janv. 2012
 *      Author: oliv
 */

#ifndef SORTEDLIST_HPP_
#define SORTEDLIST_HPP_

#include <list>
#include <iterator>

template <class Score, class Contenu>
class SortedList {
public:
	typedef typename std::pair<Score, Contenu*> Item;
	typedef typename std::list<Item> Liste;
	typedef typename Liste::iterator Iterator;

	class iterator {
	private:
		Iterator m_element;

	public:
		iterator(const Iterator& element):
			m_element(element) {}

		iterator(const iterator& position):
			m_element(position.m_element) {}

		iterator& operator++()
		{	++m_element; return *this;	}

		iterator operator++(int)
		{	iterator tmp(*this); operator++(); return tmp;	}

		bool operator==(const iterator& rhs) const
		{	return m_element==rhs.m_element;	}

		bool operator!=(const iterator& rhs) const
		{	return m_element!=rhs.m_element;	}

		Contenu& operator*()
		{	return *(m_element->second);	}

		Contenu* operator->()
		{	return m_element->second;	}
	};

	class Comparator {
	public:
		bool operator() (Item& lhs, Item& rhs)
		{	 return (lhs.first < rhs.first);	}
	};

private:
	/**
	 * Liste des maximums tri�s par ordre croissant
	 */
	Liste m_items;

public:
	SortedList():
		m_items() {}

	~SortedList() {}

	void ajouter(const Score& score, Contenu& contenu) {
		m_items.push_back(Item(score, &contenu));
	}

	void sort() {
		m_items.sort(SortedList::Comparator());
	}

	iterator begin()
	{	return iterator(m_items.begin());	}

	iterator end()
	{	return iterator(m_items.end());	}
};

#endif /* SORTEDLIST_HPP_ */
