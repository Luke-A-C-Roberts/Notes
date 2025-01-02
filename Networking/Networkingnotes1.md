#Routing
RIP protocol - controlls routing in a network
OSPF protocol - Builds routing table to remote networks

S* 0.0.0.0/0 [1/0] via 209.265.200.234, serial0/0/1
R  172.16.1.0/24 via 208.165.200.226, serial0/0/0
O
D

R  stands for RIP
S* stands from default route
O  stands for OSPF
D  stands for EIGRP

serial is the serial port used on the router for the relevent ip


Static routs are manually configured between two points, define an explicit path
any change to the topology means the routs must also be changed.

Default static route is 0.0.0.0 0.0.0.0 for IPv4 and ::/0 for IPv6

Dynamic Routing happens in real time. if the network topology is changed so does the routing
protocols include IGRP EIGRP and BGP.

#OSPF
Open Shortest Parth First (Routing protocol)

uses shortest path first SPF

OSPF works in areas (all routers of the same area carry the same topology)
Data can be routed between areas through a ABR (area border router)

All devices can be set up in an autonomous system AS
Routers send LSAs (link state Advertisements) for topology updates

when we create a network we create a series of "roads" that map data traffic
we identify possible routs for traffic to follow, which paths are better and how paths should be used

OSPF has a dead interval (4 times the hello packet updates)
if the router detects a dead interval it removes it from the routing table

the DR holds the master database of tables
BDR holds the backup

we use the network ommand to specify which interfaces are participating in an OSPF area

DO THE OSPF WORKSHOP!! (this is very important for the ASSESSMENT)

--------

CRC: cyclical redundancy check. Store and forward switches perform error checking on packets.
Switch issues
Collision Domains, Where devices compete for the right to communicate, which can lead to packet collisions
Network Redundancy STP prevents switch loops from occuring on a network by blocking ports.
Switches allow subnetworks to only require one router. the switches extend the routers number of ports
VLANs, certain domains that are for specific users eg in a school guests students staff techies

VLANs have different types
Default:	used for administration
Data:		used for user generated traphic
Native: 	used for untagged traphic
management: 	used for management capabilities

all taffic is tagged for its VLAN
The router allows subnets to communicate with the appropriate VLAN

--------

LAN Attacks
Common security solution using routers, firewalls, intrusion Prevention System (IPSs), and VPN devices protect layer 3 and above
Layer2 must also be protected.
Common Layer 2 attacks include:
	Telnet Attacks
		-Brute force password attacl : trial and error to gain admin password
		-Telnet DoS attack : continuously requests Telnet connections in an attempt to render the Telnet service unevailaible
		-Using SSH instead of telnet mitgates Telnet Attacks
	-MAC Address Table Flooding
		-An attack sends fake source MAC address untill the switch MAC address table is full and the switch is overwhelmed
		-Blocking ports on switches prevents Unauthorized access to the network
	-VLAN Attacks
		-Attacker spoofs a switch's ip address by using an unorthrized connection (trunk)
	-DHCO Attacks
		-An attacker configures a face DHCP server on the network to issue IP addresses to clients

Securer the LAN
	-use secure protocols suck has SSH, SCP, and SSL
  -use secure administrative access an strong passwords

Intro to SNMP
	-simple network management protocol enables network administrators to monitor and manage network nodes
	-it comprises of:
		-SNMP manager:collects information from SNMP agent to the "get" action. Changes configuration on an agent using the "set" action
		-Management Information Base (MIB) stores data and operational statistics about the managed device.
	-SNMP agents reside on managed devices collect and store information about the device
	-This information is stored by the agent locally in the MIB

ACls - access controll lists
Permit or Deny network reaffic
Can be done by IP Address or protocol

//comment on what you are allowing blocking
R3(config)# access-list 1 remark Allow R1 LANs Access

//allows device at 192.168.10.0
R3(config)# access-list 1 permit 192.168.10.0 0.0.0.255

//allows device at 192.168.20.0
R3(config)# access-list 1 permit 192.168.20.0 0.0.0.255

//denies all other traffic
R3(config)# access-list 1 deny any


