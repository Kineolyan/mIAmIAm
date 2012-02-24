/*
 * fonctions.hpp
 *
 *  Created on: 28 janv. 2012
 *      Author: oliv
 */

#ifndef FONCTIONS_HPP_
#define FONCTIONS_HPP_

template <typename T>
const T tMaximum(const T& lh, const T& rh)
{	return lh>rh? lh: rh;	}

template <typename T>
const T tMinimum(const T& lh, const T& rh)
{	return lh<rh? lh: rh;	}

template <typename T>
const T vabs(const T& lh)
{	return lh<0? -lh: lh;	}

#endif /* FONCTIONS_HPP_ */
