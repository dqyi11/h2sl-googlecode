/**
 * @file    objective.h
 * @author  Daqing Yi (daqing.yi@byu.edu)
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
 * The interface for a class used to describe an objective
 */

#ifndef H2SL_OBJECTIVE_H
#define H2SL_OBJECTIVE_H

#include <iostream>
#include <libxml/tree.h>

#include "h2sl/grounding.h"
#include "h2sl/transform.h"

namespace h2sl {
  typedef enum {
    OBJECTIVE_TYPE_UNKNOWN,
    OBJECTIVE_TYPE_QUICKLY,
    OBJECTIVE_TYPE_SAFETLY,
    OBJECTIVE_TYPE_COVERTLY,
    OBJECTIVE_TYPE_CAREFULLY,
    NUM_OBJECTIVE_TYPES
  } objective_type_t;

  class Objective: public Grounding {
  public:
    Objective( const std::string& name = "na", const unsigned int& type = 0 );
    Objective( const std::string& name, const object_type_t& type );
    virtual ~Objective();
    Objective( const Objective& other );
    Objective& operator=( const Objective& other );
    bool operator==( const Objective& other )const;
    bool operator!=( const Objective& other )const;
    virtual Objective* dup( void )const;

    static std::string type_to_std_string( const unsigned int& type );
    static unsigned int type_from_std_string( const std::string& type );

    virtual void to_xml( const std::string& filename )const;
    virtual void to_xml( xmlDocPtr doc, xmlNodePtr root )const;

    virtual void from_xml( const std::string& filename );
    virtual void from_xml( xmlNodePtr root );

    inline std::string& name( void ){ return _name; };
    inline const std::string& name( void )const{ return _name; };
    inline unsigned int& type( void ){ return _type; };
    inline const unsigned int& type( void )const{ return _type; };

  protected:
    std::string _name;
    unsigned int _type;

  private:

  };
  std::ostream& operator<<( std::ostream& out, const Objective& other );
}

#endif /* H2SL_OBJECTIVE_H */
