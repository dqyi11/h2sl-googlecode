/**
 * @file    feature_word.cc
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
 * The implementation of a class that looks for a word in a phrase
 */

#include <sstream>

#include <h2sl/feature_word.h>

using namespace std;
using namespace h2sl;

Feature_Word::
Feature_Word( const bool& invert,
              const Word& word ) : Feature( invert ),
                                      _word( word ) {

}

Feature_Word::
~Feature_Word() {

}

Feature_Word::
Feature_Word( const Feature_Word& other ) : Feature( other ),
                                            _word( other._word ){

}

Feature_Word&
Feature_Word::
operator=( const Feature_Word& other ) {
  _invert = other._invert;
  _word = other._word;
  return (*this);
}

bool
Feature_Word::
value( const unsigned int& cv,
        const Grounding* grounding,
        const vector< Grounding* >& children,
        const Phrase* phrase,
        const World* world ){
  if( phrase->has_word( _word ) ){
    return !_invert;
  }
  return false;
}

void 
Feature_Word::
to_xml( xmlDocPtr doc, xmlNodePtr root )const{
  xmlNodePtr node = xmlNewDocNode( doc, NULL, ( xmlChar* )( "feature_word" ), NULL );
  stringstream invert_string;
  invert_string << _invert;
  xmlNewProp( node, ( const xmlChar* )( "invert" ), ( const xmlChar* )( invert_string.str().c_str() ) );
  xmlNewProp( node, ( const xmlChar* )( "pos" ), ( const xmlChar* )( pos_t_to_std_string( _word.pos() ).c_str() ) );
  xmlNewProp( node, ( const xmlChar* )( "text" ), ( const xmlChar* )( _word.text().c_str() ) );
  xmlAddChild( root, node );
  return;
}

void 
Feature_Word::
from_xml( xmlNodePtr root ){
  _invert = false;
  _word = Word();
  if( root->type == XML_ELEMENT_NODE ){
    xmlChar * tmp = xmlGetProp( root, ( const xmlChar* )( "invert" ) );
    if( tmp != NULL ){
      string invert_string = ( char* )( tmp );
      _invert = ( bool )( strtol( invert_string.c_str(), NULL, 10 ) );
      xmlFree( tmp );
    }
    tmp = xmlGetProp( root, ( const xmlChar* )( "pos" ) );
    if( tmp != NULL ){
      string pos_string = ( char* )( tmp );
      _word.pos() = pos_t_from_std_string( pos_string );
      xmlFree( tmp );
    }
    tmp = xmlGetProp( root, ( const xmlChar* )( "text" ) );
    if( tmp != NULL ){
      _word.text() = ( char* )( tmp );
      xmlFree( tmp );
    }
  }
  return;
}

namespace h2sl {
  ostream&
  operator<<( ostream& out,
              const Feature_Word& other ) {
    return out;
  }

}
