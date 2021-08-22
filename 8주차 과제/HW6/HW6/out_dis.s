
out.elf:     file format elf32-littlearm


Disassembly of section .init:

0800018c <_init>:
 800018c:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
 800018e:	bf00      	nop

Disassembly of section .fini:

08000190 <_fini>:
 8000190:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
 8000192:	bf00      	nop

Disassembly of section .text.sum:

08000194 <sum>:

int sum(int num1, int num2)
{
 8000194:	b480      	push	{r7}
 8000196:	b083      	sub	sp, #12
 8000198:	af00      	add	r7, sp, #0
 800019a:	6078      	str	r0, [r7, #4]
 800019c:	6039      	str	r1, [r7, #0]
    return num1 + num2;
 800019e:	687a      	ldr	r2, [r7, #4]
 80001a0:	683b      	ldr	r3, [r7, #0]
 80001a2:	4413      	add	r3, r2
}
 80001a4:	4618      	mov	r0, r3
 80001a6:	370c      	adds	r7, #12
 80001a8:	46bd      	mov	sp, r7
 80001aa:	f85d 7b04 	ldr.w	r7, [sp], #4
 80001ae:	4770      	bx	lr

Disassembly of section .text.mul:

080001b0 <mul>:

int mul(int num1, int num2)
{
 80001b0:	b480      	push	{r7}
 80001b2:	b083      	sub	sp, #12
 80001b4:	af00      	add	r7, sp, #0
 80001b6:	6078      	str	r0, [r7, #4]
 80001b8:	6039      	str	r1, [r7, #0]
    return num1*num2;
 80001ba:	687b      	ldr	r3, [r7, #4]
 80001bc:	683a      	ldr	r2, [r7, #0]
 80001be:	fb02 f303 	mul.w	r3, r2, r3
}
 80001c2:	4618      	mov	r0, r3
 80001c4:	370c      	adds	r7, #12
 80001c6:	46bd      	mov	sp, r7
 80001c8:	f85d 7b04 	ldr.w	r7, [sp], #4
 80001cc:	4770      	bx	lr

Disassembly of section .text.main:

080001ce <main>:





int main(){
 80001ce:	b580      	push	{r7, lr}
 80001d0:	b086      	sub	sp, #24
 80001d2:	af00      	add	r7, sp, #0
    int P2;
    int P3;
    int temp1;
    int temp2;

    P1 = 1;
 80001d4:	2301      	movs	r3, #1
 80001d6:	617b      	str	r3, [r7, #20]
    P2 = 2;
 80001d8:	2302      	movs	r3, #2
 80001da:	613b      	str	r3, [r7, #16]
    P3 = 3;
 80001dc:	2303      	movs	r3, #3
 80001de:	60fb      	str	r3, [r7, #12]

    P1 ++;
 80001e0:	697b      	ldr	r3, [r7, #20]
 80001e2:	3301      	adds	r3, #1
 80001e4:	617b      	str	r3, [r7, #20]
    P1 ++;
 80001e6:	697b      	ldr	r3, [r7, #20]
 80001e8:	3301      	adds	r3, #1
 80001ea:	617b      	str	r3, [r7, #20]
    P2 ++;
 80001ec:	693b      	ldr	r3, [r7, #16]
 80001ee:	3301      	adds	r3, #1
 80001f0:	613b      	str	r3, [r7, #16]

    temp1=sum(P1,P2);
 80001f2:	6939      	ldr	r1, [r7, #16]
 80001f4:	6978      	ldr	r0, [r7, #20]
 80001f6:	f7ff ffcd 	bl	8000194 <sum>
 80001fa:	60b8      	str	r0, [r7, #8]
    temp2=mul(P1,P2);
 80001fc:	6939      	ldr	r1, [r7, #16]
 80001fe:	6978      	ldr	r0, [r7, #20]
 8000200:	f7ff ffd6 	bl	80001b0 <mul>
 8000204:	6078      	str	r0, [r7, #4]


	while(1);
 8000206:	e7fe      	b.n	8000206 <main+0x38>
