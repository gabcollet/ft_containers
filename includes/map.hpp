/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:08:45 by gcollet           #+#    #+#             */
/*   Updated: 2022/05/03 16:19:31 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <functional>
#include "pair.hpp"

namespace ft
{
    template< class Key, 
              class T, 
              class Compare = std::less<Key>,
              class Allocator = std::allocator<ft::pair<const Key, T> > > 
    class map
    {
        
    };
}
