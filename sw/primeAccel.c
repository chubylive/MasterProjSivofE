chubylive
#1588

Khoa — 02/20/2022
i'd like to quick meeting now to describe to you how the build process will work for you. and then i'd like you to try it out yourself, and then let me know if it works for you, or if you run into any issues that i need to fix
Stew — 02/20/2022
sure i'm here
Khoa — 02/20/2022
i am not done with my C code for the program yet. for that, I'd like a quick meeting tomorrow (I will be done with the C code tomorrow) when we can talk about the C program. but let's get the build process out of the way now.
chubylive — 02/20/2022
looks good. got a bin file
Khoa — 02/20/2022
Super
Stew — 02/20/2022
yeah got a bin as well! never doubted you man
Khoa — 02/20/2022
We are ready to roll. Yay.
Khoa — 02/21/2022
please don't wait for me if you have other things to do. i am still debugging. i'll give out an update later tonight when i am done. i will post what i currently have later tonight as well.
i will post in git
Stew — 02/21/2022
👍
chubylive — 02/21/2022
if you want another pair of eyes i am available
Khoa — 02/21/2022
Thanks Chuby! I'll let you know.
Khoa — 02/22/2022
i just checked in our first working program. it is in sw @ sw/0.c . sorry for the delay! it works. let's have a quick meeting tomorrow. that program that i just checked in finds all prime numbers using all available bram, which is currently 256 pe multiply 16kilobits for each pe, meaning it finds all primes up to 256 * 16 * 1024 - 1 = 4194303. it means it finds correctly all primes that are less than or equal 4194303
it runs pretty quickly
there are things remaining that i still need to do of course, and i found a number of optimizations that can be done to make it run even faster, and we can put in clock counter to measure performance.
and we can use up all bram to have 280 pe's, and there are other things that can be done as well.
Khoa — 02/22/2022
guys, let's have a quick meeting!
Khoa — 02/22/2022
write registers: 0: argument1 : step for compute, row for read mem
code cmd: 0: compute 1: clear 2: read memm
write registers: 1: argument2 , and 3,     2 lower 16 bits 3 upper 16 bits
write registers 2: cmd     5:4
Stew — 02/22/2022
code cmd: 0: compute 1: clear 2: read memm
Khoa — 02/22/2022
write registers :3
write registers :3   noop , read only
read registers 0 and 1 same as before
2 same as before with status in bit 0
status is readonly
read registers 3: mem read data
chubylive — 02/22/2022
Image
Khoa you da man! I can add timing code blocks
pretty epic actually
Khoa — 02/22/2022
yay
chubylive — 02/25/2022
compute all took: 0.102445 seconds
read all took: 0.313863 seconds
output.txt
1 KB

