 #Congestion Control

 we will explore the differences between Congestion Control (hereafter: "CC") algorithms, specifically, between "cubic", which is the deductive one, and "reno".

 First we will need a large file so write code that produces one or take a file larger than M1 to simulate a big packet.
 So in sender.c we create a FILE and use fseek(filePointer, X , SEEK_SET) resize the file to be 1MB (X == 1024 * 1024 - 1 *size of 1MB file*).

 Next we create to classes - sender.c and measure.c
 sender.c will send our file and change the algo from "cubic" to "reno".
 measure.c will receive the file and measure how long it took to receive everything.
 After that, you will make a change in their CC algorithm and repeat the sending and calculation. To simulate packet loss, we will use a Linux tool called tc.

 If you don't have the tool. Download it using the following command: sudo apt install iproute 
 

 After every run we will generate random packet loss. 
 First round:
 commend: sudo tc qdisc add dev lo root netem loss 10%

 Every other round: 
 commend: sudo tc qdisc change dev lo root netem loss XX% *(XX == 10 or 15 or 20 or 25 or 30)*

 *To return to normal:*
 *commend: sudo tc qdisc del dev lo root netem*

 !!*You can run the code only in a full Linux environment and not through Windows or WSL*!!