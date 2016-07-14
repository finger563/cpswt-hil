#include "main.hpp"

void HILProxy::initialize( void )
{
  HILProxyATRCallback hilproxyATRCb( *this );
  putAdvanceTimeRequest(  _currentTime, hilproxyATRCb );

  readyToPopulate();
  readyToRun();
}

void HILProxy::execute( void )
{
  // update class variables
  _currentTime += 1;

  // init temporary variables
  InteractionRoot::SP interactionRootSP;

  // GET MESSAGES HERE FROM HLA
  while ( (interactionRootSP = getNextInteraction() ) != 0 )
    {
    }

  // Advance Time
  HILProxyATRCallback hilproxyATRcb( *this );
  putAdvanceTimeRequest( _currentTime, hilproxyATRcb );
}

int main(int argc, char** argv)
{
  std::cout << "Creating HILProxy Object" << std::endl;
  HILProxy hilproxy( argc, argv );
  std::cout << "HILProxy created" << std::endl;

  std::cout << "Initializing HILProxy" << std::endl;
  hilproxy.initialize();
  std::cout << "HILProxy initialized" << std::endl;

  std::cout << "Running HILProxy" << std::endl;
  hilproxy.run();

  kill(0, SIGKILL);

  return 0;
}