#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
Expand
0.c
10 KB
less than a second to execute the compute command
the read takes longer. I took out the print statement to get a better time
Stew — 02/25/2022
nice
haven't gotten a chance to work on my part yet, will start this weekend
chubylive — 02/28/2022
I wrote a kernel module for the code
you can try loading it with ismod
I am getting 75msec compute time
so a little faster but the printk is really slow so printing the primes takes a long time
a really long time
Attachment file type: unknown
myprog_u
10.84 KB
Attachment file type: unknown
primeAccel.ko
13.00 KB
/*
* ioctl.c - the process to use ioctl's to control the kernel module
*
* Until now we could have used cat for input and output. But now
* we need to do ioctl's, which require writing our own process.
*/
Expand
userApp.c
3 KB
/*  primeAccel.c - The simplest kernel module.

* Copyright (C) 2013 - 2016 Xilinx, Inc
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
Expand
primeAccel.c
17 KB
man theres a lot of prime numbers
I almost feel like we could do interrupts but meh
Khoa — 02/28/2022
wow. so going to the kernel does make the code to run faster.
by the way, guys if you have question please let me know.
just some update from me: i still need to check in git, but i currently have a new build (and verify using C code that it is working) where we can maximize bram usage all the way to 100% and max out the number of pe at 280. this working build also includes already a number of other optimizations in the hardware design. but recently, after getting the 280-pe build to work, i discovered yet more hardware optimizations that i can do. however, for the second group of hardware optimization features that i recently discover, i will have to do them later since right now i am concentrating on the remaining computing methods.
so far we completed the computing method #1
one thing i forget to let you know (i will need to explain more details in our next meeting) that the computing method #2 can use the same exact build as computing method #1, but only the software is different. and computing method #2 allows the computing to twice the maximum limit compared to method #1 and therefore about twice the number of primes  being discovered compared to #1. again, only the software is different. the hardware can stay the same with absolutely no performance penalty. and i already got a working C program for computing method #2.
so with that we are done with the first two methods #1 and #2
currently i am working on the hardware for computing method #3. again as i mentioned before, everything can stay the same including about more than half of the PE rtl design. some of the internal design of the pe will have to change for computing methods #3 and #4 and i am doing that.
so time continues to be tight, and we all need to continue to push hard.
but do not panic since i think we will get it all done guys.
and we need also the final presentation and the report.
Stew — 03/01/2022
I have already started w/ the report
also checked in some changes to make the row/#pe modifiable i also  put everything into a class ... using cpp for the driver code, can change if we don't want it that way i guess
i want to get some timing diagrams
this is what i'm seeing so far
Image
does that make sense?
also i didn't see a progress update 4 in canvas...
Khoa — 03/01/2022
the prof did not hand out assignment 4 i guess
let's just have a quick meeting either today or tomorrow just to catch up on things, then we can run off to our little corners and keep pushing forward
Stew — 03/01/2022
ok i'll be free tomorrow
Khoa — 03/01/2022
ok let's make it tomorrow. a quick one just to tag up.
Stew — 03/02/2022
do we still plan on meeting today?
Khoa — 03/02/2022
yes can we meet quickly @ 5:30 CA time, which is 7:30 TX time, and 8:30 DC time? just a quick one.
Stew — 03/02/2022
ok
chubylive — 03/03/2022
yeah I will be available
chubylive — 03/03/2022
we meeting?
Stew — 03/03/2022
we met yesterday @chubylive
chubylive — 03/03/2022
oh dang I thought it was today
I was out kold yesterday
Stew — 03/03/2022
np it's just pretty much what khoa typed in chat
chubylive — 03/03/2022
what did I miss
Stew — 03/03/2022
going to have the fully utilized bram by this weekend and he's also working the #2 and #3 algorithm compute
chubylive — 03/03/2022
kay. We need to put stuff together for the presentation
Stew — 03/03/2022
yea
chubylive — 03/03/2022
did he give us a guide?
Stew — 03/03/2022
don't think so
chubylive — 03/03/2022
hm. I guess we just start a power point
do we have a software implementation of the seive?
something like this should work a comparison against a single pe https://www.geeksforgeeks.org/sieve-of-eratosthenes/
GeeksforGeeks
Sieve of Eratosthenes - GeeksforGeeks
Sieve of Eratosthenes - The sieve of Eratosthenes is one of the efficient ways to find all primes smaller than given n

Stew — 03/03/2022
i have an implementation in python
but yeah having a baseline would be a good idea
chubylive — 03/03/2022
okay. either way we need to show the complexity of the algorithm
Stew — 03/03/2022
hmm but idk if petalinux can run python
chubylive — 03/03/2022
the one I shared was a O(N log(log N))
it can be added to the rootfs but is worth the trouble
this one is https://www.geeksforgeeks.org/sieve-eratosthenes-0n-time-complexity/
GeeksforGeeks
Sieve of Eratosthenes in 0(n) time complexity - GeeksforGeeks
A Computer Science portal for geeks. It contains well written, well thought and well explained computer science and programming articles, quizzes and practice/competitive programming/company interview Questions.
o(n)
Stew — 03/03/2022
ah
chubylive — 03/03/2022
and is similar to our approach
chubylive — 03/06/2022
eh. Thinking about it again I dont think we will get much info from running an algorithmic comparison. We can you python code and time it to see how much of an improvement we get
Khoa — 03/07/2022
Let’s have a quick meeting tomorrow!
chubylive — 03/08/2022
what time are you thinking 8:30 9?
Khoa — 03/08/2022
my schedule is open. please select the time that works best for you.
chubylive — 03/08/2022
kay i might have some engagment 6-8 so 8:30 9 is looking good for me but that might change so I will keep you posted .
Khoa — 03/08/2022
ok
Khoa — 03/08/2022
if Chuby is not available, let's meet tomorrow after class
Stew — 03/08/2022
ok did chuby mean 8:30 his time?
Khoa — 03/08/2022
it is 6:30 here, so it is 9:30 for Chuby
btw, i just for method 3 working
just got
Stew — 03/08/2022
oh ok right
yeah i'm ok to meet after class tomorrow
Khoa — 03/08/2022
and method 4 is close behind.
i pulled my hair out just now for about two hours, got too many programs lying around. got to organize a bit here 🙂
ok let's meet tomorrow.
chubylive — 03/08/2022
Sorry guys
we have class tomorrow?
see the notification
Khoa — 03/08/2022
yes Prof requested that everyone present for class tomorrow Wed from 4-6pm
Khoa — 03/09/2022
i made a bunch of push to git. please pull all!
Khoa — 03/09/2022
yay one more week yay 🙂
Khoa — 03/09/2022
how do you guys want to vote on this?
chubylive — 03/09/2022
more time is welcome as long as does not add more complexity
Khoa — 03/09/2022
no we are done with scope. our scope has not changed for weeks now.
chubylive — 03/09/2022
then yeah more time to generate doc and presentation material is welcome
Khoa — 03/09/2022
i think so too. how do you think Stew?
we will have a quick meeting right after class is done
chubylive — 03/09/2022
yeah
chubylive — 03/10/2022
Sorry guys. My sleep schedule has been messed up. I fell asleep towards the end of the class meeting
did you end up meeting after the class
stew can you give me the lowdown
I should be available after work today 6-7pm est
Stew — 03/10/2022
sure thing @chubylive
i feel you on sleep schedule man
chubylive — 03/10/2022
you available?
Stew — 03/10/2022
yea sorry free now chuby
Khoa — 03/14/2022
i am going to push to git, which includes the final version of files for bitstream build for both methods 1 and 2, and method 3. the final version has clock counter which can be used for performance measurement. i was able to fit in all 280 pe's for the final version for both methods 1 and 2, and method 3.
Khoa — 03/15/2022
i just pushed to git for final RTL of methods 1, 2, and 3. i also updated C files for corresponding reference drivers and models/expected output text file (updated model/expected output text file for method 3 only, due to now i am able to fit all 280 PE in for method 3 RTL).
chubylive — 03/15/2022
these are changes to both the C code and vivado project
Khoa — 03/15/2022
yeah
the final RTL all have clock counters. and in the updated drivers (the C files), there are references on how to use the clock counter.
chubylive — 03/15/2022
yeah I was gonna try running to get number for the presentation
takes quite  a while to build
I guess we are going to abandon comp 4 and focus on the presentation?
Khoa — 03/15/2022
i already stopped playing further with the methods 1, 2, and 3 RTL 🙂 so those RTL are final unless we have a need to go back and modify them
oh the method 4 is about done as well.
chubylive — 03/15/2022
kk
Khoa — 03/15/2022
yeah i will also work on the presentation and the report
i think i should let you guys look at what i just checked in and then we can have a quick meeting right after class tomorrow, or on Thursday.
chubylive — 03/15/2022
kk
Khoa — 03/15/2022
yeah i know i got carried away, i got too much fun with the RTL development man 🙂 but i know it's time to stop 🙂
chubylive — 03/15/2022
lol. I feel you. find you grove and you just fall in. I think we have a lot to condense in to the slides
gotta make pretty charts and diagrams to channel all you effort to the class
I mean professor lol
Khoa — 03/15/2022
yeah i know.
Stew — 03/15/2022
i'm free tomorrow or thursday to meet 
Khoa — 03/16/2022
do we want to have a quick meeting now? or tomorrow?
chubylive — 03/16/2022
i am awake lol
so today works
Khoa — 03/16/2022
ok. let's have it right after this.
chubylive — 03/16/2022
https://docs.google.com/presentation/d/1xsZvR0llDFflJdFvvumW96GfwH7p-_KgvDLE9Ym2DCw/edit#slide=id.p
Google Slides - create and edit presentations online, for free.
Create a new presentation and edit with others at the same time. Get stuff done with or without an internet connection. Use Slides to edit PowerPoint files. Free from Google.
chubylive — 03/16/2022
https://docs.google.com/presentation/d/1xsZvR0llDFflJdFvvumW96GfwH7p-_KgvDLE9Ym2DCw/edit?usp=sharing
Google Docs
Accelerating Algorithms via parallel processing using multiple proc...
Accelerating Algorithms via parallel processing using multiple processing elements(PEs). Group 4 Khoa, Chuby, Stewart

https://matplotlib.org/
that is a really good plotting tool.
Stew — 03/18/2022
Image
@Khoa  seeing some weird results with Computation method 1 & 2, it might just be sw related, could you help us take a look?
this is running driver.cpp
Khoa — 03/18/2022
yes. what is the weird results that you are seeing?
from the screenshot, it looks like it is the driver for method 1, not yet method 2
Stew — 03/18/2022
it's missing prime results no?
where's 5, 7 
Khoa — 03/18/2022
then that is a problem
can you send me the code? or is it the same as what is already checked in?
Stew — 03/18/2022
yeah it's already checked in
Khoa — 03/18/2022
ok
Stew — 03/18/2022
MasterProjSivofE\Computational_Methods_1_and_2\sw\Computational_Method_1\driver\driver.cpp
Khoa — 03/18/2022
when was the bitstream built? i mean did you pull the latest, both hw and sw, and build and test using the latest?
Stew — 03/18/2022
@chubylive  can u answer?
chubylive — 03/18/2022
it was built last night
one se
c
the 15th
Khoa — 03/18/2022
can you retrieve the git commit number, or commit id, for that build? i just want to make sure you did build with the latest?
chubylive — 03/18/2022
be54a27b9dffa952dfb2b7d9fd877d57d8ab15d6
Khoa — 03/18/2022
ok so it is the latest for method 1 and 2
and you use the same corresponding driver.c i suppose?
i also included the expected output (in the case all rows of all pe's are used) in all the 'model' directory
one thing we can do to save time further: the bit stream is only a few megabytes each. i don't mind doing all the builds because i did that all the time. should i start posting bin files so that should save you time? i think i should do that.
yeah build is automated but build time is still long. ok. i am trying this right now: please expect bin files in your mailbox soon. only one bin per email. the title of the email i should mention what the attached bin file is for.
chubylive — 03/18/2022
yeah using the driver.c in the appropriate folder
Khoa — 03/18/2022
please use the bin file that i just sent to see if you see better result
ok sorry. we should do everything to save time. from now on, i should provide the bin files. you can build if you prefer, and i will always check in everything in git. but if you want to save time and not have to wait for the build to complete, you can just use the bin files i provide.
chubylive — 03/18/2022
it just hangs
for but software comp 1 and 2
Khoa — 03/18/2022
you meant i just hang for the model.c
?
you meant it just hang for the model.c?
if it is not too troublesome, try restart the board. now that you have the bin files, please make sure you pull the latest and use only the latest sw. with the bin files, you can start testing right away and not have to do any build.
the fact that it hangs i think means the sw and hw are not compatible. so something is out of sync here. we just have to make sure everything is latest, to make sure the hw and sw are in sync.
if you can share screen i can get involved with the debugging too
chubylive — 03/18/2022
sure
wanna hope on the call
hi
chubylive — 03/19/2022
Compute method 1 0x3fff using 1   pe and 512 rows took   0.511000ms.
Compute method 1 0x3fff using 2   pe and 256 rows took   0.456000ms.
Compute method 1 0x3fff using 4   pe and 128 rows took   0.475000ms.
Compute method 1 0x3fff using 8   pe and  64 rows took   0.634000ms.
Compute method 1 0x3fff using 16  pe and  32 rows took   1.026000ms.
Compute method 1 0x3fff using 32  pe and  16 rows took   1.820000ms.
Compute method 1 0x3fff using 64  pe and   8 rows took   3.448000ms.
Compute method 1 0x3fff using 128 pe and   4 rows took   6.666000ms.
Compute method 1 0x3fff using 256 pe and   2 rows took  12.230000ms.
--------------------------

Compute all method 1 took 216.862000ms.
Compute method 2 0x3fff using 1   pe and 512 rows took   0.221000ms.
Compute method 2 0x3fff using 2   pe and 256 rows took   0.273000ms.
Compute method 2 0x3fff using 4   pe and 128 rows took   0.298000ms.
Compute method 2 0x3fff using 8   pe and  64 rows took   0.426000ms.
Compute method 2 0x3fff using 16  pe and  32 rows took   0.712000ms.
Compute method 2 0x3fff using 32  pe and  16 rows took   1.303000ms.
Compute method 2 0x3fff using 64  pe and   8 rows took   2.489000ms.
Compute method 2 0x3fff using 128 pe and   4 rows took   4.839000ms.
Compute method 2 0x3fff using 256 pe and   2 rows took   8.287000ms.
--------------------------

Compute method 2  all took 159.246002ms. 
﻿
/*  primeAccel.c - The simplest kernel module.

* Copyright (C) 2013 - 2016 Xilinx, Inc
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or
*   (at your option) any later version.

*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License along
*   with this program. If not, see <http://www.gnu.org/licenses/>.

*/
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/time.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>

