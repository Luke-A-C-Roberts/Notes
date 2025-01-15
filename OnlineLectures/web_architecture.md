Web Architecture
=================

*Monolithic*: bundling all features
*Microservice*: Seperated on different hardware (not one codebase), the services of the system are modular.
*Serverless*: (AKA serverless computing/ function as a service (FaaS)), one or more of the microservices are hosted by a third party.

Major component relationships.

*Client-server* architecture

Client + Server + Database: 1 tier
Client | Server + Database: 2 tier
Client | Server + Database: 2 tier
Client | Server | Database: 3 tier
N tier (Single responsibility principle)

Client -HTTP-> Server: Call/ Request
Client <-HTTP- Server: Response

*Peer-to-peer* architecture
For example web3 blockchain
Distributed


## HTTP requests

**IKEA** store analogy.

Three lines of customers with three resceptionists

-LINE1-> Resceptionist1 (Mandarin) | Warehouse parts (warehouse language)
-LINE2-> Resceptionist2 (English)  |
-LINE3-> Resceptionist3 (Swedish)  |

Browser sends HTTP request to DNS server. DNS server retrieves external IP address, and sends request to the web server. The request is queued and eventually retrieves the information.

MVC framework
M: Models   (database)
V: Views    (UI)
C: Controll (Middleware)


