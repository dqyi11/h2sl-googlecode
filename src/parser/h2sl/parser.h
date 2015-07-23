/**
 * @file    parser.h
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
 * The definition of a class that describes a parser
 */

#ifndef H2SL_PARSER_H
#define H2SL_PARSER_H

#include <iostream>
#include <boost/algorithm/string.hpp>

#include "h2sl/word.h"
#include "h2sl/grammar.h"

namespace h2sl {
  template< class T >
  class Parser {
  public:
    Parser();
    virtual ~Parser();
    Parser( const Parser<T>& other );
    Parser<T>& operator=( const Parser<T>& other );

    virtual bool parse( const Grammar& grammar, const std::string& text, std::vector<T*>& phrases, const bool& debug = false )const = 0;

  protected:
    virtual void _text_to_words( const std::string& text, std::vector< Word >& words )const;

  private:

  };

  template< class T >
  std::ostream& operator<<( std::ostream& out, const Parser<T>& other );
  #include "h2sl/parser.ipp"
}

#endif /* H2SL_PARSER_H */