/* Standard module information, edit as appropriate */
MODULE_LICENSE("GPL");
MODULE_AUTHOR
    ("Xilinx Inc.");
MODULE_DESCRIPTION
    ("primeAccel - loadable module template generated by petalinux-create -t modules");

#define DRIVER_NAME "primeAccel_v1.0"
#define DEVICE_NAME "/dev/primeAccel"

#define SUCCESS 0

// Start of  IP Defines
//
#define PE_BLOCK_BASE_ADDRESS_0 0x43C00000
#define PE_BLOCK_BASE_ADDRESS_1 0x43C10000
// #define PE_BLOCK_BASE_ADDRESS_2 0x43C20000

#define PE_BLOCK_HIGH_ADDRESS_0 0x43C0FFFF
#define PE_BLOCK_HIGH_ADDRESS_1 0x43C1FFFF
// #define PE_BLOCK_HIGH_ADDRESS_2 0x43C20FFFF

#define NUMBER_OF_ROWS 512
#define NUMBER_OF_PE   256
#define FIRST_PRIME    2
#define MAX_OFFSET     ((NUMBER_OF_ROWS << 5) - 1)
#define COMPUTE_CMD 0
#define CLEAR_MEM_CMD 1
#define READ_CMD 2
#define CMD_STATUS 2

