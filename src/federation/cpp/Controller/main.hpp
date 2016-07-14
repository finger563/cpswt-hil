#ifndef MAIN_HPP
#define MAIN_HPP

#include "ControllerBase.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Controller : public ControllerBase
{
private:
  double _currentTime;
public:
  typedef ControllerBase Super;
  Controller( int argc, char *argv[] ) 
    : Super( argc, argv ), _currentTime( 0 ) { }
  virtual ~ Controller( void )
    throw (RTI::FederateInternalError) { }

  class ControllerATRCallback : public ATRCallback 
  {
  private:
    Controller &_ctrlfed;
  public:
    ControllerATRCallback( Controller &ctrlfed ) : _ctrlfed( ctrlfed ) { }
    virtual void execute( void ) { _ctrlfed.execute(); }
    virtual SP clone( void ) { return SP( new ControllerATRCallback( *this ) ); }
  };

  void initialize( void );
  void execute( void );
};

#endif
