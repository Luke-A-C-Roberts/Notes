# Networking Devices and their Operations

## Switches
physical device that operates on the data link layer of the OSI7 model. It takes in
packets from devices and forwards them to a specific device intended to be reached.
when a device connects to a switch the switch remembers the MAC address. It uses this to
know where to send and recieve packets. When a packet is sent it reads the address in
the packet header and sends the packets through the appropreate port. Most switches are
full-duplex so packets have access to the full bandwidth of the switch connection. Some
switches are also compatable with layer 3 functionality like VLANS.

## Routers
Routers are at the network layer of the OSI7 model and allow the sending of packets from
one network to another via forwarding IP. Routing is the ability to forward IP packets,
a package of data with an ip address from one network to another. The router is therefor
used to connext the networks in a super-network together and manage traffic within these
networks. Routers usually more than one NIC to connect to multiple networks and
additionally find the shortest path of data transfer between network devices, called the
metric value or preference number. It will always choose paths with lower metric if more
than one is availible, and each metric is stored in a routing table.

## Static Routing: each route is specified manually and if there is a change it needs to
be updated.

## Dynamic Routing: happens in real time and a change to the topology means there will be
a change to the routing tables.

--OSI 7 Layer Model--
7	Application		Data		high level protocols and resorce sharing		HTTP SSH
6	Presentation	Data		encription, encoding & compression					TLS
5	Session				Data		handles multiple transmission and exchange	Sockets RTP
4	Transport			Segment	handles reliability of transmission of data	TCP UDP
3	Network				Packet	addressing and routing of packets						IP RIP OSPF
2	Data Link			Frame		transmission between two nodes							MAC
1	Physical			Bit			transmision of data via physical medium			Ethernet

# Internet Protocol
when a packet is sent in the Network layer, the packet gets an IP header for the
destination of the packet. When the packet is recieved by the router, it does a lookup
for the corresponding ethernet port and MAC address and replaces the ethernet and MAC
headers of the packet and then sends the packet.

# Encapsulation and Decapsulation
encapsulation is the process of adding headers to the data being sent

Application Layer
-     data     -

Transport Layer
-Segment Header-
-     data     -

Network Layer
-Packet Header -
-Segment Header-
-     data     -

Data Layer
- Frame Header -
-Packet Header -
-Segment Header-
-     data     -

In decapsulation, decapsulation happens layer by layer so for example the packet header
is removed during decapsulation in the network layer (the same one it was added)

# RIP and OSPF