//
// End of IP Defines

unsigned long * device_base_vaddress [3];
struct timeval stop_us, start_us;
unsigned int cpu_time;
static int major_num;


/* Simple example of how to receive command line parameters to your module.
   Delete if you don't need them */
unsigned myint = 0xdeadbeef;
char *mystr = "default";


module_param(myint, int, S_IRUGO);
module_param(mystr, charp, S_IRUGO);


unsigned long * pe_register_vaddress (unsigned int pe_id, unsigned int register_id);
void write_register_0 (unsigned int pe_id, unsigned int argument_1);
void write_register_1 (unsigned int pe_id, unsigned int argument_2, unsigned int argument_3);
void write_register_2 (unsigned int pe_id, unsigned int command);
unsigned int read_register (unsigned int pe_id, unsigned int register_id);
void clear_memory (unsigned int pe_id);
void clear_memory_all (void);
unsigned int read_memory_row (unsigned int pe_id, unsigned int row);
void read_memory (unsigned int pe_id);
void read_memory_all (void);
void compute (unsigned int pe_id, unsigned int step, unsigned int first_offset, unsigned int max_offset);
unsigned int compute_for_current_prime (unsigned int current_prime);
unsigned int get_next_prime (unsigned int current_prime);
void compute_all (void);


struct primeAccel_local {
        int irq;
        unsigned long mem_start;
        unsigned long mem_end;
        void __iomem *base_addr;
};

