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

Some browsers will take a “greedy” approach to this, requesting the entire domain name at each level in hopes of skipping a few steps.

As a result, every DNS server knows the eventual destination of the traffic.

however, this can be mitigated using DNS minimization.

## DoH methods comparisons table:





| ------------- | DoH-application layer  | DoH-proxy server | DoH-proxy local server  | plugin that implements DoH  |
| ------------- | ------------- | ------------- | ------------- | ------------- |
| Advantages  | DoH respecting the intent of the standard which Provides privacy in DNS  | No need to perform any Another action to work with DoH  | No need to perform any Another action to work with DoH. Mainly suitable for organizations  | Suited for individual users  |
| Disadvantages  | DoH - in the application layer, browsers and other software would bypass traditional DNS and use port 443 to make encrypted requests  | The downside is that the DNS queries still do not come out Encrypted, until you reach the external proxy server  | Is necessary to run the local proxy server. The queries come out encrypted, though they "roam" the unencrypted local network  | The downside is that if we want an organization to work In this way we will have to reconfigure each computer  |




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
 

 # Screenshots:

 ## No packet loss code run:
 
 ![measure_sender](https://user-images.githubusercontent.com/106338500/184532237-4053d51b-49dd-4a59-9dbe-3d65bbdc9d4c.png)


 ## wireshark:
 
 ![measure_sender_wiresharke](https://user-images.githubusercontent.com/106338500/184532258-18d3c50d-3447-4a2c-b37e-93487299a793.png)


 ## 10% loss:
 
![10%](https://user-images.githubusercontent.com/106338500/184532263-08ab4f38-1e4f-4f45-bb8b-d3bb68f98e02.png)

 
 ## 10% loss wireshark:
 
 ![10_w](https://user-images.githubusercontent.com/106338500/184532266-70fa6c68-e1a2-4dda-9677-01b77ccda34c.png)

 
 ## 15% loss:
 
 ![15%](https://user-images.githubusercontent.com/106338500/184532269-c53fe32e-0952-4189-b7fd-e050203fa6bb.png)

 ## 15% loss wireshark:
 
 ![15_w](https://user-images.githubusercontent.com/106338500/184532278-387bb75a-e199-46e0-ad79-3c4148108e3b.png)
 
 ## 20% loss:
 
 ![20%](https://user-images.githubusercontent.com/106338500/184532288-a404b012-3269-4ae4-92d3-9455ccd21691.png)

 ## 20% loss wireshark:
 
  ![20_w](https://user-images.githubusercontent.com/106338500/184532295-aa9ac1a0-b1d0-48b8-9fe6-b6842bf53aad.png)

 ## 25% loss:
 
 ![25%](https://user-images.githubusercontent.com/106338500/184532305-dd493c00-9df9-4d43-93dd-5fbf319daf6e.png)

 ## 25% loss wireshark:
 
 ![25_w](https://user-images.githubusercontent.com/106338500/184532318-198312fe-d0f9-4e87-a3fa-443f9cf16470.png)

 ## Performance graph:
 
 
![graph](https://user-images.githubusercontent.com/106338500/184532337-40f221fd-4e84-4727-ae35-f2f26c730329.png)

