/**
 * @file    object.cc
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
 * 02110-1301, USA. *
 * @section DESCRIPTION
 *
 * The implementation of a class used to describe an object
 */

#include "h2sl/objective.h"

using namespace std;
using namespace h2sl;

Objective::
Objective( const string& name,
        const unsigned int& type ) : Grounding(),
                                        _name( name ),
                                        _type( type ) {
  
}

Objective::
Objective( const string& name,
        const objective_type_t& type ) : Grounding(),
                                        _name( name ),
                                        _type( type ) {

}

Objective::
~Objective() {

}

Objective::
Objective( const Objective& other ) : Grounding( other ),
                                _name( other._name ),
                                _type( other._type ) {

}

Objective&
Objective::
operator=( const Objective& other ) {
  _name = other._name;
  _type = other._type;
  return (*this);
}

bool
Objective::
operator==( const Objective& other )const{
  if( _name != other._name ){
    return false;
  } else if ( _type != other._type ){
    return false;
  } else {
    return true;
  }   
}

bool
Objective::
operator!=( const Objective& other )const{
  return !( *this == other );
} 
 
Objective*
Objective::
dup( void )const{
  return new Objective( *this );
}
 
string
Objective::
type_to_std_string( const unsigned int& type ){
  switch( type ){
  case( OBJECTIVE_TYPE_QUICKLY ):
    return "quickly";
    break;
  case( OBJECTIVE_TYPE_SAFELY ):
    return "safely";
    break;
  case( OBJECTIVE_TYPE_COVERTLY ):
    return "covertly";
    break;
  case( OBJECTIVE_TYPE_CAREFULLY ):
    return "carefully";
    break;
  default:
    return "na";
    break;
  }
}

unsigned int
Objective::
type_from_std_string( const string& type ){
  for( unsigned int i = 0; i < NUM_OBJECTIVE_TYPES; i++ ){
    if( type == Objective::type_to_std_string( i ) ){
      return i;
    }
  }
  return OBJECTIVE_TYPE_UNKNOWN;
}

void
Objective::
to_xml( const string& filename )const{
  xmlDocPtr doc = xmlNewDoc( ( xmlChar* )( "1.0" ) );
  xmlNodePtr root = xmlNewDocNode( doc, NULL, ( xmlChar* )( "root" ), NULL );
  xmlDocSetRootElement( doc, root );
  to_xml( doc, root );
  xmlSaveFormatFileEnc( filename.c_str(), doc, "UTF-8", 1 );
  xmlFreeDoc( doc );
  return;
}

void
Objective::
to_xml( xmlDocPtr doc,
        xmlNodePtr root )const{
  xmlNodePtr node = xmlNewDocNode( doc, NULL, ( const xmlChar* )( "object" ), NULL );
  xmlNewProp( node, ( const xmlChar* )( "name" ), ( const xmlChar* )( _name.c_str() ) );
  xmlNewProp( node, ( const xmlChar* )( "type" ), ( const xmlChar* )( Objective::type_to_std_string( _type ).c_str() ) );
  xmlAddChild( root, node );
  return;
}

void
Objective::
from_xml( const string& filename ){
  xmlDoc * doc = NULL;
  xmlNodePtr root = NULL;
  doc = xmlReadFile( filename.c_str(), NULL, 0 );
  if( doc != NULL ){
    root = xmlDocGetRootElement( doc );
    if( root->type == XML_ELEMENT_NODE ){
      xmlNodePtr l1 = NULL;
      for( l1 = root->children; l1; l1 = l1->next ){
        if( l1->type == XML_ELEMENT_NODE ){
          if( xmlStrcmp( l1->name, ( const xmlChar* )( "object" ) ) == 0 ){
            from_xml( l1 );
          }
        }
      }
    }
    xmlFreeDoc( doc );
  }
  return;
}

void
Objective::
from_xml( xmlNodePtr root ){
  if( root->type == XML_ELEMENT_NODE ){
    xmlChar * tmp = xmlGetProp( root, ( const xmlChar* )( "name" ) );
    if( tmp != NULL ){
      _name = ( char* )( tmp );
      xmlFree( tmp );
    }
    tmp = xmlGetProp( root, ( const xmlChar* )( "type" ) );
    if( tmp != NULL ){
      string type_string = ( char* )( tmp );
      _type = Objective::type_from_std_string( type_string );
      xmlFree( tmp );
    }
  }
  return;
}


namespace h2sl {
  ostream&
  operator<<( ostream& out,
              const Objective& other ) {
    out << "Objective(";
    out << "name=\"" << other.name() << "\",";
    out << "type=\"" << Objective::type_to_std_string( other.type() ) << "\",";
    out << ")";
    return out;
  }
}
