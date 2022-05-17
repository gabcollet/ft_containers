/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_node.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:04:07 by gcollet           #+#    #+#             */
/*   Updated: 2022/05/17 14:17:46 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

enum Color {red, black};

namespace ft
{
    template < typename value_type >
    class rb_tree_node 
    {
    
    public:
        rb_tree_node(const value_type& val = value_type(), Color c = red) :
            left(nullptr), right(nullptr), parent(nullptr), data(val), color(c) {}
        
        rb_tree_node<value_type>* left;
        rb_tree_node<value_type>* right;
        rb_tree_node<value_type>* parent;
        value_type data;
        Color color;
    };
}