static irqreturn_t primeAccel_irq(int irq, void *lp)
{
        printk("primeAccel interrupt\n");
        return IRQ_HANDLED;
}




unsigned long  * pe_register_vaddress (unsigned int pe_id, unsigned int register_id) {
        unsigned long * vaddress = device_base_vaddress [pe_id >> 7] + ((pe_id & 127) << 2) + register_id;     
        return vaddress;
}

void write_register_0 (unsigned int pe_id, unsigned int argument_1) {
        unsigned long * vaddress = pe_register_vaddress (pe_id, 0);
        // * vaddress = argument_1;
        iowrite32(argument_1, vaddress);
}

void write_register_1 (unsigned int pe_id, unsigned int argument_2, unsigned int argument_3) {
        unsigned long * vaddress = pe_register_vaddress (pe_id, 1);
        // * vaddress = argument_2 | (argument_3 << 16);
        iowrite32(argument_2 | (argument_3 << 16), vaddress);

}

void write_register_2 (unsigned int pe_id, unsigned int command) {
        unsigned long * vaddress = pe_register_vaddress (pe_id, 2);
        // * vaddress = (command << 4);
        iowrite32((command << 4), vaddress);

}

unsigned int read_register (unsigned int pe_id, unsigned int register_id) {
        unsigned long * vaddress = pe_register_vaddress (pe_id, register_id);
        return  ioread32(vaddress);
}

