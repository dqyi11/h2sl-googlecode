/**
 * @file    dcg.h
 * @author  Thomas M. Howard (tmhoward@csail.mit.edu)
 *          Matthew R. Walter (mwalter@csail.mit.edu)
 * @version 1.0
 *
 * @section LICENSE
 *
 * This file is part of h2sl.
 *
 * Copyright (C) 2014 by the Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see
 * <http://www.gnu.org/licenses/gpl-2.0.html> or write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 * @section DESCRIPTION
 *
 * The interface for a class used to represent a Distributed Correspondence
 *   Graph
 */

#ifndef H2SL_DCG_H
#define H2SL_DCG_H

#include <iostream>
#include <vector>

#include "h2sl/phrase.h"
#include "h2sl/world.h"
#include "h2sl/llm.h"
#include "h2sl/factor_set.h"

namespace h2sl {
  class DCG {
  public:
    DCG();
    virtual ~DCG();
    DCG( const DCG& other );
    DCG& operator=( const DCG& other );

    virtual void fill_search_spaces( const World* world );
    void construct( const Phrase* phrase, const World* world, const bool& fill = false );
    bool leaf_search( const Phrase* phrase, const World* world, LLM* llm, const unsigned int beamWidth = 4, const bool& debug = false );

    void to_latex( const std::string& filename )const;

    inline const std::vector< std::vector< std::pair< std::vector< unsigned int >, Grounding* > > >& search_spaces( void ){ return _search_spaces; };
    inline const std::vector< std::pair< double, Phrase* > >& solutions( void )const{ return _solutions; };
    inline const Factor_Set* root( void )const{ return _root; };

  protected:
    virtual void _find_leaf( Factor_Set* node, Factor_Set*& leaf );
    virtual void _fill_phrase( Factor_Set* node, Factor_Set_Solution& solution, Phrase* phrase );
    virtual void _fill_factors( Factor_Set* node, const Phrase* phrase, const bool& fill = false );

    std::vector< std::vector< std::pair< std::vector< unsigned int >, Grounding* > > > _search_spaces;
    std::vector< std::pair< double, Phrase* > > _solutions;
    Factor_Set * _root;
  
  private:

  };
  std::ostream& operator<<( std::ostream& out, const DCG& other );
}

#endif /* H2SL_DCG_H */
