/**
 * @file    grounding.cc
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
 * The implementation of a class used to describe a grounding
 */

#include "h2sl/grounding.h"
#include "h2sl/object.h"
#include "h2sl/region.h"
#include "h2sl/constraint.h"
#include "h2sl/objective.h"
#include "h2sl/grounding_set.h"

using namespace std;
using namespace h2sl;

Grounding::
Grounding() {

}

Grounding::
~Grounding() {

}

Grounding::
Grounding( const Grounding& other ) {

}

Grounding&
Grounding::
operator=( const Grounding& other ) {
  return (*this);
}

bool 
Grounding::
operator==( const Grounding& other )const{
  return true;
}

bool 
Grounding::
operator!=( const Grounding& other )const{
  return !( *this == other );
}

Grounding*
Grounding::
dup( void )const{
  return new Grounding( *this );
}

void 
Grounding::
to_xml( const string& filename )const{
  return;
}

void 
Grounding::
to_xml( xmlDocPtr doc, 
        xmlNodePtr root )const{
  return;
}

void 
Grounding::
from_xml( const string& filename ){
  return;
}

void 
Grounding::
from_xml( xmlNodePtr root ){
  return;
}

namespace h2sl {
  ostream&
  operator<<( ostream& out,
              const Grounding& other ) {
    if( dynamic_cast< const Grounding_Set* >( &other ) != NULL ){
      out << *static_cast< const Grounding_Set* >( &other ); 
    } else if( dynamic_cast< const Object* >( &other ) != NULL ){
      out << *static_cast< const Object* >( &other );
    } else if( dynamic_cast< const Region* >( &other ) != NULL ){
      out << *static_cast< const Region* >( &other );
    } else if( dynamic_cast< const Constraint* >( &other ) != NULL ){
      out << *static_cast< const Constraint* >( &other );
    } else if( dynamic_cast< const Objective* >( &other ) != NULL ){
      out << *static_cast< const Objective* >( &other );
    }
    return out;
  }
}