void clear_memory (unsigned int pe_id) {
        write_register_2 (pe_id, CLEAR_MEM_CMD);
}

void clear_memory_all (void) {
        unsigned int pe_busy [NUMBER_OF_PE];
        unsigned int done;
        unsigned int pe_id;
        for (pe_id = 0; pe_id < NUMBER_OF_PE; pe_id ++) {
                clear_memory (pe_id);
                pe_busy [pe_id] = 1;
        }

        do {
                done = 1;

                for (pe_id = 0; pe_id < NUMBER_OF_PE; pe_id ++) {
                        if (pe_busy [pe_id]) {
                                unsigned int register_2 = read_register (pe_id, CMD_STATUS);

                                if (register_2 & 1) {
                                        done = 0;
                                } else {
                                        pe_busy [pe_id] = 0;
                                }
                        }
                }
        } while (done == 0);
}

unsigned int read_memory_row (unsigned int pe_id, unsigned int row) {
        unsigned int register_2;
        unsigned int register_3;

        write_register_0 (pe_id, row);
        write_register_2 (pe_id, READ_CMD);

        do {
                register_2 = read_register (pe_id, CMD_STATUS);
        } while (register_2 & 1);

        register_3 = read_register (pe_id, 3);

        return register_3;
}

void read_memory (unsigned int pe_id) {
        printk("read_memory *******\n");
        unsigned int row;
        unsigned int bit_position;
        for (row = 0; row < NUMBER_OF_ROWS; row ++) {
                unsigned int memory_read_data;

                memory_read_data = read_memory_row (pe_id, row);

                for (bit_position = 0; bit_position < 32; bit_position ++) {
                        if ((memory_read_data & (1 << bit_position)) == 0) {
                                unsigned int boolean_id;

                                boolean_id = ((pe_id * NUMBER_OF_ROWS + row) << 5) + bit_position;

                                if (boolean_id >= FIRST_PRIME) {
                                        printk("is prime: %u\n", boolean_id);
                                }
                        }
                }
        }
}

void read_memory_all (void) {
        printk("read_memory_all\n");
        unsigned int pe_id;
        for (pe_id = 0; pe_id < NUMBER_OF_PE; pe_id ++) {
                read_memory (pe_id);
        }
}


void compute (unsigned int pe_id, unsigned int step, unsigned int first_offset, unsigned int max_offset) {
        write_register_0 (pe_id, step);
        write_register_1 (pe_id, first_offset, max_offset);
        write_register_2 (pe_id, COMPUTE_CMD);
}

unsigned int compute_for_current_prime (unsigned int current_prime) {
        unsigned int current_prime_squared;
        unsigned int pe_id;
        current_prime_squared = current_prime * current_prime;

        if (current_prime_squared > (((NUMBER_OF_PE * NUMBER_OF_ROWS) << 5) - 1)) {
                return 0;
        } else {
                unsigned int current_boolean_id;

                unsigned int pe_busy [NUMBER_OF_PE];
                unsigned int done;

                current_boolean_id = current_prime_squared;

                for (pe_id = 0; pe_id < NUMBER_OF_PE; pe_id ++) {
                        pe_busy [pe_id] = 0;
                }

                do {
                        unsigned int pe_id;
                        unsigned int first_offset;

                        pe_id = current_boolean_id / (MAX_OFFSET + 1);
                        first_offset = current_boolean_id % (MAX_OFFSET + 1);

                        compute (pe_id, current_prime, first_offset, MAX_OFFSET);
                        pe_busy [pe_id] = 1;

                        current_boolean_id += (((MAX_OFFSET - first_offset) / current_prime) + 1) * current_prime;
                } while (current_boolean_id <= (((NUMBER_OF_PE * NUMBER_OF_ROWS) << 5) - 1));

                do {
                        done = 1;

                        for (pe_id = 0; pe_id < NUMBER_OF_PE; pe_id ++) {
                                if (pe_busy [pe_id]) {
                                        unsigned int register_2 = read_register (pe_id, CMD_STATUS);

                                        if (register_2 & 1) {
                                                done = 0;
                                        } else {
                                                pe_busy [pe_id] = 0;
                                        }
                                }
                        }
                } while (done == 0);

                return 1;
        }
}


