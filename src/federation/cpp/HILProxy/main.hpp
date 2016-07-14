#ifndef MAIN_HPP
#define MAIN_HPP

#include "HILProxyBase.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class HILProxy : public HILProxyBase 
{
private:
  double _currentTime;
public:
  typedef HILProxyBase Super;
  HILProxy( int argc, char *argv[] ) 
    : Super( argc, argv ), _currentTime( 0 ) { }
  virtual ~ HILProxy( void )
    throw (RTI::FederateInternalError) { }

  class HILProxyATRCallback : public ATRCallback 
  {
  private:
    HILProxy &_hilproxy;
  public:
    HILProxyATRCallback( HILProxy &hilproxy ) : _hilproxy( hilproxy ) { }
    virtual void execute( void ) { _hilproxy.execute(); }
    virtual SP clone( void ) { return SP( new HILProxyATRCallback( *this ) ); }
  };

  void initialize( void );
  void execute( void );
};

#endif
