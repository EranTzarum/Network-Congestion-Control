# Research project on DoH

**This subject of the DoH is controversial,we tried to look for the best sources**


## Part 1: DNS over HTTPS 

use advantage of DoH:
DoH  helps to prevent DNS spoofing and man-in-the-middle (MitM) attacks. 
In other words, because the session between the browser and the DNS server is encrypted, nobody can alter the resolution request results to point the user's browser toward a fraudulent website.  

## Two disadvantages to using the method:

1. Vocal opponents of DoH, such as Comcast, have shared concerns that DoH would concentrate most of DNS data with Google, giving it control of internet traffic routing and access to large amounts of consumer and competitor data.

2. DoH may not be “good enough” at protecting privacy, due to the fact that it still uses the traditional recursive DNS scheme for lookups.


## Proposal for a solution for disadvantages number 2: 
In disadvantage number 2 the problem is that for example, visiting www.example.com will require queries to both the .com and the example.com DNS servers in order to resolve the request.
Some browsers will take a “greedy” approach to this, requesting the entire domain name at each level in hopes of skipping a few steps. As a result, every DNS server knows the eventual destination of the traffic.
however, this can be mitigated using DNS minimization.

## DoH methods comparisons table:





| First Header  | Second Header |
| ------------- | ------------- |
| Content Cell  | Content Cell  |
| Content Cell  | Content Cell  |






| ------------- | DoH- application layer  | DoH-
proxy server
 | DoH-
proxy local server
 | plugin that implements DoH |
| ------------- | ------------- | ------------- | ------------- | ------------- |
| Advantages  | DoH respecting the intent of the standard which Provides privacy in DNS  | No need to perform any
Another action to work with DoH
 | No need to perform any
Another action to work with DoH.
Mainly suitable for organizations | Suited for individual users |
| Disadvantages | DoH - in the application layer, browsers and other software would bypass traditional DNS and use port 443 to make encrypted requests  | The downside is that the DNS queries still do not come out
Encrypted, until you reach the external proxy server
 | Is necessary to run the local proxy server.
The queries come out encrypted, though they "roam" the unencrypted local network
 | The downside is that if we want an organization to work
In this way we will have to reconfigure each computer
 |


 We think that the **DoH in the application layer** is the best method.


## Let's assume that there is packet loss (packet loss) in an unknown percentage and we want to load a page that needs 25 queries to request all the resources in it. 
A clear advantage that DoH has over Do53 is:
From what we know DoH uses the TCP protocol - this protocol provides reliability over speed so we get minimum of data loss and maximize reliability and information retention , also DoH seeks to improve online privacy by hiding DNS queries from view however DNS uses the UDP protocol - this protocol provides better speed at the expense of data so it is faster but less reliable protocol for information for these reasons in the DoH we are more likely to lose less information over the DNS.



# Congestion Control

 We will explore the differences between Congestion Control (hereafter: "CC") algorithms, specifically, between "cubic", which is the deductive one, and "reno".

 First we will need a large file so write code that produces one or take a file larger than M1 to simulate a big packet.

 So in sender.c we create a FILE and use fseek(filePointer, X , SEEK_SET) resize the file to be 1MB (X == 1024 * 1024 - 1 *size of 1MB file*).

 Next we create to classes - sender.c and measure.c
 sender.c will send our file and change the algo from "cubic" to "reno".

 measure.c will receive the file and measure how long it took to receive everything.
 
 After that, you will make a change in their CC algorithm and repeat the sending and calculation.
 
 To simulate packet loss, we will use a Linux tool called tc.

 If you don't have the tool. Download it using the following command: sudo apt install iproute 
 

 After every run we will generate random packet loss. 
 First round:
 commend: sudo tc qdisc add dev lo root netem loss 10%

 Every other round: 
 commend: sudo tc qdisc change dev lo root netem loss XX% *(XX == 10 or 15 or 20 or 25 or 30)*

 **To return to normal:**
 **commend: sudo tc qdisc del dev lo root netem**

 !!**You can run the code only in a full Linux environment and not through Windows or WSL**!!

 Screenshots:

 No packet loss code run:

 wireshark:

 10% loss:
 10% loss wireshark:
 
 15% loss:
 15% loss wireshark:

 20% loss:
 20% loss wireshark:

 25% loss:
 25% loss wireshark:

 Performance graph:







