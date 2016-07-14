#include "main.hpp"

void Controller::initialize( void )
{
  ControllerATRCallback ctrlfedATRCb( *this );
  putAdvanceTimeRequest(  _currentTime, ctrlfedATRCb );

  readyToPopulate();
  readyToRun();
}

void Controller::execute( void )
{
  // update class variables
  _currentTime += 1;

  // GET MESSAGES HERE FROM HLA
  // init temporary variables
  InteractionRoot::SP interactionRootSP;

  while ( (interactionRootSP = getNextInteraction() ) != 0 )
    {
    }

  // Advance Time
  ControllerATRCallback ctrlfedATRcb( *this );
  putAdvanceTimeRequest( _currentTime, ctrlfedATRcb );
}

int main(int argc, char** argv)
{
  std::cout << "Creating Controller Object" << std::endl;
  Controller ctrlfed( argc, argv );
  std::cout << "Controller created" << std::endl;

  std::cout << "Initializing Controller" << std::endl;
  ctrlfed.initialize();
  std::cout << "Controller initialized" << std::endl;

  std::cout << "Running Controller" << std::endl;
  ctrlfed.run();

  return 0;
}
