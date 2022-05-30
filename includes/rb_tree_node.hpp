/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_node.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:04:07 by gcollet           #+#    #+#             */
/*   Updated: 2022/05/30 11:38:27 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils.hpp"
#include <cstddef>

enum Color {red, black};

namespace ft
{
    template < typename value_type >
    class rb_tree_node 
    {
    
    public:
        typedef rb_tree_node<value_type>*       node_pointer;
        
        node_pointer    left;
        node_pointer    right;
        node_pointer    parent;
        value_type      data;
        Color           color;
        bool            end;
    };

    // struct rb_tree_endNode
    // {
    //     typedef rb_tree_endNode*       node_pointer;
        
    //     node_pointer    parent;
    //     bool            end;
    // };
}
