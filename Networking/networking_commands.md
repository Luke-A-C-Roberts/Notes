#configuring routers

en
#enables configuration mode

conf t
#begins configuration

hostname <hostname>
#sets hostname to any string

no ip domain-lookup
#prevents DNS lookup

service password-encryption
#allows password to be set

enable secret class
#allows the secret class (super user)

banner motd #
<warning message> #
#banner message

line con 0
#starts writing config lines

password <password>
#sets password

login
#allows logging in

logging synchronous
#prevents you from being interupted during login

line vty 0 4
#allows the network to be visable to outside networks (potentially)

login
exit

end

copy run start
#copies the newly created config into the start config

#interfacing router ports

int <interface>
#begins configuring interface

ip add <ip address> <subnet mask>
#sets ip and subnet

clock rate <clock rate>
#sets clock rate

no shutdown
#opens the connection