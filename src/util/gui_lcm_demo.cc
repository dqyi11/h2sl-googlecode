/**
 * @file    gui_lcm_demo.cc
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
 * A GUI_LCM class demo program
 */

#include <iostream>
#include <QtGui/QApplication>

#include "h2sl/parser_cyk.h"
#include "h2sl/gui_lcm.h"
#include "gui_lcm_demo_cmdline.h"

using namespace std;
using namespace h2sl;

int
main( int argc,
      char* argv[] ) {
  gengetopt_args_info args;
  if( cmdline_parser( argc, argv, &args ) != 0 ){
    exit(1);
  }

  cout << "start of GUI_LCM class demo program" << endl;

  QApplication app( argc, argv );

  Grammar * grammar = new Grammar();
  grammar->from_xml( args.grammar_arg );

  Parser< Phrase > * parser = new Parser_CYK< Phrase >();

  World * world = new World();
  if( args.world_given ){
    world->from_xml( args.world_arg );
  }

  Feature_Set * feature_set = new Feature_Set();

  LLM * llm = new LLM( feature_set );
  if( args.llm_given ){
    llm->from_xml( args.llm_arg );
  }

  DCG * dcg = new DCG();

  GUI_LCM gui_lcm( grammar, parser, world, llm, dcg, args.beam_width_arg, args.command_arg, args.world_channel_arg );
  
  if( args.phrase_given ){
    Phrase * phrase = new Phrase();
    phrase->from_xml( args.phrase_arg );
  
//    gui_lcm.dcg()->construct( phrase, world, llm, true );
//    gui_lcm.update_graph();
      
    if( phrase != NULL ){
      delete phrase;
      phrase = NULL;
    }
  }

  gui_lcm.show();

  return app.exec();
}