unsigned int get_next_prime (unsigned int current_prime) {
        unsigned int memory_read_data_available;

        memory_read_data_available = 0;

        while (1) {
                unsigned int global_row;
                unsigned int bit_position;
                unsigned int memory_read_data;

                unsigned int pe_id;
                unsigned int row;

                current_prime ++;

                global_row = current_prime >> 5;
                bit_position = current_prime & 31;

                if (memory_read_data_available && ((global_row / NUMBER_OF_ROWS) == pe_id) && ((global_row % NUMBER_OF_ROWS) == row)) {
                } else {
                        memory_read_data_available = 1;
                        pe_id = global_row / NUMBER_OF_ROWS;
                        row = global_row % NUMBER_OF_ROWS;

                        memory_read_data = read_memory_row (pe_id, row);
                }

                if ((memory_read_data & (1 << bit_position)) == 0) {
                        break;
                }
        }

        return current_prime;
}

void compute_all (void) {
        unsigned int current_prime;

        current_prime = FIRST_PRIME;

        while (compute_for_current_prime (current_prime)) {
                current_prime = get_next_prime (current_prime);
        }
}


/*
* This function is called whenever a process tries to do an ioctl on our
* device file. We get two extra parameters (additional to the inode and file
* structures, which all device functions get): the number of the ioctl called
* and the parameter given to the ioctl function.
*
* If the ioctl is write or read/write (meaning output is returned to the
* calling process), the ioctl call returns the output of this function.
*
*/
static long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param)
{
        unsigned int diff = 0;
        /*
        * Switch according to the ioctl called
        */
        if (ioctl_param == CLEAR_MEM_CMD)
        {
                clear_memory_all ();
                printk("cleared memory. \n");
        }else if (ioctl_param == COMPUTE_CMD)
        {
                do_gettimeofday(&start_us);
                compute_all();
                do_gettimeofday(&stop_us);
                diff = (stop_us.tv_sec - start_us.tv_sec) + (stop_us.tv_usec - start_us.tv_usec);
                printk("compute all took: %u usec\n", diff);
        }else if (ioctl_param == READ_CMD)
        {
                printk("read mem CMD\n");
                read_memory_all  ();
        }else{  
                return -1;
                printk("Command not supported \n");
                
        }
        return 0;
}

static int device_open(struct inode *inode, struct file *file)
{
    printk("MYCHARDEV: Device open\n");
    return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
    printk("MYCHARDEV: Device close\n");
    return 0;
}


static ssize_t device_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{
    printk("MYCHARDEV: Device read\n");
    return 0;
}

static ssize_t device_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
    printk("MYCHARDEV: Device write\n");
    return 0;
}
/* Module Declarations */
/*
* This structure will hold the functions to be called
* when a process does something to the device we
* created. Since a pointer to this structure is kept in
* the devices table, it can't be local to
* init_module. NULL is for unimplemented functions.
*/
struct file_operations Fops = {
                                                                .owner = THIS_MODULE,       
                                                                .read = device_read,
                                                                .write = device_write,
                                                                .unlocked_ioctl = device_ioctl,
                                                                .open = device_open,
                                                                .release = device_release, /*close */                                                           
                                                        };


