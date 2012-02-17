/*
 * fonctions.hpp
 *
 *  Created on: 28 janv. 2012
 *      Author: oliv
 */

#ifndef MAXLIST_HPP_
#define MAXLIST_HPP_

#include <list>
#include <iterator>

template <class Score, class Contenu>
class ListeMax {
public:
	typedef typename std::pair<Score, Contenu*> Item;
	typedef typename std::list<Item> Liste;
	typedef typename Liste::iterator Iterator;

	class iterator: public std::iterator<std::output_iterator_tag, typename Contenu*> {
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

private:
	/**
	 * Liste des maximums triés par ordre croissant
	 */
	Liste m_items;

	/**
	 * Nombre d'items maximum à garder
	 */
	const int m_taille;

	void ajouterItem(const Score& score, Contenu& contenu) {
		Iterator item = m_items.begin(), _end = m_items.end();
		for (; item!=_end; ++item) {
			if (score>item->first) {
				m_items.insert(item, Item(score, &contenu));
				return;
			}
		}
		m_items.push_back(Item(score, &contenu));
	}

	void remplacerItem(const Score& score, Contenu& contenu) {
		Iterator item = m_items.begin(), _end = m_items.end();
		for (; item!=_end; ++item) {
			if (score>item->first) {
				m_items.insert(item, Item(score, &contenu));
				m_items.pop_back();
			}
		}
	}

public:
	ListeMax(int taille):
		m_items(),
		m_taille(taille) {}

	~ListeMax() {}

	void ajouter(const Score& score, Contenu& contenu) {
		if (m_taille==m_items.size()) {
			remplacerItem(score, contenu);
		}
		else {
			ajouterItem(score, contenu);
		}
	}

	iterator begin()
	{	return iterator(m_items.begin());	}

	iterator end()
	{	return iterator(m_items.end());	}
};

#endif /* MAXLIST_HPP_ */
