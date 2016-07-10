# cpswt-hil
Hardware in the Loop (HiL) Gateway/Proxy service example

This repository contains the design documentation and code for a
reference example of Hardware in the Loop (HiL) as a service with
HLA-based distributed simulation.  The HiL is not deployed or managed
by the simulation platform, but merely provides an interface for
discovery, configuration, and data transfer between the simulations
and the HiL.

## Purpose

The purpose of the HiL interface to distributed simulation platforms
is to provide a way for developers to replace parts of the simulated
systems with one or more real systems.  In practice, this replacement
may mean replacing simulated sensor streams with real sensor data,
replacing a simulated plant with a real physical plant (over which the
simulated or real controllers have actuation control), or some
combination thereof.  Since HiL can consist of practically any types
of devices and interfaces, and since the data, configuration, and user
management is domain or system specific, we cannot develop a single
paradigm which governs or covers all possible scenarios.  Instead, we
provide the high-level design and interfaces which enable a
stand-alone service or services (acting as the interface between the
HiL and the distributed simulations) and a corresponding gateway
federate to communicate meaningfully.

This allows the developers/maintainers of the HiL to have complete
control over how they expose their system, w.r.t. which and how many
simulations can connect to their system at a given time, as well as
ensuring that their system remains as stable and safe as they deem
necessary.

Some terms used:

* _ATP_: Application Transport Protocol, the protocols involved when
  HiL processes send data to each other on the HiL network

## Overall Interface

Federates in a federation need to be able to:

* Run-Time:
  * Get sensor data from the HiL
  * Send actuator commands to the HiL
  * Configure HiL controllers that exist (possibly, not required)
  * Send a generic ATP-formatted message (needed?)
* Start-Up:
  * Connection establishment (federation name, security, availability)
  * Requirements specification (what the federation needs from the HiL)
  * Data-Flow configuration: 
    * How to determine which interactions to foward/split to which HiL
      processes on which nodes?
	* How to determine which messages to forward/split to which
      federates?
  * How to configure the mapping between the interactions and the ATP
    messages?  ATP messages aren't known by the federation and the
    interactions aren't known by the HiL (which may even be
    communicating with multiple federations which each have completely
    different interactions; possibly with the same name)

For these interfaces, we need to be able to clearly specify what we
mean by requirements and their properties, i.e. what are the entities
and their properties that the federation will request from the HiL and
that the HiL will have to determine if it has?  This may also include
the datatypes and messages within the HiL.

What is the best interaction structure which the HiL gateway/proxy
federate will communicate with?  Who writes/generates the mapping
between interaction data and HiL interface data (which is somewhat
standardized).

What are the timing properties and requirements on the interactions
with the HiL?  And how does the timing and execution of the HiL
interact with the timing and execution of the gateway/proxy federate?
So far the best design is to keep it simple: timestamps are handled at
reception time in either the proxy federate or the HiL service,
i.e. the message generation timestamp (if applicable) occurs whenever
the proces sees the message.  Keeps the specification simple.

Most importantly: all interfaces need meaningful errors, esp. the
querying interfaces.

## HIL Service Design



## HIL Gateway/Proxy Design



## Sample Implementation

The sample implementation for this HiL service / proxy will be
developed using C2WT (HLA) for the distributed simulation federates
and using ZeroMQ + Protobuf for the HiL ATP.  The communication
between the proxy federate and the HiL service will be ZeroMQ +
Protobuf for ease of specification and for speed.

The sample for this will be a set of traffic intersections.  The
controllers for the traffic lights at the intersections will be
federates in the federation, while the sensors and actuators (and the
physical system) will be the HiL.  The federates will need to get
sensor streams from the HiL which contain the current queue lengths of
cars at each of the intersections, and the controller federates will
send actuation commands to the traffic lights to set their states.

To enable this scenario, the HiL service will provide an interface by
which the proxy federate will query (and validate) the available
traffic lights and sensors which exist in the HiL system and with
which the proxy will establish communication flows.  The flow mapping
between the sensors, actuators, and controllers will be provided as
configuration data to the proxy federate which it will parse and set
up through the configuration interface of the HiL service process.