static int primeAccel_probe(struct platform_device *pdev)
{
        struct resource *r_irq; /* Interrupt resources */
        struct resource *r_mem; /* IO mem resources */
        struct device *dev = &pdev->dev;
        struct primeAccel_local *lp = NULL;

        int rc = 0;
        dev_info(dev, "Device Tree Probing\n");
        /* Get iospace for the device */
        r_mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
        if (!r_mem) {
                dev_err(dev, "invalid address\n");
                return -ENODEV;
        }
        lp = (struct primeAccel_local *) kmalloc(sizeof(struct primeAccel_local), GFP_KERNEL);
        if (!lp) {
                dev_err(dev, "Cound not allocate primeAccel device\n");
                return -ENOMEM;
        }
        dev_set_drvdata(dev, lp);
        lp->mem_start = r_mem->start;
        lp->mem_end = r_mem->end;

        if (!request_mem_region(lp->mem_start,
                                lp->mem_end - lp->mem_start + 1,
                                DRIVER_NAME)) {
                dev_err(dev, "Couldn't lock memory region at %p\n",
                        (void *)lp->mem_start);
                rc = -EBUSY;
                goto error1;
        }

        lp->base_addr = ioremap(lp->mem_start, lp->mem_end - lp->mem_start + 1);
        if (!lp->base_addr) {
                dev_err(dev, "primeAccel: Could not allocate iomem\n");
                rc = -EIO;
                goto error2;
        }

        /* Get IRQ for the device */
        r_irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
        if (!r_irq) {
                dev_info(dev, "no IRQ found\n");
                dev_info(dev, "primeAccel at 0x%08x mapped to 0x%08x\n",
                        (unsigned int __force)lp->mem_start,
                        (unsigned int __force)lp->base_addr);
                return 0;
        }
        lp->irq = r_irq->start;
        rc = request_irq(lp->irq, &primeAccel_irq, 0, DRIVER_NAME, lp);
        if (rc) {
                dev_err(dev, "testmodule: Could not allocate interrupt %d.\n",
                        lp->irq);
                goto error3;
        }

        dev_info(dev,"primeAccel at 0x%08x mapped to 0x%08x, irq=%d\n",
                (unsigned int __force)lp->mem_start,
                (unsigned int __force)lp->base_addr,
                lp->irq);
        return 0;
error3:
        free_irq(lp->irq, lp);
error2:
        release_mem_region(lp->mem_start, lp->mem_end - lp->mem_start + 1);
error1:
        kfree(lp);
        dev_set_drvdata(dev, NULL);
        return rc;
}

static int primeAccel_remove(struct platform_device *pdev)
{
        struct device *dev = &pdev->dev;
        struct primeAccel_local *lp = dev_get_drvdata(dev);
        free_irq(lp->irq, lp);
        release_mem_region(lp->mem_start, lp->mem_end - lp->mem_start + 1);
        kfree(lp);
        dev_set_drvdata(dev, NULL);
        return 0;
}

#ifdef CONFIG_OF
static struct of_device_id primeAccel_of_match[] = {
        { .compatible = "xlnx,myipInterrupt-1.0", },
        { /* end of list */ },
};
MODULE_DEVICE_TABLE(of, primeAccel_of_match);
#else
# define primeAccel_of_match
#endif


static struct platform_driver primeAccel_driver = {
        .driver = {
                .name = DRIVER_NAME,
                .owner = THIS_MODULE,
                
        },
        .probe          = primeAccel_probe,
        .remove         = primeAccel_remove,
};

static int __init primeAccel_init(void)
{
        printk("<1>Prime number sieve accelerator module.\n");
        printk("<1>Module parameters were (0x%08x) and \"%s\"\n", myint, mystr);
        /*
        * Register the character device (atleast try)
        */
        major_num = register_chrdev(0,DEVICE_NAME, &Fops);

        /*
        * Negative values signify an error
        */
        if (major_num < 0) 
        {
                printk(KERN_ALERT "%s failed with \n","Sorry, registering the character device ");
        }
        
        device_base_vaddress [0] = ioremap_nocache(PE_BLOCK_BASE_ADDRESS_0, PE_BLOCK_HIGH_ADDRESS_0 - PE_BLOCK_BASE_ADDRESS_0 + 1);
        device_base_vaddress [1] = ioremap_nocache(PE_BLOCK_BASE_ADDRESS_1, PE_BLOCK_HIGH_ADDRESS_1 - PE_BLOCK_BASE_ADDRESS_1 + 1);


        printk(KERN_INFO "%s the major device number is %d.\n","Registeration is a success", major_num);
        printk(KERN_INFO "If you want to talk to the device driver,\n");
        printk(KERN_INFO "create a device file by following command. \n \n");
        printk(KERN_INFO "mknod %s c %d 0\n\n", DEVICE_NAME, major_num);
        printk(KERN_INFO "The device file name is important, because\n");
        printk(KERN_INFO "the ioctl program assumes that's the file you'll use\n");

        return platform_driver_register(&primeAccel_driver);
}


static void __exit primeAccel_exit(void)
{
    unregister_chrdev(major_num,DEVICE_NAME);
        platform_driver_unregister(&primeAccel_driver);
        printk(KERN_ALERT "Goodbye module world.\n");
}

module_init(primeAccel_init);
module_exit(primeAccel_exit);
primeAccel.c
17 KB